#include "put.h"
#include "sched.h"
#define uint64_t unsigned long long
int count = 0;
void handler_s(uint64_t cause)
{
	if (cause >> 63) {		// interrupt
		if ( ( (cause << 1) >> 1 ) == 5 ) {	// supervisor timer interrupt
			asm volatile("ecall");
			do_timer();
			count++;
		}
	}
	return;
}
