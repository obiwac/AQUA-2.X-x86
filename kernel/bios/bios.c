
#include "bios.h"

uint16_t detect_bios_area_hardware(void) {
	const uint16_t* ptr = (const uint16_t*) 0x410;
	return *ptr;
	
}
