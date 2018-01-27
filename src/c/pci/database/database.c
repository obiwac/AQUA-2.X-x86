
#include "../structs.h"
#include "vendor_count.h"

void* malloc(uint32_t size);
int printf(const char* format, ...);

pci_vendor_t* pci_init_database(void) {
	#ifdef PCI_VENDOR_COUNT
		pci_vendors = (pci_vendor_t*) malloc(PCI_VENDOR_COUNT * sizeof(pci_vendor_t));
		#include "database.h"
		
		return pci_vendors;
	#else
		return (void*) 0;
	#endif
	
}
