
#include "ata.h"

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
uint8_t ata_current_drive_set = 0;

ata_drive_t ata_setup(uint8_t master, uint16_t port_base) {
	ata_drive_t drive;
	
	drive.data_port = port_base;
	drive.error_port = port_base + 0x1;
	drive.sector_count_port = port_base + 0x2;
	
	drive.lba_low_port = port_base + 0x3;
	drive.lba_mid_port = port_base + 0x4;
	drive.lba_hi_port = port_base + 0x5;
	
	drive.device_port = port_base + 0x6;
	drive.command_port = port_base + 0x7;
	drive.control_port = port_base + 0x206;
	
	drive.master = master;
	drive.master_name = drive.master ? "master" : "slave";
	
	switch (port_base) {
		case ATA_PRIMARY: drive.name = "primary"; break;
		case ATA_SECONDARY: drive.name = "secondary"; break;
		case ATA_TERTIARY: drive.name = "tertiary"; break;
		case ATA_QUATERNARY: drive.name = "quaternary"; break;
		default: drive.name = "unknown"; break;
		
	}
	
	return drive;
	
}

uint8_t ata_identify(ata_drive_t* drive) {
	if (drive == (ata_drive_t*) 0) {
		drive = ata_current_drive;
		
	}
	
	drive->useable = 0;
	
	outportb(drive->device_port, drive->master ? 0xA0 : 0xB0);
	outportb(drive->control_port, 0);
	
	outportb(drive->device_port, 0xA0);
	uint8_t status = inportb(drive->command_port);
	
	if (status == 0xFF) {
		printf_warn("\t\tATA Device BUS does not exist.\n");
		
	} else {
		outportb(drive->device_port, drive->master ? 0xA0 : 0xB0);
		outportb(drive->sector_count_port, 0);
		
		outportb(drive->lba_low_port, 0);
		outportb(drive->lba_mid_port, 0);
		outportb(drive->lba_hi_port, 0);
		
		outportb(drive->command_port, 0xEC);
		status = inportb(drive->command_port);
		
		if (status == 0x00) {
			printf_warn("\t\tATA Device does not exist.\n");
			
		} else {
			while (((status & 0x80) == 0x80) && ((status & 1) != 1)) {
				status = inportb(drive->command_port);
				
			}
			
			if (status & 1) {
				printf_warn("\t\tATA Could not detect the device's identity (could possibly be the boot disk).\n");
				
			} else {
				printf_minor("\t\t");
				
				int i;
				for (i = 0; i < 256; i++) {
					uint16_t data = inportw(drive->data_port);
					char* text = "  \0";
					
					text[0] = data & 0xFF;
					text[1] = (data >> 8) & 0xFF;
					
					printf_minor(text);
					
				}
				
				printf("\n");
				drive->useable = 1;
				
			}
			
		}
		
	}
	
	if (drive->useable) {
		ata_current_drive = drive;
		ata_current_drive_set = 1;
		
	}
	
	return drive->useable;
	
}

char* ata_read28(ata_drive_t* drive, uint32_t sector, int count) {
	if (drive == (ata_drive_t*) 0) {
		drive = ata_current_drive;
		
	}
	
	uint8_t auto_count = count < 0;
	int data_size = auto_count ? BYTES_PER_SECTOR + 1 : count + 1;
	char* data = (char*) kmalloc(data_size);
	
	if (auto_count) {
		count = BYTES_PER_SECTOR;
		
	}
	
	if (sector & 0xF0000000) {
		printf_warn("ATA The first four bytes you are reading are not zeros.\n");
		
	} else {
		if (count > BYTES_PER_SECTOR) {
			printf_warn("ATA You are trying to read more data than a sector can hold (512 bytes).\n");
			
		} else {
			outportb(drive->device_port, (drive->master ? 0xE0 : 0xF0) | ((sector & 0xF000000) >> 24));
			outportb(drive->error_port, 0);
			outportb(drive->sector_count_port, 1);
			
			outportb(drive->lba_low_port, sector & 0xFF);
			outportb(drive->lba_mid_port, (sector & 0xFF00) >> 8);
			outportb(drive->lba_hi_port, (sector & 0xFF0000) >> 16);
			outportb(drive->command_port, 0x20);
			
			uint8_t status = inportb(drive->command_port);
			
			while (((status & 0x80) == 0x80) && ((status & 0x01) != 0x01)) {
				status = inportb(drive->command_port);
				
			}
			
			if (status & 0x01) {
				printf_warn("ATA Could not detect the device's identity.\n", 0x06);
				
			} else {
				int16_t i;
				for (i = 0; i < count; i += 2) {
					uint16_t wdata = inportw(drive->data_port);
					
					data[i] = wdata & 0xFF;
					if (auto_count && data[i] == '\0') count = i - 1;
					
					if (i + 1 < count) data[i + 1] = (wdata >> 8) & 0xFF;
					if (auto_count && data[i + 1] == '\0') count = i;
					
					printf("%c", data[i + 1]);
					
				}
				
				for (i = count + (count % 2); i < BYTES_PER_SECTOR; i += 2) {
					inportw(drive->data_port);
					
				}
				
				data[i] = '\0';
				
			}
			
		}
		
	}
	
	return data;
	
}

void ata_write28(ata_drive_t* drive, uint32_t sector, char* data, int count) {
	if (drive == (ata_drive_t*) 0) {
		drive = ata_current_drive;
		
	}
	
	if (count < 0) {
		count = kstrlen(data);
		
	}
	
	if (sector & 0xF0000000) {
		printf_warn("ATA The first four bytes you are writing are not zeros.\n");
		
	} else {
		if (count > BYTES_PER_SECTOR) {
			printf_warn("ATA You are trying to write more data than a sector can hold (512 bytes).\n");
			
		} else {
			outportb(drive->device_port, (drive->master ? 0xE0 : 0xF0) | ((sector & 0xF000000) >> 24));
			outportb(drive->error_port, 0);
			outportb(drive->sector_count_port, 1);
			
			outportb(drive->lba_low_port, sector & 0xFF);
			outportb(drive->lba_mid_port, (sector & 0xFF00) >> 8);
			outportb(drive->lba_hi_port, (sector & 0xFF0000) >> 16);
			outportb(drive->command_port, 0x30);
			
			uint16_t i;
			for (i = 0; i < count; i += 2) {
				uint16_t wdata = data[i];
				
				if (i + 1 < count) {
					wdata |= ((uint16_t) data[i + 1]) << 8;
					
				}
				
				outportw(drive->data_port, wdata);
				
			}
			
			for (i = count + (count % 2); i < BYTES_PER_SECTOR; i += 2) {
				outportw(drive->data_port, 0);
				
			}
			
		}
		
	}
	
}

void ata_flush(ata_drive_t* drive) {
	if (drive == (ata_drive_t*) 0) {
		drive = ata_current_drive;
		
	}
	
	outportb(drive->device_port, drive->master ? 0xE0 : 0xF0);
	outportb(drive->command_port, 0xE7);
	
	uint8_t status = inportb(drive->command_port);
	
	while (((status & 0x80) == 0x80) && ((status & 0x01) != 0x01)) {
		status = inportb(drive->command_port);
		
	}
	
	if (status & 1) {
		printf_warn("ATA Could not detect the device's identity.\n");
		
	}
	
}

void ata_read28_mul(char* result, ata_drive_t* drive, uint32_t sector) {
	if (drive == (ata_drive_t*) 0) {
		drive = ata_current_drive;
		
	}
	
	char* buffer;
	int i = 0;
	
	uint8_t reading = 1;
	while (reading) {
		buffer = ata_read28(drive, sector + i, BYTES_PER_SECTOR);
		buffer[3] = '\0';
		printf("\t%s\n", buffer);
		
		int j;
		for (j = i * BYTES_PER_SECTOR; j < i * BYTES_PER_SECTOR + BYTES_PER_SECTOR; j++) {
			result[j] = buffer[j % BYTES_PER_SECTOR];
			reading = !(result[j] == '\0');
			
		}
		
		i++;
		kfree(buffer, BYTES_PER_SECTOR);
		
	}
	
}

void ata_write28_mul(ata_drive_t* drive, uint32_t sector, char* data) {
	if (drive == (ata_drive_t*) 0) {
		drive = ata_current_drive;
		
	}
	
	char buffer[BYTES_PER_SECTOR];
	int buffer_count = 0;
	
	int i;
	for (i = 0; i < kstrlen(data) + 1; i++) {
		if (!(buffer_count % BYTES_PER_SECTOR) && buffer_count) {
			ata_write28(drive, sector + i / BYTES_PER_SECTOR, buffer, buffer_count);
			ata_flush(drive);
			buffer_count = 0;
			
		} else {
			buffer[buffer_count++] = data[i];
			
		}
		
	}
	
	ata_write28(drive, sector + i / BYTES_PER_SECTOR, buffer, buffer_count);
	ata_flush(drive);
	
}
