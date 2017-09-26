
#include "idt.h"

static uint8_t flags = 0x8E;
static struct idt_entry_t idt[256];
struct idt_pointer_t idt_ptr;

void set_idt_gate(uint8_t num, uint32_t loc) {
	idt[num].offset_low = LOW_16(loc);
	idt[num].offset_high = HIGH_16(loc);
	idt[num].selector = KERNEL_CS;
	
	idt[num].zero = 0;
	idt[num].attrs = flags;
	
}

void register_idt(void) {
	idt_ptr.size = (sizeof(struct idt_entry_t) * 256) - 1;
	idt_ptr.offset = (int) &idt;
	
	memset(&idt, 0, sizeof(struct idt_entry_t) * 256);
	idt_load();
	
}

void set_idt_flags(uint8_t _flags) {
	flags = _flags;
	
}

struct idt_entry_t get_entry(int num) {
	return idt[num];
	
}
