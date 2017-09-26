
#include "ports.h"


/*
void outportq(uint16_t port, uint64_t data) {
	__asm__ volatile ("outq %1, %0" :: "dN" (port), "a" (data));
	
}

uint64_t inportq(uint16_t port) {
	uint64_t data;
	__asm__ volatile ("inq %1, %0" : "=a" (data) : "dN" (port));
	
	return data;

}
*/
