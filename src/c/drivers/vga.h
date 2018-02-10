
#ifndef __AQUA__DRIVERS_VGA_H
	#define __AQUA__DRIVERS_VGA_H
	
	#include "../types.h"
	#include "../io/ports.h"
	
	#define VGA_MAX_BPP 16
	#define VGA_MAX_WIDTH 320
	#define VGA_MAX_HEIGHT 200
	
	char* vga_get_graphics_device_name(void);
	void vga_write_regs(uint8_t* regs);
	unsigned char vga_supports_mode(uint32_t width, uint32_t height, uint8_t bpp);
	
	uint8_t* vga_get_framebuffer_segment(void);
	uint8_t vga_set_mode(uint32_t width, uint32_t height, uint8_t bpp);
	void vga_put_pixel(uint32_t x, uint32_t y, uint16_t colour);
	
#endif
