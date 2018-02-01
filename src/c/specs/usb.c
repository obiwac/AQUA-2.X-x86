
#include "usb.h"

char usb_max_version_str[16];

void get_usb_max_version_str(void) {
	switch (usb_calculate_max_spec()) {
		case USB_VERSION_1_0: {
			printf("You computer supports USB 1.0");
			break;
			
		} case USB_VERSION_1_1: {
			printf("You computer supports USB 1.1");
			break;
			
		} case USB_VERSION_2_0: {
			printf("You computer supports USB 2.0");
			break;
			
		} case USB_VERSION_3_0: {
			printf("You computer supports USB 3.0");
			break;
			
		} case USB_VERSION_NONE:
		default: {
			strcpy(usb_max_version_str, "Your computer does not support USB");
			break;
			
		}
		
	}
	
}
