
#ifndef __AQUA__INT_ISR_H
	#define __AQUA__INT_ISR_H
	
	#include "../types.h"
	#include "../common/print.h"
	#include "../descr_tables/idt.h"
	
	void isr0(void);
	void isr1(void);
	void isr2(void);
	void isr3(void);
	void isr4(void);
	void isr5(void);
	void isr6(void);
	void isr7(void);
	void isr8(void);
	void isr9(void);
	void isr10(void);
	void isr11(void);
	void isr12(void);
	void isr13(void);
	void isr14(void);
	void isr15(void);
	void isr16(void);
	void isr17(void);
	void isr18(void);
	void isr19(void);
	void isr20(void);
	void isr21(void);
	void isr22(void);
	void isr23(void);
	void isr24(void);
	void isr25(void);
	void isr26(void);
	void isr27(void);
	void isr28(void);
	void isr29(void);
	void isr30(void);
	void isr31(void);
	
	char* exception_messages[32];
	void isr_install(void);
	
#endif
