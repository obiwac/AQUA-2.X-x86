
#ifndef __AQUA__BIOS_SMBIOS_H
	#define __AQUA__BIOS_SMBIOS_H
	
	#include "../types.h"
	#include "../common/print.h"
	
	#include "smbios/smbios_structs.h"
	
	#define SMBIOS_HEADER_TYPE_BIOS_INFO 0
	#define SMBIOS_HEADER_TYPE_SYSTEM_INFO 1
	#define SMBIOS_HEADER_TYPE_MAINBOARD_INFO 2
	#define SMBIOS_HEADER_TYPE_CHASIS_INFO 3
	#define SMBIOS_HEADER_TYPE_PROCESSOR_INFO 4
	#define SMBIOS_HEADER_TYPE_CACHE_INFO 7
	#define SMBIOS_HEADER_TYPE_SYSTEM_SLOTS_INFO 9
	
	#define SMBIOS_HEADER_TYPE_PHYSICAL_MEMORY_ARRAY 16
	#define SMBIOS_HEADER_TYPE_MEMORY_DEVICE_INFO 17
	#define SMBIOS_HEADER_TYPE_MEMORY_MAPPED_DEVICE_MAPPED_ADDRESSES 19
	#define SMBIOS_HEADER_TYPE_SYSTEM_BOOT_INFO 32
	
	#define SMBIOS_HEADER_TYPE_END 127
	
	typedef struct {
		char entry_point_string[4];
		
		uint8_t checksum;
		uint8_t length;
		
		uint8_t major_version;
		uint8_t minor_version;
		
		uint16_t max_struct_size;
		uint8_t entry_point_revision;
		
		char formatted_area[5];
		char entry_point_string2[5];
		
		uint8_t checksum2;
		uint16_t table_length;
		uint32_t table_addr;
		
		uint16_t struct_count;
		uint8_t bcd_revision;
		
	} __attribute__((packed)) smbios_entry_point_t;
	
	struct smbios_header_t {
		uint8_t type;
		uint8_t length;
		uint16_t handle;
		
	};
	
	struct smbios_header_t smbios_headers[11];
	
	char* smbios_entry(void);
	smbios_entry_point_t* smbios_get(char* entry_ptr);
	
	
	
#endif
