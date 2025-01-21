; expect: 0f9bc10f9bc20f9bc30f9b0425000000000f9b0425ff0000000f9b05f9ffffff0f9b05f80000000f9b05f8ff00000f9b000f9b000f9b80ffff0000410f9b87ffff00000f9b04300f9b8430ffff0000410f9b8437ffff0000420f9b8438ffff00000f9b8470f2ff0f000f9b84b0f4ff0f000f9b84f0f8ff0f000f9b84c4f8ff0f00410f9b84c7f8ff0f00420f9b84fcf8ff0f00430f9b84fef8ff0f00

setpo cl
setpo dl
setpo bl
setpo byte [0x0]
setpo byte [0xFF]
setpo byte [rel $ + 0x0]
setpo byte [rel $ + 0xFF]
setpo byte [rel $ + 0xFFFF]
setpo byte [rax]
setpo byte [rax + 0x0]
setpo byte [rax + 0xFFFF]
setpo byte [r15 + 0xFFFF]
setpo byte [rax + rsi * 1  + 0x0]
setpo byte [rax + rsi + 0xFFFF]
setpo byte [r15 + rsi + 0xFFFF]
setpo byte [rax + r15 + 0xFFFF]
setpo byte [rax + rsi * 2 + 0xFFFF2]
setpo byte [rax + rsi * 4 + 0xFFFF4]
setpo byte [rax + rsi * 8 + 0xFFFF8]
setpo byte [rsp + rax * 8 + 0xFFFF8]
setpo byte [r15 + rax * 8 + 0xFFFF8]
setpo byte [rsp + r15 * 8 + 0xFFFF8]
setpo byte [r14 + r15 * 8 + 0xFFFF8]