
#include "strcpy.h"

char* strcpy(char* d, const char* s) {
	char* saved = d;
	while ((*d++ = *s++) != '\0');
	
	return saved;
	
}
