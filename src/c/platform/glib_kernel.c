
#include "../specs/video.h"
#include "../drivers/irq/mouse.h"

#include "memory.h"
#include "cursor.h"

typedef struct {
	int w;
	int h;
	int pitch;
	
	void* pixels;
	
} glib_surface_t;

static int glib_screen_width = 800;
static int glib_screen_height = 600;

static glib_surface_t* glib_screen_surface;
static unsigned char* glib_screen;

void glib_init(int width, int height) {
	glib_screen_width = video_width;
	glib_screen_height = video_height;
	
	glib_screen_surface->w = video_width;
	glib_screen_surface->h = video_height;
	glib_screen_surface->pitch = video_width * video_cpc;
	
	glib_screen_surface->pixels = (unsigned char*) malloc(video_width * video_height * 4);
	glib_screen = (unsigned char*) video_addr;
	
}

void glib_fill(unsigned int colour) { /// THIS IS DEPRACATED AND SHOULD NOT BE USED
	int i;
	for (i = 0; i < glib_screen_surface->pitch * glib_screen_height; i += video_cpc) {
		glib_screen[i + 2] = (colour >> 16) & 0xFF;
		glib_screen[i + 1] = (colour >> 8) & 0xFF;
		glib_screen[i] = colour & 0xFF;
		
	}
	
}

void glib_wash(unsigned int colour) {
	glib_fill(colour);
	
}

void* glib_get_pixels(void) {
	return glib_screen_surface->pixels;
	
}

unsigned int glib_get_width(void) {
	return glib_screen_surface->w;
	
}

unsigned int glib_get_height(void) {
	return glib_screen_surface->h;
	
}

int glib_get_pitch(void) {
	return glib_screen_surface->pitch;
	
}

void glib_update(void) { /// TODO avoid flickering & just fix this huge mess
	unsigned char* uc_pixels = (unsigned char*) glib_screen_surface->pixels;
	int j = 0;
	
	unsigned char wcpc = 3; // apparently i dont have to do video_cpc?
	unsigned char cpc = 4;
	
	int x = 0;
	int y = 0;
	
	//short r;
	//short g;
	//short b;
	
	//unsigned int i_min = (mouse_y * glib_screen_width + mouse_x) * wcpc;
	//unsigned int i_max = (mouse_y * glib_screen_width + mouse_x) * wcpc + 1;
	
	int i;
	for (i = 0; i < glib_screen_surface->pitch * glib_screen_height; i += wcpc) {
		glib_screen[i] = uc_pixels[j];
		glib_screen[i + 1] = uc_pixels[j + 1];
		glib_screen[i + 2] = uc_pixels[j + 2];
		
		j += wcpc;
		
	}
	
	x = mouse_x;
	int w = glib_screen_surface->pitch * mouse_y;
	int z = 0;
	
	/*unsigned char r; 
	unsigned char g;
	unsigned char b;
	
	short _r;
	short _g;
	short _b;
	*/
	int _x;
	int _y;
	
	for (_y = 0; _y < 4; _y++) {
		for (_x = x; _x < 4 + x; _x++) {
			glib_screen[w + _x * cpc] = 0xFF;
			glib_screen[w + _x * cpc + 1] = 0xFF;
			glib_screen[w + _x * cpc + 2] = 0xFF;
			
		}
		
		w += glib_screen_surface->pitch;
		
	}
	
	/*
	for (i = 0; i < 16 * 16 * 4; i += 4) {
		x = mouse_x;
		
		
		
		r = glib_screen[w + x * cpc] + (mouse_cursor[z] - glib_screen[w + x * cpc]) * mouse_cursor[z + 3] / 0xFF;
		g = glib_screen[w + x * cpc + 1] + (mouse_cursor[z + 1] - glib_screen[w + x * cpc + 1]) * mouse_cursor[z + 3] / 0xFF;
		b = glib_screen[w + x * cpc + 2] + (mouse_cursor[z + 2] - glib_screen[w + x * cpc + 2]) * mouse_cursor[z + 3] / 0xFF;
		
		if (r > 255) r = 255;
		if (g > 255) g = 255;
		if (b > 255) b = 255;
		
		z += wcpc;
		w++;
		
		glib_screen[w + x * cpc] = (unsigned char) r;
		glib_screen[w + x * cpc + 1] = (unsigned char) g;
		glib_screen[w + x * cpc + 2] = (unsigned char) b;
		
	}
	
	
	
	
	int w = glib_screen_surface->w * wcpc * mouse_y;
	int z = 0;
	
	//int i;
	for (i = 0; i < glib_screen_surface->pitch * glib_screen_height; i += wcpc) {
		y = i / glib_screen_surface->pitch;
		x = i % glib_screen_surface->pitch / wcpc;
		
		if (y >= mouse_y && y <= mouse_y + 16 && x >= mouse_x && x <= mouse_x + 16) {
			if (++x > 16) y++;
			
			x = mouse_x;
			
			r = glib_screen[w + x * cpc] + (mouse_cursor[z] - glib_screen[w + x * cpc]) * mouse_cursor[z + 3] / 0xFF;
			g = glib_screen[w + x * cpc + 1] + (mouse_cursor[z + 1] - glib_screen[w + x * cpc + 1]) * mouse_cursor[z + 3] / 0xFF;
			b = glib_screen[w + x * cpc + 2] + (mouse_cursor[z + 2] - glib_screen[w + x * cpc + 2]) * mouse_cursor[z + 3] / 0xFF;
			
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			
			z += wcpc;
			w++;
			x = mouse_x;
			
			glib_screen[i] = (unsigned char) r;
			glib_screen[i + 1] = (unsigned char) g;
			glib_screen[i + 2] = (unsigned char) b;
			
		} else {
			glib_screen[i] = uc_pixels[j];
			glib_screen[i + 1] = uc_pixels[j + 1];
			glib_screen[i + 2] = uc_pixels[j + 2];
			
		}
		
		j += 3;
		
	}*/
	
}

void glib_quit(void) {
	mfree(glib_screen_surface, glib_screen_surface->pitch * glib_screen_surface->h);
	
}
