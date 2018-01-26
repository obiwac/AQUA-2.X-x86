
#ifndef __AQUA__SPECS_CPU_SPEED_H
	#define __AQUA__SPECS_CPU_SPEED_H
	
	#include "../types.h"
	
	#define CPU_SPEED_REFERENCE 300 // This is ~ the time (ms) my personnal computer takes to load the loading screen \
	                                   It's used as a reference for "benchmarking" other computers and seek the optimal animation / transition speed.
	
	uint64_t cpu_speed;
	
	void set_cpu_speed(uint64_t speed);
	uint64_t get_cpu_speed(void);
	
#endif
