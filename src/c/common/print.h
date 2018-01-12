
#ifndef __AQUA__COMMON_PRINT_H
	#define __AQUA__COMMON_PRINT_H
	
	#include "../specs/video.h"
	#include "../types.h"
	
	#include "../string/itoa.h"
	#include "../string/strlen.h"
	#include "../memory/memory.h"
	
	#include "../graphics/colour.h"
	#include "../vga/text.h"
	
	#include "../drivers/serial.h"
	
	#define VGA_TEXT TRUE
	#define SERIAL_OUTPUT TRUE
	
	unsigned char print_force_serial;
	
	void print_crude(char* string);
	void printf_colour(colour_t colour, const char* format, char** arg);
	void printf(char* format, ...);
	void printf_minor(char* format, ...);
	void printf_error(char* format, ...);
	void printf_warn(char* format, ...);
	
#endif
