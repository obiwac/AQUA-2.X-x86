
#ifndef __AQUA__BIOS_SMBIOS_SMBIOS_STRUCTS_H
	#define __AQUA__BIOS_SMBIOS_SMBIOS_STRUCTS_H
	
	#include "../../types.h"
	
	struct smbios_bios_info_t {
		uint8_t type;
		uint8_t length;
		uint16_t handle;
		
		uint8_t vendor_name;
		uint8_t version;
		
		uint16_t starting_address;
		uint8_t build_date;
		
		uint8_t rom_size;
		uint64_t characteristics;
		
		uint8_t string1;
		uint8_t string2;
		uint8_t string3;
		
		uint8_t end;
		
	};
	
#endif
