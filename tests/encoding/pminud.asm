; expect: 660f383bc0660f383bc166410f383bc7660f383bc8660f383bc966410f383bcf66440f383bf866440f383bf966450f383bff660f383b042500000000660f383b0425ff000000660f383b05f7ffffff660f383b05f6000000660f383b05f6ff0000660f383b00660f383b00660f383b80ffff000066410f383b87ffff0000660f383b0430660f383b8430ffff000066410f383b8437ffff000066420f383b8438ffff0000660f383b8470f2ff0f00660f383b84b0f4ff0f00660f383b84f0f8ff0f00660f383b84c4f8ff0f0066410f383b84c7f8ff0f0066420f383b84fcf8ff0f0066430f383b84fef8ff0f00660f383b0c2500000000660f383b0c25ff000000660f383b0df7ffffff660f383b0df6000000660f383b0df6ff0000660f383b08660f383b08660f383b88ffff000066410f383b8fffff0000660f383b0c30660f383b8c30ffff000066410f383b8c37ffff000066420f383b8c38ffff0000660f383b8c70f2ff0f00660f383b8cb0f4ff0f00660f383b8cf0f8ff0f00660f383b8cc4f8ff0f0066410f383b8cc7f8ff0f0066420f383b8cfcf8ff0f0066430f383b8cfef8ff0f0066440f383b3c250000000066440f383b3c25ff00000066440f383b3df6ffffff66440f383b3df500000066440f383b3df5ff000066440f383b3866440f383b3866440f383bb8ffff000066450f383bbfffff000066440f383b3c3066440f383bbc30ffff000066450f383bbc37ffff000066460f383bbc38ffff000066440f383bbc70f2ff0f0066440f383bbcb0f4ff0f0066440f383bbcf0f8ff0f0066440f383bbcc4f8ff0f0066450f383bbcc7f8ff0f0066460f383bbcfcf8ff0f0066470f383bbcfef8ff0f00

bits 64

pminud xmm0, xmm0
pminud xmm0, xmm1
pminud xmm0, xmm15
pminud xmm1, xmm0
pminud xmm1, xmm1
pminud xmm1, xmm15
pminud xmm15, xmm0
pminud xmm15, xmm1
pminud xmm15, xmm15
pminud xmm0, [0x0]
pminud xmm0, [0xFF]
pminud xmm0, [rel $ + 0x0]
pminud xmm0, [rel $ + 0xFF]
pminud xmm0, [rel $ + 0xFFFF]
pminud xmm0, [rax]
pminud xmm0, [rax + 0x0]
pminud xmm0, [rax + 0xFFFF]
pminud xmm0, [r15 + 0xFFFF]
pminud xmm0, [rax + rsi * 1  + 0x0]
pminud xmm0, [rax + rsi + 0xFFFF]
pminud xmm0, [r15 + rsi + 0xFFFF]
pminud xmm0, [rax + r15 + 0xFFFF]
pminud xmm0, [rax + rsi * 2 + 0xFFFF2]
pminud xmm0, [rax + rsi * 4 + 0xFFFF4]
pminud xmm0, [rax + rsi * 8 + 0xFFFF8]
pminud xmm0, [rsp + rax * 8 + 0xFFFF8]
pminud xmm0, [r15 + rax * 8 + 0xFFFF8]
pminud xmm0, [rsp + r15 * 8 + 0xFFFF8]
pminud xmm0, [r14 + r15 * 8 + 0xFFFF8]
pminud xmm1, [0x0]
pminud xmm1, [0xFF]
pminud xmm1, [rel $ + 0x0]
pminud xmm1, [rel $ + 0xFF]
pminud xmm1, [rel $ + 0xFFFF]
pminud xmm1, [rax]
pminud xmm1, [rax + 0x0]
pminud xmm1, [rax + 0xFFFF]
pminud xmm1, [r15 + 0xFFFF]
pminud xmm1, [rax + rsi * 1  + 0x0]
pminud xmm1, [rax + rsi + 0xFFFF]
pminud xmm1, [r15 + rsi + 0xFFFF]
pminud xmm1, [rax + r15 + 0xFFFF]
pminud xmm1, [rax + rsi * 2 + 0xFFFF2]
pminud xmm1, [rax + rsi * 4 + 0xFFFF4]
pminud xmm1, [rax + rsi * 8 + 0xFFFF8]
pminud xmm1, [rsp + rax * 8 + 0xFFFF8]
pminud xmm1, [r15 + rax * 8 + 0xFFFF8]
pminud xmm1, [rsp + r15 * 8 + 0xFFFF8]
pminud xmm1, [r14 + r15 * 8 + 0xFFFF8]
pminud xmm15, [0x0]
pminud xmm15, [0xFF]
pminud xmm15, [rel $ + 0x0]
pminud xmm15, [rel $ + 0xFF]
pminud xmm15, [rel $ + 0xFFFF]
pminud xmm15, [rax]
pminud xmm15, [rax + 0x0]
pminud xmm15, [rax + 0xFFFF]
pminud xmm15, [r15 + 0xFFFF]
pminud xmm15, [rax + rsi * 1  + 0x0]
pminud xmm15, [rax + rsi + 0xFFFF]
pminud xmm15, [r15 + rsi + 0xFFFF]
pminud xmm15, [rax + r15 + 0xFFFF]
pminud xmm15, [rax + rsi * 2 + 0xFFFF2]
pminud xmm15, [rax + rsi * 4 + 0xFFFF4]
pminud xmm15, [rax + rsi * 8 + 0xFFFF8]
pminud xmm15, [rsp + rax * 8 + 0xFFFF8]
pminud xmm15, [r15 + rax * 8 + 0xFFFF8]
pminud xmm15, [rsp + r15 * 8 + 0xFFFF8]
pminud xmm15, [r14 + r15 * 8 + 0xFFFF8]
