
#ifndef __AQUA__DRIVERS_IRQ_PIT_H
	#define __AQUA__DRIVERS_IRQ_PIT_H
	
	#include "../../types.h"
	#include "../../io/ports.h"
	#include "../../common/regs.h"
	#include "../../int/irq.h"
	#include "../../time/events.h"
	
	uint32_t pit_uptime;
	extern uint32_t pit_uptime;
	
	extern void cpu_sleep(uint64_t ticks);
	
	void pit_install(void);
	void pit_handler(register_t* regs);
	void pit_phase(int hertz);
	
#endif
