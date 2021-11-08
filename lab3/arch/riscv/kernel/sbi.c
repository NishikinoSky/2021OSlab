#include "defs.h" 
#include "riscv.h"

uint64_t sbi_call(uint64_t sbi_type, uint64_t arg0, uint64_t arg1, uint64_t arg2) {
    uint64_t ret_val;
    __asm__ volatile ( 
         //Your code
    "mv a7, %[sbi_type]\n"
	"mv a0, %[arg0]\n"
	"mv a1, %[arg1]\n"
	"mv a2, %[arg2]\n"
	"ecall\n"
	"mv %[ret_val], a0\n"
	: [ret_val] "=r" (ret_val)
	: [sbi_type] "r" (sbi_type), [arg0] "r" (arg0), [arg1] "r" (arg1), [arg2] "r" (arg2)
	: "memory"
		              
   );
    return ret_val;
}


void trigger_time_interrupt(unsigned long long stime_value) {
    sbi_call(0, stime_value, 0, 0);
}
