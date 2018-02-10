
#include "irq.h"
#include "../common/extern.h"

void* irq_routines[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
};

void irq_init(void) {
	asm("cli");
	irq_remap();
	
	set_idt_gate(32, (uint32_t) irq0);
	set_idt_gate(33, (uint32_t) irq1);
	set_idt_gate(34, (uint32_t) irq2);
	set_idt_gate(35, (uint32_t) irq3);
	set_idt_gate(36, (uint32_t) irq4);
	set_idt_gate(37, (uint32_t) irq5);
	set_idt_gate(38, (uint32_t) irq6);
	set_idt_gate(39, (uint32_t) irq7);
	set_idt_gate(40, (uint32_t) irq8);
	set_idt_gate(41, (uint32_t) irq9);
	set_idt_gate(42, (uint32_t) irq10);
	set_idt_gate(43, (uint32_t) irq11);
	set_idt_gate(44, (uint32_t) irq12);
	set_idt_gate(45, (uint32_t) irq13);
	set_idt_gate(46, (uint32_t) irq14);
	set_idt_gate(47, (uint32_t) irq15);
	
}

void irq_remap(void) {
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
	
}

void irq_handler(register_t* regs) {
	void (*handler) (register_t* regs);
	handler = irq_routines[regs->num - 32];
	
	if (handler) {
		handler(regs);
		
	} if (regs->num >= 40) {
		outportb(0xA0, 0x20);
		
	}
	
	outportb(0x20, 0x20);
	
}

void irq_add_handler(int irq, void (*handler) (register_t* r)) {
	irq_routines[irq] = handler;
	
}

void irq_remove_handler(int irq) {
	irq_routines[irq] = 0;
	
}
