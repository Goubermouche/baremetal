; expect: 0ffbc00ffbc10ffbc70ffbc80ffbc90ffbcf0ffbf80ffbf90ffbff660ffbc0660ffbc166410ffbc7660ffbc8660ffbc966410ffbcf66440ffbf866440ffbf966450ffbff660ffb042500000000660ffb0425ff000000660ffb05f8ffffff660ffb05f7000000660ffb05f7ff0000660ffb00660ffb00660ffb80ffff000066410ffb87ffff0000660ffb0430660ffb8430ffff000066410ffb8437ffff000066420ffb8438ffff0000660ffb8470f2ff0f00660ffb84b0f4ff0f00660ffb84f0f8ff0f00660ffb84c4f8ff0f0066410ffb84c7f8ff0f0066420ffb84fcf8ff0f0066430ffb84fef8ff0f00660ffb0c2500000000660ffb0c25ff000000660ffb0df8ffffff660ffb0df7000000660ffb0df7ff0000660ffb08660ffb08660ffb88ffff000066410ffb8fffff0000660ffb0c30660ffb8c30ffff000066410ffb8c37ffff000066420ffb8c38ffff0000660ffb8c70f2ff0f00660ffb8cb0f4ff0f00660ffb8cf0f8ff0f00660ffb8cc4f8ff0f0066410ffb8cc7f8ff0f0066420ffb8cfcf8ff0f0066430ffb8cfef8ff0f0066440ffb3c250000000066440ffb3c25ff00000066440ffb3df7ffffff66440ffb3df600000066440ffb3df6ff000066440ffb3866440ffb3866440ffbb8ffff000066450ffbbfffff000066440ffb3c3066440ffbbc30ffff000066450ffbbc37ffff000066460ffbbc38ffff000066440ffbbc70f2ff0f0066440ffbbcb0f4ff0f0066440ffbbcf0f8ff0f0066440ffbbcc4f8ff0f0066450ffbbcc7f8ff0f0066460ffbbcfcf8ff0f0066470ffbbcfef8ff0f00

bits 64

psubq mm0, mm0
psubq mm0, mm1
psubq mm0, mm7
psubq mm1, mm0
psubq mm1, mm1
psubq mm1, mm7
psubq mm7, mm0
psubq mm7, mm1
psubq mm7, mm7
psubq xmm0, xmm0
psubq xmm0, xmm1
psubq xmm0, xmm15
psubq xmm1, xmm0
psubq xmm1, xmm1
psubq xmm1, xmm15
psubq xmm15, xmm0
psubq xmm15, xmm1
psubq xmm15, xmm15
psubq xmm0, [0x0]
psubq xmm0, [0xFF]
psubq xmm0, [rel $ + 0x0]
psubq xmm0, [rel $ + 0xFF]
psubq xmm0, [rel $ + 0xFFFF]
psubq xmm0, [rax]
psubq xmm0, [rax + 0x0]
psubq xmm0, [rax + 0xFFFF]
psubq xmm0, [r15 + 0xFFFF]
psubq xmm0, [rax + rsi * 1  + 0x0]
psubq xmm0, [rax + rsi + 0xFFFF]
psubq xmm0, [r15 + rsi + 0xFFFF]
psubq xmm0, [rax + r15 + 0xFFFF]
psubq xmm0, [rax + rsi * 2 + 0xFFFF2]
psubq xmm0, [rax + rsi * 4 + 0xFFFF4]
psubq xmm0, [rax + rsi * 8 + 0xFFFF8]
psubq xmm0, [rsp + rax * 8 + 0xFFFF8]
psubq xmm0, [r15 + rax * 8 + 0xFFFF8]
psubq xmm0, [rsp + r15 * 8 + 0xFFFF8]
psubq xmm0, [r14 + r15 * 8 + 0xFFFF8]
psubq xmm1, [0x0]
psubq xmm1, [0xFF]
psubq xmm1, [rel $ + 0x0]
psubq xmm1, [rel $ + 0xFF]
psubq xmm1, [rel $ + 0xFFFF]
psubq xmm1, [rax]
psubq xmm1, [rax + 0x0]
psubq xmm1, [rax + 0xFFFF]
psubq xmm1, [r15 + 0xFFFF]
psubq xmm1, [rax + rsi * 1  + 0x0]
psubq xmm1, [rax + rsi + 0xFFFF]
psubq xmm1, [r15 + rsi + 0xFFFF]
psubq xmm1, [rax + r15 + 0xFFFF]
psubq xmm1, [rax + rsi * 2 + 0xFFFF2]
psubq xmm1, [rax + rsi * 4 + 0xFFFF4]
psubq xmm1, [rax + rsi * 8 + 0xFFFF8]
psubq xmm1, [rsp + rax * 8 + 0xFFFF8]
psubq xmm1, [r15 + rax * 8 + 0xFFFF8]
psubq xmm1, [rsp + r15 * 8 + 0xFFFF8]
psubq xmm1, [r14 + r15 * 8 + 0xFFFF8]
psubq xmm15, [0x0]
psubq xmm15, [0xFF]
psubq xmm15, [rel $ + 0x0]
psubq xmm15, [rel $ + 0xFF]
psubq xmm15, [rel $ + 0xFFFF]
psubq xmm15, [rax]
psubq xmm15, [rax + 0x0]
psubq xmm15, [rax + 0xFFFF]
psubq xmm15, [r15 + 0xFFFF]
psubq xmm15, [rax + rsi * 1  + 0x0]
psubq xmm15, [rax + rsi + 0xFFFF]
psubq xmm15, [r15 + rsi + 0xFFFF]
psubq xmm15, [rax + r15 + 0xFFFF]
psubq xmm15, [rax + rsi * 2 + 0xFFFF2]
psubq xmm15, [rax + rsi * 4 + 0xFFFF4]
psubq xmm15, [rax + rsi * 8 + 0xFFFF8]
psubq xmm15, [rsp + rax * 8 + 0xFFFF8]
psubq xmm15, [r15 + rax * 8 + 0xFFFF8]
psubq xmm15, [rsp + r15 * 8 + 0xFFFF8]
psubq xmm15, [r14 + r15 * 8 + 0xFFFF8]
