; 
; expect: e9030000000000007402eb02eb067502eb02eb000f84e6ffffff

bits 64

section .text

_start:
	jmp label_1

section .data

label_1:
	je label_2
	jmp label_3

label_2:
	jmp end

label_3:
	jne label_4
	jmp end

label_4:
	jmp end

end:
	je _start
