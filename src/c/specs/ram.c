
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

void set_ram_max(uint64_t _int) {
	_int += 0x444;
	float _float = (float) _int;
	
	float float_compressed = _float >= 0x400 ? \
		(_float / 0x400 > 0x400 ? \
		(_float / 0x400 / 0x400 > 0x400 ? \
		(_float / 0x400 / 0x400 / 0x400 > 0x400 ? \
		\
		_float / 0x400 / 0x400 / 0x400 / 0x400 : \
		_float / 0x400 / 0x400 / 0x400) : \
		_float / 0x400 / 0x400) : \
		_float / 0x400) : \
		_float;
	
	char _char = _float >= 0x400 ? \
		(_float / 0x400 > 0x400 ? \
		(_float / 0x400 / 0x400 > 0x400 ? \
		(_float / 0x400 / 0x400 / 0x400 > 0x400 ? \
		'P' : 'T') : 'G') : 'M') : 'K';
	
	ram_max = (uint64_t) _float;
	sprintf(ram_max_str, "%d.%d %cB", (uint32_t) float_compressed, (uint32_t) (float_compressed * 10) % 10, _char);
	
}
