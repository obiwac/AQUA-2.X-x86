
#ifndef __AQUA__VGA_TEXT_H
	#define __AQUA__VGA_TEXT_H
	
	#include "../types.h"
	#include "../specs/standards.h"
	#include "../specs/video.h"
	#include "../io/ports.h"
	
	#define VGA_TEXT_COLUMNS 80
	#define VGA_TEXT_LINES 24
	#define VGA_TEXT_VIDEO_ADDRESS 0xB8000
	
	void vga_clear_line(uint8_t from, uint8_t to);
	void vga_update_cursor(void);
	void vga_clear_screen(void);
	
	void vga_scroll_up(uint8_t line_number);
	void vga_new_line_check(void);
	
	void vga_printch(char c, char colour);
	
	void print_char_vga_text(char _char, char colour);
	void vga_text_clear_screen(void);
	
#endif
