; expect: 660f38dec0660f38dec166410f38dec7660f38dec8660f38dec966410f38decf66440f38def866440f38def966450f38deff660f38de042500000000660f38de0425ff000000660f38de05f7ffffff660f38de05f6000000660f38de05f6ff0000660f38de00660f38de00660f38de80ffff000066410f38de87ffff0000660f38de0430660f38de8430ffff000066410f38de8437ffff000066420f38de8438ffff0000660f38de8470f2ff0f00660f38de84b0f4ff0f00660f38de84f0f8ff0f00660f38de84c4f8ff0f0066410f38de84c7f8ff0f0066420f38de84fcf8ff0f0066430f38de84fef8ff0f00660f38de0c2500000000660f38de0c25ff000000660f38de0df7ffffff660f38de0df6000000660f38de0df6ff0000660f38de08660f38de08660f38de88ffff000066410f38de8fffff0000660f38de0c30660f38de8c30ffff000066410f38de8c37ffff000066420f38de8c38ffff0000660f38de8c70f2ff0f00660f38de8cb0f4ff0f00660f38de8cf0f8ff0f00660f38de8cc4f8ff0f0066410f38de8cc7f8ff0f0066420f38de8cfcf8ff0f0066430f38de8cfef8ff0f0066440f38de3c250000000066440f38de3c25ff00000066440f38de3df6ffffff66440f38de3df500000066440f38de3df5ff000066440f38de3866440f38de3866440f38deb8ffff000066450f38debfffff000066440f38de3c3066440f38debc30ffff000066450f38debc37ffff000066460f38debc38ffff000066440f38debc70f2ff0f0066440f38debcb0f4ff0f0066440f38debcf0f8ff0f0066440f38debcc4f8ff0f0066450f38debcc7f8ff0f0066460f38debcfcf8ff0f0066470f38debcfef8ff0f00

bits 64

aesdec xmm0, xmm0
aesdec xmm0, xmm1
aesdec xmm0, xmm15
aesdec xmm1, xmm0
aesdec xmm1, xmm1
aesdec xmm1, xmm15
aesdec xmm15, xmm0
aesdec xmm15, xmm1
aesdec xmm15, xmm15
aesdec xmm0, [0x0]
aesdec xmm0, [0xFF]
aesdec xmm0, [rel $ + 0x0]
aesdec xmm0, [rel $ + 0xFF]
aesdec xmm0, [rel $ + 0xFFFF]
aesdec xmm0, [rax]
aesdec xmm0, [rax + 0x0]
aesdec xmm0, [rax + 0xFFFF]
aesdec xmm0, [r15 + 0xFFFF]
aesdec xmm0, [rax + rsi * 1  + 0x0]
aesdec xmm0, [rax + rsi + 0xFFFF]
aesdec xmm0, [r15 + rsi + 0xFFFF]
aesdec xmm0, [rax + r15 + 0xFFFF]
aesdec xmm0, [rax + rsi * 2 + 0xFFFF2]
aesdec xmm0, [rax + rsi * 4 + 0xFFFF4]
aesdec xmm0, [rax + rsi * 8 + 0xFFFF8]
aesdec xmm0, [rsp + rax * 8 + 0xFFFF8]
aesdec xmm0, [r15 + rax * 8 + 0xFFFF8]
aesdec xmm0, [rsp + r15 * 8 + 0xFFFF8]
aesdec xmm0, [r14 + r15 * 8 + 0xFFFF8]
aesdec xmm1, [0x0]
aesdec xmm1, [0xFF]
aesdec xmm1, [rel $ + 0x0]
aesdec xmm1, [rel $ + 0xFF]
aesdec xmm1, [rel $ + 0xFFFF]
aesdec xmm1, [rax]
aesdec xmm1, [rax + 0x0]
aesdec xmm1, [rax + 0xFFFF]
aesdec xmm1, [r15 + 0xFFFF]
aesdec xmm1, [rax + rsi * 1  + 0x0]
aesdec xmm1, [rax + rsi + 0xFFFF]
aesdec xmm1, [r15 + rsi + 0xFFFF]
aesdec xmm1, [rax + r15 + 0xFFFF]
aesdec xmm1, [rax + rsi * 2 + 0xFFFF2]
aesdec xmm1, [rax + rsi * 4 + 0xFFFF4]
aesdec xmm1, [rax + rsi * 8 + 0xFFFF8]
aesdec xmm1, [rsp + rax * 8 + 0xFFFF8]
aesdec xmm1, [r15 + rax * 8 + 0xFFFF8]
aesdec xmm1, [rsp + r15 * 8 + 0xFFFF8]
aesdec xmm1, [r14 + r15 * 8 + 0xFFFF8]
aesdec xmm15, [0x0]
aesdec xmm15, [0xFF]
aesdec xmm15, [rel $ + 0x0]
aesdec xmm15, [rel $ + 0xFF]
aesdec xmm15, [rel $ + 0xFFFF]
aesdec xmm15, [rax]
aesdec xmm15, [rax + 0x0]
aesdec xmm15, [rax + 0xFFFF]
aesdec xmm15, [r15 + 0xFFFF]
aesdec xmm15, [rax + rsi * 1  + 0x0]
aesdec xmm15, [rax + rsi + 0xFFFF]
aesdec xmm15, [r15 + rsi + 0xFFFF]
aesdec xmm15, [rax + r15 + 0xFFFF]
aesdec xmm15, [rax + rsi * 2 + 0xFFFF2]
aesdec xmm15, [rax + rsi * 4 + 0xFFFF4]
aesdec xmm15, [rax + rsi * 8 + 0xFFFF8]
aesdec xmm15, [rsp + rax * 8 + 0xFFFF8]
aesdec xmm15, [r15 + rax * 8 + 0xFFFF8]
aesdec xmm15, [rsp + r15 * 8 + 0xFFFF8]
aesdec xmm15, [r14 + r15 * 8 + 0xFFFF8]
