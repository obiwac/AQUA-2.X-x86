
#ifndef __AQUA__DRIVERS_PC_SPEAKER_H
	#define __AQUA__DRIVERS_PC_SPEAKER_H
	
	#include "../types.h"
	#include "../io/ports.h"
	
	void pc_speaker_play(uint32_t hertz);
	void pc_speaker_mute(void);
	
#endif
