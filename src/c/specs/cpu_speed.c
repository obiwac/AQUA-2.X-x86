
#include "cpu_speed.h"

uint64_t cpu_speed;

void set_cpu_speed(uint64_t speed) {
	cpu_speed = speed;
	
}

uint64_t get_cpu_speed(void) {
	return cpu_speed;
	
}
