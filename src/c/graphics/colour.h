
#ifndef __AQUA__GRAPHICS_COLOUR_H
	#define __AQUA__GRAPHICS_COLOUR_H
	
	#include "../types.h"
	
	typedef struct {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		
	} colour_t;
	
	static colour_t TEXT_COLOUR = {255, 255, 255, 255};
	static colour_t ERROR_COLOUR = {255, 0, 127, 255};
	static colour_t WARNING_COLOUR = {255, 127, 0, 255};
	static colour_t MINOR_COLOUR = {126, 126, 126, 255};
	
	char colour_compress_4bit(colour_t colour);
	
#endif
