; test parser edge cases (trailing comments) 
; expect: 010f05881c25000000004489fb8a0c250000000062f1859a5810

bits 64                                ; comment
                                       ; comment
msg db 1                               ; comment
syscall                                ; comment
mov byte [0x0], bl                     ; comment
mov ebx, r15d                          ; comment
mov cl, byte [0x0]                     ; comment
vaddpd xmm2{k2}{z}, xmm15, [rax]{1to2} ; comment

