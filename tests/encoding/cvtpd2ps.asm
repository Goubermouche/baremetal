; expect: 660f5ac0660f5ac166410f5ac7660f5ac8660f5ac966410f5acf66440f5af866440f5af966450f5aff660f5a042500000000660f5a0425ff000000660f5a05f8ffffff660f5a05f7000000660f5a05f7ff0000660f5a00660f5a00660f5a80ffff000066410f5a87ffff0000660f5a0430660f5a8430ffff000066410f5a8437ffff000066420f5a8438ffff0000660f5a8470f2ff0f00660f5a84b0f4ff0f00660f5a84f0f8ff0f00660f5a84c4f8ff0f0066410f5a84c7f8ff0f0066420f5a84fcf8ff0f0066430f5a84fef8ff0f00660f5a0c2500000000660f5a0c25ff000000660f5a0df8ffffff660f5a0df7000000660f5a0df7ff0000660f5a08660f5a08660f5a88ffff000066410f5a8fffff0000660f5a0c30660f5a8c30ffff000066410f5a8c37ffff000066420f5a8c38ffff0000660f5a8c70f2ff0f00660f5a8cb0f4ff0f00660f5a8cf0f8ff0f00660f5a8cc4f8ff0f0066410f5a8cc7f8ff0f0066420f5a8cfcf8ff0f0066430f5a8cfef8ff0f0066440f5a3c250000000066440f5a3c25ff00000066440f5a3df7ffffff66440f5a3df600000066440f5a3df6ff000066440f5a3866440f5a3866440f5ab8ffff000066450f5abfffff000066440f5a3c3066440f5abc30ffff000066450f5abc37ffff000066460f5abc38ffff000066440f5abc70f2ff0f0066440f5abcb0f4ff0f0066440f5abcf0f8ff0f0066440f5abcc4f8ff0f0066450f5abcc7f8ff0f0066460f5abcfcf8ff0f0066470f5abcfef8ff0f00

bits 64

cvtpd2ps xmm0, xmm0
cvtpd2ps xmm0, xmm1
cvtpd2ps xmm0, xmm15
cvtpd2ps xmm1, xmm0
cvtpd2ps xmm1, xmm1
cvtpd2ps xmm1, xmm15
cvtpd2ps xmm15, xmm0
cvtpd2ps xmm15, xmm1
cvtpd2ps xmm15, xmm15
cvtpd2ps xmm0, [0x0]
cvtpd2ps xmm0, [0xFF]
cvtpd2ps xmm0, [rel $ + 0x0]
cvtpd2ps xmm0, [rel $ + 0xFF]
cvtpd2ps xmm0, [rel $ + 0xFFFF]
cvtpd2ps xmm0, [rax]
cvtpd2ps xmm0, [rax + 0x0]
cvtpd2ps xmm0, [rax + 0xFFFF]
cvtpd2ps xmm0, [r15 + 0xFFFF]
cvtpd2ps xmm0, [rax + rsi * 1  + 0x0]
cvtpd2ps xmm0, [rax + rsi + 0xFFFF]
cvtpd2ps xmm0, [r15 + rsi + 0xFFFF]
cvtpd2ps xmm0, [rax + r15 + 0xFFFF]
cvtpd2ps xmm0, [rax + rsi * 2 + 0xFFFF2]
cvtpd2ps xmm0, [rax + rsi * 4 + 0xFFFF4]
cvtpd2ps xmm0, [rax + rsi * 8 + 0xFFFF8]
cvtpd2ps xmm0, [rsp + rax * 8 + 0xFFFF8]
cvtpd2ps xmm0, [r15 + rax * 8 + 0xFFFF8]
cvtpd2ps xmm0, [rsp + r15 * 8 + 0xFFFF8]
cvtpd2ps xmm0, [r14 + r15 * 8 + 0xFFFF8]
cvtpd2ps xmm1, [0x0]
cvtpd2ps xmm1, [0xFF]
cvtpd2ps xmm1, [rel $ + 0x0]
cvtpd2ps xmm1, [rel $ + 0xFF]
cvtpd2ps xmm1, [rel $ + 0xFFFF]
cvtpd2ps xmm1, [rax]
cvtpd2ps xmm1, [rax + 0x0]
cvtpd2ps xmm1, [rax + 0xFFFF]
cvtpd2ps xmm1, [r15 + 0xFFFF]
cvtpd2ps xmm1, [rax + rsi * 1  + 0x0]
cvtpd2ps xmm1, [rax + rsi + 0xFFFF]
cvtpd2ps xmm1, [r15 + rsi + 0xFFFF]
cvtpd2ps xmm1, [rax + r15 + 0xFFFF]
cvtpd2ps xmm1, [rax + rsi * 2 + 0xFFFF2]
cvtpd2ps xmm1, [rax + rsi * 4 + 0xFFFF4]
cvtpd2ps xmm1, [rax + rsi * 8 + 0xFFFF8]
cvtpd2ps xmm1, [rsp + rax * 8 + 0xFFFF8]
cvtpd2ps xmm1, [r15 + rax * 8 + 0xFFFF8]
cvtpd2ps xmm1, [rsp + r15 * 8 + 0xFFFF8]
cvtpd2ps xmm1, [r14 + r15 * 8 + 0xFFFF8]
cvtpd2ps xmm15, [0x0]
cvtpd2ps xmm15, [0xFF]
cvtpd2ps xmm15, [rel $ + 0x0]
cvtpd2ps xmm15, [rel $ + 0xFF]
cvtpd2ps xmm15, [rel $ + 0xFFFF]
cvtpd2ps xmm15, [rax]
cvtpd2ps xmm15, [rax + 0x0]
cvtpd2ps xmm15, [rax + 0xFFFF]
cvtpd2ps xmm15, [r15 + 0xFFFF]
cvtpd2ps xmm15, [rax + rsi * 1  + 0x0]
cvtpd2ps xmm15, [rax + rsi + 0xFFFF]
cvtpd2ps xmm15, [r15 + rsi + 0xFFFF]
cvtpd2ps xmm15, [rax + r15 + 0xFFFF]
cvtpd2ps xmm15, [rax + rsi * 2 + 0xFFFF2]
cvtpd2ps xmm15, [rax + rsi * 4 + 0xFFFF4]
cvtpd2ps xmm15, [rax + rsi * 8 + 0xFFFF8]
cvtpd2ps xmm15, [rsp + rax * 8 + 0xFFFF8]
cvtpd2ps xmm15, [r15 + rax * 8 + 0xFFFF8]
cvtpd2ps xmm15, [rsp + r15 * 8 + 0xFFFF8]
cvtpd2ps xmm15, [r14 + r15 * 8 + 0xFFFF8]
