
#include "parse_mboot.h"

void parse_mboot(uint32_t magic, uint32_t address) {
	printf("GRUB: Parsing multiboot 2 information structure ...\n");
	
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		printf_error("ERROR invalid magic number: 0x%x\n", (uint32_t) magic);
		while (1);
		
	}
	
	multiboot_info_t* mbi = (multiboot_info_t*) address;
	printf("GRUB: flags = 0x%x\n", (uint32_t) mbi->flags);
	
	if (CHECK_FLAG(mbi->flags, 0)) {
		printf("\tGRUB: mem_lower = %uKB, mem_upper = %uKB\n", (uint32_t) mbi->mem_lower, (uint32_t) mbi->mem_upper);
		
	} if (CHECK_FLAG(mbi->flags, 1)) {
		printf("\tGRUB: boot_device = 0x%x\n", mbi->boot_device);
		
	} if (CHECK_FLAG(mbi->flags, 2)) {
		printf("\tGRUB: cmdline = %s\n", (char*) mbi->cmdline);
		
	} if (CHECK_FLAG(mbi->flags, 3)) {
		multiboot_module_t* mod;
		printf("\tGRUB: mods_count = %d, mods_addr = 0x%x\n", (int) mbi->mods_count, (int) mbi->mods_addr);
		
		int i;
		for (i = 0, mod = (multiboot_module_t*) mbi->mods_addr; i < mbi->mods_count; i++, mod++) {
			printf_minor("\t\tmod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n", (uint32_t) mod->mod_start, (uint32_t) mod->mod_end, (char*) mod->cmdline);
			
		}
		
	} if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5)) {
		printf_error("\tGRUB ERROR: Both bits 4 and 5 are set.\n");
		while (1);
		
	} if (CHECK_FLAG(mbi->flags, 4)) {
		multiboot_aout_symbol_table_t* multiboot_aout_sym = &(mbi->u.aout_sym);
		printf("\tGRUB: multiboot_aout_symbol_table: tabsize = 0x%x, strsize = 0x%x, addr = 0x%x\n", (uint32_t) multiboot_aout_sym->tabsize, (uint32_t) multiboot_aout_sym->strsize, (uint32_t) multiboot_aout_sym->addr);
		
	} if (CHECK_FLAG(mbi->flags, 5)) {
		multiboot_elf_section_header_table_t* multiboot_elf_sec = &(mbi->u.elf_sec);
		printf("\tGRUB: multiboot_elf_sec: num = %d, size = 0x%x, addr = 0x%x, shndx = 0x%x\n", (uint32_t) multiboot_elf_sec->num, (uint32_t) multiboot_elf_sec->size,(uint32_t) multiboot_elf_sec->addr, (uint32_t) multiboot_elf_sec->shndx);
		
	} if (CHECK_FLAG(mbi->flags, 6)) {
		multiboot_memory_map_t* mmap;
		printf("\tGRUB: mmap_addr = 0x%x, mmap_length = 0x%x\n", mbi->mmap_addr, mbi->mmap_length);
		
		for (mmap = (multiboot_memory_map_t*) mbi->mmap_addr; (uint32_t) mmap < mbi->mmap_addr + mbi->mmap_length; mmap = (multiboot_memory_map_t*) ((uint32_t) mmap + mmap->size + sizeof(mmap->size))) {
			printf_minor("\t\tsize = 0x%x, base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n", (uint32_t) mmap->size, mmap->addr >> 32, mmap->addr & 0xFFFFFFFF, mmap->len >> 32, mmap->len & 0xFFFFFFFF, (uint32_t) mmap->type);
			
		}
		
	}
	
	video_width = mbi->framebuffer_width;
	video_height = mbi->framebuffer_height;
	video_bpp = mbi->framebuffer_bpp;
	video_cpc = video_bpp / BITS_PER_COMPONENT;
	
	video_addr = mbi->framebuffer_addr;
	video_type = mbi->framebuffer_type;
	
	printf("Graphics: width = %d, height = %d, bpp = %d, addr = 0x%x, type = %s\n", video_width, video_height, video_bpp, video_addr, video_type ? "text" : "graphics");
	
}
