
#ifndef __AQUA__KEY_MAPS_KEY_MAP_H
	#define __AQUA__KEY_MAPS_KEY_MAP_H
	
	#include "../types.h"
	#include "../string/string.h"
	
	void set_layout(char* _layout);
	char* get_layout(void);
	
	char get_letter_from_map(char stroke, uint8_t shift);
	
#endif
