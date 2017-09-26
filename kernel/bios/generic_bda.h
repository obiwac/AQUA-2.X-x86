
#ifndef __AQUA__BIOS_GENERIC_BDA_H
	#define __AQUA__BIOS_GENERIC_BDA_H
	
	#include "../types.h"
	
	#define BDA_COM_PORTS 0x400
	#define BDA_LPT_PORTS 0x408
	
	#define BDA_EBDA_BASE 0x40E // need to do a << 4 to get final address
	#define BDA_PACKED_BIT_FLAGS_FOR_DETECTED_HARDWARE 0x410
	
	#define BDA_KEYBOARD_STATE 0x417
	#define BDA_KEYBOARD_BUFFER 0x41E
	
	#define BDA_DISPLAY_MODE 0x449
	#define BDA_COLUMNS_IN_TEXT_MODE 0x44A
	#define BDA_VIDEO_PORT 0x463
	
	#define BDA_PIT_TICKS_SINCE_BOOT 0x46C
	#define BDA_DRIVE_COUNT 0x475
	
	#define BDA_KEYBOARD_BUFFER_START 0x480
	#define BDA_KEYBOARD_BUFFER_END 0x482
	#define BDA_KEYBOARD_LED 0x497
	
	uint8_t bda_get_lpt_count(void);
	uint8_t bda_get_com_count(void);
	
	uint16_t bda_get_lpt1_port(void);
	
	uint16_t bda_get_text_mode_columns(void);
	uint16_t bda_pit_ticks_since_boot(void);
	uint8_t bda_get_drive_count(void);
	
	uint8_t bda_keyboard_led(void);
	char* bda_get_keyboard_buffer(void);
	
#endif
