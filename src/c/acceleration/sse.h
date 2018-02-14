
#ifndef __AQUA__ACCELERATION_SSE_H
	#define __AQUA__ACCELERATION_SSE_H
	
	#include "../types.h"
	
	extern uint8_t _detect_sse(void);
	extern void _enable_sse(void);
	
	extern void _sse_memcpy(void* dest, void* src, int64_t size);
	
	uint8_t detect_sse(void);
	void setup_sse(void);
	
	void sse_memcpy(void* _dest, void* _src, int64_t size);
	
#endif
