
#ifndef __AQUA__BIOS_VIDEO_COLOUR_TYPE_H
	#define __AQUA__BIOS_VIDEO_COLOUR_TYPE_H
	
	#include "../types.h"
	#include "bios.h"
	
	#define VIDEO_TYPE_NONE 0x00
	#define VIDEO_TYPE_COLOUR 0x20
	#define VIDEO_TYPE_MONOCHROME 0x30
	
	uint8_t get_video_type(void);
	
#endif
