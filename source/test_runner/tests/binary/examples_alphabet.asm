; source: https://rosettacode.org/wiki/Generate_lower_case_ASCII_alphabet
; expect: 4831c040b7614000c74088b84800000048ffc04883f81a7ceac680480000000ab801000000bf0100000048be4800000000000000ba1b0000000f05b83c0000004831ff0f05
bits 64

section .text
_start:
	xor  rax, rax
.loop:
	mov dil, 'a'
	add dil, al
	mov byte[alphabet + rax], dil
	inc rax
	cmp rax, 26
	jl .loop
.print:
	mov byte[alphabet + rax], 0x0a 
	mov rax, 1
	mov rdi, 1
	mov rsi, alphabet
	mov rdx, 27
	syscall
.exit:
	mov rax, 60
	xor rdi, rdi
	syscall
section .bss
alphabet: resb 27

