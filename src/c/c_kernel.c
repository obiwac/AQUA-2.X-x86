
#include "types.h"

#include "math/math.h"
#include "memory/memory.h"
#include "string/string.h"

#include "user/death.h"

#include "common/print.h"
#include "common/scan.h"
#include "vga/text.h"
#include "graphics/colour.h"

#include "specs/video.h"
#include "specs/version.h" /// REMME
#include "specs/help.h" /// REMME
#include "specs/pci.h"

#include "drivers/power/acpi.h"
#include "drivers/power/shutdown.h"
#include "drivers/power/reboot.h"

#include "drivers/pc_speaker.h"
#include "drivers/cmos.h"
#include "drivers/keyboard_old.h"

#include "drivers/serial.h"
#include "drivers/lpt.h"

#include "drivers/ata/ata.h"

#include "cpu/cpuid.h"
#include "cpu/rdtsc.h"
#include "cpu/speed.h"

#include "pci/pci.h"

#include "bios/bios.h"
#include "bios/smbios.h"

#include "bios/video_colour_type.h" // BDA stuff
#include "bios/generic_bda.h"

#include "key_maps/key_map.h"
#include "grub/parse_mboot.h"

#include "drivers/irq/pit.h"
#include "drivers/irq/mouse.h"
#include "drivers/irq/keyboard.h"

#include "int/irq.h"
#include "int/isr.h"
#include "int/misc.h"

#include "descr_tables/idt.h"
#include "descr_tables/gdt.h"

#include "loading/loading.h"
#include "specs/cpu_speed.h"

void main(void);
char vga_log[1000];

static uint8_t startup = 1;
static uint8_t BOOT_AQUA = 1;

static uint8_t print_force_serial_de = 0;

void c_main(uint32_t mb_magic, uint32_t mb_address) {
	printf("Awaiting kernel boot keypress ...\n");
	
	int i;
	for (i = 0; i < 0xFFFFF; i++) {
		if (inportb(0x64) & 1) {
			switch (inportb(0x60)) {
				case 49: {
					printf_warn("Entering kernel shell instead of AQUA DE ...\n");
					BOOT_AQUA = 0;
					
					break;
					
				} case 48: {
					printf_warn("Forcing serial output ...\n");
					print_force_serial = 1;
					
					break;
					
				} case 47: {
					print_force_serial = 1;
					printf_warn("Forcing ACPI to poweroff ...\n");
					
					printf("ACPI: Initializing ... \n");
					printf_minor("\tACPI: %d\n", acpi_init());
					
					acpi_poweroff();
					break;
					
				} case 46: {
					printf_warn("Forcing serial output in the DE ...\n");
					print_force_serial_de = 1;
					
					break;
					
				} default: {
					break;
					
				}
				
			}
			
		}
		
	}
	
	//~ vga_text_clear_screen();
	parse_mboot(mb_magic, mb_address);
	
	printf("GDT: Loading the gdt ...\n");
	load_gdt();
	
	printf("Interrupts: Installing isr ...\n");
	isr_install();
	
	printf("Memory: Initializing heap ...\n");
	init_heap();
	
	printf("Serial: Initializing serial ...\n");
	init_serial();
	
	printf("Interrupts: Initializing irqs ...\n");
	irq_init();
	
	printf_minor("\tInterrupts: Installing PIT on IRQ0 ...\n");
	pit_install();
	
	printf_minor("\tInterrupts: Installing keyboard on IRQ1 ...\n");
	if (BOOT_AQUA) keyboard_install();
	
	printf_minor("\tInterrupts: Installing serial COM on IRQ3 and IRQ4 ...\n");
	serial_install();
	
	printf_minor("\tInterrutps: Installing parallel LPT on IRQ5 and IRQ7 ...\n");
	parallel_install();
	
	printf_minor("\tInterrupts: Installing PS/2 mouse on IRQ12 ...\n");
	mouse_install();
	
	parse_bda:
	
	printf("BDA: Parsing BDA ...\n");
	
	pit_uptime = (uint32_t) bda_pit_ticks_since_boot();
	printf_minor("\tBDA: %d PIT ticks have occured since boot.\n", pit_uptime);
	
	set_lpt_port(bda_get_lpt1_port());
	printf_minor("\tBDA: Setting LPT port to LPT1 (0x%x) ...\n", get_lpt_port());
	
	printf_minor("\tBDA: Detected %d LPT ports.\n", bda_get_lpt_count());
	printf_minor("\tBDA: Detected %d COM ports.\n", bda_get_com_count());
	
	printf_minor("\tBDA: The keyboard LED is %s.\n", bda_keyboard_led() ? "on" : "off");
	printf_minor("\tBDA: The keyboard buffer is %s.\n", bda_get_keyboard_buffer());
	printf_minor("\tBDA: There are %d coloumns in text mode.\n", bda_get_text_mode_columns());
	printf_minor("\tBDA: Screen is %s.\n", get_video_type() == VIDEO_TYPE_COLOUR ? "coloured" : "monochrome");
	printf_minor("\tBDA: There are %d disk drives.\n", bda_get_drive_count());
	
	if (!startup) goto cmd_line;
	
	printf("Interrupts: Storing interrupt flags ...\n");
	__asm__ __volatile__ ("sti");
	
	printf("PIT: Setting phase to 1000Hz ...\n");
	pit_phase(1000);
	
	if (BOOT_AQUA) {
		printf("Loading: Showing loading screen ...\n");
		printf("CPU Speed: Setting CPU speed to the time it takes for the loading screen to load ...\n");
		
		cpu_speed = show_loading((uint32_t*) video_addr, video_width, video_height, video_cpc);
		printf("Loading: Showed loading screen in %dms.\n", cpu_speed);
		
	} else {
		printf("CPU Speed: Setting CPU speed to CPU_SPEED_REFERENCE (%dms)\n", CPU_SPEED_REFERENCE);
		cpu_speed = CPU_SPEED_REFERENCE;
		
	}
	
	detect_ints_enabled:
	
	printf("Interrupts: Detecting if they are enabled ...\n");
	are_ints_enabled();
	printf_minor("\tInterrupts are %s.\n", !ints_enabled ? "enabled" : "disabled");
	
	if (!startup) goto cmd_line;
	
	printf("PC Speaker: Making sure it is set to mute ...\n");
	//~ pc_speaker_mute(); /// FIXME
	
	detect_cpu:
	
	printf("CPU RDTSC: Timestamp is %d.\n", cpu_rdtsc());
	
	printf("CPUID: Detecting cpuid ...\n");
	uint8_t cpu = cpuid_detect_cpu();
	
	printf_minor("\tCPUID: CPU %s TSC.\n", cpuid_detect_tsc() ? "supports" : "does not support");
	printf_minor("\tCPUID: CPU %s SSE.\n", cpuid_detect_sse() ? "supports" : "does not support");
	
	printf("CPU: Benchmarking the CPU speed without interrupts (~ %d Hz).\n", cpu_detect_speed_noint());
	
	if (!startup) goto cmd_line;
	smbios:
	
	printf("SMBIOS: Detecting SMBIOS ...\n");
	char* smbios_entry_ptr = smbios_entry();
	
	if (smbios_entry_ptr) {
		printf_minor("\tSMBIOS exists at 0x%x.\n", (uint32_t) &smbios_entry_ptr);
		smbios_entry_point_t* smbios = smbios_get(smbios_entry_ptr);
		
		printf_minor("\tSMBIOS version %d.%d.\n", smbios->major_version, smbios->minor_version);
		printf_minor("\tSMBIOS table address 0x%x.\n", smbios->table_addr);
		
		
	} else {
		printf_warn("SMBIOS does not exist.\n");
		
	}
	
	if (!startup) goto cmd_line;
	
	printf("ATA: Setting up drives ...\n");
	printf_minor("\tBDA: Detected %d disk drives.\n", bda_get_drive_count());
	
	printf_minor("\tATA: Setting up primary master ...\n");
	_drive_primary_master = ata_setup(1, ATA_PRIMARY);
	printf_minor("\tATA: Setting up primary slave ...\n");
	_drive_primary_slave = ata_setup(0, ATA_PRIMARY);
	
	printf_minor("\tATA: Setting up secondary master ...\n");
	_drive_secondary_master = ata_setup(1, ATA_SECONDARY);
	printf_minor("\tATA: Setting up secondary slave ...\n");
	_drive_secondary_slave = ata_setup(0, ATA_SECONDARY);
	
	printf_minor("\tATA: Setting up tertiary master ...\n");
	_drive_tertiary_master = ata_setup(1, ATA_TERTIARY);
	printf_minor("\tATA: Setting up tertiary slave ...\n");
	_drive_tertiary_slave = ata_setup(0, ATA_TERTIARY);
	
	printf_minor("\tATA: Setting up quaternary master ...\n");
	_drive_quaternary_master = ata_setup(1, ATA_QUATERNARY);
	printf_minor("\tATA: Setting up quaternary slave ...\n");
	_drive_quaternary_slave = ata_setup(0, ATA_QUATERNARY);
	
	drive_primary_master = &_drive_primary_master;
	drive_primary_slave = &_drive_primary_slave;
	drive_secondary_master = &_drive_secondary_master;
	drive_secondary_slave = &_drive_secondary_slave;
	drive_tertiary_master = &_drive_tertiary_master;
	drive_tertiary_slave = &_drive_tertiary_slave;
	drive_quaternary_master = &_drive_quaternary_master;
	drive_quaternary_slave = &_drive_quaternary_slave;
	
	identify_ata:
	printf("ATA: Identifying drives ...\n");
	
	printf_minor("\tATA: Identifying primary master ...\n");
	ata_identify(drive_primary_master);
	printf_minor("\tATA: Identifying primary slave ...\n");
	ata_identify(drive_primary_slave);
	
	printf_minor("\tATA: Identifying secondary master ...\n");
	ata_identify(drive_secondary_master);
	printf_minor("\tATA: Identifying secondary slave ...\n");
	ata_identify(drive_secondary_slave);
	
	printf_minor("\tATA: Identifying tertiary master ...\n");
	ata_identify(drive_tertiary_master);
	printf_minor("\tATA: Identifying tertiary slave ...\n");
	ata_identify(drive_tertiary_slave);
	
	printf_minor("\tATA: Identifying quaternary master ...\n");
	ata_identify(drive_quaternary_master);
	printf_minor("\tATA: Identifying quaternary slave ...\n");
	ata_identify(drive_quaternary_slave);
	
	if (ata_current_drive_set) {
		printf("ATA: The selected drive is %s %s.\n", ata_current_drive->name, ata_current_drive->master_name);
		
	} else {
		printf_warn("ATA: No useable drive was found, so no drives were selected ...\n");
		
	}
	
	if (!startup) goto cmd_line;
	
	printf("CMOS: Initializing ...\n");
	cmos_init();
	
	printf_minor("\tCMOS: Adding RTC update event to occur every minute ...\n");
	add_event(60000, cmos_read_rtc_event);
	
	printf("ACPI: Initializing ... \n");
	printf_minor("\tACPI: %d\n", acpi_init());
	
	detect_pci:
	
	printf("PCI: Scanning for devices ...\n");
	pci_debug();
	
	printf("PCI: Analysing devices ...\n");
	pci_analyse();
	
	printf("PCI: Selecting main cards ...\n");
	
	if (!pci_graphics_card_set) printf_warn("\tWARNING No graphics card was selected.\n");
	else printf_minor("\tGraphics card: %s from %s\n", pci_graphics_card_device_name, pci_graphics_card_vendor_name);
	
	if (!pci_sound_card_set) printf_warn("\tWARNING No sound card was selected.\n");
	else printf_minor("\tSound card: %s from %s\n", pci_sound_card_device_name, pci_sound_card_vendor_name);
	
	if (!pci_networking_card_set) printf_warn("\tWARNING No networking card was selected.\n");
	else printf_minor("\tNetworking card: %s from %s\n", pci_networking_card_device_name, pci_networking_card_vendor_name);
	
	if (!startup) goto cmd_line;
	
	if (!BOOT_AQUA) {
		char buffer[32];
		cmd_line:
		startup = 0;
		
		while (1) {
			printf("> ");
			buffer[0] = 0;
			basic_scan(buffer);
			printf("\n");
			
			if (strcmp(buffer, "bda") == 0) goto parse_bda;
			else if (strcmp(buffer, "int") == 0) goto detect_ints_enabled;
			else if (strcmp(buffer, "log") == 0) printf("%s\n", vga_log);
			else if (strcmp(buffer, "mboot") == 0) parse_mboot(mb_magic, mb_address);
			else if (strcmp(buffer, "cpu") == 0) goto detect_cpu;
			else if (strcmp(buffer, "smbios") == 0) goto smbios;
			else if (strcmp(buffer, "ata") == 0) goto identify_ata;
			else if (strcmp(buffer, "pci") == 0) goto detect_pci;
			else if (strcmp(buffer, "poweroff") == 0) acpi_poweroff();
			else if (strcmp(buffer, "reboot") == 0) power_reboot();
			else if (strcmp(buffer, "aqua") == 0) break;
			else if (strcmp(buffer, "help") == 0) printf_warn("bda\nint\nmboot\ncpu\nsmbios\nata\npci\n\npoweroff\nreboot\naqua\nhelp\nlog\n");
			else printf_error("\"%s\" is unknown ... Type \"help\" for a list of commands.\n", buffer);
			
		}
		
	}
	
	if (print_force_serial_de) {
		printf("DE: Forcing serial output ...\n");
		print_force_serial = 1;
		
	}
	
	printf("DE: Entering ...\n");
	unloading_screen();
	main();
	
	printf("ACPI: Powering off system ...\n");
	acpi_poweroff();
	
	for (;;);
	
}
