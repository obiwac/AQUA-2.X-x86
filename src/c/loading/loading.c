
#include "loading.h"
#include "res/aqua.h"

uint64_t show_loading(uint32_t* _video_ptr, uint32_t width, uint32_t height, uint8_t cpc) {
	uint64_t full_size = width * height * cpc;
	uint32_t colour;
	
	uint32_t x;
	uint32_t y;
	
	uint32_t min_x = width / 2 - 73;
	uint32_t max_x = width / 2 + 72;
	
	uint32_t min_y = height / 2 - 26;
	uint32_t max_y = height / 2 + 25;
	
	int k = 0;
	
	int i;
	int j;
	
	uint64_t start = pit_uptime;
	
	for (i = 0; i < 256; i += 256 / 48) {
		k = 0;
		colour = (i << 16) | (i << 8) | i;
		
		for (j = 0; j < full_size / sizeof(uint32_t); j++) {
			x = j % width;
			y = j / width;
			
			_video_ptr[j] = x > min_x && x < max_x && y > min_y && y < max_y ? loading_res_aqua[k++] : colour;
			
		}
		
	}
	
	return pit_uptime - start;
	
}
