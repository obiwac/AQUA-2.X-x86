
#include "pit.h"

uint32_t pit_uptime;

void pit_install(void) {
	pit_uptime = 0;
	irq_add_handler(0, pit_handler);
	
}

void pit_handler(register_t* regs) {
	pit_uptime++;
	update_events(pit_uptime);
	
}

void pit_phase(int hertz) {
	int divisor = 1193182 / hertz;
	
	outportb(0x43, 0x36);
	outportb(0x40, divisor & 0xFF);
	outportb(0x40, (divisor >> 8) & 0xFF);
	
}
