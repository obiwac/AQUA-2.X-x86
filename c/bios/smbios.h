
#ifndef __AQUA__BIOS_SMBIOS_H
	#define __AQUA__BIOS_SMBIOS_H
	
	#include "../types.h"
	
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
	
	char* smbios_entry(void);
	smbios_entry_point_t* smbios_get(char* entry_ptr);
	
#endif
