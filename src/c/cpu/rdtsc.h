
#ifndef __AQUA__CPU_RDTSC_H
	#define __AQUA__CPU_RDTSC_H
	
	#include "../types.h"
	
	static inline uint64_t cpu_rdtsc(void) {
		uint64_t stamp;
		asm volatile("rdtsc" : "=A"(stamp));
		
		return stamp;
		
	}
	
#endif
