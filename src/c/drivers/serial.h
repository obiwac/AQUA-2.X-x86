
#ifndef __AQUA__DRIVERS_SERIAL_H
	#define __AQUA__DRIVERS_SERIAL_H
	
	#include "../types.h"
	#include "../io/ports.h"
	#include "../int/irq.h"
	#include "../common/regs.h"
	
	#define COM1 0x03F8
	#define COM2 0x02F8
	#define COM3 0x03E8
	#define COM4 0x02E8
	
	void set_serial_port(uint16_t port);
	uint16_t get_serial_port(void);

	void init_serial(void);
	void serial_install(void);
	
	void serial1_handler(register_t* regs);
	void serial2_handler(register_t* regs);
	
	uint8_t serial_received(void);
	uint8_t serial_is_transmit_empty(void);

	char read_serial(void);
	char* read_all_serial(void);
	
	void write_serial(char _char);
	
#endif
