
#include "memcpy.h"

void memcpy(void* _source, void* _dest, uint32_t size) {
	char* source = (char*) _source;
	char* dest = (char*) _dest;
	
	int i;
	for (i = 0; i < size; i++) {
		*(dest + i) = *(source + i);
		
	}
	
}
