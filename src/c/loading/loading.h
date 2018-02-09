
#ifndef __AQUA__LOADING_LOADING_H
	#define __AQUA__LOADING_LOADING_H
	
	#include "../types.h"
	#include "../memory/memset.h"
	#include "../drivers/irq/pit.h"
	
	void render_loading_frame(uint32_t* _video_ptr, uint32_t width, uint32_t height, uint8_t bpp);
	
	uint64_t show_loading(uint32_t* _video_ptr, uint32_t width, uint32_t height, uint8_t bpp);
	void unloading_screen(void);
	
#endif
