
#ifndef __AQUA__STRING_FTOA_H
	#define __AQUA__STRING_FTOA_H
	
	#include "../types.h"
	
	#include "../memory/memset.h"
	#include "../string/strcat.h"
	#include "../string/itoa.h"
	
	void kernel_ftoa(char* buffer, uint8_t precision, float _float);
	
#endif
