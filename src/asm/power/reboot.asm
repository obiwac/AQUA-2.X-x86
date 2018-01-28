
	bits 32

%define bit(n) (1 << n)

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

	.hang:
		hlt
		jmp .hang
