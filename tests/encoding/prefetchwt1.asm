; expect: 0f0d1425000000000f0d1425ff0000000f0d15f9ffffff0f0d15f80000000f0d15f8ff00000f0d100f0d100f0d90ffff0000410f0d97ffff00000f0d14300f0d9430ffff0000410f0d9437ffff0000420f0d9438ffff00000f0d9470f2ff0f000f0d94b0f4ff0f000f0d94f0f8ff0f000f0d94c4f8ff0f00410f0d94c7f8ff0f00420f0d94fcf8ff0f00430f0d94fef8ff0f00

bits 64

prefetchwt1 [0x0]
prefetchwt1 [0xFF]
prefetchwt1 [rel $ + 0x0]
prefetchwt1 [rel $ + 0xFF]
prefetchwt1 [rel $ + 0xFFFF]
prefetchwt1 [rax]
prefetchwt1 [rax + 0x0]
prefetchwt1 [rax + 0xFFFF]
prefetchwt1 [r15 + 0xFFFF]
prefetchwt1 [rax + rsi * 1  + 0x0]
prefetchwt1 [rax + rsi + 0xFFFF]
prefetchwt1 [r15 + rsi + 0xFFFF]
prefetchwt1 [rax + r15 + 0xFFFF]
prefetchwt1 [rax + rsi * 2 + 0xFFFF2]
prefetchwt1 [rax + rsi * 4 + 0xFFFF4]
prefetchwt1 [rax + rsi * 8 + 0xFFFF8]
prefetchwt1 [rsp + rax * 8 + 0xFFFF8]
prefetchwt1 [r15 + rax * 8 + 0xFFFF8]
prefetchwt1 [rsp + r15 * 8 + 0xFFFF8]
prefetchwt1 [r14 + r15 * 8 + 0xFFFF8]
