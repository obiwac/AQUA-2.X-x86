
#ifndef __AQUA__COMMON_REGS_H
	#define __AQUA__COMMON_REGS_H
	
	#include "../types.h"
	
	typedef struct {
		uint32_t gs, fs, es, ds;
		uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
		uint32_t num, err_code;
		uint32_t eip, cs, eflags, useresp, ss;
		
	} __attribute__((packed)) register_t;
	
	void print_regs(int eax, int ebx, int ecx, int edx);
	
#endif
