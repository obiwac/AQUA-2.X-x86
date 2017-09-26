
#ifndef __AQUA__CPU_CPUID_H
	#define __AQUA__CPU_CPUID_H
	
	#include "../types.h"
	#include "../common/print.h"
	#include "../common/regs.h"
	
	#define CPU_UNKNOWN 0
	#define CPU_INTEL 1
	#define CPU_AMD 2
	
	#define cpuid(in, a, b, c, d) asm("cpuid" : "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));
	
	uint8_t cpuid_detect_cpu(void);
	void cpuid_do_intel(void);
	void cpuid_do_amd(void);
	
	uint8_t cpuid_detect_tsc(void);
	uint8_t cpuid_detect_sse(void);
	
#endif
