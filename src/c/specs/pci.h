
#ifndef __AQUA__SPECS_PCI_H
	#define __AQUA__SPECS_PCI_H
	
	#include "../pci/pci.h"
	
	#define PCI_MAX_NAME_SIZE 96
	
	char pci_graphics_card_device_name[PCI_MAX_NAME_SIZE];
	char pci_sound_card_device_name[PCI_MAX_NAME_SIZE];
	char pci_networking_card_device_name[PCI_MAX_NAME_SIZE];
	
	char pci_graphics_card_vendor_name[PCI_MAX_NAME_SIZE];
	char pci_sound_card_vendor_name[PCI_MAX_NAME_SIZE];
	char pci_networking_card_vendor_name[PCI_MAX_NAME_SIZE];
	
	uint8_t pci_graphics_card_set;
	uint8_t pci_sound_card_set;
	uint8_t pci_networking_card_set;
	
#endif
