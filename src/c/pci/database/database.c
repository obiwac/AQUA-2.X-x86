
#include "../structs.h"

#define PCI_VENDOR_COUNT 

void pci_init_database(void) {
	pci_vendors = (pci_vendor_t*) malloc(PCI_VENDOR_COUNT * sizeof(pci_vendor_t));
	#include "database.h"
	
}
