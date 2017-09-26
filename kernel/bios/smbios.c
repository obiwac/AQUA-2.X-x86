
#include "smbios.h"

char* smbios_entry(void) {
	char* ptr = (uint8_t*) 0xF0000;
	uint8_t checksum;
	
	while ((uint32_t) ptr < 0x100000) {
		if (ptr[0] == '_' && ptr[1] == 'S' && ptr[2] == 'M' && ptr[3] == '_') {
			checksum = 0;
			
			int i;
			for (i = 0; i < ptr[5]; i++) {
				checksum += ptr[i];
				
			}
			
			if (checksum == 0) {
				break;
				
			}
			
		}
		
		ptr += 0xF;
		
	}
	
	if ((uint32_t) ptr == 0x100000) return (char*) 0;
	else return ptr;
	
}

smbios_entry_point_t* smbios_get(char* entry_ptr) {
	return (smbios_entry_point_t*) entry_ptr;
	
}
