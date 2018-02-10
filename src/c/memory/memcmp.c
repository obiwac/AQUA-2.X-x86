
#include "memcmp.h"

int memcmp(const void* buf1, const void* buf2, uint32_t size) {
	if (!size) {
		return 0;
		
	}
	
	while (--size && *(char*) buf1 == *(char*) buf2) {
		buf1 = (char*) buf1 + 1;
		buf2 = (char*) buf2 + 1;
		
	}
	
	return *((uint8_t*) buf1) - *((uint8_t*) buf2);
	
}
