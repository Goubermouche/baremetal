; tests more complex jumps and labels
; expect: eb004883f8007402eb02eb094839db7502eb02eb00
bits 64

section .text

_start:
	jmp label_1

label_1:
	cmp rax, 0
	je label_2
	jmp label_3

label_2:
	jmp end

label_3:
	cmp rbx, rbx
	jne label_4
	jmp end

label_4:
	jmp end

end:
