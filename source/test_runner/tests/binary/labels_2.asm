; tests more complex jumps and labels
; expect: eb004883f8007402eb02eb094839db7502eb02eb00
bits 64

_start:
	jmp label_1
	times 140 nop

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
