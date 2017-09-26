
#include "video_colour_type.h"

uint8_t get_video_type(void) {
	return (uint8_t) (detect_bios_area_hardware() & 0x30);
	
}
