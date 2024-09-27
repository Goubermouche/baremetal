; expect: eb02eb02ebfc
bits 64

section .text

_start:
	jmp label_1

label_2:
	jmp end

label_1:
	jmp label_2

end:

