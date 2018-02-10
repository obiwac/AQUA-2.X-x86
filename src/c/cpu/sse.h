
#ifndef __AQUA__CPU_SSE_H
	#define __AQUA__CPU_SSE_H
	
	#include "../types.h"
	#include "../common/extern.h"
	
	char fxsave_region[512] __attribute__((aligned(16)));
	
	void sse_init(void);
	
#endif
