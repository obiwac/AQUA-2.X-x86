
#include "regs.h"

void printf_minor(char* format, ...);

void print_regs(int eax, int ebx, int ecx, int edx) {
	char str[17] = "################\0";
	
	int i;
	for (i = 0; i < 4; i++) {
		str[i] = eax >> (i * 8);
		str[i + 4] = ebx >> (i * 8);
		str[i + 8] = ecx >> (i * 8);
		str[i + 12] = edx >> (i * 8);
		
	}
	
	printf_minor("%s", str);
	
}
