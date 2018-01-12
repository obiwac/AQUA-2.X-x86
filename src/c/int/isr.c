
#include "isr.h"
#include "../common/extern.h"

void isr_install(void) {
	set_idt_gate(0, (uint32_t) isr0);
	set_idt_gate(1, (uint32_t) isr1);
	set_idt_gate(2, (uint32_t) isr2);
	set_idt_gate(3, (uint32_t) isr3);
	set_idt_gate(4, (uint32_t) isr4);
	set_idt_gate(5, (uint32_t) isr5);
	set_idt_gate(6, (uint32_t) isr6);
	set_idt_gate(7, (uint32_t) isr7);
	set_idt_gate(8, (uint32_t) isr8);
	set_idt_gate(9, (uint32_t) isr9);
	set_idt_gate(10, (uint32_t) isr10);
	set_idt_gate(11, (uint32_t) isr11);
	set_idt_gate(12, (uint32_t) isr12);
	set_idt_gate(13, (uint32_t) isr13);
	set_idt_gate(14, (uint32_t) isr14);
	set_idt_gate(15, (uint32_t) isr15);
	set_idt_gate(16, (uint32_t) isr16);
	set_idt_gate(17, (uint32_t) isr17);
	set_idt_gate(18, (uint32_t) isr18);
	set_idt_gate(19, (uint32_t) isr19);
	set_idt_gate(20, (uint32_t) isr20);
	set_idt_gate(21, (uint32_t) isr21);
	set_idt_gate(22, (uint32_t) isr22);
	set_idt_gate(23, (uint32_t) isr23);
	set_idt_gate(24, (uint32_t) isr24);
	set_idt_gate(25, (uint32_t) isr25);
	set_idt_gate(26, (uint32_t) isr26);
	set_idt_gate(27, (uint32_t) isr27);
	set_idt_gate(28, (uint32_t) isr28);
	set_idt_gate(29, (uint32_t) isr29);
	set_idt_gate(30, (uint32_t) isr30);
	set_idt_gate(31, (uint32_t) isr31);
	
	register_idt();
	
}

void isr0(void) {
	printf("%s\n", exception_messages[0]);
	hang();
	
		
}

void isr1(void) {
	printf("%s\n", exception_messages[1]);
	hang();
	
}

void isr2(void) {
	printf("%s\n", exception_messages[2]);
	hang();
	
}

void isr3(void) {
	printf("%s\n", exception_messages[3]);
	hang();
	
}

void isr4(void) {
	printf("%s\n", exception_messages[4]);
	hang();
	
}

void isr5(void) {
	printf("%s\n", exception_messages[5]);
	hang();
	
}

void isr6(void) {
	printf("%s\n", exception_messages[6]);
	hang();
	
}

void isr7(void) {
	printf("%s\n", exception_messages[7]);
	hang();
	
}

void isr8(void) {
	printf("%s\n", exception_messages[8]);
	hang();
	
}

void isr9(void) {
	printf("%s\n", exception_messages[9]);
	hang();
	
}

void isr10(void) {
	printf("%s\n", exception_messages[10]);
	hang();
	
}

void isr11(void) {
	printf("%s\n", exception_messages[11]);
	hang();
	
}

void isr12(void) {
	printf("%s\n", exception_messages[12]);
	hang();
	
}

void isr13(void) {
	printf("%s\n", exception_messages[13]);
	hang();
	
}

void isr14(void) {
	printf("%s\n", exception_messages[14]);
	hang();
	
}

void isr15(void) {
	printf("%s\n", exception_messages[15]);
	hang();
	
}

void isr16(void) {
	printf("%s\n", exception_messages[16]);
	hang();
	
}

void isr17(void) {
	printf("%s\n", exception_messages[17]);
	hang();
	
}

void isr18(void) {
	printf("%s\n", exception_messages[18]);
	hang();
	
}

void isr19(void) {
	printf("%s\n", exception_messages[19]);
	hang();
	
}

void isr20(void) {
	printf("%s\n", exception_messages[20]);
	hang();
	
}

void isr21(void) {
	printf("%s\n", exception_messages[21]);
	hang();
	
}

void isr22(void) {
	printf("%s\n", exception_messages[22]);
	hang();
	
}

void isr23(void) {
	printf("%s\n", exception_messages[23]);
	hang();
	
}

void isr24(void) {
	printf("%s\n", exception_messages[24]);
	hang();
	
}

void isr25(void) {
	printf("%s\n", exception_messages[25]);
	hang();
	
}

void isr26(void) {
	printf("%s\n", exception_messages[26]);
	hang();
	
}

void isr27(void) {
	printf("%s\n", exception_messages[27]);
	hang();
	
}

void isr28(void) {
	printf("%s\n", exception_messages[28]);
	hang();
	
}

void isr29(void) {
	printf("%s\n", exception_messages[29]);
	hang();
	
}

void isr30(void) {
	printf("%s\n", exception_messages[30]);
	hang();
	
}

void isr31(void) {
	printf("%s\n", exception_messages[31]);
	hang();
	
}

char* exception_messages[32] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	
};

