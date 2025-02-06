; expect: 0f0d0425000000000f0d0425ff0000000f0d05f9ffffff0f0d05f80000000f0d05f8ff00000f0d000f0d000f0d80ffff0000410f0d87ffff00000f0d04300f0d8430ffff0000410f0d8437ffff0000420f0d8438ffff00000f0d8470f2ff0f000f0d84b0f4ff0f000f0d84f0f8ff0f000f0d84c4f8ff0f00410f0d84c7f8ff0f00420f0d84fcf8ff0f00430f0d84fef8ff0f00

bits 64

prefetch [0x0]
prefetch [0xFF]
prefetch [rel $ + 0x0]
prefetch [rel $ + 0xFF]
prefetch [rel $ + 0xFFFF]
prefetch [rax]
prefetch [rax + 0x0]
prefetch [rax + 0xFFFF]
prefetch [r15 + 0xFFFF]
prefetch [rax + rsi * 1  + 0x0]
prefetch [rax + rsi + 0xFFFF]
prefetch [r15 + rsi + 0xFFFF]
prefetch [rax + r15 + 0xFFFF]
prefetch [rax + rsi * 2 + 0xFFFF2]
prefetch [rax + rsi * 4 + 0xFFFF4]
prefetch [rax + rsi * 8 + 0xFFFF8]
prefetch [rsp + rax * 8 + 0xFFFF8]
prefetch [r15 + rax * 8 + 0xFFFF8]
prefetch [rsp + r15 * 8 + 0xFFFF8]
prefetch [r14 + r15 * 8 + 0xFFFF8]
