; expect: 660f28c0660f28c166410f28c7660f28c8660f28c966410f28cf66440f28f866440f28f966450f28ff660f28042500000000660f280425ff000000660f2805f8ffffff660f2805f7000000660f2805f7ff0000660f2800660f2800660f2880ffff000066410f2887ffff0000660f280430660f288430ffff000066410f288437ffff000066420f288438ffff0000660f288470f2ff0f00660f2884b0f4ff0f00660f2884f0f8ff0f00660f2884c4f8ff0f0066410f2884c7f8ff0f0066420f2884fcf8ff0f0066430f2884fef8ff0f00660f280c2500000000660f280c25ff000000660f280df8ffffff660f280df7000000660f280df7ff0000660f2808660f2808660f2888ffff000066410f288fffff0000660f280c30660f288c30ffff000066410f288c37ffff000066420f288c38ffff0000660f288c70f2ff0f00660f288cb0f4ff0f00660f288cf0f8ff0f00660f288cc4f8ff0f0066410f288cc7f8ff0f0066420f288cfcf8ff0f0066430f288cfef8ff0f0066440f283c250000000066440f283c25ff00000066440f283df7ffffff66440f283df600000066440f283df6ff000066440f283866440f283866440f28b8ffff000066450f28bfffff000066440f283c3066440f28bc30ffff000066450f28bc37ffff000066460f28bc38ffff000066440f28bc70f2ff0f0066440f28bcb0f4ff0f0066440f28bcf0f8ff0f0066440f28bcc4f8ff0f0066450f28bcc7f8ff0f0066460f28bcfcf8ff0f0066470f28bcfef8ff0f00660f29042500000000660f290c250000000066440f293c2500000000660f290425ff000000660f290c25ff00000066440f293c25ff000000660f2905f8ffffff660f290df8ffffff66440f293df7ffffff660f2905f7000000660f290df700000066440f293df6000000660f2905f7ff0000660f290df7ff000066440f293df6ff0000660f2900660f290866440f2938660f2900660f290866440f2938660f2980ffff0000660f2988ffff000066440f29b8ffff000066410f2987ffff000066410f298fffff000066450f29bfffff0000660f290430660f290c3066440f293c30660f298430ffff0000660f298c30ffff000066440f29bc30ffff000066410f298437ffff000066410f298c37ffff000066450f29bc37ffff000066420f298438ffff000066420f298c38ffff000066460f29bc38ffff0000660f298470f2ff0f00660f298c70f2ff0f0066440f29bc70f2ff0f00660f2984b0f4ff0f00660f298cb0f4ff0f0066440f29bcb0f4ff0f00660f2984f0f8ff0f00660f298cf0f8ff0f0066440f29bcf0f8ff0f00660f2984c4f8ff0f00660f298cc4f8ff0f0066440f29bcc4f8ff0f0066410f2984c7f8ff0f0066410f298cc7f8ff0f0066450f29bcc7f8ff0f0066420f2984fcf8ff0f0066420f298cfcf8ff0f0066460f29bcfcf8ff0f0066430f2984fef8ff0f0066430f298cfef8ff0f0066470f29bcfef8ff0f00

movapd xmm0, xmm0
movapd xmm0, xmm1
movapd xmm0, xmm15
movapd xmm1, xmm0
movapd xmm1, xmm1
movapd xmm1, xmm15
movapd xmm15, xmm0
movapd xmm15, xmm1
movapd xmm15, xmm15
movapd xmm0, [0x0]
movapd xmm0, [0xFF]
movapd xmm0, [rel $ + 0x0]
movapd xmm0, [rel $ + 0xFF]
movapd xmm0, [rel $ + 0xFFFF]
movapd xmm0, [rax]
movapd xmm0, [rax + 0x0]
movapd xmm0, [rax + 0xFFFF]
movapd xmm0, [r15 + 0xFFFF]
movapd xmm0, [rax + rsi * 1  + 0x0]
movapd xmm0, [rax + rsi + 0xFFFF]
movapd xmm0, [r15 + rsi + 0xFFFF]
movapd xmm0, [rax + r15 + 0xFFFF]
movapd xmm0, [rax + rsi * 2 + 0xFFFF2]
movapd xmm0, [rax + rsi * 4 + 0xFFFF4]
movapd xmm0, [rax + rsi * 8 + 0xFFFF8]
movapd xmm0, [rsp + rax * 8 + 0xFFFF8]
movapd xmm0, [r15 + rax * 8 + 0xFFFF8]
movapd xmm0, [rsp + r15 * 8 + 0xFFFF8]
movapd xmm0, [r14 + r15 * 8 + 0xFFFF8]
movapd xmm1, [0x0]
movapd xmm1, [0xFF]
movapd xmm1, [rel $ + 0x0]
movapd xmm1, [rel $ + 0xFF]
movapd xmm1, [rel $ + 0xFFFF]
movapd xmm1, [rax]
movapd xmm1, [rax + 0x0]
movapd xmm1, [rax + 0xFFFF]
movapd xmm1, [r15 + 0xFFFF]
movapd xmm1, [rax + rsi * 1  + 0x0]
movapd xmm1, [rax + rsi + 0xFFFF]
movapd xmm1, [r15 + rsi + 0xFFFF]
movapd xmm1, [rax + r15 + 0xFFFF]
movapd xmm1, [rax + rsi * 2 + 0xFFFF2]
movapd xmm1, [rax + rsi * 4 + 0xFFFF4]
movapd xmm1, [rax + rsi * 8 + 0xFFFF8]
movapd xmm1, [rsp + rax * 8 + 0xFFFF8]
movapd xmm1, [r15 + rax * 8 + 0xFFFF8]
movapd xmm1, [rsp + r15 * 8 + 0xFFFF8]
movapd xmm1, [r14 + r15 * 8 + 0xFFFF8]
movapd xmm15, [0x0]
movapd xmm15, [0xFF]
movapd xmm15, [rel $ + 0x0]
movapd xmm15, [rel $ + 0xFF]
movapd xmm15, [rel $ + 0xFFFF]
movapd xmm15, [rax]
movapd xmm15, [rax + 0x0]
movapd xmm15, [rax + 0xFFFF]
movapd xmm15, [r15 + 0xFFFF]
movapd xmm15, [rax + rsi * 1  + 0x0]
movapd xmm15, [rax + rsi + 0xFFFF]
movapd xmm15, [r15 + rsi + 0xFFFF]
movapd xmm15, [rax + r15 + 0xFFFF]
movapd xmm15, [rax + rsi * 2 + 0xFFFF2]
movapd xmm15, [rax + rsi * 4 + 0xFFFF4]
movapd xmm15, [rax + rsi * 8 + 0xFFFF8]
movapd xmm15, [rsp + rax * 8 + 0xFFFF8]
movapd xmm15, [r15 + rax * 8 + 0xFFFF8]
movapd xmm15, [rsp + r15 * 8 + 0xFFFF8]
movapd xmm15, [r14 + r15 * 8 + 0xFFFF8]
movapd [0x0], xmm0
movapd [0x0], xmm1
movapd [0x0], xmm15
movapd [0xFF], xmm0
movapd [0xFF], xmm1
movapd [0xFF], xmm15
movapd [rel $ + 0x0], xmm0
movapd [rel $ + 0x0], xmm1
movapd [rel $ + 0x0], xmm15
movapd [rel $ + 0xFF], xmm0
movapd [rel $ + 0xFF], xmm1
movapd [rel $ + 0xFF], xmm15
movapd [rel $ + 0xFFFF], xmm0
movapd [rel $ + 0xFFFF], xmm1
movapd [rel $ + 0xFFFF], xmm15
movapd [rax], xmm0
movapd [rax], xmm1
movapd [rax], xmm15
movapd [rax + 0x0], xmm0
movapd [rax + 0x0], xmm1
movapd [rax + 0x0], xmm15
movapd [rax + 0xFFFF], xmm0
movapd [rax + 0xFFFF], xmm1
movapd [rax + 0xFFFF], xmm15
movapd [r15 + 0xFFFF], xmm0
movapd [r15 + 0xFFFF], xmm1
movapd [r15 + 0xFFFF], xmm15
movapd [rax + rsi * 1  + 0x0], xmm0
movapd [rax + rsi * 1  + 0x0], xmm1
movapd [rax + rsi * 1  + 0x0], xmm15
movapd [rax + rsi + 0xFFFF], xmm0
movapd [rax + rsi + 0xFFFF], xmm1
movapd [rax + rsi + 0xFFFF], xmm15
movapd [r15 + rsi + 0xFFFF], xmm0
movapd [r15 + rsi + 0xFFFF], xmm1
movapd [r15 + rsi + 0xFFFF], xmm15
movapd [rax + r15 + 0xFFFF], xmm0
movapd [rax + r15 + 0xFFFF], xmm1
movapd [rax + r15 + 0xFFFF], xmm15
movapd [rax + rsi * 2 + 0xFFFF2], xmm0
movapd [rax + rsi * 2 + 0xFFFF2], xmm1
movapd [rax + rsi * 2 + 0xFFFF2], xmm15
movapd [rax + rsi * 4 + 0xFFFF4], xmm0
movapd [rax + rsi * 4 + 0xFFFF4], xmm1
movapd [rax + rsi * 4 + 0xFFFF4], xmm15
movapd [rax + rsi * 8 + 0xFFFF8], xmm0
movapd [rax + rsi * 8 + 0xFFFF8], xmm1
movapd [rax + rsi * 8 + 0xFFFF8], xmm15
movapd [rsp + rax * 8 + 0xFFFF8], xmm0
movapd [rsp + rax * 8 + 0xFFFF8], xmm1
movapd [rsp + rax * 8 + 0xFFFF8], xmm15
movapd [r15 + rax * 8 + 0xFFFF8], xmm0
movapd [r15 + rax * 8 + 0xFFFF8], xmm1
movapd [r15 + rax * 8 + 0xFFFF8], xmm15
movapd [rsp + r15 * 8 + 0xFFFF8], xmm0
movapd [rsp + r15 * 8 + 0xFFFF8], xmm1
movapd [rsp + r15 * 8 + 0xFFFF8], xmm15
movapd [r14 + r15 * 8 + 0xFFFF8], xmm0
movapd [r14 + r15 * 8 + 0xFFFF8], xmm1
movapd [r14 + r15 * 8 + 0xFFFF8], xmm15