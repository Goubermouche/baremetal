; expect: 0f1c0425000000000f1c0425ff0000000f1c05f9ffffff0f1c05f80000000f1c05f8ff00000f1c000f1c000f1c80ffff0000410f1c87ffff00000f1c04300f1c8430ffff0000410f1c8437ffff0000420f1c8438ffff00000f1c8470f2ff0f000f1c84b0f4ff0f000f1c84f0f8ff0f000f1c84c4f8ff0f00410f1c84c7f8ff0f00420f1c84fcf8ff0f00430f1c84fef8ff0f00

bits 64

cldemote [0x0]
cldemote [0xFF]
cldemote [rel $ + 0x0]
cldemote [rel $ + 0xFF]
cldemote [rel $ + 0xFFFF]
cldemote [rax]
cldemote [rax + 0x0]
cldemote [rax + 0xFFFF]
cldemote [r15 + 0xFFFF]
cldemote [rax + rsi * 1  + 0x0]
cldemote [rax + rsi + 0xFFFF]
cldemote [r15 + rsi + 0xFFFF]
cldemote [rax + r15 + 0xFFFF]
cldemote [rax + rsi * 2 + 0xFFFF2]
cldemote [rax + rsi * 4 + 0xFFFF4]
cldemote [rax + rsi * 8 + 0xFFFF8]
cldemote [rsp + rax * 8 + 0xFFFF8]
cldemote [r15 + rax * 8 + 0xFFFF8]
cldemote [rsp + r15 * 8 + 0xFFFF8]
cldemote [r14 + r15 * 8 + 0xFFFF8]
