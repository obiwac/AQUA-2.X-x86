
#ifndef __AQUA__DRIVERS_LPT_H
	#define __AQUA__DRIVERS_LPT_H
	
	#include "../types.h"
	#include "../io/ports.h"
	#include "../time/sleep.h"
	
	#define LPT1 0x378
	#define LPT2 0x278
	#define LPT3 0x3BC
	
	#define LPT_STATUS_IRQ 0b00100000
	#define LPT_STATUS_ERROR 0b00010000
	#define LPT_STATUS_SELECT_IN 0b00001000
	#define LPT_STATUS_PAPER_OUT 0b00000100
	#define LPT_STATUS_ACK 0b00000010
	#define LPT_STATUS_BUSY 0b00000001
	
	#define LPT_CONTROL_STROBE 0b10000000
	#define LPT_CONTROL_AUTO_LF 0b01000000
	#define LPT_CONTROL_PRIME 0b00100000
	#define LPT_CONTROL_SELECT 0b00010000
	#define LPT_CONTROL_IRQ_ACK 0b00001000
	#define LPT_CONTROL_BIDI 0b00000100
	
	#define LPT_RESET 0
	
	void set_lpt_port(uint16_t port);
	uint16_t get_lpt_port(void);
	
	void parallel_printer_send_byte(uint8_t byte);
	
	void parallel_write(uint8_t data);
	uint8_t parallel_read(void);
	
	void parallel_install(void);
	
#endif
