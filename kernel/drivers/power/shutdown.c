
#include "shutdown.h"

void shutdown(void) {
	printf("Attempting to poweroff with ACPI ...\n");
	acpi_poweroff();
	
	printf_warn("ACPI poweroff failed. Trying APM poweroff ...\n");
	apm_poweroff();
	
	printf_warn("APM poweroff failed. Trying emulator specific poweroff ...\n");
	
	const char* str;
	for (str = "Shutdown"; *str; ++str) {
		outportb(0x8900, *str);
		
	}
	
	outportb(0xF4, 0x00);
	
	printf_warn("Emulator specific poweroff failed. Hanging ...\n");
	hang();
	
}
