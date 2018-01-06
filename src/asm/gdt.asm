
	bits 32

extern gdt_ptr

global gdt_flush
gdt_flush:
	cli
	lgdt [gdt_ptr]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x08:flush2

flush2:
	ret
