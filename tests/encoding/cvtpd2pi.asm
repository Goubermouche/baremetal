; expect: 660f2dc0660f2dc166410f2dc7660f2dc8660f2dc966410f2dcf660f2df8660f2df966410f2dff660f2d042500000000660f2d0425ff000000660f2d05f8ffffff660f2d05f7000000660f2d05f7ff0000660f2d00660f2d00660f2d80ffff000066410f2d87ffff0000660f2d0430660f2d8430ffff000066410f2d8437ffff000066420f2d8438ffff0000660f2d8470f2ff0f00660f2d84b0f4ff0f00660f2d84f0f8ff0f00660f2d84c4f8ff0f0066410f2d84c7f8ff0f0066420f2d84fcf8ff0f0066430f2d84fef8ff0f00660f2d0c2500000000660f2d0c25ff000000660f2d0df8ffffff660f2d0df7000000660f2d0df7ff0000660f2d08660f2d08660f2d88ffff000066410f2d8fffff0000660f2d0c30660f2d8c30ffff000066410f2d8c37ffff000066420f2d8c38ffff0000660f2d8c70f2ff0f00660f2d8cb0f4ff0f00660f2d8cf0f8ff0f00660f2d8cc4f8ff0f0066410f2d8cc7f8ff0f0066420f2d8cfcf8ff0f0066430f2d8cfef8ff0f00660f2d3c2500000000660f2d3c25ff000000660f2d3df8ffffff660f2d3df7000000660f2d3df7ff0000660f2d38660f2d38660f2db8ffff000066410f2dbfffff0000660f2d3c30660f2dbc30ffff000066410f2dbc37ffff000066420f2dbc38ffff0000660f2dbc70f2ff0f00660f2dbcb0f4ff0f00660f2dbcf0f8ff0f00660f2dbcc4f8ff0f0066410f2dbcc7f8ff0f0066420f2dbcfcf8ff0f0066430f2dbcfef8ff0f00

bits 64

cvtpd2pi mm0, xmm0
cvtpd2pi mm0, xmm1
cvtpd2pi mm0, xmm15
cvtpd2pi mm1, xmm0
cvtpd2pi mm1, xmm1
cvtpd2pi mm1, xmm15
cvtpd2pi mm7, xmm0
cvtpd2pi mm7, xmm1
cvtpd2pi mm7, xmm15
cvtpd2pi mm0, [0x0]
cvtpd2pi mm0, [0xFF]
cvtpd2pi mm0, [rel $ + 0x0]
cvtpd2pi mm0, [rel $ + 0xFF]
cvtpd2pi mm0, [rel $ + 0xFFFF]
cvtpd2pi mm0, [rax]
cvtpd2pi mm0, [rax + 0x0]
cvtpd2pi mm0, [rax + 0xFFFF]
cvtpd2pi mm0, [r15 + 0xFFFF]
cvtpd2pi mm0, [rax + rsi * 1  + 0x0]
cvtpd2pi mm0, [rax + rsi + 0xFFFF]
cvtpd2pi mm0, [r15 + rsi + 0xFFFF]
cvtpd2pi mm0, [rax + r15 + 0xFFFF]
cvtpd2pi mm0, [rax + rsi * 2 + 0xFFFF2]
cvtpd2pi mm0, [rax + rsi * 4 + 0xFFFF4]
cvtpd2pi mm0, [rax + rsi * 8 + 0xFFFF8]
cvtpd2pi mm0, [rsp + rax * 8 + 0xFFFF8]
cvtpd2pi mm0, [r15 + rax * 8 + 0xFFFF8]
cvtpd2pi mm0, [rsp + r15 * 8 + 0xFFFF8]
cvtpd2pi mm0, [r14 + r15 * 8 + 0xFFFF8]
cvtpd2pi mm1, [0x0]
cvtpd2pi mm1, [0xFF]
cvtpd2pi mm1, [rel $ + 0x0]
cvtpd2pi mm1, [rel $ + 0xFF]
cvtpd2pi mm1, [rel $ + 0xFFFF]
cvtpd2pi mm1, [rax]
cvtpd2pi mm1, [rax + 0x0]
cvtpd2pi mm1, [rax + 0xFFFF]
cvtpd2pi mm1, [r15 + 0xFFFF]
cvtpd2pi mm1, [rax + rsi * 1  + 0x0]
cvtpd2pi mm1, [rax + rsi + 0xFFFF]
cvtpd2pi mm1, [r15 + rsi + 0xFFFF]
cvtpd2pi mm1, [rax + r15 + 0xFFFF]
cvtpd2pi mm1, [rax + rsi * 2 + 0xFFFF2]
cvtpd2pi mm1, [rax + rsi * 4 + 0xFFFF4]
cvtpd2pi mm1, [rax + rsi * 8 + 0xFFFF8]
cvtpd2pi mm1, [rsp + rax * 8 + 0xFFFF8]
cvtpd2pi mm1, [r15 + rax * 8 + 0xFFFF8]
cvtpd2pi mm1, [rsp + r15 * 8 + 0xFFFF8]
cvtpd2pi mm1, [r14 + r15 * 8 + 0xFFFF8]
cvtpd2pi mm7, [0x0]
cvtpd2pi mm7, [0xFF]
cvtpd2pi mm7, [rel $ + 0x0]
cvtpd2pi mm7, [rel $ + 0xFF]
cvtpd2pi mm7, [rel $ + 0xFFFF]
cvtpd2pi mm7, [rax]
cvtpd2pi mm7, [rax + 0x0]
cvtpd2pi mm7, [rax + 0xFFFF]
cvtpd2pi mm7, [r15 + 0xFFFF]
cvtpd2pi mm7, [rax + rsi * 1  + 0x0]
cvtpd2pi mm7, [rax + rsi + 0xFFFF]
cvtpd2pi mm7, [r15 + rsi + 0xFFFF]
cvtpd2pi mm7, [rax + r15 + 0xFFFF]
cvtpd2pi mm7, [rax + rsi * 2 + 0xFFFF2]
cvtpd2pi mm7, [rax + rsi * 4 + 0xFFFF4]
cvtpd2pi mm7, [rax + rsi * 8 + 0xFFFF8]
cvtpd2pi mm7, [rsp + rax * 8 + 0xFFFF8]
cvtpd2pi mm7, [r15 + rax * 8 + 0xFFFF8]
cvtpd2pi mm7, [rsp + r15 * 8 + 0xFFFF8]
cvtpd2pi mm7, [r14 + r15 * 8 + 0xFFFF8]
