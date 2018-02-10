
#include "text.h"

static int cursor_x = 0;
static int cursor_y = 0;

static const uint8_t screen_width = 80;
static const uint8_t screen_height = 25;
static const uint8_t screen_depth = 2;

void vga_clear_line(uint8_t from, uint8_t to) {
	volatile char* vidmem = (volatile char*) 0xb8000;
	
	uint16_t i;
	for (i = screen_width * from * screen_depth; i < (screen_width * (to + 1) * screen_depth); i++) {
		vidmem[i] = 0x0;
		
	}
	
}

void vga_update_cursor(void) {
	uint32_t temp;
	temp = cursor_y * screen_width + cursor_x;
	
	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
	
}

void vga_clear_screen(void) {
	vga_clear_line(0, screen_height - 1);
	cursor_x = 0;
	cursor_y = 0;
	vga_update_cursor();
	
}

void vga_scroll_up(uint8_t line_number) {
	volatile char* vidmem = (volatile char*) 0xB8000;
	
	uint16_t i;
	for (i = 0; i < screen_width * (screen_height - 1) * 2; i++) {
		vidmem[i] = vidmem[i + screen_width * 2 * line_number];
		
	}
	
	vga_clear_line(screen_height - 1 - line_number, screen_height - 1);
	
	if ((cursor_y - line_number) < 0) {
		cursor_x = 0;
		cursor_y = 0;
		
	} else {
		cursor_y -= line_number;
		
	}
	
	vga_update_cursor();
	
}

void vga_new_line_check(void) {
	if (cursor_y >= screen_height - 1) {
		vga_scroll_up(1);
		
	}
	
}

void vga_printch(char c, char colour) {
	volatile char* vidmem = (volatile char*) 0xB8000;
	
	switch (c) {
		case 0x08: {
			if (cursor_x > 0) {
				cursor_x--;
				vidmem[(cursor_y * screen_width + cursor_x) * screen_depth] = 0x00;
				
			}
			
			break;
			
		} case '\t': {
			cursor_x = (cursor_x + 4) & ~(4 - 1);
			break;
			
		} case '\r': {
			cursor_x = 0;
			break;
			
		} case '\n': {
			cursor_x = 0;
			cursor_y++;
			
			break;
			
		} default: {
			vidmem[(cursor_y * screen_width + cursor_x) * screen_depth] = c;
			vidmem[(cursor_y * screen_width + cursor_x) * screen_depth + 1] = colour;
			cursor_x++;
			
			break;
			
		}
		
	}
	
	if (cursor_x >= screen_width) {
		cursor_x = 0;
		cursor_y++;
		
	}
	
	vga_new_line_check();
	vga_update_cursor();
	
}

char vga_log[1000] = "\0";
static unsigned int log_index = 0;

void print_char_vga_text(char _char, char colour) {
	vga_printch(_char, colour);
	
	if (log_index < 1000) {
		if (_char == '\t') {
			int i;
			for (i = 0; i < 4; i++) {
				vga_log[log_index++] = ' ';
				vga_log[log_index] = '\0';
				
			}
			
		} else {
			vga_log[log_index++] = _char;
			vga_log[log_index] = '\0';
			
		}
		
	}
	
}

void vga_text_clear_screen(void) {
	vga_clear_screen();
	
}
