
#ifndef __AQUA__GRAPHICS_SURFACE_H
	#define __AQUA__GRAPHICS_SURFACE_H
	
	#include "../types.h"
	#include "../memory/memory.h"
	
	#include "colour.h"
	
	#define MAX_LAYERS 256
	
	typedef struct {
		uint32_t width;
		uint32_t height;
		
		colour_t* data;
		uint8_t alpha;
		
		uint32_t x;
		uint32_t y;
		
	} surface_t;
	
	typedef struct {
		uint8_t layer_count;
		surface_t* layers[MAX_LAYERS];
		
		uint32_t width;
		uint32_t height;
		
	} surface_layered_t;
	
	surface_t* new_surface(uint32_t width, uint32_t height, uint8_t alpha);
	surface_layered_t* new_layered_surface(uint32_t width, uint32_t height);
	
	surface_t* render_layered_surface(surface_layered_t* surface, uint8_t alpha);
	surface_layered_t* blit_surface(surface_layered_t* target, surface_t* surface);
	
	
	
#endif
