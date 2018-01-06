
ENTRY(start)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS {
	. = 0xC000000;
	krnlstart = .;
	
	.text : AT(ADDR(.text) - 0x00000000) {
		*(.text)
		
	}
	
	.data : AT(ADDR(.data) - 0x00000000) {
		start_ctors = .;
		KEEP(*(.init_array));
		KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)));
		end_ctors = .;
		
		*(.data)
		
	}
	
	.bss : AT(ADDR(.bss) - 0x00000000) {
		*(.COMMON)
		*(.bss)
		
	}
	
	end = .;
	_end = .;
	__end = .;
	
	/DISCARD/ : {
		*(.fini_array*)
		*(.comment)
		
	}
	
}
