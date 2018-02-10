
#ifndef __AQUA__SPECS_VIDEO_H
	#define __AQUA__SPECS_VIDEO_H
	
	#include "../types.h"
	
	#define BITS_PER_COMPONENT 8
	
	uint32_t video_width;
	uint32_t video_height;
	uint8_t video_bpp;
	uint8_t video_cpc;
	
	uint8_t video_type;
	uint32_t video_addr;
	
#endif
