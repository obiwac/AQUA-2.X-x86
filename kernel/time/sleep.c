
#include "sleep.h"

static uint8_t _break = 0;

void sleep_break(int ms) {
	_break = 1;
	
}

void sleep_ms(int ms) {
	int id = add_event(ms, sleep_break);
	while(!_break);
	
	_break = 0;
	remove_event(id);
	
}
