#ifndef VM_H
#define VM_H
#define uint64_t unsigned long long
#define offset (0xffffffe000000000-0x80000000)
#define TEST_MODE 0
#define PAGE_SIZE 0x1000 //4kb
#define MAX_SPACE 0xffffffff
#define PAGE_FAULT -1
#define MAP_SIZE 0x1000000 //16mb
#define P_KERNEL 0x80000000
#define V_KERNEL 0xffffffe000000000
#define TEXT_SIZE 0x2000
#define RODATA_SIZE 0x1000
#define UART_ADDR 0x10000000
#define X_ENABLE 8 //1000
#define W_ENABLE 4 //100
#define R_ENABLE 2 //10
#define V_ENABLE 1 //1
#define MAPPING_MODE 0

void create_mapping(uint64_t* pgtbl,uint64_t va,uint64_t pa,uint64_t sz,int perm);
uint64_t* change_pagelevel(uint64_t* pgtbl,uint64_t va);
extern uint64_t cur;
void paging_init();

#endif
