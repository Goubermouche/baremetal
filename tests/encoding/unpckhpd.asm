; expect: 660f15c0660f15c166410f15c7660f15c8660f15c966410f15cf66440f15f866440f15f966450f15ff660f15042500000000660f150425ff000000660f1505f8ffffff660f1505f7000000660f1505f7ff0000660f1500660f1500660f1580ffff000066410f1587ffff0000660f150430660f158430ffff000066410f158437ffff000066420f158438ffff0000660f158470f2ff0f00660f1584b0f4ff0f00660f1584f0f8ff0f00660f1584c4f8ff0f0066410f1584c7f8ff0f0066420f1584fcf8ff0f0066430f1584fef8ff0f00660f150c2500000000660f150c25ff000000660f150df8ffffff660f150df7000000660f150df7ff0000660f1508660f1508660f1588ffff000066410f158fffff0000660f150c30660f158c30ffff000066410f158c37ffff000066420f158c38ffff0000660f158c70f2ff0f00660f158cb0f4ff0f00660f158cf0f8ff0f00660f158cc4f8ff0f0066410f158cc7f8ff0f0066420f158cfcf8ff0f0066430f158cfef8ff0f0066440f153c250000000066440f153c25ff00000066440f153df7ffffff66440f153df600000066440f153df6ff000066440f153866440f153866440f15b8ffff000066450f15bfffff000066440f153c3066440f15bc30ffff000066450f15bc37ffff000066460f15bc38ffff000066440f15bc70f2ff0f0066440f15bcb0f4ff0f0066440f15bcf0f8ff0f0066440f15bcc4f8ff0f0066450f15bcc7f8ff0f0066460f15bcfcf8ff0f0066470f15bcfef8ff0f00

bits 64

unpckhpd xmm0, xmm0
unpckhpd xmm0, xmm1
unpckhpd xmm0, xmm15
unpckhpd xmm1, xmm0
unpckhpd xmm1, xmm1
unpckhpd xmm1, xmm15
unpckhpd xmm15, xmm0
unpckhpd xmm15, xmm1
unpckhpd xmm15, xmm15
unpckhpd xmm0, [0x0]
unpckhpd xmm0, [0xFF]
unpckhpd xmm0, [rel $ + 0x0]
unpckhpd xmm0, [rel $ + 0xFF]
unpckhpd xmm0, [rel $ + 0xFFFF]
unpckhpd xmm0, [rax]
unpckhpd xmm0, [rax + 0x0]
unpckhpd xmm0, [rax + 0xFFFF]
unpckhpd xmm0, [r15 + 0xFFFF]
unpckhpd xmm0, [rax + rsi * 1  + 0x0]
unpckhpd xmm0, [rax + rsi + 0xFFFF]
unpckhpd xmm0, [r15 + rsi + 0xFFFF]
unpckhpd xmm0, [rax + r15 + 0xFFFF]
unpckhpd xmm0, [rax + rsi * 2 + 0xFFFF2]
unpckhpd xmm0, [rax + rsi * 4 + 0xFFFF4]
unpckhpd xmm0, [rax + rsi * 8 + 0xFFFF8]
unpckhpd xmm0, [rsp + rax * 8 + 0xFFFF8]
unpckhpd xmm0, [r15 + rax * 8 + 0xFFFF8]
unpckhpd xmm0, [rsp + r15 * 8 + 0xFFFF8]
unpckhpd xmm0, [r14 + r15 * 8 + 0xFFFF8]
unpckhpd xmm1, [0x0]
unpckhpd xmm1, [0xFF]
unpckhpd xmm1, [rel $ + 0x0]
unpckhpd xmm1, [rel $ + 0xFF]
unpckhpd xmm1, [rel $ + 0xFFFF]
unpckhpd xmm1, [rax]
unpckhpd xmm1, [rax + 0x0]
unpckhpd xmm1, [rax + 0xFFFF]
unpckhpd xmm1, [r15 + 0xFFFF]
unpckhpd xmm1, [rax + rsi * 1  + 0x0]
unpckhpd xmm1, [rax + rsi + 0xFFFF]
unpckhpd xmm1, [r15 + rsi + 0xFFFF]
unpckhpd xmm1, [rax + r15 + 0xFFFF]
unpckhpd xmm1, [rax + rsi * 2 + 0xFFFF2]
unpckhpd xmm1, [rax + rsi * 4 + 0xFFFF4]
unpckhpd xmm1, [rax + rsi * 8 + 0xFFFF8]
unpckhpd xmm1, [rsp + rax * 8 + 0xFFFF8]
unpckhpd xmm1, [r15 + rax * 8 + 0xFFFF8]
unpckhpd xmm1, [rsp + r15 * 8 + 0xFFFF8]
unpckhpd xmm1, [r14 + r15 * 8 + 0xFFFF8]
unpckhpd xmm15, [0x0]
unpckhpd xmm15, [0xFF]
unpckhpd xmm15, [rel $ + 0x0]
unpckhpd xmm15, [rel $ + 0xFF]
unpckhpd xmm15, [rel $ + 0xFFFF]
unpckhpd xmm15, [rax]
unpckhpd xmm15, [rax + 0x0]
unpckhpd xmm15, [rax + 0xFFFF]
unpckhpd xmm15, [r15 + 0xFFFF]
unpckhpd xmm15, [rax + rsi * 1  + 0x0]
unpckhpd xmm15, [rax + rsi + 0xFFFF]
unpckhpd xmm15, [r15 + rsi + 0xFFFF]
unpckhpd xmm15, [rax + r15 + 0xFFFF]
unpckhpd xmm15, [rax + rsi * 2 + 0xFFFF2]
unpckhpd xmm15, [rax + rsi * 4 + 0xFFFF4]
unpckhpd xmm15, [rax + rsi * 8 + 0xFFFF8]
unpckhpd xmm15, [rsp + rax * 8 + 0xFFFF8]
unpckhpd xmm15, [r15 + rax * 8 + 0xFFFF8]
unpckhpd xmm15, [rsp + r15 * 8 + 0xFFFF8]
unpckhpd xmm15, [r14 + r15 * 8 + 0xFFFF8]
