; expect: 660fedc0660fedc166410fedc7660fedc8660fedc966410fedcf66440fedf866440fedf966450fedff660fed042500000000660fed0425ff000000660fed05f8ffffff660fed05f7000000660fed05f7ff0000660fed00660fed00660fed80ffff000066410fed87ffff0000660fed0430660fed8430ffff000066410fed8437ffff000066420fed8438ffff0000660fed8470f2ff0f00660fed84b0f4ff0f00660fed84f0f8ff0f00660fed84c4f8ff0f0066410fed84c7f8ff0f0066420fed84fcf8ff0f0066430fed84fef8ff0f00660fed0c2500000000660fed0c25ff000000660fed0df8ffffff660fed0df7000000660fed0df7ff0000660fed08660fed08660fed88ffff000066410fed8fffff0000660fed0c30660fed8c30ffff000066410fed8c37ffff000066420fed8c38ffff0000660fed8c70f2ff0f00660fed8cb0f4ff0f00660fed8cf0f8ff0f00660fed8cc4f8ff0f0066410fed8cc7f8ff0f0066420fed8cfcf8ff0f0066430fed8cfef8ff0f0066440fed3c250000000066440fed3c25ff00000066440fed3df7ffffff66440fed3df600000066440fed3df6ff000066440fed3866440fed3866440fedb8ffff000066450fedbfffff000066440fed3c3066440fedbc30ffff000066450fedbc37ffff000066460fedbc38ffff000066440fedbc70f2ff0f0066440fedbcb0f4ff0f0066440fedbcf0f8ff0f0066440fedbcc4f8ff0f0066450fedbcc7f8ff0f0066460fedbcfcf8ff0f0066470fedbcfef8ff0f00

bits 64

paddsw xmm0, xmm0
paddsw xmm0, xmm1
paddsw xmm0, xmm15
paddsw xmm1, xmm0
paddsw xmm1, xmm1
paddsw xmm1, xmm15
paddsw xmm15, xmm0
paddsw xmm15, xmm1
paddsw xmm15, xmm15
paddsw xmm0, [0x0]
paddsw xmm0, [0xFF]
paddsw xmm0, [rel $ + 0x0]
paddsw xmm0, [rel $ + 0xFF]
paddsw xmm0, [rel $ + 0xFFFF]
paddsw xmm0, [rax]
paddsw xmm0, [rax + 0x0]
paddsw xmm0, [rax + 0xFFFF]
paddsw xmm0, [r15 + 0xFFFF]
paddsw xmm0, [rax + rsi * 1  + 0x0]
paddsw xmm0, [rax + rsi + 0xFFFF]
paddsw xmm0, [r15 + rsi + 0xFFFF]
paddsw xmm0, [rax + r15 + 0xFFFF]
paddsw xmm0, [rax + rsi * 2 + 0xFFFF2]
paddsw xmm0, [rax + rsi * 4 + 0xFFFF4]
paddsw xmm0, [rax + rsi * 8 + 0xFFFF8]
paddsw xmm0, [rsp + rax * 8 + 0xFFFF8]
paddsw xmm0, [r15 + rax * 8 + 0xFFFF8]
paddsw xmm0, [rsp + r15 * 8 + 0xFFFF8]
paddsw xmm0, [r14 + r15 * 8 + 0xFFFF8]
paddsw xmm1, [0x0]
paddsw xmm1, [0xFF]
paddsw xmm1, [rel $ + 0x0]
paddsw xmm1, [rel $ + 0xFF]
paddsw xmm1, [rel $ + 0xFFFF]
paddsw xmm1, [rax]
paddsw xmm1, [rax + 0x0]
paddsw xmm1, [rax + 0xFFFF]
paddsw xmm1, [r15 + 0xFFFF]
paddsw xmm1, [rax + rsi * 1  + 0x0]
paddsw xmm1, [rax + rsi + 0xFFFF]
paddsw xmm1, [r15 + rsi + 0xFFFF]
paddsw xmm1, [rax + r15 + 0xFFFF]
paddsw xmm1, [rax + rsi * 2 + 0xFFFF2]
paddsw xmm1, [rax + rsi * 4 + 0xFFFF4]
paddsw xmm1, [rax + rsi * 8 + 0xFFFF8]
paddsw xmm1, [rsp + rax * 8 + 0xFFFF8]
paddsw xmm1, [r15 + rax * 8 + 0xFFFF8]
paddsw xmm1, [rsp + r15 * 8 + 0xFFFF8]
paddsw xmm1, [r14 + r15 * 8 + 0xFFFF8]
paddsw xmm15, [0x0]
paddsw xmm15, [0xFF]
paddsw xmm15, [rel $ + 0x0]
paddsw xmm15, [rel $ + 0xFF]
paddsw xmm15, [rel $ + 0xFFFF]
paddsw xmm15, [rax]
paddsw xmm15, [rax + 0x0]
paddsw xmm15, [rax + 0xFFFF]
paddsw xmm15, [r15 + 0xFFFF]
paddsw xmm15, [rax + rsi * 1  + 0x0]
paddsw xmm15, [rax + rsi + 0xFFFF]
paddsw xmm15, [r15 + rsi + 0xFFFF]
paddsw xmm15, [rax + r15 + 0xFFFF]
paddsw xmm15, [rax + rsi * 2 + 0xFFFF2]
paddsw xmm15, [rax + rsi * 4 + 0xFFFF4]
paddsw xmm15, [rax + rsi * 8 + 0xFFFF8]
paddsw xmm15, [rsp + rax * 8 + 0xFFFF8]
paddsw xmm15, [r15 + rax * 8 + 0xFFFF8]
paddsw xmm15, [rsp + r15 * 8 + 0xFFFF8]
paddsw xmm15, [r14 + r15 * 8 + 0xFFFF8]
