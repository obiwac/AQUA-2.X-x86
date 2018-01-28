
#include "usb.h"

static char usb_max_spec = USB_VERSION_NONE;

unsigned char usb_calculate_max_spec(void) {
	if (!xhci_controller_device.unknown) usb_max_spec = USB_VERSION_3_0;
	else if (!ehci_controller_device.unknown) usb_max_spec = USB_VERSION_2_0;
	else if (!uhci_controller_device.unknown) usb_max_spec = USB_VERSION_1_1;
	else if (!ohci_controller_device.unknown) usb_max_spec = USB_VERSION_1_0;
	else usb_max_spec = USB_VERSION_NONE;
	
	return usb_max_spec;
	
}
