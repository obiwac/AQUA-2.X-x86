
#include "mouse.h"

static uint8_t buffer[3];
static uint8_t offset;
static uint8_t buttons;

int mouse_x;
int mouse_y;

uint8_t mouse_press;
uint8_t mouse_release;

static void _mouse_move_handler(char dx, char dy) {
	mouse_x += dx;
	mouse_y += dy;
	
	mouse_x = mouse_x < 0 ? 0 : mouse_x;
	mouse_y = mouse_y < 0 ? 0 : mouse_y;
	
	mouse_x = mouse_x >= video_width ? video_width - 1 : mouse_x;
	mouse_y = mouse_y >= video_height ? video_height - 1 : mouse_y; 
	
}

static void _mouse_press_handler(uint8_t button) {
	mouse_press = button;
	
}

static void _mouse_release_handler(uint8_t button) {
	mouse_release = button;
	
}

void (*mouse_move_handler) (char dx, char dy) = _mouse_move_handler;
void (*mouse_press_handler) (uint8_t button) = _mouse_press_handler;
void (*mouse_release_handler) (uint8_t button) = _mouse_release_handler;

uint8_t get_mouse_press(void) {
	uint8_t temp = mouse_press;
	mouse_press = 127;
	
	return temp;
	
}

uint8_t get_mouse_release(void) {
	uint8_t temp = mouse_release;
	mouse_release = 127;
	
	return temp;
	
}

void mouse_handler(register_t* regs) {
	uint8_t status = inportb(0x64);
	
	if (status & 0x20) {
		buffer[offset] = inportb(0x60);
		offset = (offset + 1) % 3;
		
		if (!offset) {
			mouse_move_handler((char) buffer[1], -((char) buffer[2]));
			
			uint8_t i;
			for (i = 0; i < 3; i++) {
				if ((buffer[0] & (1 << i)) != (buttons & (1 << i))) {
					if (buttons & (1 << i)) mouse_release_handler(i + 1);
					else mouse_press_handler(i + 1);
					
				}
				
			}
			
			buttons = buffer[0];
			
		}
		
	}
	
}

void mouse_install(void) {
	offset = 0;
	buttons = 0;
	
	mouse_x = video_width / 2;
	mouse_y = video_height / 2;
	
	mouse_press = 127;
	mouse_release = 127;
	
	outportb(0x64, 0xA8);
	outportb(0x64, 0x20);
	
	uint8_t status = inportb(0x60) | 2;
	
	outportb(0x64, 0x60);
	outportb(0x60, status);
	
	outportb(0x64, 0xD4);
	outportb(0x60, 0xF4);
	inportb(0x60);
	
	irq_add_handler(12, mouse_handler);
	
}
