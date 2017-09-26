#ifndef __AQUA__COMMON_SYSTEM_H
	#define __AQUA__COMMON_SYSTEM_H
	
	#include "../types.h"
	
	#define KERNEL_CS 0x08
	
	#define LOW_16(address) (uint16_t) ((address) & 0xFFFF)            
	#define HIGH_16(address) (uint16_t) (((address) >> 16) & 0xFFFF)

#endif
