
	bits 32

global _detect_sse
_detect_sse:
	mov eax, 1
	cpuid
	test edx, 1 << 26 ; SSE2
	jz .no_sse
	
	mov eax, 1
	ret
	
	.no_sse:
		mov eax, 0
		ret

global _enable_sse
_enable_sse:
	mov eax, 0x600
	mov cr4, eax
	
	mov eax, cr0
	and eax, 0xFFFFFFFB
	or eax, 2
	mov cr0, eax
	
	ret

global _sse_memcpy
_sse_memcpy:
	mov edi, [esp + 4]
	mov esi, [esp + 8]
	
	mov ecx, [esp + 12]
	.loop:
		movdqu xmm0, [esi]
		movdqu xmm1, [esi + 0x10]
		movdqu xmm2, [esi + 0x20]
		movdqu xmm3, [esi + 0x30]
		movdqu xmm4, [esi + 0x40]
		movdqu xmm5, [esi + 0x50]
		movdqu xmm6, [esi + 0x60]
		movdqu xmm7, [esi + 0x70]
		
		movdqu [edi], xmm0
		movdqu [edi + 0x10], xmm1
		movdqu [edi + 0x20], xmm2
		movdqu [edi + 0x30], xmm3
		movdqu [edi + 0x40], xmm4
		movdqu [edi + 0x50], xmm5
		movdqu [edi + 0x60], xmm6
		movdqu [edi + 0x70], xmm7
		
		add esi, 128
		add edi, 128
		
	loop .loop
