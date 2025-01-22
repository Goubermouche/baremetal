; skip
; expect: c680070000000a0000000000000000000000000000000000000000
bits 64

mov byte[alphabet + rax], 0x0a

alphabet: resb 20

