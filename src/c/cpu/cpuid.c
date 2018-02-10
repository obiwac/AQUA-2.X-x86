
#include "cpuid.h"

char cpu_name[64] = "Unknown";
char cpu_vendor[16] = "Unknown";
unsigned char cpu_tsc = 0;
unsigned char cpu_sse = 0;
unsigned int cpu_stepping = 0;
char cpu_stepping_str[4] = "0";

char* cpuid_intel[] = { /// TODO update the cpu brands
	"Brand ID Not Supported.", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Intel(R) Pentium(R) III Xeon(R) processor", 
	"Intel(R) Pentium(R) III processor", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) III processor-M", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Pentium(R) 4 processor", 
	"Intel(R) Celeron(R) processor", 
	"Intel(R) Xeon(R) Processor", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Mobile Intel(R) Pentium(R) 4 processor-M", 
	"Mobile Intel(R) Pentium(R) Celeron(R) processor", 
	"Reserved", 
	"Mobile Genuine Intel(R) processor", 
	"Intel(R) Celeron(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor", 
	"Intel(R) Celeron(R) processor", 
	"Mobile Geniune Intel(R) processor", 
	"Intel(R) Pentium(R) M processor", 
	"Mobile Intel(R) Celeron(R) processor",
	
};

char* cpuid_intel_other[] = {
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Celeron(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor MP", 
	"Reserved", 
	"Reserved", 
	"Intel(R) Xeon(R) processor", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Reserved",
	
};

uint8_t cpuid_detect_cpu(void) {
	uint8_t cpu;
	
	uint32_t ebx;
	uint32_t unused;
	
	cpuid(0, unused, ebx, unused, unused);
	
	switch (ebx) {
		case 0x756E6547: {
			cpuid_do_intel();
			cpu = CPU_INTEL;
			strcpy(cpu_vendor, "Intel");
			
			break;
			
		} case 0x68747541: {
			cpuid_do_amd();
			cpu = CPU_AMD;
			strcpy(cpu_vendor, "AMD");
			
			break;
			
		} default: {
			printf_warn("CPUID Unknown x86 CPU detected.\n");
			cpu = CPU_UNKNOWN;
			strcpy(cpu_vendor, "Unknown");
			
			break;
			
		}
		
	}
	
	return cpu;
	
}
	
void cpuid_do_intel(void) {
	printf("CPUID Intel specific features:\n");
	
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	
	uint32_t max_eax;
	uint32_t unused;
	
	cpuid(1, eax, ebx, unused, unused);
	
	int model = (eax >> 4) & 16;
	int family = (eax >> 8) & 16;
	int extended_family = -1;
	int type = (eax >> 12) & 3;
	
	int brand = ebx & 0xFF;
	int stepping = ebx & 16;
	int reserved = eax >> 14;
	int signature = eax;
	
	printf_minor("\ttype = %d - ", type);
	
	switch (type) {
		case 0: {
			printf_minor("origial OEM");
			break;
			
		} case 1: {
			printf_minor("overdrive");
			break;
			
		} case 2: {
			printf_minor("dual-capable");
			break;
			
		} case 3: {
			printf_minor("reserved");
			break;
			
		} default: {
			printf_warn("unknown type");
			break;
			
		}
		
	}
	
	printf_minor("\n\tfamily = %d - ", family);
	
	switch (family) {
		case 3: {
			printf_minor("i368");
			break;
			
		} case 4: {
			printf_minor("i486");
			break;
			
		} case 5: {
			printf_minor("Pentium");
			break;
			
		} case 6: {
			printf_minor("Pentium Pro");
			break;
			
		} case 15: {
			extended_family = (eax >> 20) & 0xFF;
			printf_minor("Pentium 4 (extended family = %d)", extended_family);
			
			break;
			
		} default: {
			printf_warn("unknown family");
			break;
			
		}
		
	}
	
	printf_minor("\n\tmodel = %d - ", model);
	
	switch (family) {
		case 4: {
			switch (model) {
				case 0:
				case 1: {
					printf_minor("DX");
					break;
					
				} case 2: {
					printf_minor("SX");
					break;
					
				} case 3: {
					printf_minor("487/DX2");
					break;
					
				} case 4: {
					printf_minor("SL");
					break;
					
				} case 5: {
					printf_minor("SX2");
					break;
					
				} case 7: {
					printf_minor("write-back enhanced DX2");
					break;
					
				} case 8: {
					printf_minor("DX4");
					break;
					
				}
				
			}
			
			break;
			
		} case 5: {
			switch (model) {
				case 1: {
					printf_minor("60/66");
					break;
					
				} case 2: {
					printf_minor("75-200");
					break;
					
				} case 3: {
					printf_minor("for 486 system");
					break;
					
				} case 4: {
					printf_minor("MMX");
					break;
					
				}
				
			}
			
			break;
			
		} case 6: {
			switch (model) {
				case 1: {
					printf_minor("Pentium Pro");
					break;
					
				} case 3: {
					printf_minor("Pentium II Model 3");
					break;
					
				} case 5: {
					printf_minor("Pentium II Model 5/Xeon/Celeron");
					break;
					
				} case 6: {
					printf_minor("Celeron");
					break;
					
				} case 7: {
					printf_minor("Pentium III/Pentium III Xeon - external L2 cache");
					break;
					
				} case 8: {
					printf_minor("Pentium III/Pentium III Xeon - internal L2 cache");
					break;
					
				}
				
			}
			
			break;
			
		} case 15:
		case 3:
		default: {
			break;
			
		}
		
	}
	
	printf_minor("\n");
	cpuid(0x80000000, max_eax, unused, unused, unused);
	
	if (max_eax >= 0x80000004) {
		printf_minor("\tbrand = ");
		
		if (max_eax >= 0x80000002) {
			cpuid(0x80000002, eax, ebx, ecx, edx);
			print_regs(eax, ebx, ecx, edx);
			
		}
		
		if (max_eax >= 0x80000003) {
			cpuid(0x80000003, eax, ebx, ecx, edx);
			print_regs(eax, ebx, ecx, edx);
			
		}
		
		if (max_eax >= 0x80000004) {
			cpuid(0x80000004, eax, ebx, ecx, edx);
			print_regs(eax, ebx, ecx, edx);
			
		}
		
	} else if (brand > 0) {
		printf_minor("\tbrand = %d - ", brand);
		
		if (brand < 0x18) {
			if (signature == 0x000006B1 || signature == 0x00000F13) {
				printf_minor("%s", cpuid_intel_other[brand]);
				
			} else {
				printf_minor("%s", cpuid_intel[brand]);
				
			}
			
		} else {
			printf_minor("reserved\n");
			
		}
		
	}
	
	cpu_stepping = stepping;
	printf_minor("\n\tStepping = %d\n\treserved: %d\n", stepping, reserved);
	
	kernel_itoa(cpu_stepping_str, 10, cpu_stepping);
	strcpy(cpu_vendor, "Intel CPU");
	
}

void cpuid_do_amd(void) {
	printf("CPUID AMD specific features:\n");
	
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	
	uint32_t extended;
	uint32_t unused;
	
	cpuid(1, eax, unused, unused, unused);
	
	int model = (eax >> 4) & 16;
	int family = (eax >> 8) & 16;
	int stepping = eax & 16;
	int reserved = eax >> 12;
	
	printf_minor("\tfamily = %d\n\tmodel = %d (", family, model);
	
	switch (family) {
		case 4: {
			printf_minor("486 Model %d", model);
			break;
			
		} case 5: {
			switch(model) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 6:
				case 7: {
					printf_minor("K6 Model %d", model);
					break;
					
				} case 8: {
					printf_minor("K6-2 Model 8");
					break;
					
				} case 9: {
					printf_minor("K6-III Model 9");
					break;
					
				} default: {
					printf_minor("K5/K6 Model %d", model);
					break;
					
				}
				
			}
			
			break;
			
		} case 6: {
			switch (model) {
				case 1:
				case 2:
				case 4: {
					printf_minor("Athlon Model %d", model);
					break;
					
				} case 3: {
					printf_minor("Duron Model 3");
					break;
					
				} case 6: {
					printf_minor("Athlon MP/Mobile Athlon Model 6");
					break;
					
				} case 7: {
					printf_minor("Mobile Duron Model 7");
					break;
					
				} default: {
					printf_minor("Duron/Athlon Model %d", model);
					break;
					
				}
				
			}
			
			break;
			
		}
		
	}
	
	printf_minor(")\n");
	cpuid(0x80000000, extended, unused, unused, unused);
	
	if (extended == 0) {
		return;
		
	} if (extended >= 0x80000002) {
		printf_minor("\tDetected processor name: ");
		cpu_name[0] = '\0';
		
		int i;
		for (i = 0x80000002; i <= 0x80000004; i++) {
			cpuid(i, eax, ebx, ecx, edx);
			print_regs(eax, ebx, ecx, edx);
			strcat(cpu_name, regs_string);
			
		}
		
		for (i = 0; i < 64; i++) {
			if (cpu_name[i] == ' ' && cpu_name[i - 1] == ' ') {
				cpu_name[i - 1] = '\0';
				break;
				
			}
			
		}
		
	} if (extended >= 0x80000007) {
		cpuid(0x80000007, unused, unused, unused, edx);
		
		if (edx & 1) {
			printf_minor("\tTemperature sensing diode detected.");
			
		}
		
	}
	
	cpu_stepping = stepping;
	kernel_itoa(cpu_stepping_str, 10, cpu_stepping);
	printf_minor("\n\tstepping = %d\n\treserved = %d\n", stepping, reserved);
	
}

uint8_t cpuid_detect_tsc(void) {
	uint32_t edx;
	uint32_t unused;
	
	cpuid(1, unused, unused, unused, edx);
	cpu_tsc = edx & 0x10;
	
	return cpu_tsc;
	
}

uint8_t cpuid_detect_sse(void) {
	uint32_t edx;
	uint32_t unused;
	
	cpuid(1, unused, unused, unused, edx);
	cpu_sse = edx & 0x2000000;
	
	return cpu_sse;
	
}
