
#ifndef __AQUA__INT_IRQ_H
	#define __AQUA__INT_IRQ_H
	
	#include "../common/regs.h"
	#include "../io/ports.h"
	#include "../descr_tables/idt.h"
	
	extern void irq0(void);
	extern void irq1(void);
	extern void irq2(void);
	extern void irq3(void);
	extern void irq4(void);
	extern void irq5(void);
	extern void irq6(void);
	extern void irq7(void);
	extern void irq8(void);
	extern void irq9(void);
	extern void irq10(void);
	extern void irq11(void);
	extern void irq12(void);
	extern void irq13(void);
	extern void irq14(void);
	extern void irq15(void);
	
	void irq_init(void);
	void irq_remap(void);
	void irq_handler(register_t* regs);
	
	void irq_add_handler(int irq, void (*handler) (register_t* regs));
	void irq_remove_handler(int irq);
	
#endif
