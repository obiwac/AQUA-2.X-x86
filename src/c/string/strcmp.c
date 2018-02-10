
#include "strcmp.h"

int strcmp(const char* a, const char* b) {
	while (*a && (*a == *b)) {
		a++;
		b++;
		
	}
	
    return *(const uint8_t*) a - *(const uint8_t*) b;
	
}
