
#include "smbios.h"

struct smbios_header_t smbios_headers[11];

static void parse_table(smbios_entry_point_t* entry_point) {
	printf("SMBIOS: Parsing table ...\n");
	
	struct smbios_header_t* table = (struct smbios_header_t*) entry_point->table_addr;
	uint32_t count = 0;
	
	//~ while (count++) { /// TODO
		printf_minor("\tTable %d ...\n", count);
		printf_minor("\t\ttype = %d,\n", table->type);
		printf_minor("\t\tlength = %d,\n", table->length);
		
	//~ }
	
}

smbios_entry_point_t* smbios_get(char* entry_ptr) {
	return (smbios_entry_point_t*) entry_ptr;
	
}

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
	
	if ((uint32_t) ptr >= 0x100000) {
		printf_warn("WARNING SMBIOS was not found.\n");
		return (char*) 0;
		
	} else {
		printf_minor("\tSMBIOS found at 0x%x ...\n", ptr);
		parse_table(smbios_get(ptr));
		
		return ptr;
		
	}
	
}
