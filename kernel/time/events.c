
#include "events.h"

void* events[MAX_EVENTS];
static uint32_t event_ms[MAX_EVENTS];
static uint8_t event_count = 0;

int add_event(int ms, void (*handler) (int)) {
	event_ms[event_count] = ms;
	events[event_count] = handler;
	
	return event_count++;
	
}

void remove_event(int id) {
	events[id] = NULL;
	
}

void update_events(int ms) {
	void (*event) (int);
	
	int i;
	for (i = 0; i < event_count; i++) {
		if (events[i] != NULL && !(ms % event_ms[i])) {
			event = events[i];
			event(/*ms*/500);
			
		}
		
	}
	
}
