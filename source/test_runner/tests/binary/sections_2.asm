; expect: 48b8240000000000000048b81400000000000000630000006148b818000000000000000062
bits 64

section .custom
	data2 db "a"

section .custom
	mov rax, data2

section .data
	data0 db "b"

section .text
	mov rax, data0
	mov rax, data1

section .text
	data1 db "c"

