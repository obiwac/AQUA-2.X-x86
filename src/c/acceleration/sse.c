
#include "sse.h"

static uint8_t has_sse;

uint8_t detect_sse(void) {
	has_sse = _detect_sse();
	return has_sse;
	
}

void setup_sse(void) {
	 _enable_sse();
	
}

void sse_memcpy(void* _dest, void* _src, int64_t size) {
	if (has_sse) {
		size = (size + 127) / 128;
		_sse_memcpy(_dest, _src, size);
		
	} else {
		size /= sizeof(uint64_t);
		
		uint64_t* dest = (uint64_t*) _dest;
		uint64_t* src = (uint64_t*) _src;
		
		while (--size) {
			dest[size] = src[size];
			
		}
		
	}
	
}
