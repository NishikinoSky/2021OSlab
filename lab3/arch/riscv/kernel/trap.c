#include "defs.h"

extern main(),puts(),put_num(),ticks,do_timer();

extern void clock_set_next_event(void); 

void handler_s(uint64_t cause, uint64_t epc )
{
	// interrupt	
	if ( cause & 0x1000000000000000 == 0x1000000000000000 ) {
		// supervisor timer interrupt
		uint64_t cause1 = cause & 0x7fffffffffffffff;
		if ( cause1 == 5 ) {	
			//run do_timer() per 10 ticks, which means 0.1s. 
            if(ticks%10==0){
            	do_timer();
            }
            clock_set_next_event();
		}
	}
	return;
}

