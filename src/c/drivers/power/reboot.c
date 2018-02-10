
#include "reboot.h"

void reboot(void) {
	printf("Attempting to reboot machine using ACPI ...\n");
	acpi_reboot();
	
	printf_warn("ACPI reboot failed. Trying a 8042 reset ...\n");
	
	uint8_t good = 0x02;
	while (good & 0x02) {
		good = inportb(0x64);
		
	}
	
	outportb(0x64, 0xFE);
	
	printf_warn("8042 reset failed. Attempting a triple fault ...\n");
	asm volatile("int $0x80");
	
}
