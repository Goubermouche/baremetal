; expect: 660f2b042500000000660f2b0c250000000066440f2b3c2500000000660f2b0425ff000000660f2b0c25ff00000066440f2b3c25ff000000660f2b05f8ffffff660f2b0df8ffffff66440f2b3df7ffffff660f2b05f7000000660f2b0df700000066440f2b3df6000000660f2b05f7ff0000660f2b0df7ff000066440f2b3df6ff0000660f2b00660f2b0866440f2b38660f2b00660f2b0866440f2b38660f2b80ffff0000660f2b88ffff000066440f2bb8ffff000066410f2b87ffff000066410f2b8fffff000066450f2bbfffff0000660f2b0430660f2b0c3066440f2b3c30660f2b8430ffff0000660f2b8c30ffff000066440f2bbc30ffff000066410f2b8437ffff000066410f2b8c37ffff000066450f2bbc37ffff000066420f2b8438ffff000066420f2b8c38ffff000066460f2bbc38ffff0000660f2b8470f2ff0f00660f2b8c70f2ff0f0066440f2bbc70f2ff0f00660f2b84b0f4ff0f00660f2b8cb0f4ff0f0066440f2bbcb0f4ff0f00660f2b84f0f8ff0f00660f2b8cf0f8ff0f0066440f2bbcf0f8ff0f00660f2b84c4f8ff0f00660f2b8cc4f8ff0f0066440f2bbcc4f8ff0f0066410f2b84c7f8ff0f0066410f2b8cc7f8ff0f0066450f2bbcc7f8ff0f0066420f2b84fcf8ff0f0066420f2b8cfcf8ff0f0066460f2bbcfcf8ff0f0066430f2b84fef8ff0f0066430f2b8cfef8ff0f0066470f2bbcfef8ff0f00

bits 64

movntpd [0x0], xmm0
movntpd [0x0], xmm1
movntpd [0x0], xmm15
movntpd [0xFF], xmm0
movntpd [0xFF], xmm1
movntpd [0xFF], xmm15
movntpd [rel $ + 0x0], xmm0
movntpd [rel $ + 0x0], xmm1
movntpd [rel $ + 0x0], xmm15
movntpd [rel $ + 0xFF], xmm0
movntpd [rel $ + 0xFF], xmm1
movntpd [rel $ + 0xFF], xmm15
movntpd [rel $ + 0xFFFF], xmm0
movntpd [rel $ + 0xFFFF], xmm1
movntpd [rel $ + 0xFFFF], xmm15
movntpd [rax], xmm0
movntpd [rax], xmm1
movntpd [rax], xmm15
movntpd [rax + 0x0], xmm0
movntpd [rax + 0x0], xmm1
movntpd [rax + 0x0], xmm15
movntpd [rax + 0xFFFF], xmm0
movntpd [rax + 0xFFFF], xmm1
movntpd [rax + 0xFFFF], xmm15
movntpd [r15 + 0xFFFF], xmm0
movntpd [r15 + 0xFFFF], xmm1
movntpd [r15 + 0xFFFF], xmm15
movntpd [rax + rsi * 1  + 0x0], xmm0
movntpd [rax + rsi * 1  + 0x0], xmm1
movntpd [rax + rsi * 1  + 0x0], xmm15
movntpd [rax + rsi + 0xFFFF], xmm0
movntpd [rax + rsi + 0xFFFF], xmm1
movntpd [rax + rsi + 0xFFFF], xmm15
movntpd [r15 + rsi + 0xFFFF], xmm0
movntpd [r15 + rsi + 0xFFFF], xmm1
movntpd [r15 + rsi + 0xFFFF], xmm15
movntpd [rax + r15 + 0xFFFF], xmm0
movntpd [rax + r15 + 0xFFFF], xmm1
movntpd [rax + r15 + 0xFFFF], xmm15
movntpd [rax + rsi * 2 + 0xFFFF2], xmm0
movntpd [rax + rsi * 2 + 0xFFFF2], xmm1
movntpd [rax + rsi * 2 + 0xFFFF2], xmm15
movntpd [rax + rsi * 4 + 0xFFFF4], xmm0
movntpd [rax + rsi * 4 + 0xFFFF4], xmm1
movntpd [rax + rsi * 4 + 0xFFFF4], xmm15
movntpd [rax + rsi * 8 + 0xFFFF8], xmm0
movntpd [rax + rsi * 8 + 0xFFFF8], xmm1
movntpd [rax + rsi * 8 + 0xFFFF8], xmm15
movntpd [rsp + rax * 8 + 0xFFFF8], xmm0
movntpd [rsp + rax * 8 + 0xFFFF8], xmm1
movntpd [rsp + rax * 8 + 0xFFFF8], xmm15
movntpd [r15 + rax * 8 + 0xFFFF8], xmm0
movntpd [r15 + rax * 8 + 0xFFFF8], xmm1
movntpd [r15 + rax * 8 + 0xFFFF8], xmm15
movntpd [rsp + r15 * 8 + 0xFFFF8], xmm0
movntpd [rsp + r15 * 8 + 0xFFFF8], xmm1
movntpd [rsp + r15 * 8 + 0xFFFF8], xmm15
movntpd [r14 + r15 * 8 + 0xFFFF8], xmm0
movntpd [r14 + r15 * 8 + 0xFFFF8], xmm1
movntpd [r14 + r15 * 8 + 0xFFFF8], xmm15
