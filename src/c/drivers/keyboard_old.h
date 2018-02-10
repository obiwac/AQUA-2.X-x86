
#ifndef KEYBOARD_DRIVER_OLD_H
	#define KEYBOARD_DRIVER_OLD_H
	
	#include "../types.h"
	#include "../common/print.h"
	#include "../io/ports.h"
	
	uint8_t poll_key(void);
	void read_str(char* buffer, char colour);
	
#endif
