
#include "itoa.h"

void kernel_itoa(char* buffer, int base, int _int) {
	char* ptr = buffer;
	char *ptr1;
	char* ptr2;
	
	uint32_t unsigned_int = _int;
	int divisor = 10;
	
	if (base == 'd' && _int < 0) {
		*ptr++ = '-';
		buffer++;
		unsigned_int = -_int;
		
	} else if (base == 'x') {
		divisor = 16;
		
	}
	
	do {
		int remainder = unsigned_int % divisor;
		*ptr++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
		
	} while (unsigned_int /= divisor);
	
	*ptr = 0;
	ptr1 = buffer;
	ptr2 = ptr - 1;
	
	while (ptr1 < ptr2) {
		char temp = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = temp;
		
		ptr1++;
		ptr2--;
		
	}
	
}
