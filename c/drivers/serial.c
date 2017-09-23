
#include "serial.h"

static uint16_t serial_port = COM1;

void set_serial_port(uint16_t port) {
	serial_port = port;
	
} uint16_t get_serial_port(void) {
	return serial_port;
	
}

void init_serial(void) {
	outportb(serial_port + 1, 0x00);
	outportb(serial_port + 3, 0x80);
	outportb(serial_port + 0, 0x03);
	outportb(serial_port + 1, 0x00);
	outportb(serial_port + 3, 0x03);
	outportb(serial_port + 2, 0xC7);
	outportb(serial_port + 4, 0x0B);
	
}

void serial1_handler(register_t* regs) {
	printf("serial1\n");
	
}

void serial2_handler(register_t* regs) {
	printf("serial2\n");
	
}

void serial_install(void) {
	irq_add_handler(4, serial1_handler);
	irq_add_handler(3, serial2_handler);
	
}

uint8_t serial_received(void) {
	return inportb(serial_port + 5) & 1;
	
}

uint8_t serial_is_transmit_empty(void) {
	return inportb(serial_port + 5) & 0x20;
	
}

char read_serial(void) {
	while (!serial_received());
	return inportb(serial_port);
	
}

char* read_all_serial(void) {
	char* buffer;
	int buffer_count = 0;
	
	buffer[buffer_count++] = read_serial();
	
	buffer[buffer_count] = '\0';
	return buffer;
	
}

void write_serial(char _char) {
	while (!serial_is_transmit_empty());
	outportb(serial_port, _char);
	
}
