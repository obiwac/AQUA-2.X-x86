
#include "generic_bda.h"

uint8_t bda_get_lpt_count(void) {
	uint8_t count = 0;
	uint16_t* port = (uint16_t*) BDA_LPT_PORTS;
	
	count += *port++ != 0;
	count += *port++ != 0;
	count += *port++ != 0;
	
	return count;
	
}

uint8_t bda_get_com_count(void) {
	uint8_t count = 0;
	uint16_t* port = (uint16_t*) BDA_COM_PORTS;
	
	count += *port++ != 0;
	count += *port++ != 0;
	count += *port++ != 0;
	count += *port++ != 0;
	
	return count;
	
}

uint16_t bda_get_lpt1_port(void) {
	return *((uint16_t*) BDA_LPT_PORTS);
	
}

uint16_t bda_get_text_mode_columns(void) {
	return *((uint16_t*) BDA_COLUMNS_IN_TEXT_MODE);
	
}

uint16_t bda_pit_ticks_since_boot(void) {
	return *((uint16_t*) BDA_PIT_TICKS_SINCE_BOOT);
	
}

uint8_t bda_get_drive_count(void) {
	return *((uint8_t*) BDA_DRIVE_COUNT);
	
}

uint8_t bda_keyboard_led(void) {
	return *((uint8_t*) BDA_KEYBOARD_LED);
	
}

char* bda_get_keyboard_buffer(void) {
	return (char*) BDA_KEYBOARD_BUFFER;
	
}
