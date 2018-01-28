
#ifndef __AQUA__COMMON_EXTERN_H
	#define __AQUA__COMMON_EXTERN_H
	
	extern void hang(void);
	extern void power_reboot(void);
	
	extern void clear_interrupts(void);
	extern void enable_avx(void);
	extern void enable_sse(void);
	
#endif
