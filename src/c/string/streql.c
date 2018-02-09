
#include "streql.h"

uint8_t streql(char* a, char* b) {
	uint8_t result = 1;
	uint8_t size = kstrlen(a);
	
	if (size != kstrlen(b)) {
		result = 0;
		
	} else {
		uint8_t i;
		for (i = 0; i <= size; i++) {
			if (a[i] != b[i]) {
				result = 0;
				
			}
			
		}
		
	}
	
	return result;
	
}
