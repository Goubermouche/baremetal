; expect: 0f181425000000000f181425ff0000000f1815f9ffffff0f1815f80000000f1815f8ff00000f18100f18100f1890ffff0000410f1897ffff00000f1814300f189430ffff0000410f189437ffff0000420f189438ffff00000f189470f2ff0f000f1894b0f4ff0f000f1894f0f8ff0f000f1894c4f8ff0f00410f1894c7f8ff0f00420f1894fcf8ff0f00430f1894fef8ff0f00

bits 64

prefetcht1 [0x0]
prefetcht1 [0xFF]
prefetcht1 [rel $ + 0x0]
prefetcht1 [rel $ + 0xFF]
prefetcht1 [rel $ + 0xFFFF]
prefetcht1 [rax]
prefetcht1 [rax + 0x0]
prefetcht1 [rax + 0xFFFF]
prefetcht1 [r15 + 0xFFFF]
prefetcht1 [rax + rsi * 1  + 0x0]
prefetcht1 [rax + rsi + 0xFFFF]
prefetcht1 [r15 + rsi + 0xFFFF]
prefetcht1 [rax + r15 + 0xFFFF]
prefetcht1 [rax + rsi * 2 + 0xFFFF2]
prefetcht1 [rax + rsi * 4 + 0xFFFF4]
prefetcht1 [rax + rsi * 8 + 0xFFFF8]
prefetcht1 [rsp + rax * 8 + 0xFFFF8]
prefetcht1 [r15 + rax * 8 + 0xFFFF8]
prefetcht1 [rsp + r15 * 8 + 0xFFFF8]
prefetcht1 [r14 + r15 * 8 + 0xFFFF8]
