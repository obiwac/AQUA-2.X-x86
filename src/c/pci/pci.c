
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
				uint16_t class_and_sub = pci_read_word(bus, device, 0, 10);
				printf_minor("\tPCI Found device (0x%x) at 0x%x, 0x%x", class_and_sub, bus, device);
				
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
				
				uint16_t class_and_sub = pci_read_word(bus, device, 0, 10);
				
				device_descriptor.class_id = (uint8_t) (class_and_sub >> 8);
				device_descriptor.subclass_id = (uint8_t) (class_and_sub & 0xFF);
				device_descriptor.interface_id = (uint8_t) (pci_read_word(bus, device, 0, 8) >> 8);
				
				driver = pci_get_driver(device_descriptor);
				
				if (driver.unknown) printf_warn("\tWARNING The PCI database was not constructed.\n");
				else printf_minor("\tFound %s (%s) from %s ...\n", driver.device_name, driver.device_type, driver.vendor_name);
				
			}
			
		}
		
	}
	
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

#include "database/vendor_count.h"
#include "structs.h"
#include "layman.h"
#include "defs.h"

pci_vendor_t* pci_init_database(void);
static pci_vendor_t* data;

#define PCI_SET_NONE 0
#define PCI_SET_NETWORKING 1
#define PCI_SET_GRAPHICS 2
#define PCI_SET_SOUND 3

pci_driver_descriptor_t pci_get_driver(pci_device_descriptor_t device) { /// TODO device.subclass_id & device.interface_id
	pci_driver_descriptor_t result = {
		.unknown = 0,
		.device = device
		
	};
	
	data = pci_init_database();
	uint8_t set = PCI_SET_NONE;
	
	#ifdef PCI_VENDOR_COUNT
		result.vendor_name = "unknown";
		result.device_name = "unknown";
		result.device_type = "unknown";
		
		int v;
		for (v = 0; v < PCI_VENDOR_COUNT; v++) {
			if (data[v].id == result.device.vendor_id) {
				result.vendor_name = data[v].name;
				
				int p;
				for (p = 0; p < data[v].product_count; p++) {
					if (data[v].products[p].id == result.device.device_id) {
						result.device_name = data[v].products[p].name;
						
						switch (result.device.class_id) {
							case PCI_CLASS_MASS_STORAGE_CONTROLLER: result.device_type = "mass storage controller"; break;
							case PCI_CLASS_NETWORK_CONTROLLER: {
								result.device_type = "network controller";
								set = PCI_SET_NETWORKING;
								
								break;
								
							} case PCI_CLASS_DISPLAY_CONTROLLER: {
								result.device_type = "display controller";
								set = PCI_SET_GRAPHICS;
								
								break;
								
							} case PCI_CLASS_MULTIMEDIA_CONTROLLER: {
								result.device_type = "multimedia controller";
								set = PCI_SET_SOUND;
								
								break;
								
							} case PCI_CLASS_MEMORY_CONTROLLER: result.device_type = "memory controller"; break;
							case PCI_CLASS_BRIDGE_DEVICE: result.device_type = "bridge device"; break;
							case PCI_CLASS_SIMPLE_COMMNUICATION_CONTROLLER: result.device_type = "simple communication controller"; break;
							case PCI_CLASS_BASE_SYSTEM_PERIPHERAL: result.device_type = "base system peripheral"; break;
							case PCI_CLASS_INPUT_DEVICE: result.device_type = "input device"; break;
							case PCI_CLASS_DOCKING_STATION: result.device_type = "docking station"; break;
							case PCI_CLASS_PROCESSOR: result.device_type = "processor"; break;
							case PCI_CLASS_SERIAL_BUS_CONTROLLER: result.device_type = "serial bus controller"; break;
							case PCI_CLASS_WIRELESS_CONTROLLER: result.device_type = "wireless controller"; break;
							case PCI_CLASS_INTELLIGENT_IO_CONTROLLER: result.device_type = "intelligent I/O controller"; break;
							case PCI_CLASS_SATELLITE_COMMUNICATION_CONTROLLER: result.device_type = "satellite controller"; break;
							case PCI_CLASS_ENCRYPTION_CONTROLLER: result.device_type = "encryption controller"; break;
							case PCI_CLASS_DATA_ACQUISITION_AND_SIGNAL_PROCESSING_CONTROLLER: result.device_type = "data acquisition and signal processing controller"; break;
							
							case PCI_CLASS_NULL:
							case PCI_CLASS_UNCLASSIFIABLE: {
								break;
								
							} case PCI_CLASS_RESERVED:
							default: {
								result.device_type = "reserved";
								break;
								
							}
							
						}
						
						break;
						
					}
					
				}
				
				break;
				
			}
			
		}
	#else
		result.unknown = 1;
		
		result.vendor_name = "The PCI database was not constructed";
		result.device_name = "The PCI database was not constructed";
		result.device_type = "The PCI database was not constructed";
	#endif
	
	switch (set) {
		case PCI_SET_NETWORKING: {
			pci_networking_card_set = 1;
			
			strcpy(pci_networking_card_device_name, result.device_name);
			strcpy(pci_networking_card_vendor_name, result.vendor_name);
			
			break;
			
		} case PCI_SET_GRAPHICS: {
			pci_graphics_card_set = 1;
			
			strcpy(pci_graphics_card_device_name, result.device_name);
			strcpy(pci_graphics_card_vendor_name, result.vendor_name);
			
			break;
			
		} case PCI_SET_SOUND: {
			pci_sound_card_set = 1;
			
			strcpy(pci_sound_card_device_name, result.device_name);
			strcpy(pci_sound_card_vendor_name, result.vendor_name);
			
			break;
			
		} case PCI_SET_NONE:
		default: {
			break;
			
		}
		
	}
	
	return result;
	
}


