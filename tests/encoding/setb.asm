; expect: 0f92c10f92c20f92c30f920425000000000f920425ff0000000f9205f9ffffff0f9205f80000000f9205f8ff00000f92000f92000f9280ffff0000410f9287ffff00000f9204300f928430ffff0000410f928437ffff0000420f928438ffff00000f928470f2ff0f000f9284b0f4ff0f000f9284f0f8ff0f000f9284c4f8ff0f00410f9284c7f8ff0f00420f9284fcf8ff0f00430f9284fef8ff0f00

bits 64

setb cl
setb dl
setb bl
setb byte [0x0]
setb byte [0xFF]
setb byte [rel $ + 0x0]
setb byte [rel $ + 0xFF]
setb byte [rel $ + 0xFFFF]
setb byte [rax]
setb byte [rax + 0x0]
setb byte [rax + 0xFFFF]
setb byte [r15 + 0xFFFF]
setb byte [rax + rsi * 1  + 0x0]
setb byte [rax + rsi + 0xFFFF]
setb byte [r15 + rsi + 0xFFFF]
setb byte [rax + r15 + 0xFFFF]
setb byte [rax + rsi * 2 + 0xFFFF2]
setb byte [rax + rsi * 4 + 0xFFFF4]
setb byte [rax + rsi * 8 + 0xFFFF8]
setb byte [rsp + rax * 8 + 0xFFFF8]
setb byte [r15 + rax * 8 + 0xFFFF8]
setb byte [rsp + r15 * 8 + 0xFFFF8]
setb byte [r14 + r15 * 8 + 0xFFFF8]
