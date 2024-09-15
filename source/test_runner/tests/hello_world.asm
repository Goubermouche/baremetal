bits 64

section .data
	msg db "Hello world!", 0ah

section .text
	global _start

_start:
	mov rax, 1
