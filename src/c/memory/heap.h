
#ifndef __AQUA__MEMORY_HEAP
	#define __AQUA__MEMORY_HEAP
	
	#include "../types.h"
	#include "../common/print.h"
	
	#define MAX_HEAP_SPACE 0xFFFFFF
	#define MAX_FRAMES 0xFFFFF // 0x2000
	
	typedef struct {
		uint32_t num;
		uint32_t set;
		uint32_t pos;
		
	} frame_t;
	
	typedef struct {
		frame_t start;
		uint32_t len;
		
	} frame_set_t;
	
	void init_heap(void);
	
	frame_t heap_first_available_frame(void);
	frame_set_t heap_first_available_frame_set(uint32_t len);
	frame_t heap_get_frame(uint32_t id);
	
	frame_t heap_falloc(void);
	void heap_ffree(frame_t frame);
	frame_set_t heap_fsalloc(uint32_t len);
	
	void* kmalloc(uint32_t len);
	void kfree(void* ptr, uint32_t len);
	
#endif
