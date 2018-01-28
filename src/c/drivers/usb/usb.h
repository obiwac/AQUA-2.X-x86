
#ifndef __AQUA__DRIVERS_USB_USB_H
	#define __AQUA__DRIVERS_USB_USB_H
	
	#include "protocols/ohci.h"
	#include "protocols/uhci.h"
	#include "protocols/ehci.h"
	#include "protocols/xhci.h"
	
	#define USB_VERSION_NONE 4
	
	#define USB_VERSION_1_0 0
	#define USB_VERSION_1_1 1
	#define USB_VERSION_2_0 2
	#define USB_VERSION_3_0 3
	
	pci_driver_descriptor_t ohci_controller_device;
	pci_driver_descriptor_t uhci_controller_device;
	pci_driver_descriptor_t ehci_controller_device;
	pci_driver_descriptor_t xhci_controller_device;
	
	unsigned char usb_calculate_max_spec(void);
	
#endif
