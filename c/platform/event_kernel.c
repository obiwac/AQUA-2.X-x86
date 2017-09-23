
#include "../../../platforms/defs.h"
#include "../drivers/irq/mouse.h"
#include "../drivers/irq/keyboard.h"
#include "../drivers/irq/pit.h"

void event_init(void) {
	
	
}

event_list_t event_update(void) { /// TODO
	event_list_t event_list = {
		.event_count = 0,
		
	};
	
	event_t event = {
		.type = __AQUA__EVENT_TYPE_WINDOW,
		.window_type = __AQUA__EVENT_QUIT,
		
		.button = 0,
		.released = 0,
		
		.x = 0,
		.y = 0,
		
		.timestamp = 0,
		.clicks = 0,
		
	};
	
	uint8_t mp = get_mouse_press();
	uint8_t mr = get_mouse_release();
	
	uint8_t kp = get_key_press();
	uint8_t kr = get_key_release();
	
	if (mp != 127) {
		event.type = __AQUA__EVENT_TYPE_MOUSE;
		event.button = mp;
		
	} else if (mr != 127) {
		event.type = __AQUA__EVENT_TYPE_MOUSE;
		event.button = mr;
		event.released = 1;
		
	}
	
	if (mp != 127 || mr != 127) {
		event.x = mouse_x;
		event.y = mouse_y;
		
		event.timestamp = pit_uptime;
		event.clicks = 1;
		
		event_list.events[event_list.event_count] = event;
		event_list.event_count++;
		
	}
	
	if (kp != 127) {
		event.type = __AQUA__EVENT_TYPE_KEYBOARD;
		event.button = kp;
		
	} else if (kr != 127) {
		event.type = __AQUA__EVENT_TYPE_KEYBOARD;
		event.button = kr;
		event.released = 1;
		
	}
	
	if (kp != 127 || kr != 127) {
		event.timestamp = pit_uptime;
		
		event_list.events[event_list.event_count] = event;
		event_list.event_count++;
		
	}
	
	return event_list;
	
}
