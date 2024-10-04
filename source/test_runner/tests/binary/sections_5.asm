; expect: c680080000000a000000000000000000000000000000000000000000
bits 64

section .text
	mov byte[alphabet + rax], 0x0a

section .data
	alphabet: resb 20

