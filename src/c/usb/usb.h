
#ifndef __AQUA__DRIVERS_USB_USB_H
	#define __AQUA__DRIVERS_USB_USB_H
	
	// from all the different host controllers in `host_controllers/`
	
	#include "../pci/pci.h"
	
	void ohci_controller_init(void);
	void uhci_controller_init(void);
	void ehci_controller_init(void);
	void xhci_controller_init(void);
	
	#define USB_VERSION_NONE 4
	
	#define USB_VERSION_1_0 0
	#define USB_VERSION_1_1 1
	#define USB_VERSION_2_0 2
	#define USB_VERSION_3_0 3
	
	#define USB_MAX_ADDRESSES 128
	
	pci_driver_descriptor_t ohci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t uhci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t ehci_controller[MAX_USB_CONTROLLER_COUNT];
	pci_driver_descriptor_t xhci_controller[MAX_USB_CONTROLLER_COUNT];

	uint8_t ohci_controller_count;
	uint8_t uhci_controller_count;
	uint8_t ehci_controller_count;
	uint8_t xhci_controller_count;
	
	char usb_max_spec;
	unsigned char usb_calculate_max_spec(void);
	
#endif
