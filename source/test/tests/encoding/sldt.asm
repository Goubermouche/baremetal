; expect: 0f000425000000000f000425ff0000000f0005f9ffffff0f0005f80000000f0005f8ff00000f00000f00000f0080ffff0000410f0087ffff00000f0004300f008430ffff0000410f008437ffff0000420f008438ffff00000f008470f2ff0f000f0084b0f4ff0f000f0084f0f8ff0f000f0084c4f8ff0f00410f0084c7f8ff0f00420f0084fcf8ff0f00430f0084fef8ff0f00660f00c1660f00c2660f00c366410f00c70f00c10f00c3410f00c70f00c10f00c3410f00c7

sldt word [0x0]
sldt word [0xFF]
sldt word [rel $ + 0x0]
sldt word [rel $ + 0xFF]
sldt word [rel $ + 0xFFFF]
sldt word [rax]
sldt word [rax + 0x0]
sldt word [rax + 0xFFFF]
sldt word [r15 + 0xFFFF]
sldt word [rax + rsi * 1  + 0x0]
sldt word [rax + rsi + 0xFFFF]
sldt word [r15 + rsi + 0xFFFF]
sldt word [rax + r15 + 0xFFFF]
sldt word [rax + rsi * 2 + 0xFFFF2]
sldt word [rax + rsi * 4 + 0xFFFF4]
sldt word [rax + rsi * 8 + 0xFFFF8]
sldt word [rsp + rax * 8 + 0xFFFF8]
sldt word [r15 + rax * 8 + 0xFFFF8]
sldt word [rsp + r15 * 8 + 0xFFFF8]
sldt word [r14 + r15 * 8 + 0xFFFF8]
sldt cx
sldt dx
sldt bx
sldt r15w
sldt ecx
sldt ebx
sldt r15d
sldt rcx
sldt rbx
sldt r15