
#include "regs.h"

void printf_minor(char* format, ...);

char* print_regs(int eax, int ebx, int ecx, int edx) {
	strcpy(regs_string, "################\0");
	
	int i;
	for (i = 0; i < 4; i++) {
		regs_string[i] = eax >> (i * 8);
		regs_string[i + 4] = ebx >> (i * 8);
		regs_string[i + 8] = ecx >> (i * 8);
		regs_string[i + 12] = edx >> (i * 8);
		
	}
	
	printf_minor("%s", regs_string);
	return (char*) regs_string;
	
}
