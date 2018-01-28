
#include "ram.h"

/*
	Ronsor
		obiwac that looks like spaghetti
		code isn't supposed to be edible
	
	obiwac
		Dont you touch my SPAGHET
*/ 

uint64_t ram_max;
char ram_max_str[16];

extern uint32_t kernel_start_address;

void set_ram_max(uint64_t _int) {
	_int += kernel_start_address / 0x400;
	uint32_t int32 = (uint32_t) _int;
	
	int int32_compressed = int32 >= 0x400 ? \
		(int32 / 0x400 > 0x400 ? \
		(int32 / 0x400 / 0x400 > 0x400 ? \
		(int32 / 0x400 / 0x400 / 0x400 > 0x400 ? \
		\
		int32 / 0x400 / 0x400 / 0x400 / 0x400 : \
		int32 / 0x400 / 0x400 / 0x400) : \
		int32 / 0x400 / 0x400) : \
		int32 / 0x400) : int32;
	
	char _char = int32 >= 0x400 ? \
		(int32 / 0x400 > 0x400 ? \
		(int32 / 0x400 / 0x400 > 0x400 ? \
		(int32 / 0x400 / 0x400 / 0x400 > 0x400 ? \
		'P' : 'T') : 'G') : 'M') : 'K';
	
	ram_max = (uint64_t) int32;
	sprintf(ram_max_str, "%d %cB", int32_compressed, _char);
	
}
