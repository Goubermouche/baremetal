; expect: f20ff0042500000000f20ff00425ff000000f20ff005f8fffffff20ff005f7000000f20ff005f7ff0000f20ff000f20ff000f20ff080ffff0000f2410ff087ffff0000f20ff00430f20ff08430ffff0000f2410ff08437ffff0000f2420ff08438ffff0000f20ff08470f2ff0f00f20ff084b0f4ff0f00f20ff084f0f8ff0f00f20ff084c4f8ff0f00f2410ff084c7f8ff0f00f2420ff084fcf8ff0f00f2430ff084fef8ff0f00f20ff00c2500000000f20ff00c25ff000000f20ff00df8fffffff20ff00df7000000f20ff00df7ff0000f20ff008f20ff008f20ff088ffff0000f2410ff08fffff0000f20ff00c30f20ff08c30ffff0000f2410ff08c37ffff0000f2420ff08c38ffff0000f20ff08c70f2ff0f00f20ff08cb0f4ff0f00f20ff08cf0f8ff0f00f20ff08cc4f8ff0f00f2410ff08cc7f8ff0f00f2420ff08cfcf8ff0f00f2430ff08cfef8ff0f00f2440ff03c2500000000f2440ff03c25ff000000f2440ff03df7fffffff2440ff03df6000000f2440ff03df6ff0000f2440ff038f2440ff038f2440ff0b8ffff0000f2450ff0bfffff0000f2440ff03c30f2440ff0bc30ffff0000f2450ff0bc37ffff0000f2460ff0bc38ffff0000f2440ff0bc70f2ff0f00f2440ff0bcb0f4ff0f00f2440ff0bcf0f8ff0f00f2440ff0bcc4f8ff0f00f2450ff0bcc7f8ff0f00f2460ff0bcfcf8ff0f00f2470ff0bcfef8ff0f00

bits 64

lddqu xmm0, [0x0]
lddqu xmm0, [0xFF]
lddqu xmm0, [rel $ + 0x0]
lddqu xmm0, [rel $ + 0xFF]
lddqu xmm0, [rel $ + 0xFFFF]
lddqu xmm0, [rax]
lddqu xmm0, [rax + 0x0]
lddqu xmm0, [rax + 0xFFFF]
lddqu xmm0, [r15 + 0xFFFF]
lddqu xmm0, [rax + rsi * 1  + 0x0]
lddqu xmm0, [rax + rsi + 0xFFFF]
lddqu xmm0, [r15 + rsi + 0xFFFF]
lddqu xmm0, [rax + r15 + 0xFFFF]
lddqu xmm0, [rax + rsi * 2 + 0xFFFF2]
lddqu xmm0, [rax + rsi * 4 + 0xFFFF4]
lddqu xmm0, [rax + rsi * 8 + 0xFFFF8]
lddqu xmm0, [rsp + rax * 8 + 0xFFFF8]
lddqu xmm0, [r15 + rax * 8 + 0xFFFF8]
lddqu xmm0, [rsp + r15 * 8 + 0xFFFF8]
lddqu xmm0, [r14 + r15 * 8 + 0xFFFF8]
lddqu xmm1, [0x0]
lddqu xmm1, [0xFF]
lddqu xmm1, [rel $ + 0x0]
lddqu xmm1, [rel $ + 0xFF]
lddqu xmm1, [rel $ + 0xFFFF]
lddqu xmm1, [rax]
lddqu xmm1, [rax + 0x0]
lddqu xmm1, [rax + 0xFFFF]
lddqu xmm1, [r15 + 0xFFFF]
lddqu xmm1, [rax + rsi * 1  + 0x0]
lddqu xmm1, [rax + rsi + 0xFFFF]
lddqu xmm1, [r15 + rsi + 0xFFFF]
lddqu xmm1, [rax + r15 + 0xFFFF]
lddqu xmm1, [rax + rsi * 2 + 0xFFFF2]
lddqu xmm1, [rax + rsi * 4 + 0xFFFF4]
lddqu xmm1, [rax + rsi * 8 + 0xFFFF8]
lddqu xmm1, [rsp + rax * 8 + 0xFFFF8]
lddqu xmm1, [r15 + rax * 8 + 0xFFFF8]
lddqu xmm1, [rsp + r15 * 8 + 0xFFFF8]
lddqu xmm1, [r14 + r15 * 8 + 0xFFFF8]
lddqu xmm15, [0x0]
lddqu xmm15, [0xFF]
lddqu xmm15, [rel $ + 0x0]
lddqu xmm15, [rel $ + 0xFF]
lddqu xmm15, [rel $ + 0xFFFF]
lddqu xmm15, [rax]
lddqu xmm15, [rax + 0x0]
lddqu xmm15, [rax + 0xFFFF]
lddqu xmm15, [r15 + 0xFFFF]
lddqu xmm15, [rax + rsi * 1  + 0x0]
lddqu xmm15, [rax + rsi + 0xFFFF]
lddqu xmm15, [r15 + rsi + 0xFFFF]
lddqu xmm15, [rax + r15 + 0xFFFF]
lddqu xmm15, [rax + rsi * 2 + 0xFFFF2]
lddqu xmm15, [rax + rsi * 4 + 0xFFFF4]
lddqu xmm15, [rax + rsi * 8 + 0xFFFF8]
lddqu xmm15, [rsp + rax * 8 + 0xFFFF8]
lddqu xmm15, [r15 + rax * 8 + 0xFFFF8]
lddqu xmm15, [rsp + r15 * 8 + 0xFFFF8]
lddqu xmm15, [r14 + r15 * 8 + 0xFFFF8]
