
	bits 32

global enable_avx
enable_avx:
	;push rax
	;push rcx
	
	;xor rcx, rcx
	;xgetbv
	;or eax, 7
	;xsetbv
	
	;pop rcx
	;pop rax
	
	ret
