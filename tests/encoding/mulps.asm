; expect: 0f59c00f59c1410f59c70f59c80f59c9410f59cf440f59f8440f59f9450f59ff0f590425000000000f590425ff0000000f5905f9ffffff0f5905f80000000f5905f8ff00000f59000f59000f5980ffff0000410f5987ffff00000f5904300f598430ffff0000410f598437ffff0000420f598438ffff00000f598470f2ff0f000f5984b0f4ff0f000f5984f0f8ff0f000f5984c4f8ff0f00410f5984c7f8ff0f00420f5984fcf8ff0f00430f5984fef8ff0f000f590c25000000000f590c25ff0000000f590df9ffffff0f590df80000000f590df8ff00000f59080f59080f5988ffff0000410f598fffff00000f590c300f598c30ffff0000410f598c37ffff0000420f598c38ffff00000f598c70f2ff0f000f598cb0f4ff0f000f598cf0f8ff0f000f598cc4f8ff0f00410f598cc7f8ff0f00420f598cfcf8ff0f00430f598cfef8ff0f00440f593c2500000000440f593c25ff000000440f593df8ffffff440f593df7000000440f593df7ff0000440f5938440f5938440f59b8ffff0000450f59bfffff0000440f593c30440f59bc30ffff0000450f59bc37ffff0000460f59bc38ffff0000440f59bc70f2ff0f00440f59bcb0f4ff0f00440f59bcf0f8ff0f00440f59bcc4f8ff0f00450f59bcc7f8ff0f00460f59bcfcf8ff0f00470f59bcfef8ff0f00

bits 64

mulps xmm0, xmm0
mulps xmm0, xmm1
mulps xmm0, xmm15
mulps xmm1, xmm0
mulps xmm1, xmm1
mulps xmm1, xmm15
mulps xmm15, xmm0
mulps xmm15, xmm1
mulps xmm15, xmm15
mulps xmm0, [0x0]
mulps xmm0, [0xFF]
mulps xmm0, [rel $ + 0x0]
mulps xmm0, [rel $ + 0xFF]
mulps xmm0, [rel $ + 0xFFFF]
mulps xmm0, [rax]
mulps xmm0, [rax + 0x0]
mulps xmm0, [rax + 0xFFFF]
mulps xmm0, [r15 + 0xFFFF]
mulps xmm0, [rax + rsi * 1  + 0x0]
mulps xmm0, [rax + rsi + 0xFFFF]
mulps xmm0, [r15 + rsi + 0xFFFF]
mulps xmm0, [rax + r15 + 0xFFFF]
mulps xmm0, [rax + rsi * 2 + 0xFFFF2]
mulps xmm0, [rax + rsi * 4 + 0xFFFF4]
mulps xmm0, [rax + rsi * 8 + 0xFFFF8]
mulps xmm0, [rsp + rax * 8 + 0xFFFF8]
mulps xmm0, [r15 + rax * 8 + 0xFFFF8]
mulps xmm0, [rsp + r15 * 8 + 0xFFFF8]
mulps xmm0, [r14 + r15 * 8 + 0xFFFF8]
mulps xmm1, [0x0]
mulps xmm1, [0xFF]
mulps xmm1, [rel $ + 0x0]
mulps xmm1, [rel $ + 0xFF]
mulps xmm1, [rel $ + 0xFFFF]
mulps xmm1, [rax]
mulps xmm1, [rax + 0x0]
mulps xmm1, [rax + 0xFFFF]
mulps xmm1, [r15 + 0xFFFF]
mulps xmm1, [rax + rsi * 1  + 0x0]
mulps xmm1, [rax + rsi + 0xFFFF]
mulps xmm1, [r15 + rsi + 0xFFFF]
mulps xmm1, [rax + r15 + 0xFFFF]
mulps xmm1, [rax + rsi * 2 + 0xFFFF2]
mulps xmm1, [rax + rsi * 4 + 0xFFFF4]
mulps xmm1, [rax + rsi * 8 + 0xFFFF8]
mulps xmm1, [rsp + rax * 8 + 0xFFFF8]
mulps xmm1, [r15 + rax * 8 + 0xFFFF8]
mulps xmm1, [rsp + r15 * 8 + 0xFFFF8]
mulps xmm1, [r14 + r15 * 8 + 0xFFFF8]
mulps xmm15, [0x0]
mulps xmm15, [0xFF]
mulps xmm15, [rel $ + 0x0]
mulps xmm15, [rel $ + 0xFF]
mulps xmm15, [rel $ + 0xFFFF]
mulps xmm15, [rax]
mulps xmm15, [rax + 0x0]
mulps xmm15, [rax + 0xFFFF]
mulps xmm15, [r15 + 0xFFFF]
mulps xmm15, [rax + rsi * 1  + 0x0]
mulps xmm15, [rax + rsi + 0xFFFF]
mulps xmm15, [r15 + rsi + 0xFFFF]
mulps xmm15, [rax + r15 + 0xFFFF]
mulps xmm15, [rax + rsi * 2 + 0xFFFF2]
mulps xmm15, [rax + rsi * 4 + 0xFFFF4]
mulps xmm15, [rax + rsi * 8 + 0xFFFF8]
mulps xmm15, [rsp + rax * 8 + 0xFFFF8]
mulps xmm15, [r15 + rax * 8 + 0xFFFF8]
mulps xmm15, [rsp + r15 * 8 + 0xFFFF8]
mulps xmm15, [r14 + r15 * 8 + 0xFFFF8]
