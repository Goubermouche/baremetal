; expect: 0f180425000000000f180425ff0000000f1805f9ffffff0f1805f80000000f1805f8ff00000f18000f18000f1880ffff0000410f1887ffff00000f1804300f188430ffff0000410f188437ffff0000420f188438ffff00000f188470f2ff0f000f1884b0f4ff0f000f1884f0f8ff0f000f1884c4f8ff0f00410f1884c7f8ff0f00420f1884fcf8ff0f00430f1884fef8ff0f00

bits 64

prefetchnta [0x0]
prefetchnta [0xFF]
prefetchnta [rel $ + 0x0]
prefetchnta [rel $ + 0xFF]
prefetchnta [rel $ + 0xFFFF]
prefetchnta [rax]
prefetchnta [rax + 0x0]
prefetchnta [rax + 0xFFFF]
prefetchnta [r15 + 0xFFFF]
prefetchnta [rax + rsi * 1  + 0x0]
prefetchnta [rax + rsi + 0xFFFF]
prefetchnta [r15 + rsi + 0xFFFF]
prefetchnta [rax + r15 + 0xFFFF]
prefetchnta [rax + rsi * 2 + 0xFFFF2]
prefetchnta [rax + rsi * 4 + 0xFFFF4]
prefetchnta [rax + rsi * 8 + 0xFFFF8]
prefetchnta [rsp + rax * 8 + 0xFFFF8]
prefetchnta [r15 + rax * 8 + 0xFFFF8]
prefetchnta [rsp + r15 * 8 + 0xFFFF8]
prefetchnta [r14 + r15 * 8 + 0xFFFF8]
