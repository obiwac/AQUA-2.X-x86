
#include "pc_speaker.h"

void pc_speaker_play(uint32_t hertz) {
	uint32_t div = 1193180 / hertz;
	
	outportb(0x43, 0xB6);
	outportb(0x42, (uint8_t) div);
	outportb(0x42, (uint8_t) (div >> 8));
	
	uint8_t status = inportb(0x61);
	
	if (status != (status | 3)) {
		outportb(0x61, status | 3);
		
	}
	
}

void pc_speaker_mute(void) {
	uint8_t status = inportb(0x61) & 0xFC;
	outportb(0x61, status);
	
}
