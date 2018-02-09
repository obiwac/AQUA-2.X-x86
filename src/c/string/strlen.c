
#include "strlen.h"

uint32_t kstrlen(const char* string) {
	if (string[0]) {
		uint32_t i = 1;
		while (string[i++]);
		
		return --i;
		
	} else {
		return 0;
		
	}
	
}
