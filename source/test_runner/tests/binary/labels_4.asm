;
;

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
