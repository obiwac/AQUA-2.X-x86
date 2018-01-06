
#ifndef __AQUA__DRIVERS_IRQ_MOUSE_H
	#define __AQUA__DRIVERS_IRQ_MOUSE_H
	
	#include "../../types.h"
	#include "../../io/ports.h"
	#include "../../common/regs.h"
	#include "../../int/irq.h"
	#include "../../specs/video.h"
	
	int mouse_x;
	int mouse_y;
	
	uint8_t mouse_press;
	uint8_t mouse_release;
	
	//~ void (*mouse_move_handler) (char dx, char dy);
	//~ void (*mouse_press_handler) (uint8_t button);
	//~ void (*mouse_release_handler) (uint8_t button);
	
	uint8_t get_mouse_press(void);
	uint8_t get_mouse_release(void);
	
	void mouse_handler(register_t* regs);
	void mouse_install(void);
	
#endif
