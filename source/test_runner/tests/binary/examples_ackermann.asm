; source: https://rosettacode.org/wiki/Ackermann_function
; expect: b803000000bb04000000e801000000c383f800741683fb007414ffcb50e8eeffffff58ffc8e8e6ffffffc3ffc3c3ffc8ffc3e8d9ffffffc3
bits 64

section .text

; global _main
_main:
	mov eax, 3
	mov ebx, 4
	call ack
	ret
ack:
	cmp eax, 0
	je M0 
	cmp ebx, 0
	je N0 
	dec ebx
	push rax 
	call ack
	pop rax
	dec eax
	call ack
	ret
M0:
	inc ebx
	ret
N0:
	dec eax
	inc ebx 
	call ack
	ret
