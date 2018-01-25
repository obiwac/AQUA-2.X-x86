
#include "../structs.h"
#include "vendor_count.h"

void* malloc(uint32_t size);

void pci_init_database(void) {
	#ifdef PCI_VENDOR_COUNT
		pci_vendors = (pci_vendor_t*) malloc(PCI_VENDOR_COUNT * sizeof(pci_vendor_t));
		#include "database.h"
	#endif
	
}
