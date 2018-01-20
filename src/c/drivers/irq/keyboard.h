
#ifndef __AQUA__DRIVERS_IRQ_KEYBOARD_H
	#define __AQUA__DRIVERS_IRQ_KEYBOARD_H
	
	#include "../../types.h"
	#include "../../io/ports.h"
	#include "../../common/regs.h"
	#include "../../int/irq.h"
	
	#define KEYBOARD_LED_SCROLL 0b0001
	#define KEYBOARD_LED_NUM 0b0010
	#define KEYBOARD_LED_CAPS 0b0100
	#define KEYBOARD_LED_KANA 0b1000
	
	uint8_t keyboard_detected;
	
	uint8_t key_press;
	uint8_t key_release;
	
	void (*key_press_handler) (uint8_t key);
	void (*key_release_handler) (uint8_t key);
	
	uint8_t get_key_press(void);
	uint8_t get_key_release(void);
	
	void keyboard_toggle_led(uint8_t led);
	uint8_t keyboard_echo(void);
	
	void keyboard_handler(register_t* regs);
	void keyboard_install(void);
	
#endif
