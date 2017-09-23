
#ifndef __AQUA__DRIVERS_ATA_ATAPI_H
	#define __AQUA__DRIVERS_ATA_ATAPI_H
	
	#include "ata.h"
	#include "../../types.h"
	#include "../../io/ports.h"
	
	#define ATA_MODE_ACTIVE 0
	#define ATA_MODE_STANDBY 1
	#define ATA_MODE_STANDBY_IMMEDIATE 2
	#define ATA_MODE_SLEEP 3
	
	void ata_mode(uint8_t mode, ata_drive_t* drive);
	
#endif
