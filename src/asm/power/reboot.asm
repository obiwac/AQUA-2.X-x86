
	bits 32

%define bit(n) (1 << n)

;~ 1) Try an ACPI reset.
;~ 2) Try a PS/2 reset.
;~ 3) Try a port 0x92 reset (outb(0x92, 0x01))
;~ 4) Triple fault.

global power_reboot
power_reboot:
	cli
	
	.loop:
		in al, 0x64
		and al, [bit(0)]
		
		cmp al, 0
		je .loop
		
		in al, 0x60
		
		in al, 0x64
		and al, [bit(1)]
		
		cmp al, 0
		je .loop
	
	mov eax, 0xFE
	out 0x64, eax
	
	.loop2:
		in al, 0x64
		test al, 0b00000010
		jne .loop2
	
	mov eax, 0xFE
	out 0x64, eax
	
	mov eax, 0x01
	out 0x92, eax
	
	.loop3:
		int 0x80
		jmp .loop3
	
	.hang:
		hlt
		jmp .hang
