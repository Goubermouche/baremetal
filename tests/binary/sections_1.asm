; expect: 78ff0f48b8180000000000000048b800000000000000000078ff0f0078ff0f48b81c00000000000000
bits 64

section .data
	data0 db 120, 0xff, 0b1111

section .text
	data1 db 120, 0xff, 0b1111

section .custom
	data2 db 120, 0xff, 0b1111

section .text
	mov rax, data0
	mov rax, data1

section .custom
	mov rax, data2

