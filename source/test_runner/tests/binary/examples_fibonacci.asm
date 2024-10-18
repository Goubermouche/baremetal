; source: https://rosettacode.org/wiki/Anonymous_recursion 
; expect: b930000000bb3000000029cb5368490000005589e55331c0678b5d0883fb017c23b801000000741cffcb53e8e2ffffff67890424ffcb53e8d6ffffff670344240483c4085b89ec5dc367890c2450e80f00000083c40459e2acb80100000031dbcd805589e583ec0b678d4dff67c6010a678b4508bb0a000000ffc931d2f7f380c23067881183f8007fefb804000000bb0100000089ea29cacd8089ec5dc3
bits 64

; global  _start
section .text

_start:
	mov ecx, 48
.loop:
	mov ebx, 48
	sub ebx, ecx
	push rbx 
	push .done
.fib:
	push rbp
	mov ebp, esp
	push rbx 
	xor eax, eax
	mov ebx, dword [ebp + 8]
	cmp ebx, 1 
	jl .return
	mov eax, 1
	je .return
	dec ebx
	push rbx
	call .fib
	mov dword [esp], eax 
	dec ebx
	push rbx
	call .fib
	add eax, dword [esp + 4]
	add esp, 8
.return:
	pop rbx
	mov esp, ebp
	pop rbp
	ret
.done:
	mov dword [esp], ecx
	push rax
	call .print_num
	add esp, 4
	pop rcx 
	loop .loop
	mov eax, 0x01
	xor ebx, ebx
	int 0x80 
.print_num:
	push rbp
	mov ebp, esp
	sub esp, 11
	lea ecx, [ebp - 1]
	mov byte [ecx], 0x0A
	mov eax, dword [ebp + 8]
	mov ebx, 10
.loop2:
	dec ecx
	xor edx, edx
	div ebx
	add dl, 0x30 
	mov byte [ecx], dl
	cmp eax, 0 
	jg .loop2
	mov eax, 0x04
	mov ebx, 1
	mov edx, ebp
	sub edx, ecx 
	int 0x80
	mov esp, ebp
	pop rbp
	ret
