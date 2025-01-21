; expect: 0f28c00f28c1410f28c70f28c80f28c9410f28cf440f28f8440f28f9450f28ff0f280425000000000f280425ff0000000f2805f9ffffff0f2805f80000000f2805f8ff00000f28000f28000f2880ffff0000410f2887ffff00000f2804300f288430ffff0000410f288437ffff0000420f288438ffff00000f288470f2ff0f000f2884b0f4ff0f000f2884f0f8ff0f000f2884c4f8ff0f00410f2884c7f8ff0f00420f2884fcf8ff0f00430f2884fef8ff0f000f280c25000000000f280c25ff0000000f280df9ffffff0f280df80000000f280df8ff00000f28080f28080f2888ffff0000410f288fffff00000f280c300f288c30ffff0000410f288c37ffff0000420f288c38ffff00000f288c70f2ff0f000f288cb0f4ff0f000f288cf0f8ff0f000f288cc4f8ff0f00410f288cc7f8ff0f00420f288cfcf8ff0f00430f288cfef8ff0f00440f283c2500000000440f283c25ff000000440f283df8ffffff440f283df7000000440f283df7ff0000440f2838440f2838440f28b8ffff0000450f28bfffff0000440f283c30440f28bc30ffff0000450f28bc37ffff0000460f28bc38ffff0000440f28bc70f2ff0f00440f28bcb0f4ff0f00440f28bcf0f8ff0f00440f28bcc4f8ff0f00450f28bcc7f8ff0f00460f28bcfcf8ff0f00470f28bcfef8ff0f000f290425000000000f290c2500000000440f293c25000000000f290425ff0000000f290c25ff000000440f293c25ff0000000f2905f9ffffff0f290df9ffffff440f293df8ffffff0f2905f80000000f290df8000000440f293df70000000f2905f8ff00000f290df8ff0000440f293df7ff00000f29000f2908440f29380f29000f2908440f29380f2980ffff00000f2988ffff0000440f29b8ffff0000410f2987ffff0000410f298fffff0000450f29bfffff00000f2904300f290c30440f293c300f298430ffff00000f298c30ffff0000440f29bc30ffff0000410f298437ffff0000410f298c37ffff0000450f29bc37ffff0000420f298438ffff0000420f298c38ffff0000460f29bc38ffff00000f298470f2ff0f000f298c70f2ff0f00440f29bc70f2ff0f000f2984b0f4ff0f000f298cb0f4ff0f00440f29bcb0f4ff0f000f2984f0f8ff0f000f298cf0f8ff0f00440f29bcf0f8ff0f000f2984c4f8ff0f000f298cc4f8ff0f00440f29bcc4f8ff0f00410f2984c7f8ff0f00410f298cc7f8ff0f00450f29bcc7f8ff0f00420f2984fcf8ff0f00420f298cfcf8ff0f00460f29bcfcf8ff0f00430f2984fef8ff0f00430f298cfef8ff0f00470f29bcfef8ff0f00

movaps xmm0, xmm0
movaps xmm0, xmm1
movaps xmm0, xmm15
movaps xmm1, xmm0
movaps xmm1, xmm1
movaps xmm1, xmm15
movaps xmm15, xmm0
movaps xmm15, xmm1
movaps xmm15, xmm15
movaps xmm0, [0x0]
movaps xmm0, [0xFF]
movaps xmm0, [rel $ + 0x0]
movaps xmm0, [rel $ + 0xFF]
movaps xmm0, [rel $ + 0xFFFF]
movaps xmm0, [rax]
movaps xmm0, [rax + 0x0]
movaps xmm0, [rax + 0xFFFF]
movaps xmm0, [r15 + 0xFFFF]
movaps xmm0, [rax + rsi * 1  + 0x0]
movaps xmm0, [rax + rsi + 0xFFFF]
movaps xmm0, [r15 + rsi + 0xFFFF]
movaps xmm0, [rax + r15 + 0xFFFF]
movaps xmm0, [rax + rsi * 2 + 0xFFFF2]
movaps xmm0, [rax + rsi * 4 + 0xFFFF4]
movaps xmm0, [rax + rsi * 8 + 0xFFFF8]
movaps xmm0, [rsp + rax * 8 + 0xFFFF8]
movaps xmm0, [r15 + rax * 8 + 0xFFFF8]
movaps xmm0, [rsp + r15 * 8 + 0xFFFF8]
movaps xmm0, [r14 + r15 * 8 + 0xFFFF8]
movaps xmm1, [0x0]
movaps xmm1, [0xFF]
movaps xmm1, [rel $ + 0x0]
movaps xmm1, [rel $ + 0xFF]
movaps xmm1, [rel $ + 0xFFFF]
movaps xmm1, [rax]
movaps xmm1, [rax + 0x0]
movaps xmm1, [rax + 0xFFFF]
movaps xmm1, [r15 + 0xFFFF]
movaps xmm1, [rax + rsi * 1  + 0x0]
movaps xmm1, [rax + rsi + 0xFFFF]
movaps xmm1, [r15 + rsi + 0xFFFF]
movaps xmm1, [rax + r15 + 0xFFFF]
movaps xmm1, [rax + rsi * 2 + 0xFFFF2]
movaps xmm1, [rax + rsi * 4 + 0xFFFF4]
movaps xmm1, [rax + rsi * 8 + 0xFFFF8]
movaps xmm1, [rsp + rax * 8 + 0xFFFF8]
movaps xmm1, [r15 + rax * 8 + 0xFFFF8]
movaps xmm1, [rsp + r15 * 8 + 0xFFFF8]
movaps xmm1, [r14 + r15 * 8 + 0xFFFF8]
movaps xmm15, [0x0]
movaps xmm15, [0xFF]
movaps xmm15, [rel $ + 0x0]
movaps xmm15, [rel $ + 0xFF]
movaps xmm15, [rel $ + 0xFFFF]
movaps xmm15, [rax]
movaps xmm15, [rax + 0x0]
movaps xmm15, [rax + 0xFFFF]
movaps xmm15, [r15 + 0xFFFF]
movaps xmm15, [rax + rsi * 1  + 0x0]
movaps xmm15, [rax + rsi + 0xFFFF]
movaps xmm15, [r15 + rsi + 0xFFFF]
movaps xmm15, [rax + r15 + 0xFFFF]
movaps xmm15, [rax + rsi * 2 + 0xFFFF2]
movaps xmm15, [rax + rsi * 4 + 0xFFFF4]
movaps xmm15, [rax + rsi * 8 + 0xFFFF8]
movaps xmm15, [rsp + rax * 8 + 0xFFFF8]
movaps xmm15, [r15 + rax * 8 + 0xFFFF8]
movaps xmm15, [rsp + r15 * 8 + 0xFFFF8]
movaps xmm15, [r14 + r15 * 8 + 0xFFFF8]
movaps [0x0], xmm0
movaps [0x0], xmm1
movaps [0x0], xmm15
movaps [0xFF], xmm0
movaps [0xFF], xmm1
movaps [0xFF], xmm15
movaps [rel $ + 0x0], xmm0
movaps [rel $ + 0x0], xmm1
movaps [rel $ + 0x0], xmm15
movaps [rel $ + 0xFF], xmm0
movaps [rel $ + 0xFF], xmm1
movaps [rel $ + 0xFF], xmm15
movaps [rel $ + 0xFFFF], xmm0
movaps [rel $ + 0xFFFF], xmm1
movaps [rel $ + 0xFFFF], xmm15
movaps [rax], xmm0
movaps [rax], xmm1
movaps [rax], xmm15
movaps [rax + 0x0], xmm0
movaps [rax + 0x0], xmm1
movaps [rax + 0x0], xmm15
movaps [rax + 0xFFFF], xmm0
movaps [rax + 0xFFFF], xmm1
movaps [rax + 0xFFFF], xmm15
movaps [r15 + 0xFFFF], xmm0
movaps [r15 + 0xFFFF], xmm1
movaps [r15 + 0xFFFF], xmm15
movaps [rax + rsi * 1  + 0x0], xmm0
movaps [rax + rsi * 1  + 0x0], xmm1
movaps [rax + rsi * 1  + 0x0], xmm15
movaps [rax + rsi + 0xFFFF], xmm0
movaps [rax + rsi + 0xFFFF], xmm1
movaps [rax + rsi + 0xFFFF], xmm15
movaps [r15 + rsi + 0xFFFF], xmm0
movaps [r15 + rsi + 0xFFFF], xmm1
movaps [r15 + rsi + 0xFFFF], xmm15
movaps [rax + r15 + 0xFFFF], xmm0
movaps [rax + r15 + 0xFFFF], xmm1
movaps [rax + r15 + 0xFFFF], xmm15
movaps [rax + rsi * 2 + 0xFFFF2], xmm0
movaps [rax + rsi * 2 + 0xFFFF2], xmm1
movaps [rax + rsi * 2 + 0xFFFF2], xmm15
movaps [rax + rsi * 4 + 0xFFFF4], xmm0
movaps [rax + rsi * 4 + 0xFFFF4], xmm1
movaps [rax + rsi * 4 + 0xFFFF4], xmm15
movaps [rax + rsi * 8 + 0xFFFF8], xmm0
movaps [rax + rsi * 8 + 0xFFFF8], xmm1
movaps [rax + rsi * 8 + 0xFFFF8], xmm15
movaps [rsp + rax * 8 + 0xFFFF8], xmm0
movaps [rsp + rax * 8 + 0xFFFF8], xmm1
movaps [rsp + rax * 8 + 0xFFFF8], xmm15
movaps [r15 + rax * 8 + 0xFFFF8], xmm0
movaps [r15 + rax * 8 + 0xFFFF8], xmm1
movaps [r15 + rax * 8 + 0xFFFF8], xmm15
movaps [rsp + r15 * 8 + 0xFFFF8], xmm0
movaps [rsp + r15 * 8 + 0xFFFF8], xmm1
movaps [rsp + r15 * 8 + 0xFFFF8], xmm15
movaps [r14 + r15 * 8 + 0xFFFF8], xmm0
movaps [r14 + r15 * 8 + 0xFFFF8], xmm1
movaps [r14 + r15 * 8 + 0xFFFF8], xmm15