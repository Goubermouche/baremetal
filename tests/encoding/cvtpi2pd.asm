; expect: 660f2ac0660f2ac1660f2ac7660f2ac8660f2ac9660f2acf66440f2af866440f2af966440f2aff660f2a042500000000660f2a0425ff000000660f2a05f8ffffff660f2a05f7000000660f2a05f7ff0000660f2a00660f2a00660f2a80ffff000066410f2a87ffff0000660f2a0430660f2a8430ffff000066410f2a8437ffff000066420f2a8438ffff0000660f2a8470f2ff0f00660f2a84b0f4ff0f00660f2a84f0f8ff0f00660f2a84c4f8ff0f0066410f2a84c7f8ff0f0066420f2a84fcf8ff0f0066430f2a84fef8ff0f00660f2a0c2500000000660f2a0c25ff000000660f2a0df8ffffff660f2a0df7000000660f2a0df7ff0000660f2a08660f2a08660f2a88ffff000066410f2a8fffff0000660f2a0c30660f2a8c30ffff000066410f2a8c37ffff000066420f2a8c38ffff0000660f2a8c70f2ff0f00660f2a8cb0f4ff0f00660f2a8cf0f8ff0f00660f2a8cc4f8ff0f0066410f2a8cc7f8ff0f0066420f2a8cfcf8ff0f0066430f2a8cfef8ff0f0066440f2a3c250000000066440f2a3c25ff00000066440f2a3df7ffffff66440f2a3df600000066440f2a3df6ff000066440f2a3866440f2a3866440f2ab8ffff000066450f2abfffff000066440f2a3c3066440f2abc30ffff000066450f2abc37ffff000066460f2abc38ffff000066440f2abc70f2ff0f0066440f2abcb0f4ff0f0066440f2abcf0f8ff0f0066440f2abcc4f8ff0f0066450f2abcc7f8ff0f0066460f2abcfcf8ff0f0066470f2abcfef8ff0f00

bits 64

cvtpi2pd xmm0, mm0
cvtpi2pd xmm0, mm1
cvtpi2pd xmm0, mm7
cvtpi2pd xmm1, mm0
cvtpi2pd xmm1, mm1
cvtpi2pd xmm1, mm7
cvtpi2pd xmm15, mm0
cvtpi2pd xmm15, mm1
cvtpi2pd xmm15, mm7
cvtpi2pd xmm0, qword [0x0]
cvtpi2pd xmm0, qword [0xFF]
cvtpi2pd xmm0, qword [rel $ + 0x0]
cvtpi2pd xmm0, qword [rel $ + 0xFF]
cvtpi2pd xmm0, qword [rel $ + 0xFFFF]
cvtpi2pd xmm0, qword [rax]
cvtpi2pd xmm0, qword [rax + 0x0]
cvtpi2pd xmm0, qword [rax + 0xFFFF]
cvtpi2pd xmm0, qword [r15 + 0xFFFF]
cvtpi2pd xmm0, qword [rax + rsi * 1  + 0x0]
cvtpi2pd xmm0, qword [rax + rsi + 0xFFFF]
cvtpi2pd xmm0, qword [r15 + rsi + 0xFFFF]
cvtpi2pd xmm0, qword [rax + r15 + 0xFFFF]
cvtpi2pd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
cvtpi2pd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
cvtpi2pd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
cvtpi2pd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
cvtpi2pd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
cvtpi2pd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
cvtpi2pd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
cvtpi2pd xmm1, qword [0x0]
cvtpi2pd xmm1, qword [0xFF]
cvtpi2pd xmm1, qword [rel $ + 0x0]
cvtpi2pd xmm1, qword [rel $ + 0xFF]
cvtpi2pd xmm1, qword [rel $ + 0xFFFF]
cvtpi2pd xmm1, qword [rax]
cvtpi2pd xmm1, qword [rax + 0x0]
cvtpi2pd xmm1, qword [rax + 0xFFFF]
cvtpi2pd xmm1, qword [r15 + 0xFFFF]
cvtpi2pd xmm1, qword [rax + rsi * 1  + 0x0]
cvtpi2pd xmm1, qword [rax + rsi + 0xFFFF]
cvtpi2pd xmm1, qword [r15 + rsi + 0xFFFF]
cvtpi2pd xmm1, qword [rax + r15 + 0xFFFF]
cvtpi2pd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
cvtpi2pd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
cvtpi2pd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
cvtpi2pd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
cvtpi2pd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
cvtpi2pd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
cvtpi2pd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
cvtpi2pd xmm15, qword [0x0]
cvtpi2pd xmm15, qword [0xFF]
cvtpi2pd xmm15, qword [rel $ + 0x0]
cvtpi2pd xmm15, qword [rel $ + 0xFF]
cvtpi2pd xmm15, qword [rel $ + 0xFFFF]
cvtpi2pd xmm15, qword [rax]
cvtpi2pd xmm15, qword [rax + 0x0]
cvtpi2pd xmm15, qword [rax + 0xFFFF]
cvtpi2pd xmm15, qword [r15 + 0xFFFF]
cvtpi2pd xmm15, qword [rax + rsi * 1  + 0x0]
cvtpi2pd xmm15, qword [rax + rsi + 0xFFFF]
cvtpi2pd xmm15, qword [r15 + rsi + 0xFFFF]
cvtpi2pd xmm15, qword [rax + r15 + 0xFFFF]
cvtpi2pd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
cvtpi2pd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
cvtpi2pd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
cvtpi2pd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
cvtpi2pd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
cvtpi2pd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
cvtpi2pd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
