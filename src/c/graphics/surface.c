
#include "surface.h"

surface_t* new_surface(uint32_t width, uint32_t height, uint8_t alpha) {
	surface_t* surface;
	
	surface->width = width;
	surface->height = height;
	surface->alpha = alpha;
	
	surface->x = 0;
	surface->y = 0;
	
	return surface;
	
}

surface_layered_t* new_layered_surface(uint32_t width, uint32_t height) {
	surface_layered_t* surface;
	
	surface->width = width;
	surface->height = height;
	
	int i;
	for (i = 0; i < width * height * video_cpc; i++) {
		surface->layers[0]->data[i].r = 0xFF;
		surface->layers[0]->data[i].g = 0x00;
		surface->layers[0]->data[i].b = 0xFF;
		surface->layers[0]->data[i].a = 0x77;
		
	}
	
	surface->layer_count = 1;
	
	return surface;
	
}

surface_t* render_layered_surface(surface_layered_t* surface, uint8_t alpha) {
	surface_t* result = new_surface(surface->width, surface->height, alpha);
	
	colour_t temp = {
		.r = 0,
		.g = 0,
		.b = 0,
		.a = alpha,
		
	};
	
	int i;
	int l;
	
	for (i = 0; i < surface->width * surface->height; i++) {
		for (l = 1; l < surface->layer_count; l++) {
			if (surface->layers[l]->data[i].a) {
				temp.r += surface->layers[l]->data[i].r / surface->layer_count;
				temp.g += surface->layers[l]->data[i].g / surface->layer_count;
				temp.b += surface->layers[l]->data[i].b / surface->layer_count;
				temp.a += surface->layers[l]->data[i].a / surface->layer_count;
				
			}
			
		}
		
		result->data[i] = temp;
		
	}
	
	return result;
	
}

surface_layered_t* blit_surface(surface_layered_t* target, surface_t* surface) {
	target->layers[target->layer_count] = surface;
	target->layer_count++;
	
	return target;
	
}
