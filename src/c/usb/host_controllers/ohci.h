
#ifndef __AQUA__DRIVERS_USB_PROTOCOLS_OHCI_H
	#define __AQUA__DRIVERS_USB_PROTOCOLS_OHCI_H
	
	#include "../usb_utils.h"
	
	#define OHCI_REVISION 0x00
	
	#define OHCI_CONTROL 0x04
	#define OHCI_COMMAND 0x08
	#define OHCI_STATUS 0x0C
	
	#define OHCI_INTERRUPT_ENABLE 0x10
	#define OHCI_INTERRUPT_DISABLE 0x14
	
	#define OHCI_HCCA 0x18
	
	#define OHCI_CONTROL_HEAD_ED 0x20
	#define OHCI_CONTROL_CURRENT_ED 0x24
	
	#define OHCI_BULK_HEAD_ED 0x28
	#define OHCI_BULK_CURRENT_ED 0x2C
	
	#define OHCI_FM_INTERVAL 0x34
	#define OHCI_FM_REMAINING 0x38
	#define OHCI_FM_NUMBER 0x3C
	
	#define OHCI_LOW_SPEED_THRESHOLD 0x44
	
	#define OHCI_ROOT_DESCIPTOR_A 0x48
	#define OHCI_ROOT_DESCIPTOR_B 0x4C
	#define OHCI_ROOT_STATUS 0x50
	#define OHCI_ROOT_PORTS 0x54
	
	typedef struct ohci_list_entry_s {
		struct ohci_list_entry_s* b_link;
		struct ohci_list_entry_s* f_link;
		
	} __attribute__((packed)) ohci_list_entry_t;
	
	void ohci_controller_init(void);
	
#endif
