
#ifndef __AQUA__PCI_STRUCTS_H
	#define __AQUA__PCI_STRUCTS_H
	
	#include "../types.h"
	
	typedef struct {
		uint16_t id;
		char* name;
		
	} __attribute__((packed)) pci_product_t;
	
	typedef struct {
		uint16_t id;
		char* name;
		
		uint16_t product_count;
		pci_product_t* products;
		
	} __attribute__((packed)) pci_vendor_t;
	
	uint16_t pci_vendor_count;
	pci_vendor_t* pci_vendors;
	
#endif
