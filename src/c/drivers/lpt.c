
#include "lpt.h"

static uint16_t lpt_port = LPT1;

void set_lpt_port(uint16_t port) {
	lpt_port = port;
	
}

uint16_t get_lpt_port(void) {
	return lpt_port;
	
}

void parallel_printer_send_byte(uint8_t data) {
	uint8_t control;
	
	while (!inportb(lpt_port + 1) & 0x80) {
		sleep_ms(10);
		
	}
	
	outportb(lpt_port, data);
	control = inportb(lpt_port + 2);
	
	outportb(lpt_port + 2, control | 1);
	sleep_ms(10);
	outportb(lpt_port + 2, control);
	
	while (!inportb(lpt_port + 1) & 0x80) {
		sleep_ms(10);
		
	}
	
}

void parallel_write(uint8_t data) {
	outportb(lpt_port + 2, LPT_RESET);
	outportb(lpt_port, data);
	
}

uint8_t parallel_read(void) {
	return inportb(lpt_port);
	
}

void parallel_install(void) {
	/// TODO LPT irq
	
}
