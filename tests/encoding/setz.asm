; expect: 0f94c10f94c20f94c30f940425000000000f940425ff0000000f9405f9ffffff0f9405f80000000f9405f8ff00000f94000f94000f9480ffff0000410f9487ffff00000f9404300f948430ffff0000410f948437ffff0000420f948438ffff00000f948470f2ff0f000f9484b0f4ff0f000f9484f0f8ff0f000f9484c4f8ff0f00410f9484c7f8ff0f00420f9484fcf8ff0f00430f9484fef8ff0f00

setz cl
setz dl
setz bl
setz byte [0x0]
setz byte [0xFF]
setz byte [rel $ + 0x0]
setz byte [rel $ + 0xFF]
setz byte [rel $ + 0xFFFF]
setz byte [rax]
setz byte [rax + 0x0]
setz byte [rax + 0xFFFF]
setz byte [r15 + 0xFFFF]
setz byte [rax + rsi * 1  + 0x0]
setz byte [rax + rsi + 0xFFFF]
setz byte [r15 + rsi + 0xFFFF]
setz byte [rax + r15 + 0xFFFF]
setz byte [rax + rsi * 2 + 0xFFFF2]
setz byte [rax + rsi * 4 + 0xFFFF4]
setz byte [rax + rsi * 8 + 0xFFFF8]
setz byte [rsp + rax * 8 + 0xFFFF8]
setz byte [r15 + rax * 8 + 0xFFFF8]
setz byte [rsp + r15 * 8 + 0xFFFF8]
setz byte [r14 + r15 * 8 + 0xFFFF8]