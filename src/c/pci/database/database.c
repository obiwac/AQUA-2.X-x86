
#include "../structs.h"

#define PCI_VENDOR_COUNT 0x863

void pci_init_database(void) {
	pci_vendors = (pci_vendor_t*) malloc(PCI_VENDOR_COUNT * sizeof(pci_vendor_t));
	#include "database.h"
	
}
