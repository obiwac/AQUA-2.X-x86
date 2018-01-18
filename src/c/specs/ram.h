
#ifndef __AQUA__SPECS_RAM_H
	#define __AQUA__SPECS_RAM_H
	
	#include "../common/sprintf.h"
	
	uint64_t ram_max;
	char ram_max_str[16];
	
	void set_ram_max(uint64_t _int);
	
#endif
