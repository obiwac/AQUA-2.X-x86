
#ifndef __AQUA__DRIVERS_CMOS_H
	#define __AQUA__DRIVERS_CMOS_H
	
	#include "../types.h"
	#include "../io/ports.h"
	
	#include "../platform/defs.h"
	
	#define CMOS_PORT_ADDRESS 0x70
	#define CMOS_PORT_DATA 0x71
	
	uint8_t cmos_second;
	uint8_t cmos_minute;
	uint8_t cmos_hour;
	
	uint8_t cmos_day;
	uint8_t cmos_month;
	uint32_t cmos_year;
	uint8_t cmos_century;
	
	int cmos_get_update_in_progress_flag(void);
	uint8_t cmos_get_rtc_register(int reg);
	
	void cmos_init(void);
	void cmos_read_rtc_event(int ms);
	void cmos_read_rtc(void);
	
	void cmos_sleep(int seconds);
	
#endif
