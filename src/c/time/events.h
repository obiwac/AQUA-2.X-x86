
#ifndef __AQUA__TIME_EVENTS_H
	#define __AQUA__TIME_EVENTS_H
	
	#include "../drivers/irq/pit.h"
	
	#define MAX_EVENTS 256
	
	int add_event(int ms, void (*handler) (int));
	void remove_event(int id);
	void update_events(int ms);
	
#endif
