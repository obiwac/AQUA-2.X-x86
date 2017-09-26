
#include "keyboard.h"

uint8_t key_shift;
uint8_t caps_lock;

uint8_t key_press;
uint8_t key_release;

void (*key_press_handler) (uint8_t key);
void (*key_release_handler) (uint8_t key);

uint8_t get_key_press(void) {
	uint8_t temp = key_press;
	key_press = 127;
	return temp;
	
}

uint8_t get_key_release(void) {
	uint8_t temp = key_release;
	key_release = 127;
	return temp;
	
}

void keyboard_handler(register_t* regs) {
	uint8_t scancode;
	outportb(0x20, 0x20);
	scancode = inportb(0x60);
	
	if ((scancode & 128) == 128) key_release = scancode - 128;
	else key_press = scancode;
	
	if (key_press == 42) key_shift = 1;
	if (key_release == 42) key_shift = 0;
	
	if (key_release == 58) caps_lock = !caps_lock;
	
}

void keyboard_install(void) {
	while (inportb(0x64) & 0x1) {
		inportb(0x60);
		
	}
	
	outportb(0x64, 0xAE);
	outportb(0x64, 0x20);
	
	key_shift = 0;
	caps_lock = 0;
	
	key_press = 127;
	key_release = 127;
	
	uint8_t status = (inportb(0x60) | 1) & ~0x10;
	
	outportb(0x64, 0x60);
	outportb(0x60, status);
	outportb(0x60, 0xF4);
	
	irq_add_handler(1, keyboard_handler);
	
}
