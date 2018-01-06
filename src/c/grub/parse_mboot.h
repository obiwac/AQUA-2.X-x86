
#ifndef __AQUA__GRUB_PARSE_MBOOT_H
	#define __AQUA__GRUB_PARSE_MBOOT_H
	
	#include "multiboot.h"
	
	#include "../types.h"
	#include "../common/print.h"
	
	#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))
	
	void parse_mboot(uint32_t magic, uint32_t address);
	
#endif
