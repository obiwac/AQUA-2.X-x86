
#ifndef __AQUA__IO_WAIT_H
	#define __AQUA__IO_WAIT_H
	
	#include "../types.h"
	
	static inline void io_wait(void) {
		asm volatile("outb %%al, $0x80" :: "a"(0));
		
	}
	
#endif
