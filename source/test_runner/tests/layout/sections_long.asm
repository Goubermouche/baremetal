; tests more complex section layouts
; expect: b804000000bb01000000b920000000ba0d000000cd80b80100000031dbcd800048656c6c6f2c20576f726c642100010203341278563412f0debc9a78563412010203040501000000020000000300000004000000
bits 64

section .data
	msg db "Hello, World!", 0
	num db 0x01, 0x02, 0x03
	word_val dw 0x1234
	dword_val dd 0x12345678
	qword_val dq 0x123456789ABCDEF0
	array db 1, 2, 3, 4, 5
	matrix dd 1, 2, 3, 4

section .bss
	buffer resb 64
	word_buffer resw 4
	dword_buffer resd 4
	qword_buffer resq 4

section .text
	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, 13
	int 0x80
	
	mov eax, 1
	xor ebx, ebx
	int 0x80

