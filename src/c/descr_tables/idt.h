#ifndef __AQUA__INT_IDT_H
	#define __AQUA__INT_IDT_H
	
	#include "../types.h"
	#include "../common/print.h"
	#include "../common/system.h"
	#include "../memory/memset.h"
	
	struct idt_entry_t {
		uint16_t offset_low;
		uint16_t selector;
		
		uint8_t zero;
		uint8_t attrs;
		
		uint16_t offset_high;
		
	} __attribute__((packed));
	
	struct idt_pointer_t {
		uint16_t size;
		uint32_t offset;
		
	} __attribute__((packed));
	
	extern void idt_load(void);
	
	void set_idt_gate(uint8_t num, uint32_t loc);
	void register_idt(void);
	void set_idt_flags(uint8_t _flags);
	
	struct idt_entry_t get_entry(int num);
	
#endif
