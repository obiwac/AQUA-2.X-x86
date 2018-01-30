
#ifndef __AQUA__DRIVERS_USB_USB_H
	#define __AQUA__DRIVERS_USB_USB_H
	
	#include "host_controllers/ohci.h"
	#include "host_controllers/uhci.h"
	#include "host_controllers/ehci.h"
	#include "host_controllers/xhci.h"
	
	#define USB_VERSION_NONE 4
	
	#define USB_VERSION_1_0 0
	#define USB_VERSION_1_1 1
	#define USB_VERSION_2_0 2
	#define USB_VERSION_3_0 3
	
	pci_driver_descriptor_t ohci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t uhci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t ehci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t xhci_controller[MAX_USB_CONTROLLER_COUNT];

	uint8_t ohci_controller_count;
	uint8_t uhci_controller_count;
	uint8_t ehci_controller_count;
	uint8_t xhci_controller_count;
	
	unsigned char usb_calculate_max_spec(void);
	
#endif
