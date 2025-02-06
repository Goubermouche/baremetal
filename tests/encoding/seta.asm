; expect: 0f97c10f97c20f97c30f970425000000000f970425ff0000000f9705f9ffffff0f9705f80000000f9705f8ff00000f97000f97000f9780ffff0000410f9787ffff00000f9704300f978430ffff0000410f978437ffff0000420f978438ffff00000f978470f2ff0f000f9784b0f4ff0f000f9784f0f8ff0f000f9784c4f8ff0f00410f9784c7f8ff0f00420f9784fcf8ff0f00430f9784fef8ff0f00

bits 64

seta cl
seta dl
seta bl
seta byte [0x0]
seta byte [0xFF]
seta byte [rel $ + 0x0]
seta byte [rel $ + 0xFF]
seta byte [rel $ + 0xFFFF]
seta byte [rax]
seta byte [rax + 0x0]
seta byte [rax + 0xFFFF]
seta byte [r15 + 0xFFFF]
seta byte [rax + rsi * 1  + 0x0]
seta byte [rax + rsi + 0xFFFF]
seta byte [r15 + rsi + 0xFFFF]
seta byte [rax + r15 + 0xFFFF]
seta byte [rax + rsi * 2 + 0xFFFF2]
seta byte [rax + rsi * 4 + 0xFFFF4]
seta byte [rax + rsi * 8 + 0xFFFF8]
seta byte [rsp + rax * 8 + 0xFFFF8]
seta byte [r15 + rax * 8 + 0xFFFF8]
seta byte [rsp + r15 * 8 + 0xFFFF8]
seta byte [r14 + r15 * 8 + 0xFFFF8]
