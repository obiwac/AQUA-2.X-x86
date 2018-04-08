
#ifndef __AQUA__DRIVERS_ATA_H
	#define __AQUA__DRIVERS_ATA_H
	
	#include "../../types.h"
	#include "../../common/print.h"
	#include "../../io/ports.h"
	#include "../../memory/heap.h"
	
	#define BYTES_PER_SECTOR 512
	
	#define ATA_PRIMARY 0x1F0
	#define ATA_SECONDARY 0x170
	#define ATA_TERTIARY 0x1E8
	#define ATA_QUATERNARY 0x168
	
	typedef struct {
		uint8_t master;
		uint8_t useable;
		
		uint16_t data_port;
		uint16_t error_port;
		uint16_t sector_count_port;
		
		uint16_t lba_low_port;
		uint16_t lba_mid_port;
		uint16_t lba_hi_port;
		
		uint16_t device_port;
		uint16_t command_port;
		uint16_t control_port;
		
		char* name;
		char* master_name;
		
	} ata_drive_t;
	
	ata_drive_t _drive_primary_master;
	ata_drive_t _drive_primary_slave;
	ata_drive_t _drive_secondary_master;
	ata_drive_t _drive_secondary_slave;
	ata_drive_t _drive_tertiary_master;
	ata_drive_t _drive_tertiary_slave;
	ata_drive_t _drive_quaternary_master;
	ata_drive_t _drive_quaternary_slave;
	
	ata_drive_t* drive_primary_master;
	ata_drive_t* drive_primary_slave;
	ata_drive_t* drive_secondary_master;
	ata_drive_t* drive_secondary_slave;
	ata_drive_t* drive_tertiary_master;
	ata_drive_t* drive_tertiary_slave;
	ata_drive_t* drive_quaternary_master;
	ata_drive_t* drive_quaternary_slave;
	
	ata_drive_t* ata_current_drive;
	uint8_t ata_current_drive_set;
	
	ata_drive_t ata_setup(uint8_t master, uint16_t port_base);
	uint8_t ata_identify(ata_drive_t* drive);
	
	char* ata_read28(ata_drive_t* drive, uint32_t sector, int count);
	void ata_write28(ata_drive_t* drive, uint32_t sector, char* data, int count);
	
	void ata_flush(ata_drive_t* drive);
	
	void ata_read28_mul(char* data, ata_drive_t* drive, uint32_t sector);
	void ata_write28_mul(ata_drive_t* drive, uint32_t sector, char* data);
	
	char* ata_read48(ata_drive_t* drive, uint32_t sector, int count);
	void ata_write48(ata_drive_t* drive, uint32_t sector, char* data, int count);
	
	void ata_flush_ext(ata_drive_t* drive);
	
	void ata_read48_mul(char* data, ata_drive_t* drive, uint32_t sector);
	void ata_write48_mul(ata_drive_t* drive, uint32_t sector, char* data);
	
	void ata_write(ata_drive_t* drive, uint32_t sector, char* data, int count);
	char* ata_read(ata_drive_t* drive, uint32_t sector, int count);
	
#endif
