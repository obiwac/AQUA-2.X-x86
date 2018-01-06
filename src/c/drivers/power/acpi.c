
#include "acpi.h"

static uint32_t* smi_cmd;

static uint8_t is_acpi_enable;
static uint8_t is_acpi_disable;

static uint32_t* pm1a_cnt;
static uint32_t* pm1b_cnt;

static uint16_t slp_typa;
static uint16_t slp_typb;
static uint16_t slp_en;
static uint16_t sci_en;

static uint8_t pm1_cnt_len;

uint32_t* acpi_check_rsd_ptr(uint32_t* ptr) {
	char* signature = "RSD PTR ";
	struct acpi_rsd_ptr_t* rsd_ptr = (struct acpi_rsd_ptr_t*) ptr;
	
	if (memcmp(signature, rsd_ptr, 8) == 0) {
		uint8_t* b_ptr = (uint8_t*) ptr;
		uint8_t check = 0;
		
		int i;
		for (i = 0; i < sizeof(struct acpi_rsd_ptr_t); i++) {
			check += *b_ptr;
			b_ptr++;
			
		}
		
		if (!check) {
			switch (rsd_ptr->revision) {
				case 0: printf_minor("\tACPI 1\n");
				default: printf_minor("\tACPI 2\n");
				
			}
			
			return (uint32_t*) rsd_ptr->rsdt_addr;
			
		}
		
	}
	
	return NULL;
	
}

uint32_t* acpi_get_rsd_ptr(void) {
	uint32_t* addr;
	uint32_t* rsd_ptr;
	
	for (addr = (uint32_t*) 0xE0000; (int) addr < 0x100000; addr += 0x10 / sizeof(addr)) {
		rsd_ptr = acpi_check_rsd_ptr(addr);
		
		if (rsd_ptr != NULL) {
			return rsd_ptr;
			
		}
		
	}
	
	int ebda = *((short*) 0x40E);
	ebda *= 0x10;
	
	for (addr = (uint32_t*) ebda; (int) addr < ebda + 0x400; addr += 0x10 / sizeof(addr)) {
		rsd_ptr = acpi_check_rsd_ptr(addr);
		
		if (rsd_ptr != NULL) {
			return rsd_ptr;
			
		}
		
	}
	
	return NULL;
	
}

int acpi_check_header(uint32_t* ptr, char* signature) {
	if (memcmp(ptr, signature, 4) == 0) {
		char* check_ptr = (char*) ptr;
		int len = *(ptr + 1);
		char check = 0;
		
		while (0 < len--) {
			check += *check_ptr;
			check_ptr++;
			
		} if (check == 0) {
			return 0;
			
		}
		
	}
	
	return -1;
	
}

int acpi_enable(void) {
	if ((inportw((uint32_t) pm1a_cnt) & sci_en) == 0) {
		if (smi_cmd != 0 && is_acpi_enable != 0) {
			outportb((uint32_t) smi_cmd, is_acpi_enable);
			
			int i;
			for (i = 0; i < 300; i++) {
				if ((inportw((uint32_t) pm1a_cnt) & sci_en) == 1) {
					break;
					
				}
				
				sleep_ms(10);
				
			}
			
			if (pm1b_cnt != 0) {
				for (; i < 300; i++) {
					if ((inportw((uint32_t) pm1b_cnt) & sci_en) == 1) {
						break;
						
					}
					
					sleep_ms(10);
					
				}
				
			}
			
			if (i < 300) {
				printf_minor("\tACPI Enabled with success.\n");
				return 0;
				
			} else {
				printf_warn("ACPI Failed to be enabled.\n");
				return -1;
				
			}
			
		} else {
			printf_warn("ACPI No known way to enable.\n");
			return -1;
			
		}
		
	} else {
		printf_warn("ACPI Was already enabled.\n");
		return 0;
		
	}
	
}

int acpi_init(void) {
	uint32_t* ptr = acpi_get_rsd_ptr();
	
	if (ptr != NULL && acpi_check_header(ptr, "RSDT") == 0) {
		int entries = *(ptr + 1);
		
		entries -= 36;
		entries /= 4;
		ptr += 9;
		
		while (0 < entries--) {
			if (acpi_check_header((uint32_t*) *ptr, "FACP") == 0) {
				entries = -2;
				struct acpi_facp_t* facp = (struct acpi_facp_t*) *ptr;
				
				if (acpi_check_header((uint32_t*) facp->dsdt, "DSDT") == 0) {
					char* s5_addr = (char*) facp->dsdt + 36;
					int dsdt_len = *(facp->dsdt + 1) - 36;
					
					while (0 < dsdt_len--) {
						if (memcmp(s5_addr, "_S5_", 4) == 0) {
							break;
							
						}
						
						s5_addr++;
						
					}
					
					if (dsdt_len > 0) {
						if ((*(s5_addr - 1) == 8 || (*(s5_addr - 2) == 8 && *(s5_addr - 1) == '\\')) && *(s5_addr + 4) == 0x12) {
							s5_addr += 5;
							s5_addr += ((*s5_addr & 0xC0) >> 6) + 2;
							
							if (*s5_addr == 0x0A) {
								s5_addr++;
								
							}
							
							slp_typa = *(s5_addr) << 10;
							s5_addr++;
							
							if (*s5_addr == 0x0A) {
								s5_addr++;
								
							}
							
							slp_typb = *(s5_addr) << 10;
							
							smi_cmd = facp->smi_cmd;
							
							is_acpi_enable = facp->enable;
							is_acpi_disable = facp->disable;
							
							pm1a_cnt = facp->pm1a_cnt_blk;
							pm1b_cnt = facp->pm1b_cnt_blk;
							
							pm1_cnt_len = facp->pm1_cnt_len;
							
							slp_en = 0x2000;
							sci_en = 1;
							
							return 0;
							
						} else {
							printf_error("ACPI \\_S5 parse error.\n");
							
						}
						
					} else {
						printf_warn("ACPI \\_S5 not present.\n");
						
					}
					
				} else {
					printf_warn("ACPI DSDT is invalid.\n");
					
				}
				
			}
			
			ptr++;
			
		}
		
		printf_warn("ACPI No valid FACP was found.\n");
		
	} else {
		printf_warn("ACPI No ACPI was found.\n");
		
	}
	
	return -1;
	
}

void acpi_poweroff(void) {
	if (sci_en == 0) {
		return;
		
	}
	
	acpi_enable();
	outportw((uint32_t) pm1a_cnt, slp_typa | slp_en);
	
	if (pm1b_cnt != 0) {
		outportw((uint32_t) pm1b_cnt, slp_typb | slp_en);
		
	}
	
}

void acpi_reboot(void) {
	if (sci_en == 0) {
		return;
		
	}
	
	acpi_enable();
	/// TODO finish reboot
	
}
