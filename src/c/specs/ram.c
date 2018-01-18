
#include "ram.h"

uint64_t ram_max;
char ram_max_str[16];

void set_ram_max(uint64_t _int) {
	ram_max = _int;
	sprintf(ram_max_str, "%d KB", ram_max);
	
}
