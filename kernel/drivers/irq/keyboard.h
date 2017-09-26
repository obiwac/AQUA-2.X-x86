
#ifndef __AQUA__DRIVERS_IRQ_KEYBOARD_H
	#define __AQUA__DRIVERS_IRQ_KEYBOARD_H
	
	#include "../../types.h"
	#include "../../io/ports.h"
	#include "../../common/regs.h"
	#include "../../int/irq.h"
	
	uint8_t key_press;
	uint8_t key_release;
	
	void (*key_press_handler) (uint8_t key);
	void (*key_release_handler) (uint8_t key);
	
	uint8_t get_key_press(void);
	uint8_t get_key_release(void);
	
	void keyboard_handler(register_t* regs);
	void keyboard_install(void);
	
#endif
