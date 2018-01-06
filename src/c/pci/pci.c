
#include "pci.h"

uint16_t pci_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
	uint32_t lbus = (uint32_t) bus;
	uint32_t lslot = (uint32_t) slot;
	uint32_t lfunc = (uint32_t) func;
	
	uint32_t address = (uint32_t) ((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t) 0x80000000));
	outportl(0xCF8, address);
	uint16_t tmp = (uint16_t) ((inportl(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
	
	return tmp;
	
}

uint32_t pci_read_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
	uint32_t lbus = (uint32_t) bus;
	uint32_t lslot = (uint32_t) slot;
	uint32_t lfunc = (uint32_t) func;
	
	uint32_t address = (uint32_t) ((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t) 0x80000000));
	outportl(0xCF8, address);
	uint32_t tmp = (uint32_t) ((inportl(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
	
	return tmp;
	
}

uint16_t get_pci_vendor(uint8_t bus, uint8_t slot, uint8_t function) {
	uint16_t vendor = pci_read_word(bus, slot, function, 0);
	uint16_t device;
	
	if (vendor != 0xFFFF) {
		device = pci_read_word(bus, slot, 0, 2);
		
	}
	
	return vendor;
	
}

pci_device_t get_pci_device(uint8_t tclass, uint8_t tsub_class, uint8_t tprog_if) {
	uint16_t class_and_sub;
	uint8_t class;
	uint8_t sub_class;
	uint8_t prog_if;
	
	pci_device_t pci_device = {
		.bus = 0,
		.slot = 0,
		.flags = 0
		
	};
	
	uint8_t found_device = 0;
	
	int bus;
	int device;
	
	for (bus = 0; bus < 256; bus++) {
		for (device = 0; device < 32; device++) {
			if (get_pci_vendor(bus, device, 0) != 0xFFFF) {
				class_and_sub = pci_read_word(bus, device, 0, 10);
				class = (uint8_t) (class_and_sub >> 8);
				sub_class = (uint8_t) class_and_sub;
				prog_if = (uint8_t) (pci_read_word(bus, device, 0, 8) >> 8);
				
				if (class == tclass && sub_class == tsub_class && prog_if == tprog_if) {
					if (!found_device) {
						pci_device.bus = bus;
						pci_device.slot = device;
						pci_device.flags |= 0b00000001;
						
					} else {
						pci_device.flags |= 0b00000010;
						
					}
					
				}
				
			}
			
		}
		
	}
	
	return pci_device;
	
}

uint32_t pci_make_addr(uint16_t bus, uint16_t slot, uint16_t func, uint16_t offset) {
	uint32_t lbus = (uint32_t) bus;
	uint32_t lslot = (uint32_t) slot;
	uint32_t lfunc = (uint32_t) func;
	
	return (uint32_t) ((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t) 0x80000000));
	
}

void pci_write_long(uint16_t bus, uint16_t slot, uint16_t func, uint16_t offset, uint32_t data) {
	uint32_t address = pci_make_addr(bus, slot, func, offset);
	outportl(PCI_DATA_PORT, address);
	outportl(PCI_COMMAND_PORT, data);
	
}

void pci_debug(void) {
	printf("PCI Checking all pci buses ...\n");
	
	int bus;
	int device;
	for (bus = 0; bus < 256; bus++) {
		for (device = 0; device < 32; device++) {
			if (get_pci_vendor(bus, device, 0) != 0xFFFF) {
				printf_minor("\tPCI Found ");
				
				uint16_t class_and_sub = pci_read_word(bus, device, 0, 10);
				print_pci_class_code((uint8_t) (class_and_sub >> 8), (uint8_t) class_and_sub, (uint8_t) (pci_read_word(bus, device, 0, 8) >> 8));
				
				printf_minor(" at 0x%x, 0x%x", bus, device);
				
				if (((uint8_t) (pci_read_word(bus, device, 0, 14) & 0xFF)) & 0x80 != 0) {
					printf_minor(" with multiple functions.");
					
				}
				
				printf("\n");
				
			}
			
		}
		
	}
	
}

void pci_analyse(void) {
	pci_driver_descriptor_t driver;
	pci_device_descriptor_t device_descriptor;
	pci_bar_t bar;
	
	int function_count;
	int bus;
	int device;
	int function;
	int bar_num;
	
	for (bus = 0; bus < 8; bus++) {
		for (device = 0; device < 32; device++) {
			function_count = pci_device_has_functions(bus, device) ? 8 : 1;
			
			for (function = 0; function < function_count; function++) {
				device_descriptor = pci_get_device_descriptor(bus, device, function);
				
				if (device_descriptor.vendor_id == 0x0000 || device_descriptor.vendor_id == 0xFFFF) {
					continue;
					
				}
				
				for (bar_num = 0; bar_num < 6; bar_num++) {
					bar = pci_get_bar(bus, device, function, bar_num);
					
					if (bar.address && (bar.type == input_output)) {
						device_descriptor.port_base = (uint32_t) bar.address;
						
					}
					
				}
				
				driver = pci_get_driver(device_descriptor);
				
			}
			
		}
		
	}
	
}

void print_pci_class_code(uint8_t class_code, uint8_t sub_class, uint8_t prog_if) {
	switch (class_code) {
		case 0x0: {
			printf_minor("Device was built prior definition of the class code field");
			break;
			
		} case 0x1: {
			printf_minor("Mass Storage Controller");
			break;
			
		} case 0x2: {
			printf_minor("Network Controller");
			break;
			
		} case 0x3: {
			printf_minor("Display Controller");
			break;
			
		} case 0x4: {
			printf_minor("Mutimedia Controller");
			break;
			
		} case 0x5: {
			printf_minor("Memory Controller");
			break;
			
		} case 0x6: {
			printf_minor("Bridge Device");
			break;
			
		} case 0x7: {
			printf_minor("Simple Communication Controller");
			break;
			
		} case 0x8: {
			printf_minor("Base System Peripheral");
			break;
			
		} case 0x9: {
			printf_minor("Input Device");
			break;
			
		} case 0xA: {
			printf_minor("Docking Station");
			break;
			
		} case 0xB: {
			printf_minor("Processor");
			break;
			
		} case 0xC: {
			printf_minor("Serial Bus Controller");
			break;
			
		} case 0xD: {
			printf_minor("Wireless Controller");
			break;
			
		} case 0xE: {
			printf_minor("Intelligent IO Controller");
			break;
			
		} case 0xF: {
			printf_minor("Satellite Communication Controller");
			break;
			
		} case 0x10: {
			printf_minor("Encryption Controller");
			break;
			
		} case 0x11: {
			printf_minor("Data Acquisition and Signal Processing Controller");
			break;
			
		} default: {
			printf_minor("Other Device (0x%x)", class_code);
			
		}
		
	}
	
	printf_minor(" (Sub 0x%x, 0x%x)", sub_class, prog_if);
	
}

uint32_t get_pci_id(uint16_t bus, uint16_t device, uint16_t function, uint32_t register_offset) {
	return 0x1 << 31 | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11) | ((function & 0x07) << 8) | (register_offset & 0xFC);
	
}

uint32_t pci_read(uint16_t bus, uint16_t device, uint16_t function, uint32_t register_offset) {
	uint32_t id = get_pci_id(bus, device, function, register_offset);
	outportl(PCI_COMMAND_PORT, id);
	uint32_t result = inportl(PCI_DATA_PORT);
	
	return result >> (8 * (register_offset % 4));
	
}

void pci_write(uint16_t bus, uint16_t device, uint16_t function, uint32_t register_offset, uint32_t value) {
	uint32_t id = get_pci_id(bus, device, function, register_offset);
	outportl(PCI_COMMAND_PORT, id);
	outportl(PCI_DATA_PORT, value);
	
}

uint8_t pci_device_has_functions(uint16_t bus, uint16_t device) {
	return (uint8_t) (pci_read(bus, device, 0, 0x0E) & (1 << 7));
	
}

pci_device_descriptor_t pci_get_device_descriptor(uint16_t bus, uint16_t device, uint16_t function) {
	pci_device_descriptor_t result;
	
	result.bus = bus;
	result.device = device;
	result.function = function;
	
	result.vendor_id = pci_read(bus, device, function, 0x00);
	result.device_id = pci_read(bus, device, function, 0x02);
	
	result.class_id = pci_read(bus, device, function, 0x0B);
	result.subclass_id = pci_read(bus, device, function, 0x0A);
	result.interface_id = pci_read(bus, device, function, 0x09);
	
	result.revision = pci_read(bus, device, function, 0x08);
	result.interrupt = pci_read(bus, device, function, 0x3C);
	
	return result;
	
}

pci_bar_t pci_get_bar(uint16_t bus, uint16_t device, uint16_t function, uint16_t bar) {
	pci_bar_t result;
	
	uint32_t header_type = pci_read(bus, device, function, 0x0E) & 0x7F;
	int max_bars = 6 - (4 * header_type);
	
	if (bar >= max_bars) {
		return result;
		
	}
	
	uint32_t bar_value = pci_read(bus, device, function, 0x10 + 4 * bar);
	result.type = (bar_value & 0x1) ? input_output : memory_mapping;
	uint32_t temp;
	
	if (result.type == memory_mapping) {
		switch ((bar_value >> 1) & 0x3) {
			case 0: // 32 bit
			case 1: // 20 bit
			case 2: { // 64 bit
				break;
				
			}
			
		}
		
	} else {
		result.address = (uint8_t*) (bar_value & ~0x3);
		result.prefetchable = 0;
		
	}
	
	return result;
	
}

pci_driver_descriptor_t pci_get_driver(pci_device_descriptor_t device) {
	pci_driver_descriptor_t result;
	
	/*
	 printf_minor("\t\t detected.\n");
					result.device_name = "";
					result.device_type = "";
					
					break;*/
	
	result.vendor_name = "unknown";
	result.device_name = "unknown";
	result.device_type = "unknown";
	
	switch (device.vendor_id) {
		case 0x80EE: {
			printf_minor("\tOracle vendor detected.\n");
			result.vendor_name = "Oracle";
			
			switch (device.device_id) {
				case 0xCAFE: {
					printf_minor("\t\tGuest additions device detected.\n");
					result.device_name = "Guest additions";
					result.device_type = "Pseudo";
					
					break;
					
				} case 0xBEEF: {
					printf_minor("\t\tVirtualBox graphics adapter device detected.\n");
					result.device_name = "tVirtualBox graphics adapter";
					result.device_type = "Pseudo";
					
					break;
					
				} default: {
					printf_warn("\t\tUnknown Oracle device detected (0x%x).\n", device.device_id);
					break;
					
				}
				
			}
			
			break;
			
		} case 0x05AC:
		case 0x106B: { /// TODO make a cool crash screen
			printf_error("An Apple device was detected!!! This may harm your system ...\n");
			result.vendor_name = "Apple";
			break;
			
		} case 0x1022:
		case 0x1002: {
			printf_minor("\tAMD vendor detected.\n");
			result.vendor_name = "AMD";
			
			switch (device.device_id) {
				case 0x2000: {
					printf_minor("\t\tPCNet network card detected (assuming it's an AM79C973).\n");
					result.device_name = "AM79C973";
					result.device_type = "Network Controller";
					
					break;
					
				} default: {
					printf_warn("\t\tUnknown AMD device detected (0x%x).\n", device.device_id);
					break;
					
				}
				
			}
			
			break;
			
		} case 0x8087:
		case 0x8086: {
			printf_minor("\tIntel vendor detected.\n");
			result.vendor_name = "Intel";
			
			switch (device.device_id) {
				case 0x1237: {
					printf_minor("\t\tPCI & Memory device detected.\n");
					result.device_name = "PCI & Memory";
					result.device_type = "Memory Controller";
					
					break;
				
				} case 0x7000: {
					printf_minor("\t\tPIIX3 PCI-to-ISA Bridge (Triton II) detected.\n");
					result.device_name = "PIIX3 PCI-to-ISA Bridge (Triton II)";
					result.device_type = "Bridge Device";
					
					break;
					
				} case 0x7111: {
					printf_minor("\t\tIntel(R) 82371AB/EB PCI Bus Master IDE Controller detected.\n");
					result.device_name = "Intel(R) 82371AB/EB PCI Bus Master IDE Controller";
					result.device_type = "Mass Storage Controller";
					
					break;
					
				} case 0x2415: {
					printf_minor("\t\tAureal (AD1881 SOUNDMAX) Placa Mãe Asaki P3-141 detected.\n");
					result.device_name = "Aureal (AD1881 SOUNDMAX) Placa Mãe Asaki P3-141";
					result.device_type = "Multimedia Controller";
					
					break;
					
				} case 0x7113: {
					printf_minor("\t\tPIIX4/4E/4M Power Management Controller detected.\n");
					result.device_name = "PIIX4/4E/4M Power Management Controller";
					result.device_type = "Base System Peripheral";
					
					break;
					
				}
				
				case 0x1977:
				case 0x27D8:
				case 0x0A0C:
				case 0x0F04:
				case 0x1C20:
				case 0x1E20:
				case 0x3B56:
				case 0x9C20: {
					printf_minor("\t\tHigh Definition audio controller card detected.\n");
					result.device_name = "High Definition";
					result.device_type = "Multimedia Controller";
					
					break;
					
				} case 0x2440: {
					printf_minor("\t\tICH2 audio controller card detected.\n");
					result.device_name = "ICH2";
					result.device_type = "Multimedia Controller";
					
					break; 
					
				} case 0x24D5: {
					printf_minor("\t\tICH5 audio controller card detected.\n");
					result.device_name = "ICH5";
					result.device_type = "Multimedia Controller";
					
					break;
					
				} case 0x2668:
				case 0x2678: {
					printf_minor("\t\tICH6 audio controller card detected.\n");
					result.device_name = "ICH6";
					result.device_type = "Multimedia Controller";
					
					break;
					
				} case 0x27: {
					printf_minor("\t\tICH7 audio controller card detected.\n");
					result.device_name = "ICH7";
					result.device_type = "Multimedia Controller";
					
					break;
					
				} case 0x293E: {
					printf_minor("\t\tICH9 audio controller card detected.\n");
					result.device_name = "ICH9";
					result.device_type = "Multimedia Controller";
					
					break;
					
				} default: {
					printf_warn("\t\tUnknown Intel device detected (0x%x).\n", device.device_id);
					break;
					
				}
				
			}
			
			break;
			
		} case 0x10DE: {
			printf_minor("\tNVIDIA vendor detected.\n");
			result.vendor_name = "NVIDIA";
			
			switch (device.device_id) {
				default: {
					printf_warn("\t\tUnknown NVIDIA device detected (0x%x).\n", device.device_id);
					break;
					
				}
				
			}
			
			break;
			
		} case 0x5143: {
			printf_minor("\tQualcomm vendor detected.\n");
			result.vendor_name = "Qualcomm";
			
			switch (device.device_id) {
				default: {
					printf_warn("\t\tUnknown Qualcomm device detected (0x%x).\n", device.device_id);
					break;
					
				}
				
			}
			
			break;
			
		} case 0x10EC: {
			printf_minor("\tRealtek vendor detected.\n");
			result.vendor_name = "Realtek";
			
			switch (device.device_id) {
				default: {
					printf_warn("\t\tUnknown Realtek device detected (0x%x).\n", device.device_id);
					break;
					
				}
				
			}
			
			break;
			
		} default: {
			printf_warn("\tUnknown vendor detected (0x%x).\n", device.vendor_id);
			break;
			
		}
		
	} switch (device.class_id) {
		case 0x03: {
			printf_minor("\tGraphics card detected.\n");
			result.device_type = "Graphics card";
			
			switch (device.subclass_id) {
				case 0x00: {
					printf_minor("\t\tVGA graphics card detected.\n");
					result.device_name = "VGA";
					
					break;
					
				} default: {
					printf_warn("\tUnknown graphics card detected (0x%x).\n", device.subclass_id);
					break;
					
				}
				
			}
			
			break;
			
		} default: {
			//~printf_warn("\tUnknown device class (0x%x).\n", device.class_id);
			break;
			
		}
		
	}
	
	return result;
	
}


