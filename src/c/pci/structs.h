
#ifndef __AQUA__PCI_STRUCTS_H
	#define __AQUA__PCI_STRUCTS_H
	
	#include "../types.h"
	
	typedef struct {
		uint16_t id;
		char* name;
		
	} pci_product_t __attribute__((packed));
	
	typedef struct {
		uint16_t id;
		char* name;
		
		uint16_t product_count;
		pci_product_t* products;
		
	} pci_vendor_t __attribute__((packed));
	
	uint16_t pci_vendor_count;
	pci_vendor_t* pci_vendors;
	
#endif
