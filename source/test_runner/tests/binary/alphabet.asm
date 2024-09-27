; expect: ff

section .text
_start:
	xor  rax, rax
.loop:
	mov dil, 'a'
	add dil, al
	;mov  byte[alphabet + rax], dil
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

