; expect: 660f6fc0660f6fc166410f6fc7660f6fc8660f6fc966410f6fcf66440f6ff866440f6ff966450f6fff660f6f042500000000660f6f0425ff000000660f6f05f8ffffff660f6f05f7000000660f6f05f7ff0000660f6f00660f6f00660f6f80ffff000066410f6f87ffff0000660f6f0430660f6f8430ffff000066410f6f8437ffff000066420f6f8438ffff0000660f6f8470f2ff0f00660f6f84b0f4ff0f00660f6f84f0f8ff0f00660f6f84c4f8ff0f0066410f6f84c7f8ff0f0066420f6f84fcf8ff0f0066430f6f84fef8ff0f00660f6f0c2500000000660f6f0c25ff000000660f6f0df8ffffff660f6f0df7000000660f6f0df7ff0000660f6f08660f6f08660f6f88ffff000066410f6f8fffff0000660f6f0c30660f6f8c30ffff000066410f6f8c37ffff000066420f6f8c38ffff0000660f6f8c70f2ff0f00660f6f8cb0f4ff0f00660f6f8cf0f8ff0f00660f6f8cc4f8ff0f0066410f6f8cc7f8ff0f0066420f6f8cfcf8ff0f0066430f6f8cfef8ff0f0066440f6f3c250000000066440f6f3c25ff00000066440f6f3df7ffffff66440f6f3df600000066440f6f3df6ff000066440f6f3866440f6f3866440f6fb8ffff000066450f6fbfffff000066440f6f3c3066440f6fbc30ffff000066450f6fbc37ffff000066460f6fbc38ffff000066440f6fbc70f2ff0f0066440f6fbcb0f4ff0f0066440f6fbcf0f8ff0f0066440f6fbcc4f8ff0f0066450f6fbcc7f8ff0f0066460f6fbcfcf8ff0f0066470f6fbcfef8ff0f00660f7f042500000000660f7f0c250000000066440f7f3c2500000000660f7f0425ff000000660f7f0c25ff00000066440f7f3c25ff000000660f7f05f8ffffff660f7f0df8ffffff66440f7f3df7ffffff660f7f05f7000000660f7f0df700000066440f7f3df6000000660f7f05f7ff0000660f7f0df7ff000066440f7f3df6ff0000660f7f00660f7f0866440f7f38660f7f00660f7f0866440f7f38660f7f80ffff0000660f7f88ffff000066440f7fb8ffff000066410f7f87ffff000066410f7f8fffff000066450f7fbfffff0000660f7f0430660f7f0c3066440f7f3c30660f7f8430ffff0000660f7f8c30ffff000066440f7fbc30ffff000066410f7f8437ffff000066410f7f8c37ffff000066450f7fbc37ffff000066420f7f8438ffff000066420f7f8c38ffff000066460f7fbc38ffff0000660f7f8470f2ff0f00660f7f8c70f2ff0f0066440f7fbc70f2ff0f00660f7f84b0f4ff0f00660f7f8cb0f4ff0f0066440f7fbcb0f4ff0f00660f7f84f0f8ff0f00660f7f8cf0f8ff0f0066440f7fbcf0f8ff0f00660f7f84c4f8ff0f00660f7f8cc4f8ff0f0066440f7fbcc4f8ff0f0066410f7f84c7f8ff0f0066410f7f8cc7f8ff0f0066450f7fbcc7f8ff0f0066420f7f84fcf8ff0f0066420f7f8cfcf8ff0f0066460f7fbcfcf8ff0f0066430f7f84fef8ff0f0066430f7f8cfef8ff0f0066470f7fbcfef8ff0f00

bits 64

movdqa xmm0, xmm0
movdqa xmm0, xmm1
movdqa xmm0, xmm15
movdqa xmm1, xmm0
movdqa xmm1, xmm1
movdqa xmm1, xmm15
movdqa xmm15, xmm0
movdqa xmm15, xmm1
movdqa xmm15, xmm15
movdqa xmm0, [0x0]
movdqa xmm0, [0xFF]
movdqa xmm0, [rel $ + 0x0]
movdqa xmm0, [rel $ + 0xFF]
movdqa xmm0, [rel $ + 0xFFFF]
movdqa xmm0, [rax]
movdqa xmm0, [rax + 0x0]
movdqa xmm0, [rax + 0xFFFF]
movdqa xmm0, [r15 + 0xFFFF]
movdqa xmm0, [rax + rsi * 1  + 0x0]
movdqa xmm0, [rax + rsi + 0xFFFF]
movdqa xmm0, [r15 + rsi + 0xFFFF]
movdqa xmm0, [rax + r15 + 0xFFFF]
movdqa xmm0, [rax + rsi * 2 + 0xFFFF2]
movdqa xmm0, [rax + rsi * 4 + 0xFFFF4]
movdqa xmm0, [rax + rsi * 8 + 0xFFFF8]
movdqa xmm0, [rsp + rax * 8 + 0xFFFF8]
movdqa xmm0, [r15 + rax * 8 + 0xFFFF8]
movdqa xmm0, [rsp + r15 * 8 + 0xFFFF8]
movdqa xmm0, [r14 + r15 * 8 + 0xFFFF8]
movdqa xmm1, [0x0]
movdqa xmm1, [0xFF]
movdqa xmm1, [rel $ + 0x0]
movdqa xmm1, [rel $ + 0xFF]
movdqa xmm1, [rel $ + 0xFFFF]
movdqa xmm1, [rax]
movdqa xmm1, [rax + 0x0]
movdqa xmm1, [rax + 0xFFFF]
movdqa xmm1, [r15 + 0xFFFF]
movdqa xmm1, [rax + rsi * 1  + 0x0]
movdqa xmm1, [rax + rsi + 0xFFFF]
movdqa xmm1, [r15 + rsi + 0xFFFF]
movdqa xmm1, [rax + r15 + 0xFFFF]
movdqa xmm1, [rax + rsi * 2 + 0xFFFF2]
movdqa xmm1, [rax + rsi * 4 + 0xFFFF4]
movdqa xmm1, [rax + rsi * 8 + 0xFFFF8]
movdqa xmm1, [rsp + rax * 8 + 0xFFFF8]
movdqa xmm1, [r15 + rax * 8 + 0xFFFF8]
movdqa xmm1, [rsp + r15 * 8 + 0xFFFF8]
movdqa xmm1, [r14 + r15 * 8 + 0xFFFF8]
movdqa xmm15, [0x0]
movdqa xmm15, [0xFF]
movdqa xmm15, [rel $ + 0x0]
movdqa xmm15, [rel $ + 0xFF]
movdqa xmm15, [rel $ + 0xFFFF]
movdqa xmm15, [rax]
movdqa xmm15, [rax + 0x0]
movdqa xmm15, [rax + 0xFFFF]
movdqa xmm15, [r15 + 0xFFFF]
movdqa xmm15, [rax + rsi * 1  + 0x0]
movdqa xmm15, [rax + rsi + 0xFFFF]
movdqa xmm15, [r15 + rsi + 0xFFFF]
movdqa xmm15, [rax + r15 + 0xFFFF]
movdqa xmm15, [rax + rsi * 2 + 0xFFFF2]
movdqa xmm15, [rax + rsi * 4 + 0xFFFF4]
movdqa xmm15, [rax + rsi * 8 + 0xFFFF8]
movdqa xmm15, [rsp + rax * 8 + 0xFFFF8]
movdqa xmm15, [r15 + rax * 8 + 0xFFFF8]
movdqa xmm15, [rsp + r15 * 8 + 0xFFFF8]
movdqa xmm15, [r14 + r15 * 8 + 0xFFFF8]
movdqa [0x0], xmm0
movdqa [0x0], xmm1
movdqa [0x0], xmm15
movdqa [0xFF], xmm0
movdqa [0xFF], xmm1
movdqa [0xFF], xmm15
movdqa [rel $ + 0x0], xmm0
movdqa [rel $ + 0x0], xmm1
movdqa [rel $ + 0x0], xmm15
movdqa [rel $ + 0xFF], xmm0
movdqa [rel $ + 0xFF], xmm1
movdqa [rel $ + 0xFF], xmm15
movdqa [rel $ + 0xFFFF], xmm0
movdqa [rel $ + 0xFFFF], xmm1
movdqa [rel $ + 0xFFFF], xmm15
movdqa [rax], xmm0
movdqa [rax], xmm1
movdqa [rax], xmm15
movdqa [rax + 0x0], xmm0
movdqa [rax + 0x0], xmm1
movdqa [rax + 0x0], xmm15
movdqa [rax + 0xFFFF], xmm0
movdqa [rax + 0xFFFF], xmm1
movdqa [rax + 0xFFFF], xmm15
movdqa [r15 + 0xFFFF], xmm0
movdqa [r15 + 0xFFFF], xmm1
movdqa [r15 + 0xFFFF], xmm15
movdqa [rax + rsi * 1  + 0x0], xmm0
movdqa [rax + rsi * 1  + 0x0], xmm1
movdqa [rax + rsi * 1  + 0x0], xmm15
movdqa [rax + rsi + 0xFFFF], xmm0
movdqa [rax + rsi + 0xFFFF], xmm1
movdqa [rax + rsi + 0xFFFF], xmm15
movdqa [r15 + rsi + 0xFFFF], xmm0
movdqa [r15 + rsi + 0xFFFF], xmm1
movdqa [r15 + rsi + 0xFFFF], xmm15
movdqa [rax + r15 + 0xFFFF], xmm0
movdqa [rax + r15 + 0xFFFF], xmm1
movdqa [rax + r15 + 0xFFFF], xmm15
movdqa [rax + rsi * 2 + 0xFFFF2], xmm0
movdqa [rax + rsi * 2 + 0xFFFF2], xmm1
movdqa [rax + rsi * 2 + 0xFFFF2], xmm15
movdqa [rax + rsi * 4 + 0xFFFF4], xmm0
movdqa [rax + rsi * 4 + 0xFFFF4], xmm1
movdqa [rax + rsi * 4 + 0xFFFF4], xmm15
movdqa [rax + rsi * 8 + 0xFFFF8], xmm0
movdqa [rax + rsi * 8 + 0xFFFF8], xmm1
movdqa [rax + rsi * 8 + 0xFFFF8], xmm15
movdqa [rsp + rax * 8 + 0xFFFF8], xmm0
movdqa [rsp + rax * 8 + 0xFFFF8], xmm1
movdqa [rsp + rax * 8 + 0xFFFF8], xmm15
movdqa [r15 + rax * 8 + 0xFFFF8], xmm0
movdqa [r15 + rax * 8 + 0xFFFF8], xmm1
movdqa [r15 + rax * 8 + 0xFFFF8], xmm15
movdqa [rsp + r15 * 8 + 0xFFFF8], xmm0
movdqa [rsp + r15 * 8 + 0xFFFF8], xmm1
movdqa [rsp + r15 * 8 + 0xFFFF8], xmm15
movdqa [r14 + r15 * 8 + 0xFFFF8], xmm0
movdqa [r14 + r15 * 8 + 0xFFFF8], xmm1
movdqa [r14 + r15 * 8 + 0xFFFF8], xmm15
