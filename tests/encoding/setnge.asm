; expect: 0f9cc10f9cc20f9cc30f9c0425000000000f9c0425ff0000000f9c05f9ffffff0f9c05f80000000f9c05f8ff00000f9c000f9c000f9c80ffff0000410f9c87ffff00000f9c04300f9c8430ffff0000410f9c8437ffff0000420f9c8438ffff00000f9c8470f2ff0f000f9c84b0f4ff0f000f9c84f0f8ff0f000f9c84c4f8ff0f00410f9c84c7f8ff0f00420f9c84fcf8ff0f00430f9c84fef8ff0f00

bits 64

setnge cl
setnge dl
setnge bl
setnge byte [0x0]
setnge byte [0xFF]
setnge byte [rel $ + 0x0]
setnge byte [rel $ + 0xFF]
setnge byte [rel $ + 0xFFFF]
setnge byte [rax]
setnge byte [rax + 0x0]
setnge byte [rax + 0xFFFF]
setnge byte [r15 + 0xFFFF]
setnge byte [rax + rsi * 1  + 0x0]
setnge byte [rax + rsi + 0xFFFF]
setnge byte [r15 + rsi + 0xFFFF]
setnge byte [rax + r15 + 0xFFFF]
setnge byte [rax + rsi * 2 + 0xFFFF2]
setnge byte [rax + rsi * 4 + 0xFFFF4]
setnge byte [rax + rsi * 8 + 0xFFFF8]
setnge byte [rsp + rax * 8 + 0xFFFF8]
setnge byte [r15 + rax * 8 + 0xFFFF8]
setnge byte [rsp + r15 * 8 + 0xFFFF8]
setnge byte [r14 + r15 * 8 + 0xFFFF8]
