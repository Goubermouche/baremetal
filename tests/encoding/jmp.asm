; expect: ebfeebffe97bffffffeb7de9f0ffffffe9ecffffffe966ffffffe960000000ffe1ffe341ffe7ff242500000000ff2425ff000000ff25faffffffff25f9000000ff25f9ff0000ff20ff20ffa0ffff000041ffa7ffff0000ff2430ffa430ffff000041ffa437ffff000042ffa438ffff0000ffa470f2ff0f00ffa4b0f4ff0f00ffa4f0f8ff0f00ffa4c4f8ff0f0041ffa4c7f8ff0f0042ffa4fcf8ff0f0043ffa4fef8ff0f00

bits 64

jmp $+0
jmp $+1
jmp $+-128
jmp $+127
jmp 0
jmp 1
jmp -128
jmp 127
jmp rcx
jmp rbx
jmp r15
jmp qword [0x0]
jmp qword [0xFF]
jmp qword [rel $ + 0x0]
jmp qword [rel $ + 0xFF]
jmp qword [rel $ + 0xFFFF]
jmp qword [rax]
jmp qword [rax + 0x0]
jmp qword [rax + 0xFFFF]
jmp qword [r15 + 0xFFFF]
jmp qword [rax + rsi * 1  + 0x0]
jmp qword [rax + rsi + 0xFFFF]
jmp qword [r15 + rsi + 0xFFFF]
jmp qword [rax + r15 + 0xFFFF]
jmp qword [rax + rsi * 2 + 0xFFFF2]
jmp qword [rax + rsi * 4 + 0xFFFF4]
jmp qword [rax + rsi * 8 + 0xFFFF8]
jmp qword [rsp + rax * 8 + 0xFFFF8]
jmp qword [r15 + rax * 8 + 0xFFFF8]
jmp qword [rsp + r15 * 8 + 0xFFFF8]
jmp qword [r14 + r15 * 8 + 0xFFFF8]
