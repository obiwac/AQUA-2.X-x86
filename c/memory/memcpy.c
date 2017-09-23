
#include "memcpy.h"

void memcpy(char* source, char* dest, uint32_t size) {
	int i;
	for (i = 0; i < size; i++) {
		*(dest + i) = *(source + i);
		
	}
	
}
