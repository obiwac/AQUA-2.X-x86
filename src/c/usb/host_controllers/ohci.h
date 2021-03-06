
#ifndef __AQUA__DRIVERS_USB_PROTOCOLS_OHCI_H
	#define __AQUA__DRIVERS_USB_PROTOCOLS_OHCI_H
	
	#include "../usb_utils.h"
	
	// Thanks omarrx024 :3
	
	#define OHCI_REVISION 0x00
	
	#define OHCI_CONTROL 0x04
	#define OHCI_COMMUNICATIONAND 0x08
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
	
	#define OHCI_CONTROL_EXECUTE_CONTROL 0x10
	#define OHCI_CONTROL_EXECUTE_BULK 0x20
	
	#define OHCI_COMMUNICATIONAND_RESET 0x01
	#define OHCI_COMMUNICATIONAND_CONTROL_FILLED 0x02
	#define OHCI_COMMUNICATIONAND_OWNERSHIP_CHANGE 0x8
	
	#define OHCI_STATUS_WRITE_DONE 0x2
	#define OHCI_STATUS_UNRECOVERABLE_ERROR 0x10
	#define OHCI_STATUS_FRAME_OVERFLOW 0x20
	#define OHCI_STATUS_OWNERSHIP_CHANGE 0x40000000
	
	#define OHCI_ROOT_STATUS_LPSC 0x10000
	
	#define OHCI_PORT_CONNECT 0x01
	#define OHCI_PORT_ENABLE 0x02
	#define OHCI_PORT_CLEAR_SUSPEND 0x08
	#define OHCI_PORT_RESET 0x10
	#define OHCI_PORT_SET_POWER 0x100
	
	#define OHCI_PACKET_SETUP 0
	#define OHCI_PACKET_OUT 1
	#define OHCI_PACKET_IN 2
	#define OHCI_PACKET_RESERVED 3
	
	#define OHCI_COMMUNICATION_INTERRUPT_TABLE 0x00
	#define OHCI_COMMUNICATION_FRAME_NUMBER 0x80
	#define OHCI_COMMUNICATION_PADDING 0x82
	#define OHCI_COMMUNICATION_DONE_HEAD 0x84
	#define OHCI_COMMUNICATION_SIZE 256
	
	#define OHCI_DESCRIPTORS_SIZE 8
	#define OHCI_MAX_WAITS 16384
	
	typedef struct {
		uint8_t* device_addresses;
		
	} ohci_controller_t;
	
	void ohci_controller_init(void);
	
#endif
