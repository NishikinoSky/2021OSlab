#include "defs.h" 

extern main(),puts(),put_num(),ticks;
extern void clock_set_next_event(void); 

void handler_s(uint64_t cause){
     //interrupt	
	if ( cause & 0x1000000000000000 == 0x1000000000000000) {
		// supervisor timer interrupt
		uint64_t cause1 = cause & 0x7fffffffffffffff;
		if ( cause1 == 5 ) {
			//设置下一个时钟中断，打印当前的中断数目。
    		//your code
			puts("[S] Supervisor Mode Timer Interrupt ");
			put_num(ticks);
            		puts("\n");
			clock_set_next_event();
		}
	}
}
