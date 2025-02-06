; expect: 0f9ac10f9ac20f9ac30f9a0425000000000f9a0425ff0000000f9a05f9ffffff0f9a05f80000000f9a05f8ff00000f9a000f9a000f9a80ffff0000410f9a87ffff00000f9a04300f9a8430ffff0000410f9a8437ffff0000420f9a8438ffff00000f9a8470f2ff0f000f9a84b0f4ff0f000f9a84f0f8ff0f000f9a84c4f8ff0f00410f9a84c7f8ff0f00420f9a84fcf8ff0f00430f9a84fef8ff0f00

bits 64

setpe cl
setpe dl
setpe bl
setpe byte [0x0]
setpe byte [0xFF]
setpe byte [rel $ + 0x0]
setpe byte [rel $ + 0xFF]
setpe byte [rel $ + 0xFFFF]
setpe byte [rax]
setpe byte [rax + 0x0]
setpe byte [rax + 0xFFFF]
setpe byte [r15 + 0xFFFF]
setpe byte [rax + rsi * 1  + 0x0]
setpe byte [rax + rsi + 0xFFFF]
setpe byte [r15 + rsi + 0xFFFF]
setpe byte [rax + r15 + 0xFFFF]
setpe byte [rax + rsi * 2 + 0xFFFF2]
setpe byte [rax + rsi * 4 + 0xFFFF4]
setpe byte [rax + rsi * 8 + 0xFFFF8]
setpe byte [rsp + rax * 8 + 0xFFFF8]
setpe byte [r15 + rax * 8 + 0xFFFF8]
setpe byte [rsp + r15 * 8 + 0xFFFF8]
setpe byte [r14 + r15 * 8 + 0xFFFF8]
