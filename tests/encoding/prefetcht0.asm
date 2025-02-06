; expect: 0f180c25000000000f180c25ff0000000f180df9ffffff0f180df80000000f180df8ff00000f18080f18080f1888ffff0000410f188fffff00000f180c300f188c30ffff0000410f188c37ffff0000420f188c38ffff00000f188c70f2ff0f000f188cb0f4ff0f000f188cf0f8ff0f000f188cc4f8ff0f00410f188cc7f8ff0f00420f188cfcf8ff0f00430f188cfef8ff0f00

bits 64

prefetcht0 [0x0]
prefetcht0 [0xFF]
prefetcht0 [rel $ + 0x0]
prefetcht0 [rel $ + 0xFF]
prefetcht0 [rel $ + 0xFFFF]
prefetcht0 [rax]
prefetcht0 [rax + 0x0]
prefetcht0 [rax + 0xFFFF]
prefetcht0 [r15 + 0xFFFF]
prefetcht0 [rax + rsi * 1  + 0x0]
prefetcht0 [rax + rsi + 0xFFFF]
prefetcht0 [r15 + rsi + 0xFFFF]
prefetcht0 [rax + r15 + 0xFFFF]
prefetcht0 [rax + rsi * 2 + 0xFFFF2]
prefetcht0 [rax + rsi * 4 + 0xFFFF4]
prefetcht0 [rax + rsi * 8 + 0xFFFF8]
prefetcht0 [rsp + rax * 8 + 0xFFFF8]
prefetcht0 [r15 + rax * 8 + 0xFFFF8]
prefetcht0 [rsp + r15 * 8 + 0xFFFF8]
prefetcht0 [r14 + r15 * 8 + 0xFFFF8]
