
#ifndef __AQUA__DESCR_TABLES_GDT_H
	#define __AQUA__DESCR_TABLES_GDT_H
	
	#include "../types.h"
	
	#define GDT_ENTRIES 5
	
	typedef struct {
		uint16_t limit;
		uint16_t base_low;
		
		uint8_t base_middle;
		uint8_t access;
		uint8_t granularity;
		uint8_t base_high;
		
	} __attribute__((packed)) gdt_entry_t;
	
	typedef struct {
		uint16_t limit;
		uint32_t base;
		
	} __attribute__((packed)) gdt_ptr_t;
	
	typedef struct {
		uint32_t limit_low : 16;
		uint32_t base_low : 24;
		
		uint32_t accessed : 1;
		uint32_t read_write : 1;
		uint32_t conforming_expand_down : 1;
		uint32_t code : 1;
		uint32_t always_1 : 1;
		uint32_t dpl : 2;
		
		uint32_t limit_high : 4;
		uint32_t available : 1;
		uint32_t always_0 : 1;
		uint32_t big : 1;
		uint32_t granularity : 1;
		uint32_t base_high : 8;
		
	} gdt_bits_t; // __attribute__((packed)) 
	
	void gdt_set_gate(uint32_t num, uint16_t limit, uint32_t base, uint8_t access, uint8_t granularity);
	void load_gdt(void);
	
#endif
