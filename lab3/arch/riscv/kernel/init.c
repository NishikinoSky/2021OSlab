#include "riscv.h"

extern void clock_init(void);

void intr_enable(void) { 
    //设置sstatus[sie]=1,打开s模式的中断开关
    //your code
    __asm__ volatile (
		"li t0, 0x0000000000000002\n"
		"csrs sstatus, t0\n"
		:
		:
	);
}

void intr_disable(void) {
    //设置sstatus[sie]=0,关闭s模式的中断开关
    //your code
    __asm__ volatile (
		"li t0, 0xfffffffffffffffd\n"
		"csrc sstatus, t0\n"
		:
		:
	);
 }

void idt_init(void) {
    extern void trap_s(void);
    //向stvec寄存器中写入中断处理后跳转函数的地址
    //your code
    unsigned long long int addr = &trap_s;
    __asm__ volatile (
		"mv t0, %[addr]\n"
		"csrw stvec, t0\n"
		:
		: [addr] "r" (addr)
	);
  
}

void init(void) {
    idt_init();
    intr_enable();
    clock_init();
    task_init();
}
