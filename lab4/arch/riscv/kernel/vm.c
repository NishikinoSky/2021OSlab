#include"vm.h"
#include"put.h"
  
extern unsigned long long text_start;
extern unsigned long long rodata_start;
extern unsigned long long data_start;
extern unsigned long long _end;

int page_count = 0;

uint64_t* change_pagelevel(uint64_t* pgtbl, uint64_t va){
    /*表示页表级数*/
    for(int i = 2; i >= 1; i --){
        uint64_t* pte_address;
        if(i == 2){
            /*把pagetable看成一个数组，VPN看成下标*/
            uint64_t vpn2 = ((uint64_t)va >> 30)&(0x1ff);
            pte_address = &pgtbl[vpn2];
            #if TEST_MODE
		    puts("VPN[2] address: ");
		    putullHex(pte_address);
        	puts("\n");
		    puts("VPN[2] value: ");
		    putullHex(*pte_address);
        	puts("\n\n");
            #endif
        }
        else if(i == 1){
            uint64_t vpn1 = ((uint64_t)va >> 21)&(0x1ff);
            pte_address = &pgtbl[vpn1];
            #if TEST_MODE
		    puts("VPN[1] address: ");
		    putullHex(pte_address);
		    puts("VPN[1] value: ");
		    putullHex(*pte_address);
        	puts("\n\n");
            #endif
        }
        /*检查pte的v位是否为1*/
        #if TEST_MODE
	    puts("PTE v-bit: ");
        puti((*pte_address) & 1);
	    puts("\n");
        #endif
	
        if((_Bool)((*pte_address) & 0x1)) {
            uint64_t ppn = (uint64_t)( (*pte_address) >>10)&(0xfffffffffff);
            pgtbl = (uint64_t*)(ppn << 12);
        }
        else{
            #if TEST_MODE
		    puts("[!] PTE Invalid.\n");
            puts("[!] Allocate Space......\n");
            #endif

            page_count ++;
            if(PAGE_SIZE * page_count <= MAP_SIZE){
            //     uint64_t ppn = (uint64_t)((uint64_t)pgtbl >> 12)&(0xfffffffffff);
            //     *pte_address = &_end + PAGE_SIZE * page_count;
            //     *pte_address = ((uint64_t)(*pte_address) & 0xffc0000000000000) | ((uint64_t)(ppn << 10)) | ((uint64_t)0) | ((uint64_t)V_ENABLE);

                pgtbl = (uint64_t)(&_end + PAGE_SIZE * page_count);
                uint64_t ppn = (uint64_t)((uint64_t)pgtbl >> 12)&(0xfffffffffff);
                *pte_address = ((uint64_t)(*pte_address) & 0xffc0000000000000) | ((uint64_t)(ppn << 10)) | ((uint64_t)0) | ((uint64_t)V_ENABLE);
             }
            else{
                puts("[!] Insufficient Space to be allocated.\n");
                return PAGE_FAULT;
            }
        }
    }
    uint64_t vpn0 = ((uint64_t)va >> 12)&(0x1ff);
    return &pgtbl[vpn0];
}

void create_mapping(uint64_t *pgtbl, uint64_t va, uint64_t pa, uint64_t sz, int perm)
{
	/*your code*/
    #if TEST_MODE
    puts("[!] Creating mapping.......\n");
    #endif

    uint64_t alimit = va + sz - 1;
    for(; va <= alimit; va = va + PAGE_SIZE, pa = pa + PAGE_SIZE){
        uint64_t* pte_address = change_pagelevel(pgtbl, va);
        if(pte_address != PAGE_FAULT){
            uint64_t ppn = (uint64_t)(pa >> 12)&(0xfffffffffff);
            *pte_address = ((uint64_t)(*pte_address) & 0xffc0000000000000) | ((uint64_t)(ppn << 10)) | ((uint64_t)perm) | ((uint64_t)V_ENABLE);            
        }
    }
}

void paging_init()
{
   uint64_t *pgtbl = &_end;
// #if TEST_MODE
//    puts("[!] initializing \n");
//    puts("[!] initializing \n");
//    puts("[!] initializing \n");
//    puts("V_addr:  \n");
//    putullHex(&text_start + offset);
//    puts("\n");
//    putullHex(&rodata_start + offset);
//    puts("\n");
//    putullHex(&data_start + offset);
//    puts("\n");
//    putullHex(&_end + offset);
//    puts("\n\n");
//    puts("P_addr:  \n");
//    putullHex(&text_start);
//    puts("\n");
//    putullHex(&rodata_start);
//    puts("\n");
//    putullHex(&data_start);
//    puts("\n");
//    putullHex(&_end);
//    puts("\n\n");
//    puts("offset:  \n");
//    putullHex(offset);
//    puts("\n\n");
// #endif
    /*your code*/
#if MAPPING_MODE
    /*3.3.2 设置映射*/
    int perm = 7;
    /*kernel起始的16mb映射到高地址*/
    create_mapping(pgtbl, (uint64_t)V_KERNEL, (uint64_t)P_KERNEL, (uint64_t)MAP_SIZE, perm);
    /*kernel起始地址的16mb做等值映射*/
    create_mapping(pgtbl,(uint64_t)P_KERNEL, (uint64_t)P_KERNEL, (uint64_t)MAP_SIZE, perm);
    /*UART等值映射*/
    create_mapping(pgtbl, (uint64_t)UART_ADDR, (uint64_t)UART_ADDR, (uint64_t)MAP_SIZE, perm);

#else
    /*3.5 对不同section的保护*/
    /*kernel高地址映射*/
    /*text section*/
    create_mapping(pgtbl, (uint64_t)(&text_start + offset), (uint64_t)(&text_start), (uint64_t)(TEXT_SIZE), R_ENABLE | X_ENABLE);
    /*rodata section*/
    create_mapping(pgtbl, (uint64_t)(&rodata_start + offset), (uint64_t)(&rodata_start), (uint64_t)(RODATA_SIZE), R_ENABLE);
    /*other sections*/
    create_mapping(pgtbl, (uint64_t)(&data_start + offset), (uint64_t)(&data_start), (uint64_t)(MAP_SIZE-TEXT_SIZE-RODATA_SIZE), R_ENABLE | W_ENABLE);

    /*kernel等值映射*/
    /*text section*/
    create_mapping(pgtbl, (uint64_t)(&text_start), (uint64_t)(&text_start), (uint64_t)(TEXT_SIZE), R_ENABLE | X_ENABLE);
    /*rodata section*/
    create_mapping(pgtbl, (uint64_t)(&rodata_start), (uint64_t)(&rodata_start), (uint64_t)(RODATA_SIZE), R_ENABLE);
    /*other sections*/
    create_mapping(pgtbl, (uint64_t)(&data_start), (uint64_t)(&data_start), (uint64_t)(MAP_SIZE-TEXT_SIZE-RODATA_SIZE), R_ENABLE | W_ENABLE);

    /*UART等值映射*/
    create_mapping(pgtbl, (uint64_t)UART_ADDR, (uint64_t)UART_ADDR, (uint64_t)PAGE_SIZE, R_ENABLE | W_ENABLE);

#endif
}
