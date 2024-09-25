; expect: 909090b80a000000b80a000000b80a0000002a2a2a
bits 64

times 3 nop
times 3 mov rax, 10
times 3 db 42

