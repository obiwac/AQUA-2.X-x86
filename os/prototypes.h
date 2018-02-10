
#ifndef __AQUA__PLATFORMS_PROTOTYPES_H
	#define __AQUA__PLATFORMS_PROTOTYPES_H
	
	#include "wrapper_defs.h"
	
	void (*glib_on_update) (void);
	void glib_init(int width, int height);
	
	void glib_fill(unsigned int colour);
	void glib_wash(unsigned int colour);
	
	void* glib_get_pixels(void);
	unsigned int glib_get_width(void);
	unsigned int glib_get_height(void);
	int glib_get_pitch(void);
	
	void glib_update(void);
	void glib_quit(void);
	
	void glib_accelerated_fade_new(char* real, char* trace);
	void glib_accelerated_fade(unsigned char alpha);
	void glib_accelerated_fade_free(void);
	
	char* log_itoa(int value, char* result, int base);
	void flogf(const char* format, ...);
	
	#if !__AQUA__INCLUDE_STDIO
		void* malloc(unsigned int size);
		
	#endif
	
	void mfree(void* ptr, unsigned int size);
	
	char clock_digital[6];
	char clock_date_words[32];
	
	void init_time(void);
	void time_wait_ms(int ms);
	
	unsigned int time_schedule(int cps, void* func);
	void time_remove(unsigned int id);
	
	unsigned char time_seconds(void);
	unsigned char time_minutes(void);
	unsigned char time_hours(void);
	
	unsigned char time_day(void);
	char* time_month_name(void);
	unsigned char time_year(void);
	
	char* time_clock_digital(void);
	char* time_clock_date_words(void);
	
	void time_update(void);
	
#endif
