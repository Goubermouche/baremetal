; expect: 0f2ac00f2ac10f2ac70f2ac80f2ac90f2acf440f2af8440f2af9440f2aff0f2a0425000000000f2a0425ff0000000f2a05f9ffffff0f2a05f80000000f2a05f8ff00000f2a000f2a000f2a80ffff0000410f2a87ffff00000f2a04300f2a8430ffff0000410f2a8437ffff0000420f2a8438ffff00000f2a8470f2ff0f000f2a84b0f4ff0f000f2a84f0f8ff0f000f2a84c4f8ff0f00410f2a84c7f8ff0f00420f2a84fcf8ff0f00430f2a84fef8ff0f000f2a0c25000000000f2a0c25ff0000000f2a0df9ffffff0f2a0df80000000f2a0df8ff00000f2a080f2a080f2a88ffff0000410f2a8fffff00000f2a0c300f2a8c30ffff0000410f2a8c37ffff0000420f2a8c38ffff00000f2a8c70f2ff0f000f2a8cb0f4ff0f000f2a8cf0f8ff0f000f2a8cc4f8ff0f00410f2a8cc7f8ff0f00420f2a8cfcf8ff0f00430f2a8cfef8ff0f00440f2a3c2500000000440f2a3c25ff000000440f2a3df8ffffff440f2a3df7000000440f2a3df7ff0000440f2a38440f2a38440f2ab8ffff0000450f2abfffff0000440f2a3c30440f2abc30ffff0000450f2abc37ffff0000460f2abc38ffff0000440f2abc70f2ff0f00440f2abcb0f4ff0f00440f2abcf0f8ff0f00440f2abcc4f8ff0f00450f2abcc7f8ff0f00460f2abcfcf8ff0f00470f2abcfef8ff0f00

bits 64

cvtpi2ps xmm0, mm0
cvtpi2ps xmm0, mm1
cvtpi2ps xmm0, mm7
cvtpi2ps xmm1, mm0
cvtpi2ps xmm1, mm1
cvtpi2ps xmm1, mm7
cvtpi2ps xmm15, mm0
cvtpi2ps xmm15, mm1
cvtpi2ps xmm15, mm7
cvtpi2ps xmm0, qword [0x0]
cvtpi2ps xmm0, qword [0xFF]
cvtpi2ps xmm0, qword [rel $ + 0x0]
cvtpi2ps xmm0, qword [rel $ + 0xFF]
cvtpi2ps xmm0, qword [rel $ + 0xFFFF]
cvtpi2ps xmm0, qword [rax]
cvtpi2ps xmm0, qword [rax + 0x0]
cvtpi2ps xmm0, qword [rax + 0xFFFF]
cvtpi2ps xmm0, qword [r15 + 0xFFFF]
cvtpi2ps xmm0, qword [rax + rsi * 1  + 0x0]
cvtpi2ps xmm0, qword [rax + rsi + 0xFFFF]
cvtpi2ps xmm0, qword [r15 + rsi + 0xFFFF]
cvtpi2ps xmm0, qword [rax + r15 + 0xFFFF]
cvtpi2ps xmm0, qword [rax + rsi * 2 + 0xFFFF2]
cvtpi2ps xmm0, qword [rax + rsi * 4 + 0xFFFF4]
cvtpi2ps xmm0, qword [rax + rsi * 8 + 0xFFFF8]
cvtpi2ps xmm0, qword [rsp + rax * 8 + 0xFFFF8]
cvtpi2ps xmm0, qword [r15 + rax * 8 + 0xFFFF8]
cvtpi2ps xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
cvtpi2ps xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
cvtpi2ps xmm1, qword [0x0]
cvtpi2ps xmm1, qword [0xFF]
cvtpi2ps xmm1, qword [rel $ + 0x0]
cvtpi2ps xmm1, qword [rel $ + 0xFF]
cvtpi2ps xmm1, qword [rel $ + 0xFFFF]
cvtpi2ps xmm1, qword [rax]
cvtpi2ps xmm1, qword [rax + 0x0]
cvtpi2ps xmm1, qword [rax + 0xFFFF]
cvtpi2ps xmm1, qword [r15 + 0xFFFF]
cvtpi2ps xmm1, qword [rax + rsi * 1  + 0x0]
cvtpi2ps xmm1, qword [rax + rsi + 0xFFFF]
cvtpi2ps xmm1, qword [r15 + rsi + 0xFFFF]
cvtpi2ps xmm1, qword [rax + r15 + 0xFFFF]
cvtpi2ps xmm1, qword [rax + rsi * 2 + 0xFFFF2]
cvtpi2ps xmm1, qword [rax + rsi * 4 + 0xFFFF4]
cvtpi2ps xmm1, qword [rax + rsi * 8 + 0xFFFF8]
cvtpi2ps xmm1, qword [rsp + rax * 8 + 0xFFFF8]
cvtpi2ps xmm1, qword [r15 + rax * 8 + 0xFFFF8]
cvtpi2ps xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
cvtpi2ps xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
cvtpi2ps xmm15, qword [0x0]
cvtpi2ps xmm15, qword [0xFF]
cvtpi2ps xmm15, qword [rel $ + 0x0]
cvtpi2ps xmm15, qword [rel $ + 0xFF]
cvtpi2ps xmm15, qword [rel $ + 0xFFFF]
cvtpi2ps xmm15, qword [rax]
cvtpi2ps xmm15, qword [rax + 0x0]
cvtpi2ps xmm15, qword [rax + 0xFFFF]
cvtpi2ps xmm15, qword [r15 + 0xFFFF]
cvtpi2ps xmm15, qword [rax + rsi * 1  + 0x0]
cvtpi2ps xmm15, qword [rax + rsi + 0xFFFF]
cvtpi2ps xmm15, qword [r15 + rsi + 0xFFFF]
cvtpi2ps xmm15, qword [rax + r15 + 0xFFFF]
cvtpi2ps xmm15, qword [rax + rsi * 2 + 0xFFFF2]
cvtpi2ps xmm15, qword [rax + rsi * 4 + 0xFFFF4]
cvtpi2ps xmm15, qword [rax + rsi * 8 + 0xFFFF8]
cvtpi2ps xmm15, qword [rsp + rax * 8 + 0xFFFF8]
cvtpi2ps xmm15, qword [r15 + rax * 8 + 0xFFFF8]
cvtpi2ps xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
cvtpi2ps xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
