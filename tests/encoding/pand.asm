; expect: 660fdbc0660fdbc166410fdbc7660fdbc8660fdbc966410fdbcf66440fdbf866440fdbf966450fdbff660fdb042500000000660fdb0425ff000000660fdb05f8ffffff660fdb05f7000000660fdb05f7ff0000660fdb00660fdb00660fdb80ffff000066410fdb87ffff0000660fdb0430660fdb8430ffff000066410fdb8437ffff000066420fdb8438ffff0000660fdb8470f2ff0f00660fdb84b0f4ff0f00660fdb84f0f8ff0f00660fdb84c4f8ff0f0066410fdb84c7f8ff0f0066420fdb84fcf8ff0f0066430fdb84fef8ff0f00660fdb0c2500000000660fdb0c25ff000000660fdb0df8ffffff660fdb0df7000000660fdb0df7ff0000660fdb08660fdb08660fdb88ffff000066410fdb8fffff0000660fdb0c30660fdb8c30ffff000066410fdb8c37ffff000066420fdb8c38ffff0000660fdb8c70f2ff0f00660fdb8cb0f4ff0f00660fdb8cf0f8ff0f00660fdb8cc4f8ff0f0066410fdb8cc7f8ff0f0066420fdb8cfcf8ff0f0066430fdb8cfef8ff0f0066440fdb3c250000000066440fdb3c25ff00000066440fdb3df7ffffff66440fdb3df600000066440fdb3df6ff000066440fdb3866440fdb3866440fdbb8ffff000066450fdbbfffff000066440fdb3c3066440fdbbc30ffff000066450fdbbc37ffff000066460fdbbc38ffff000066440fdbbc70f2ff0f0066440fdbbcb0f4ff0f0066440fdbbcf0f8ff0f0066440fdbbcc4f8ff0f0066450fdbbcc7f8ff0f0066460fdbbcfcf8ff0f0066470fdbbcfef8ff0f00

bits 64

pand xmm0, xmm0
pand xmm0, xmm1
pand xmm0, xmm15
pand xmm1, xmm0
pand xmm1, xmm1
pand xmm1, xmm15
pand xmm15, xmm0
pand xmm15, xmm1
pand xmm15, xmm15
pand xmm0, [0x0]
pand xmm0, [0xFF]
pand xmm0, [rel $ + 0x0]
pand xmm0, [rel $ + 0xFF]
pand xmm0, [rel $ + 0xFFFF]
pand xmm0, [rax]
pand xmm0, [rax + 0x0]
pand xmm0, [rax + 0xFFFF]
pand xmm0, [r15 + 0xFFFF]
pand xmm0, [rax + rsi * 1  + 0x0]
pand xmm0, [rax + rsi + 0xFFFF]
pand xmm0, [r15 + rsi + 0xFFFF]
pand xmm0, [rax + r15 + 0xFFFF]
pand xmm0, [rax + rsi * 2 + 0xFFFF2]
pand xmm0, [rax + rsi * 4 + 0xFFFF4]
pand xmm0, [rax + rsi * 8 + 0xFFFF8]
pand xmm0, [rsp + rax * 8 + 0xFFFF8]
pand xmm0, [r15 + rax * 8 + 0xFFFF8]
pand xmm0, [rsp + r15 * 8 + 0xFFFF8]
pand xmm0, [r14 + r15 * 8 + 0xFFFF8]
pand xmm1, [0x0]
pand xmm1, [0xFF]
pand xmm1, [rel $ + 0x0]
pand xmm1, [rel $ + 0xFF]
pand xmm1, [rel $ + 0xFFFF]
pand xmm1, [rax]
pand xmm1, [rax + 0x0]
pand xmm1, [rax + 0xFFFF]
pand xmm1, [r15 + 0xFFFF]
pand xmm1, [rax + rsi * 1  + 0x0]
pand xmm1, [rax + rsi + 0xFFFF]
pand xmm1, [r15 + rsi + 0xFFFF]
pand xmm1, [rax + r15 + 0xFFFF]
pand xmm1, [rax + rsi * 2 + 0xFFFF2]
pand xmm1, [rax + rsi * 4 + 0xFFFF4]
pand xmm1, [rax + rsi * 8 + 0xFFFF8]
pand xmm1, [rsp + rax * 8 + 0xFFFF8]
pand xmm1, [r15 + rax * 8 + 0xFFFF8]
pand xmm1, [rsp + r15 * 8 + 0xFFFF8]
pand xmm1, [r14 + r15 * 8 + 0xFFFF8]
pand xmm15, [0x0]
pand xmm15, [0xFF]
pand xmm15, [rel $ + 0x0]
pand xmm15, [rel $ + 0xFF]
pand xmm15, [rel $ + 0xFFFF]
pand xmm15, [rax]
pand xmm15, [rax + 0x0]
pand xmm15, [rax + 0xFFFF]
pand xmm15, [r15 + 0xFFFF]
pand xmm15, [rax + rsi * 1  + 0x0]
pand xmm15, [rax + rsi + 0xFFFF]
pand xmm15, [r15 + rsi + 0xFFFF]
pand xmm15, [rax + r15 + 0xFFFF]
pand xmm15, [rax + rsi * 2 + 0xFFFF2]
pand xmm15, [rax + rsi * 4 + 0xFFFF4]
pand xmm15, [rax + rsi * 8 + 0xFFFF8]
pand xmm15, [rsp + rax * 8 + 0xFFFF8]
pand xmm15, [r15 + rax * 8 + 0xFFFF8]
pand xmm15, [rsp + r15 * 8 + 0xFFFF8]
pand xmm15, [r14 + r15 * 8 + 0xFFFF8]
