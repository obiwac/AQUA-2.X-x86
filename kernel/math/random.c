
#include "random.h"

static uint32_t next = 0;

static int32_t rand(void) {
	next = next * 1103515245 + 12345;
	return (uint32_t) (next / 65536) % RAND_MAX;
	
}

void rand_seed(int seed) {
	next = seed;
	
}

int32_t rand_int(uint32_t min, uint32_t max) {
	max -= min - 1;
	return (int32_t) ((float) rand() / ((float) RAND_MAX / (float) max)) + min;
	
}

float rand_float(float min, float max) {
	max -= min - 1;
	return ((float) rand() / ((float) RAND_MAX / (float) max)) + min;
	
}
