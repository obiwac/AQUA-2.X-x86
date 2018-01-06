
#include "colour.h"

char colour_compress_4bit(colour_t colour) {
	char result = 0b0000;
	
	if (colour.a >= 127) result |= 0b1000;
	if (colour.b >= 127) result |= 0b0100;
	if (colour.g >= 127) result |= 0b0010;
	if (colour.r >= 127) result |= 0b0001;
	
	return result;
	
}
