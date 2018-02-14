
#include "usb.h"

char usb_max_spec = USB_VERSION_NONE;

unsigned char usb_calculate_max_spec(void) {
	if (!xhci_controller[0].unknown) usb_max_spec = USB_VERSION_3_0;
	else if (!ehci_controller[0].unknown) usb_max_spec = USB_VERSION_2_0;
	else if (!uhci_controller[0].unknown) usb_max_spec = USB_VERSION_1_1;
	else if (!ohci_controller[0].unknown) usb_max_spec = USB_VERSION_1_0;
	else usb_max_spec = USB_VERSION_NONE;
	
	return usb_max_spec;
	
}
