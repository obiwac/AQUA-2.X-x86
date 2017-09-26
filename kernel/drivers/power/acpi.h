
#ifndef __AQUA__DRIVERS_ACPI_H
	#define __AQUA__DRIVERS_ACPI_H
	
	#include "apm.h"
	#include "../../types.h"
	#include "../../common/extern.h"
	#include "../../io/ports.h"
	#include "../../common/print.h"
	#include "../../time/sleep.h"
	#include "../../memory/memcmp.h"
	
	struct acpi_rsd_ptr_t {
		uint8_t signature[8];
		uint8_t check_sum;
		
		uint8_t oem_id[4];
		uint8_t revision;
		
		uint32_t* rsdt_addr;
		
	};
	
	struct acpi_facp_t {
		uint8_t signature[4];
		uint32_t length;
		
		uint8_t reserved1[32];
		uint32_t* dsdt;
		
		uint8_t reserved2[4];
		uint32_t* smi_cmd;
		
		uint8_t enable;
		uint8_t disable;
		uint8_t reserved3[10];
		
		uint32_t* pm1a_cnt_blk;
		uint32_t* pm1b_cnt_blk;
		
		uint8_t reserved4[17];
		uint8_t pm1_cnt_len;
		
	};
	
	uint32_t* acpi_check_rsd_ptr(uint32_t* ptr);
	uint32_t* acpi_get_rsd_ptr(void);
	int acpi_check_header(uint32_t* ptr, char* signature);
	
	int acpi_enable(void);
	int acpi_init(void);
	
	void acpi_poweroff(void);
	void acpi_reboot(void);
	
#endif
