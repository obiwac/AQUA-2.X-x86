
#include "sse.h"

char fxsave_region[512] __attribute__((aligned(16)));

void sse_init(void) {
	//~ asm volatile("fxsave;" :: "m" (fxsave_region));
	
}
