
#include "../specs/video.h"
#include "../drivers/irq/mouse.h"
#include "../drivers/power/acpi.h"

#include "memory.h"
#include "cursor.h"

typedef struct {
	int w;
	int h;
	int pitch;
	int max_offset; // internal
	
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
	glib_screen_surface->max_offset = glib_screen_surface->pitch * glib_screen_surface->h - video_cpc;
	
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

static unsigned char cursor_temp[MOUSE_CURSOR_LENGTH * 4];
static unsigned int cursor_temp_offsets[MOUSE_CURSOR_LENGTH];

void glib_update(void) {
	unsigned char* uc_pixels = (unsigned char*) glib_screen_surface->pixels;
	int j = 0;
	int k = 0;
	int l = 0;
	
	unsigned char cpc = 4;
	
	int i = glib_screen_surface->pitch * mouse_y;
	
	unsigned char r;
	unsigned char a;
	
	unsigned int offset;
	int base_offset = -1;
	
	short _r;
	short _g;
	short _b;
	
	mouse_x++;
	mouse_y++;
	
	int _x;
	int _y;
	
	for (_y = 0; _y < mouse_cursor_height; _y++) {
		for (_x = mouse_x; _x < mouse_cursor_width + mouse_x; _x++) {
			offset = i + _x * cpc;
			if (offset > glib_screen_surface->max_offset) break;
			
			cursor_temp_offsets[k++] = offset;
			
			cursor_temp[l++] = uc_pixels[offset];
			cursor_temp[l++] = uc_pixels[offset + 1];
			cursor_temp[l++] = uc_pixels[offset + 2];
			
			j += 4;
			
			if (_x < glib_screen_surface->w) {
				r = mouse_cursor[j - 4] & 0xFF;
				a = mouse_cursor[j - 1];
				
				_r = uc_pixels[offset] + (r - uc_pixels[offset]) * a / 0xFF;
				_g = uc_pixels[offset + 1] + (r - uc_pixels[offset + 1]) * a / 0xFF;
				_b = uc_pixels[offset + 2] + (r - uc_pixels[offset + 2]) * a / 0xFF;
				
				_r = _r > 255 ? 255 : _r;
				_g = _g > 255 ? 255 : _g;
				_b = _b > 255 ? 255 : _b;
				
				uc_pixels[offset] = (unsigned char) _r;
				uc_pixels[offset + 1] = (unsigned char) _g;
				uc_pixels[offset + 2] = (unsigned char) _b;
				
			}
			
		}
		
		i += glib_screen_surface->pitch;
		
	}
	
	mouse_x--;
	mouse_y--;
	
	unsigned char wcpc = 3;
	j = 0;
	
	int x = 0;
	int y = 0;
	
	for (i = 0; i < glib_screen_surface->pitch * glib_screen_height; i += wcpc) {
		glib_screen[i] = uc_pixels[j];
		glib_screen[i + 1] = uc_pixels[j + 1];
		glib_screen[i + 2] = uc_pixels[j + 2];
		
		j += wcpc;
		
	}
	
	l = 0;
	for (i = 0; i < MOUSE_CURSOR_LENGTH / 4; i++) {
		offset = cursor_temp_offsets[i];
		
		if (offset > glib_screen_surface->max_offset) break;
		
		uc_pixels[offset] = cursor_temp[l++];
		uc_pixels[offset + 1] = cursor_temp[l++];
		uc_pixels[offset + 2] = cursor_temp[l++];
		
	}
	
}

void glib_quit(void) {
	mfree(glib_screen_surface, glib_screen_surface->pitch * glib_screen_surface->h);
	acpi_poweroff();
	
}
