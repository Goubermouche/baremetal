; expect: 0f92c10f92c20f92c30f920425000000000f920425ff0000000f9205f9ffffff0f9205f80000000f9205f8ff00000f92000f92000f9280ffff0000410f9287ffff00000f9204300f928430ffff0000410f928437ffff0000420f928438ffff00000f928470f2ff0f000f9284b0f4ff0f000f9284f0f8ff0f000f9284c4f8ff0f00410f9284c7f8ff0f00420f9284fcf8ff0f00430f9284fef8ff0f00

bits 64

setnae cl
setnae dl
setnae bl
setnae byte [0x0]
setnae byte [0xFF]
setnae byte [rel $ + 0x0]
setnae byte [rel $ + 0xFF]
setnae byte [rel $ + 0xFFFF]
setnae byte [rax]
setnae byte [rax + 0x0]
setnae byte [rax + 0xFFFF]
setnae byte [r15 + 0xFFFF]
setnae byte [rax + rsi * 1  + 0x0]
setnae byte [rax + rsi + 0xFFFF]
setnae byte [r15 + rsi + 0xFFFF]
setnae byte [rax + r15 + 0xFFFF]
setnae byte [rax + rsi * 2 + 0xFFFF2]
setnae byte [rax + rsi * 4 + 0xFFFF4]
setnae byte [rax + rsi * 8 + 0xFFFF8]
setnae byte [rsp + rax * 8 + 0xFFFF8]
setnae byte [r15 + rax * 8 + 0xFFFF8]
setnae byte [rsp + r15 * 8 + 0xFFFF8]
setnae byte [r14 + r15 * 8 + 0xFFFF8]
