; expect: 0f99c10f99c20f99c30f990425000000000f990425ff0000000f9905f9ffffff0f9905f80000000f9905f8ff00000f99000f99000f9980ffff0000410f9987ffff00000f9904300f998430ffff0000410f998437ffff0000420f998438ffff00000f998470f2ff0f000f9984b0f4ff0f000f9984f0f8ff0f000f9984c4f8ff0f00410f9984c7f8ff0f00420f9984fcf8ff0f00430f9984fef8ff0f00

setns cl
setns dl
setns bl
setns byte [0x0]
setns byte [0xFF]
setns byte [rel $ + 0x0]
setns byte [rel $ + 0xFF]
setns byte [rel $ + 0xFFFF]
setns byte [rax]
setns byte [rax + 0x0]
setns byte [rax + 0xFFFF]
setns byte [r15 + 0xFFFF]
setns byte [rax + rsi * 1  + 0x0]
setns byte [rax + rsi + 0xFFFF]
setns byte [r15 + rsi + 0xFFFF]
setns byte [rax + r15 + 0xFFFF]
setns byte [rax + rsi * 2 + 0xFFFF2]
setns byte [rax + rsi * 4 + 0xFFFF4]
setns byte [rax + rsi * 8 + 0xFFFF8]
setns byte [rsp + rax * 8 + 0xFFFF8]
setns byte [r15 + rax * 8 + 0xFFFF8]
setns byte [rsp + r15 * 8 + 0xFFFF8]
setns byte [r14 + r15 * 8 + 0xFFFF8]