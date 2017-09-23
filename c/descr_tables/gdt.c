
#include "gdt.h"

gdt_entry_t gdt[GDT_ENTRIES];
gdt_ptr_t gdt_ptr;

extern void gdt_flush(void);

void gdt_set_gate(uint32_t num, uint16_t limit, uint32_t base, uint8_t access, uint8_t granularity) {
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;
	
	gdt[num].limit = limit;
	gdt[num].granularity = granularity;
	gdt[num].access = access;
	
}

void load_gdt(void) {
	gdt_ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
	gdt_ptr.base = (uint32_t) &gdt;
	
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0xFFFF, 0, 0b10011010, 0b11001111);
	gdt_set_gate(2, 0xFFFF, 0, 0b10010010, 0b11001111);
	gdt_set_gate(3, 0xFFFF, 0, 0b11111010, 0b11001111);
	gdt_set_gate(4, 0xFFFF, 0, 0b11110010, 0b11001111);
	
	gdt_flush();
	
}
