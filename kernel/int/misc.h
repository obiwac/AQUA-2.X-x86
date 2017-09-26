
#ifndef __AQUA__INT_MISC_H
	#define __AQUA__INT_MISC_H
	
	#include "../types.h"
	
	uint8_t ints_enabled;
	
	static inline uint8_t are_ints_enabled(void) {
		uint32_t flags;
		asm volatile("pushf\n\tpop %0" : "=g"(flags));
		ints_enabled = flags & (1 << 9);
		
		return ints_enabled;
		
	}
	
#endif
