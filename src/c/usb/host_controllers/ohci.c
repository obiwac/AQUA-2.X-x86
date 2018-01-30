
#include "ohci.h"
#include "../usb.h"

static uint16_t ohci_descriptors;
static uint16_t ohci_communication;

static ohci_controller_t* _ohci_controllers;
static ohci_controller_t* ohci_controllers[MAX_USB_CONTROLLER_COUNT];

static ohci_controller_t single_ohci_controller_init(uint8_t id, pci_driver_descriptor_t controller) {
	uint16_t status = pci_read_dword(controller.device.bus, controller.device.device, controller.device.function, PCI_STATUS_COMMAND);
	pci_write_dword(controller.device.bus, controller.device.device, controller.device.function, PCI_STATUS_COMMAND, status | 0x406);
	
	ohci_controller_t result = {
		.device_addresses = (uint8_t*) kmalloc(USB_MAX_ADDRESSES),
		
	};
	
	return result;
	
}

void ohci_controller_init(void) {
	ohci_communication = 0;
	_ohci_controllers = (ohci_controller_t*) kmalloc(ohci_controller_count * sizeof(ohci_controller_t));
	
	int i;
	for (i = 0; i < ohci_controller_count; i++) {
		_ohci_controllers[i] = single_ohci_controller_init(i, ohci_controller[i]);
		ohci_controllers[i] = (ohci_controller_t*) &_ohci_controllers[i];
		
	}
	
}
