
#include "strcat.h"

char* strcat(char* a, const char* b) {
	char* result = a;
	
    while (*a) a++;
    while (*a++ = *b++);
    
    return result;
	
}
