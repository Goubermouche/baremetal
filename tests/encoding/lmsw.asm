; expect: 0f01f10f01f20f01f3410f01f70f013425000000000f013425ff0000000f0135f9ffffff0f0135f80000000f0135f8ff00000f01300f01300f01b0ffff0000410f01b7ffff00000f0134300f01b430ffff0000410f01b437ffff0000420f01b438ffff00000f01b470f2ff0f000f01b4b0f4ff0f000f01b4f0f8ff0f000f01b4c4f8ff0f00410f01b4c7f8ff0f00420f01b4fcf8ff0f00430f01b4fef8ff0f00

lmsw cx
lmsw dx
lmsw bx
lmsw r15w
lmsw word [0x0]
lmsw word [0xFF]
lmsw word [rel $ + 0x0]
lmsw word [rel $ + 0xFF]
lmsw word [rel $ + 0xFFFF]
lmsw word [rax]
lmsw word [rax + 0x0]
lmsw word [rax + 0xFFFF]
lmsw word [r15 + 0xFFFF]
lmsw word [rax + rsi * 1  + 0x0]
lmsw word [rax + rsi + 0xFFFF]
lmsw word [r15 + rsi + 0xFFFF]
lmsw word [rax + r15 + 0xFFFF]
lmsw word [rax + rsi * 2 + 0xFFFF2]
lmsw word [rax + rsi * 4 + 0xFFFF4]
lmsw word [rax + rsi * 8 + 0xFFFF8]
lmsw word [rsp + rax * 8 + 0xFFFF8]
lmsw word [r15 + rax * 8 + 0xFFFF8]
lmsw word [rsp + r15 * 8 + 0xFFFF8]
lmsw word [r14 + r15 * 8 + 0xFFFF8]