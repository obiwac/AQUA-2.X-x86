
#include "cmos.h"

static int century_register;

uint8_t cmos_second;
uint8_t cmos_minute;
uint8_t cmos_hour;

uint8_t cmos_day;
uint8_t cmos_month;
uint32_t cmos_year;
uint8_t cmos_century;

int cmos_get_update_in_progress_flag(void) {
	outportb(CMOS_PORT_ADDRESS, 0x0A);
	return inportb(CMOS_PORT_DATA) & 0x80;
	
}

uint8_t cmos_get_rtc_register(int reg) {
	outportb(CMOS_PORT_ADDRESS, reg);
	return inportb(CMOS_PORT_DATA);
	
}

void cmos_init(void) {
	century_register = 0x00;
	
}

void cmos_read_rtc_event(int ms) {
	uint8_t century;
	
	uint8_t last_second;
	uint8_t last_minute;
	uint8_t last_hour;
	
	uint8_t last_day;
	uint8_t last_month;
	uint8_t last_year;
	
	uint8_t last_century;
	uint8_t register_b;
	
	while (cmos_get_update_in_progress_flag());
	
	cmos_second = cmos_get_rtc_register(0x00);
	cmos_minute = cmos_get_rtc_register(0x02);
	cmos_hour = cmos_get_rtc_register(0x04);
	
	cmos_day = cmos_get_rtc_register(0x07);
	cmos_month = cmos_get_rtc_register(0x08);
	cmos_year = cmos_get_rtc_register(0x09);
	
	if (century_register != 0) {
		cmos_century = cmos_get_rtc_register(century_register);
		
	}
	
	do {
		last_second = cmos_second;
		last_minute = cmos_minute;
		last_hour = cmos_hour;
		
		last_day = cmos_day;
		last_month = cmos_month;
		last_year = cmos_year;
		last_century = cmos_century;
		
		while (cmos_get_update_in_progress_flag());
		
		cmos_second = cmos_get_rtc_register(0x00);
		cmos_minute = cmos_get_rtc_register(0x02);
		cmos_hour = cmos_get_rtc_register(0x04);
		
		cmos_day = cmos_get_rtc_register(0x07);
		cmos_month = cmos_get_rtc_register(0x08);
		cmos_year = cmos_get_rtc_register(0x09);
		
		if (century_register != 0) {
			century = cmos_get_rtc_register(century_register);
			
		}
		
	} while ((last_second != cmos_second) || (last_minute != cmos_minute) || (last_hour != cmos_hour) || (last_day != cmos_day) || (last_month != cmos_month) || (last_year != cmos_year) || (last_century != cmos_century));
	
	register_b = cmos_get_rtc_register(0x0B);
	
	if (!(register_b & 0x04)) {
		cmos_second = (cmos_second & 0x0F) + ((cmos_second / 16) * 10);
		cmos_minute = (cmos_minute & 0x0F) + ((cmos_minute / 16) * 10);
		cmos_hour = ((cmos_hour & 0x0F) + (((cmos_hour & 0x70) / 16) * 10)) | (cmos_hour & 0x80);
		
		cmos_month = (cmos_month & 0x0F) + ((cmos_month / 16) * 10);
		cmos_year = (cmos_year & 0x0F) + ((cmos_year / 16) * 10);
		
		if (century_register != 0) {
			cmos_century = (cmos_century & 0x0F) + ((cmos_century / 16) * 10);
			
		}
		
	}
	
	if (!(register_b & 0x02) && (cmos_hour & 0x80)) {
		cmos_hour = ((cmos_hour & 0x7F) + 12) % 24;
		
	}
	
	if (century_register != 0) {
		cmos_year += cmos_century * 100;
		
	} else {
		cmos_year += (__AQUA__CURRENT_YEAR / 100) * 100;
		
		if (cmos_year < __AQUA__CURRENT_YEAR) {
			cmos_year += 100;
			
		}
		
	}
	
}

void cmos_read_rtc(void) {
	cmos_read_rtc_event(0);
	
}

void cmos_sleep(int seconds) {
	int iter = 0;
	
	cmos_read_rtc();
	int old_time = cmos_second;
	int new_time;
	
	while (iter < seconds) {
		cmos_read_rtc();
		new_time = cmos_second;
		
		if (new_time != old_time) {
			iter++;
			
		}
		
		old_time = new_time;
		
	}
	
}
