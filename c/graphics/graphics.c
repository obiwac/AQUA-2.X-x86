
#include "graphics.h"

static uint8_t* video_ptr;
static uint32_t* video_ptr32;

static surface_layered_t* surface;

void graphics_init(void) {
	// video_ptr = (uint8_t*) 0xe0000000;//video_addr;
	//video_ptr32 = (uint32_t*) video_addr;

	//surface = new_layered_surface(video_width, video_height);

}

void update_layers(void) {
	int i;
	for (i = 0; i < video_width * video_height * video_cpc; i += video_cpc) {
		//video_ptr[i] = temp->data[i / video_cpc].a;
		video_ptr[i + 1] = 0xFF;//temp->data[i / video_cpc].g;
		video_ptr[i + 2] = 0x00;//temp->data[i / video_cpc].b;
		video_ptr[i + 3] = 0xFF;//temp->data[i / video_cpc].r;

	}

}
