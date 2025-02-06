; expect: 0f9dc10f9dc20f9dc30f9d0425000000000f9d0425ff0000000f9d05f9ffffff0f9d05f80000000f9d05f8ff00000f9d000f9d000f9d80ffff0000410f9d87ffff00000f9d04300f9d8430ffff0000410f9d8437ffff0000420f9d8438ffff00000f9d8470f2ff0f000f9d84b0f4ff0f000f9d84f0f8ff0f000f9d84c4f8ff0f00410f9d84c7f8ff0f00420f9d84fcf8ff0f00430f9d84fef8ff0f00

bits 64

setnl cl
setnl dl
setnl bl
setnl byte [0x0]
setnl byte [0xFF]
setnl byte [rel $ + 0x0]
setnl byte [rel $ + 0xFF]
setnl byte [rel $ + 0xFFFF]
setnl byte [rax]
setnl byte [rax + 0x0]
setnl byte [rax + 0xFFFF]
setnl byte [r15 + 0xFFFF]
setnl byte [rax + rsi * 1  + 0x0]
setnl byte [rax + rsi + 0xFFFF]
setnl byte [r15 + rsi + 0xFFFF]
setnl byte [rax + r15 + 0xFFFF]
setnl byte [rax + rsi * 2 + 0xFFFF2]
setnl byte [rax + rsi * 4 + 0xFFFF4]
setnl byte [rax + rsi * 8 + 0xFFFF8]
setnl byte [rsp + rax * 8 + 0xFFFF8]
setnl byte [r15 + rax * 8 + 0xFFFF8]
setnl byte [rsp + r15 * 8 + 0xFFFF8]
setnl byte [r14 + r15 * 8 + 0xFFFF8]
