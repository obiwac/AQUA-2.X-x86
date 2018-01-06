
#include "strlen.h"

uint32_t strlen(const char* string) {
	uint32_t i = 1;
	while (string[i++]);
	
	return --i;
	
}
