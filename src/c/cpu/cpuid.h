
#ifndef __AQUA__CPU_CPUID_H
	#define __AQUA__CPU_CPUID_H
	
	#include "../types.h"
	#include "../common/print.h"
	#include "../common/regs.h"
	
	#include "../string/strcpy.h"
	#include "../string/itoa.h"
	#include "../string/strcat.h"
	
	#define CPU_UNKNOWN 0
	#define CPU_INTEL 1
	#define CPU_AMD 2
	
	#define cpuid(in, a, b, c, d) asm("cpuid" : "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));
	
	uint8_t cpuid_detect_cpu(void);
	void cpuid_do_intel(void);
	void cpuid_do_amd(void);
	
	uint8_t cpuid_detect_tsc(void);
	uint8_t cpuid_detect_sse(void);
	
	char cpu_name[64];
	char cpu_vendor[16];
	unsigned char cpu_tsc;
	unsigned char cpu_sse;
	unsigned int cpu_stepping;
	char cpu_stepping_str[4];
	
#endif
