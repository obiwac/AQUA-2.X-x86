
	bits 32

KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)

MB_ALIGN equ 1 << 2
MB_MEMINFO equ 1 << 2

MB_MAGIC equ 0x1BADB002
MB_FLAGS equ MB_ALIGN | MB_MEMINFO
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

MB_TEXT_MODE equ 0
MB_WIDTH equ 800
MB_HEIGHT equ 600
MB_BPP equ 32

section .data
	align 0x1000
	
	retfromkernel:
		db 0xA, "|-----------------------|", 0xA, "| Returned from kernel. |", 0xA, "|-----------------------|"

section .text
	align 4
	
	dd MB_MAGIC
	dd MB_FLAGS
	dd MB_CHECKSUM
	
	times 5 dd 0
	
	dd MB_TEXT_MODE
	dd MB_WIDTH
	dd MB_HEIGHT
	dd MB_BPP
	
	extern c_main
	extern acpi_poweroff
	
	global start
	start:
		lea ecx, [start_hh]
		jmp ecx
	
	start_hh:
		mov esp, stack + 0x4000
		
		push dword ebx
		push dword eax
		
		call c_main
		call acpi_poweroff
		
		mov eax, 1
		mov ebx, retfromkernel
		int 0x80
		jmp $
		
		call hang
	
	global hang
	hang:
		cli
		
		hlt
		jmp hang

section .bss
	align 32
	
	stack:
		resb 0x4000
