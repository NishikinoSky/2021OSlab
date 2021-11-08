#include "defs.h" 
#include "riscv.h"
volatile unsigned long long ticks;
static uint64_t timebase =100000; 

//使用"rdtime"汇编指令获得当前mtime中的值并返回。
uint64_t get_cycles(void) {
#if __riscv_xlen == 64
    uint64_t n;
    __asm__ __volatile__("rdtime %0" : "=r"(n));
    return n;
#else
    uint32_t lo, hi, tmp;
    __asm__ __volatile__(
        "1:\n"
        "rdtimeh %0\n"
        "rdtime %1\n"
        "rdtimeh %2\n"
        "bne %0, %2, 1b"
        : "=&r"(hi), "=&r"(lo), "=&r"(tmp));
    return ((uint64_t)hi << 32) | lo;
#endif
}


void clock_init(void) {
    //对sie寄存器中的时钟中断位设置（sie[stie]=1）以启用时钟中断。
    //设置第一个时钟中断。
    //your code
    ticks = 0;
    __asm__ volatile (
		"li t0, 0x0000000000000020\n"
		"csrs sie, t0\n"
		:
		:
	);
    ticks ++;
    trigger_time_interrupt(get_cycles());
}


void clock_set_next_event(void) { 
    //获取当前cpu cycles数并计算下一个时钟中断的发生时刻,通过trigger_time_interrupt()触发时钟中断。
    //your code
    ticks++;
    trigger_time_interrupt(get_cycles() + timebase);
}
