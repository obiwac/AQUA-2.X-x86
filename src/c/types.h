
#ifndef __AQUA__TYPES_H
	#define __AQUA__TYPES_H
	
	#define TRUE 1
	#define FALSE 0
	#define NULL ((void*) 0)
	
	typedef unsigned char uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned long uint32_t;
	typedef unsigned long long uint64_t;
	
	typedef signed char int8_t;
	typedef signed short int16_t;
	typedef signed long int32_t;
	typedef signed long long int64_t;
	
	/*typedef unsigned __int128 uint128_t;
	typedef __int128 int128_t;*/
	
	struct __attribute__((packed)) registers_t {
		uint32_t gs, fs, es, ds;
		uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
		uint32_t num, err_code;
		uint32_t eip, cs, eflags, useresp, ss;
		
	};
	
#endif
