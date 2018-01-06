
#ifndef __AQUA__IO_PORTS_H
	#define __AQUA__IO_PORTS_H
	
	#include "../types.h"
	
	static inline void outportb(uint16_t port, uint8_t data) {
		__asm__ volatile("outb %1, %0" :: "dN" (port), "a" (data));
		
	}
	
	static inline uint8_t inportb(uint16_t port) {
		uint8_t data;
		__asm__ volatile("inb %1, %0" : "=a" (data) : "dN" (port));
		
		return data;

	}
	
	static inline void outportw(uint16_t port, uint16_t data) {
		__asm__ volatile("outw %1, %0" :: "dN" (port), "a" (data));
		
	}
	
	static inline uint16_t inportw(uint16_t port) {
		uint16_t data;
		__asm__ volatile("inw %1, %0" : "=a" (data) : "dN" (port));
		
		return data;

	}
	
	static inline void outportd(uint16_t port, uint32_t data) {
		//~__asm__ volatile("outd %1, %0" :: "dN" (port), "a" (data));
		
	}
	
	static inline uint32_t inportd(uint16_t port) {
		uint32_t data;
		//~__asm__ volatile("ind %1, %0" : "=a" (data) : "dN" (port));
		
		return data;

	}
	
	static inline void outportl(uint16_t port, uint32_t data) {
		__asm__ volatile("outl %1, %0" :: "dN" (port), "a" (data));
		
	}
	
	static inline uint32_t inportl(uint16_t port) {
		uint32_t data;
		__asm__ volatile("inl %1, %0" : "=a" (data) : "dN" (port));
		
		return data;

	}
	
	//void outportq(uint16_t port, uint64_t data);
	//uint64_t inportq(uint16_t port);
	
	
#endif
