; expect: df342500000000df3425ff000000df35faffffffdf35f9000000df35f9ff0000df30df30dfb0ffff000041dfb7ffff0000df3430dfb430ffff000041dfb437ffff000042dfb438ffff0000dfb470f2ff0f00dfb4b0f4ff0f00dfb4f0f8ff0f00dfb4c4f8ff0f0041dfb4c7f8ff0f0042dfb4fcf8ff0f0043dfb4fef8ff0f00

bits 64

fbstp tword [0x0]
fbstp tword [0xFF]
fbstp tword [rel $ + 0x0]
fbstp tword [rel $ + 0xFF]
fbstp tword [rel $ + 0xFFFF]
fbstp tword [rax]
fbstp tword [rax + 0x0]
fbstp tword [rax + 0xFFFF]
fbstp tword [r15 + 0xFFFF]
fbstp tword [rax + rsi * 1  + 0x0]
fbstp tword [rax + rsi + 0xFFFF]
fbstp tword [r15 + rsi + 0xFFFF]
fbstp tword [rax + r15 + 0xFFFF]
fbstp tword [rax + rsi * 2 + 0xFFFF2]
fbstp tword [rax + rsi * 4 + 0xFFFF4]
fbstp tword [rax + rsi * 8 + 0xFFFF8]
fbstp tword [rsp + rax * 8 + 0xFFFF8]
fbstp tword [r15 + rax * 8 + 0xFFFF8]
fbstp tword [rsp + r15 * 8 + 0xFFFF8]
fbstp tword [r14 + r15 * 8 + 0xFFFF8]
