
	bits 32

global io_wait
io_wait:
	mov eax, 0
	out 0x80, eax
