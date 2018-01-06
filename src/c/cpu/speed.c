
#include "speed.h"

uint32_t cpu_detect_speed_noint(void) {
	__asm__ __volatile__("cli");
	
	outportb(0x43, 0x34);
	outportb(0x40, 0);
	outportb(0x40, 0);
	
	uint32_t stsc = cpu_rdtsc();
	
	int i;
	for (i = 0x1000; i > 0; i--);
	
	uint32_t etsc = cpu_rdtsc();
	outportb(0x43, 4);
	
	uint8_t low = inportb(0x40);
	uint8_t high = inportb(0x40);
	
	__asm__ __volatile__("sti");
	return (etsc - stsc) * 1193180 / (0x10000 - (high * 256 + low));
	
}
