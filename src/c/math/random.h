
#ifndef __AQUA__MATH_RANDOM_H
	#define __AQUA__MATH_RANDOM_H
	
	#include "../types.h"
	#include "const.h"
	
	void rand_seed(int seed);
	int32_t rand_int(uint32_t min, uint32_t max);
	float rand_float(float min, float max);
	
#endif
