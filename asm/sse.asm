
	bits 32

global enable_sse
enable_sse:
	mov eax, cr0
	and ax, 0xFFFB
	or ax, 2
	
	mov cr0, eax
	mov eax, cr4
	or ax, 1536
	
	mov cr0, eax
	
	ret
