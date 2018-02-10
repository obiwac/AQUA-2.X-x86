
#include "atapi.h"

void ata_mode(uint8_t mode, ata_drive_t* drive) {
	switch (mode) {
		case ATA_MODE_STANDBY: {
			outportb(drive->command_port, 0xE2);
			break;
			
		} case ATA_MODE_STANDBY_IMMEDIATE: {
			outportb(drive->command_port, 0xE0);
			break;
			
		} case ATA_MODE_SLEEP: {
			outportb(drive->command_port, 0xE6);
			break;
			
		} case ATA_MODE_ACTIVE:
		default: {
			outportb(drive->control_port, inportb(drive->control_port) | 0b100000);
			break;
			
		}
		
	}
	
}
