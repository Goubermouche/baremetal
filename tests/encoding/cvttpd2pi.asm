; expect: 660f2cc0660f2cc166410f2cc7660f2cc8660f2cc966410f2ccf660f2cf8660f2cf966410f2cff660f2c042500000000660f2c0425ff000000660f2c05f8ffffff660f2c05f7000000660f2c05f7ff0000660f2c00660f2c00660f2c80ffff000066410f2c87ffff0000660f2c0430660f2c8430ffff000066410f2c8437ffff000066420f2c8438ffff0000660f2c8470f2ff0f00660f2c84b0f4ff0f00660f2c84f0f8ff0f00660f2c84c4f8ff0f0066410f2c84c7f8ff0f0066420f2c84fcf8ff0f0066430f2c84fef8ff0f00660f2c0c2500000000660f2c0c25ff000000660f2c0df8ffffff660f2c0df7000000660f2c0df7ff0000660f2c08660f2c08660f2c88ffff000066410f2c8fffff0000660f2c0c30660f2c8c30ffff000066410f2c8c37ffff000066420f2c8c38ffff0000660f2c8c70f2ff0f00660f2c8cb0f4ff0f00660f2c8cf0f8ff0f00660f2c8cc4f8ff0f0066410f2c8cc7f8ff0f0066420f2c8cfcf8ff0f0066430f2c8cfef8ff0f00660f2c3c2500000000660f2c3c25ff000000660f2c3df8ffffff660f2c3df7000000660f2c3df7ff0000660f2c38660f2c38660f2cb8ffff000066410f2cbfffff0000660f2c3c30660f2cbc30ffff000066410f2cbc37ffff000066420f2cbc38ffff0000660f2cbc70f2ff0f00660f2cbcb0f4ff0f00660f2cbcf0f8ff0f00660f2cbcc4f8ff0f0066410f2cbcc7f8ff0f0066420f2cbcfcf8ff0f0066430f2cbcfef8ff0f00

bits 64

cvttpd2pi mm0, xmm0
cvttpd2pi mm0, xmm1
cvttpd2pi mm0, xmm15
cvttpd2pi mm1, xmm0
cvttpd2pi mm1, xmm1
cvttpd2pi mm1, xmm15
cvttpd2pi mm7, xmm0
cvttpd2pi mm7, xmm1
cvttpd2pi mm7, xmm15
cvttpd2pi mm0, [0x0]
cvttpd2pi mm0, [0xFF]
cvttpd2pi mm0, [rel $ + 0x0]
cvttpd2pi mm0, [rel $ + 0xFF]
cvttpd2pi mm0, [rel $ + 0xFFFF]
cvttpd2pi mm0, [rax]
cvttpd2pi mm0, [rax + 0x0]
cvttpd2pi mm0, [rax + 0xFFFF]
cvttpd2pi mm0, [r15 + 0xFFFF]
cvttpd2pi mm0, [rax + rsi * 1  + 0x0]
cvttpd2pi mm0, [rax + rsi + 0xFFFF]
cvttpd2pi mm0, [r15 + rsi + 0xFFFF]
cvttpd2pi mm0, [rax + r15 + 0xFFFF]
cvttpd2pi mm0, [rax + rsi * 2 + 0xFFFF2]
cvttpd2pi mm0, [rax + rsi * 4 + 0xFFFF4]
cvttpd2pi mm0, [rax + rsi * 8 + 0xFFFF8]
cvttpd2pi mm0, [rsp + rax * 8 + 0xFFFF8]
cvttpd2pi mm0, [r15 + rax * 8 + 0xFFFF8]
cvttpd2pi mm0, [rsp + r15 * 8 + 0xFFFF8]
cvttpd2pi mm0, [r14 + r15 * 8 + 0xFFFF8]
cvttpd2pi mm1, [0x0]
cvttpd2pi mm1, [0xFF]
cvttpd2pi mm1, [rel $ + 0x0]
cvttpd2pi mm1, [rel $ + 0xFF]
cvttpd2pi mm1, [rel $ + 0xFFFF]
cvttpd2pi mm1, [rax]
cvttpd2pi mm1, [rax + 0x0]
cvttpd2pi mm1, [rax + 0xFFFF]
cvttpd2pi mm1, [r15 + 0xFFFF]
cvttpd2pi mm1, [rax + rsi * 1  + 0x0]
cvttpd2pi mm1, [rax + rsi + 0xFFFF]
cvttpd2pi mm1, [r15 + rsi + 0xFFFF]
cvttpd2pi mm1, [rax + r15 + 0xFFFF]
cvttpd2pi mm1, [rax + rsi * 2 + 0xFFFF2]
cvttpd2pi mm1, [rax + rsi * 4 + 0xFFFF4]
cvttpd2pi mm1, [rax + rsi * 8 + 0xFFFF8]
cvttpd2pi mm1, [rsp + rax * 8 + 0xFFFF8]
cvttpd2pi mm1, [r15 + rax * 8 + 0xFFFF8]
cvttpd2pi mm1, [rsp + r15 * 8 + 0xFFFF8]
cvttpd2pi mm1, [r14 + r15 * 8 + 0xFFFF8]
cvttpd2pi mm7, [0x0]
cvttpd2pi mm7, [0xFF]
cvttpd2pi mm7, [rel $ + 0x0]
cvttpd2pi mm7, [rel $ + 0xFF]
cvttpd2pi mm7, [rel $ + 0xFFFF]
cvttpd2pi mm7, [rax]
cvttpd2pi mm7, [rax + 0x0]
cvttpd2pi mm7, [rax + 0xFFFF]
cvttpd2pi mm7, [r15 + 0xFFFF]
cvttpd2pi mm7, [rax + rsi * 1  + 0x0]
cvttpd2pi mm7, [rax + rsi + 0xFFFF]
cvttpd2pi mm7, [r15 + rsi + 0xFFFF]
cvttpd2pi mm7, [rax + r15 + 0xFFFF]
cvttpd2pi mm7, [rax + rsi * 2 + 0xFFFF2]
cvttpd2pi mm7, [rax + rsi * 4 + 0xFFFF4]
cvttpd2pi mm7, [rax + rsi * 8 + 0xFFFF8]
cvttpd2pi mm7, [rsp + rax * 8 + 0xFFFF8]
cvttpd2pi mm7, [r15 + rax * 8 + 0xFFFF8]
cvttpd2pi mm7, [rsp + r15 * 8 + 0xFFFF8]
cvttpd2pi mm7, [r14 + r15 * 8 + 0xFFFF8]
