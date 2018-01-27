
#include "loading.h"
#include "res/aqua.h"

static uint32_t* loading_video_ptr;
static uint32_t loading_width;
static uint32_t loading_height;
static uint8_t loading_cpc;

uint64_t show_loading(uint32_t* _video_ptr, uint32_t width, uint32_t height, uint8_t cpc) {	
	loading_video_ptr = _video_ptr;
	loading_width = width;
	loading_height = height;
	loading_cpc = cpc;
	
	uint32_t colour;
	
	uint32_t x;
	uint32_t y;
	
	uint32_t min_x = width / 2 - 73;
	uint32_t max_x = width / 2 + 72;
	
	uint32_t min_y = height / 2 - 26;
	uint32_t max_y = height / 2 + 25;
	
	int i;
	int j;
	
	uint64_t start = pit_uptime;
	uint64_t full_size = width * height * cpc;
	
	for (i = 0; i < 256; i += 256 / 48) {
		int k = 0;
		colour = (i << 16) | (i << 8) | i;
		
		for (j = 0; j < full_size / sizeof(uint32_t); j++) {
			x = j % width;
			y = j / width;
			
			if (x > min_x && x < max_x && y > min_y && y < max_y) {
				int lr_colour = loading_res_aqua[k++] - (256 - i);
				lr_colour = lr_colour < 0 ? 0 : lr_colour;
				_video_ptr[j] = ((lr_colour << 16) & 0xFF0000) | ((lr_colour << 8) & 0xFF00) | (lr_colour & 0xFF);
				
			} else {
				_video_ptr[j] = colour;
				
			}
			
		}
		
	}
	
	return pit_uptime - start;
	
}

void unloading_screen(void) {
	uint32_t colour;
	
	uint32_t x;
	uint32_t y;
	
	uint32_t min_x = loading_width / 2 - 73;
	uint32_t max_x = loading_width / 2 + 72;
	
	uint32_t min_y = loading_height / 2 - 26;
	uint32_t max_y = loading_height / 2 + 25;
	
	int k = 0;
	
	int i;
	int j;
	
	uint64_t full_size = loading_width * loading_height * loading_cpc;
	
	for (i = 255; i > 0; i -= 256 / 48) {
		k = 0;
		colour = (i << 16) | (i << 8) | i;
		
		for (j = 0; j < full_size / sizeof(uint32_t); j++) {
			x = j % loading_width;
			y = j / loading_width;
			
			if (x > min_x && x < max_x && y > min_y && y < max_y) {
				int lr_colour = loading_res_aqua[k++] - (256 - i);
				lr_colour = lr_colour < 0 ? 0 : lr_colour;
				loading_video_ptr[j] = ((lr_colour << 16) & 0xFF0000) | ((lr_colour << 8) & 0xFF00) | (lr_colour & 0xFF);
				
			} else {
				loading_video_ptr[j] = colour;
				
			}
			
		}
		
	}
	
}
