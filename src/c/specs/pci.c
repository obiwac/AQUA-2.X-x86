
#include "pci.h"

char pci_graphics_card_device_name[PCI_MAX_NAME_SIZE];
char pci_sound_card_device_name[PCI_MAX_NAME_SIZE];
char pci_networking_card_device_name[PCI_MAX_NAME_SIZE];

char pci_graphics_card_vendor_name[PCI_MAX_NAME_SIZE];
char pci_sound_card_vendor_name[PCI_MAX_NAME_SIZE];
char pci_networking_card_vendor_name[PCI_MAX_NAME_SIZE];

uint8_t pci_graphics_card_set = 0;
uint8_t pci_sound_card_set = 0;
uint8_t pci_networking_card_set = 0;
