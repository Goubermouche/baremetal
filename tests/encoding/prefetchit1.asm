; expect: 0f183425000000000f183425ff0000000f1835f9ffffff0f1835f80000000f1835f8ff00000f18300f18300f18b0ffff0000410f18b7ffff00000f1834300f18b430ffff0000410f18b437ffff0000420f18b438ffff00000f18b470f2ff0f000f18b4b0f4ff0f000f18b4f0f8ff0f000f18b4c4f8ff0f00410f18b4c7f8ff0f00420f18b4fcf8ff0f00430f18b4fef8ff0f00

bits 64

prefetchit1 [0x0]
prefetchit1 [0xFF]
prefetchit1 [rel $ + 0x0]
prefetchit1 [rel $ + 0xFF]
prefetchit1 [rel $ + 0xFFFF]
prefetchit1 [rax]
prefetchit1 [rax + 0x0]
prefetchit1 [rax + 0xFFFF]
prefetchit1 [r15 + 0xFFFF]
prefetchit1 [rax + rsi * 1  + 0x0]
prefetchit1 [rax + rsi + 0xFFFF]
prefetchit1 [r15 + rsi + 0xFFFF]
prefetchit1 [rax + r15 + 0xFFFF]
prefetchit1 [rax + rsi * 2 + 0xFFFF2]
prefetchit1 [rax + rsi * 4 + 0xFFFF4]
prefetchit1 [rax + rsi * 8 + 0xFFFF8]
prefetchit1 [rsp + rax * 8 + 0xFFFF8]
prefetchit1 [r15 + rax * 8 + 0xFFFF8]
prefetchit1 [rsp + r15 * 8 + 0xFFFF8]
prefetchit1 [r14 + r15 * 8 + 0xFFFF8]
