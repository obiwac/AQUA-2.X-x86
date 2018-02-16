
	bits 32

cycle:
	sti
	hlt
	cli

extern pit_uptime

global cpu_sleep
cpu_sleep:
	push ebp
	mov ebp, esp
	
	mov eax, 0
	mov ebx, pit_uptime
	
	add eax, ebx
	add eax, ebp
	
	marker:
	call cycle
	
	cmp eax, ebx
	jle marker
	
	mov esp, ebp
	pop ebp
	
	ret
