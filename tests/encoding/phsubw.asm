; expect: 0f3805c00f3805c10f3805c70f3805c80f3805c90f3805cf0f3805f80f3805f90f3805ff0f38050425000000000f38050425ff0000000f380505f8ffffff0f380505f70000000f380505f7ff00000f3805000f3805000f380580ffff0000410f380587ffff00000f380504300f38058430ffff0000410f38058437ffff0000420f38058438ffff00000f38058470f2ff0f000f380584b0f4ff0f000f380584f0f8ff0f000f380584c4f8ff0f00410f380584c7f8ff0f00420f380584fcf8ff0f00430f380584fef8ff0f000f38050c25000000000f38050c25ff0000000f38050df8ffffff0f38050df70000000f38050df7ff00000f3805080f3805080f380588ffff0000410f38058fffff00000f38050c300f38058c30ffff0000410f38058c37ffff0000420f38058c38ffff00000f38058c70f2ff0f000f38058cb0f4ff0f000f38058cf0f8ff0f000f38058cc4f8ff0f00410f38058cc7f8ff0f00420f38058cfcf8ff0f00430f38058cfef8ff0f000f38053c25000000000f38053c25ff0000000f38053df8ffffff0f38053df70000000f38053df7ff00000f3805380f3805380f3805b8ffff0000410f3805bfffff00000f38053c300f3805bc30ffff0000410f3805bc37ffff0000420f3805bc38ffff00000f3805bc70f2ff0f000f3805bcb0f4ff0f000f3805bcf0f8ff0f000f3805bcc4f8ff0f00410f3805bcc7f8ff0f00420f3805bcfcf8ff0f00430f3805bcfef8ff0f00660f3805c0660f3805c166410f3805c7660f3805c8660f3805c966410f3805cf66440f3805f866440f3805f966450f3805ff660f3805042500000000660f38050425ff000000660f380505f7ffffff660f380505f6000000660f380505f6ff0000660f380500660f380500660f380580ffff000066410f380587ffff0000660f38050430660f38058430ffff000066410f38058437ffff000066420f38058438ffff0000660f38058470f2ff0f00660f380584b0f4ff0f00660f380584f0f8ff0f00660f380584c4f8ff0f0066410f380584c7f8ff0f0066420f380584fcf8ff0f0066430f380584fef8ff0f00660f38050c2500000000660f38050c25ff000000660f38050df7ffffff660f38050df6000000660f38050df6ff0000660f380508660f380508660f380588ffff000066410f38058fffff0000660f38050c30660f38058c30ffff000066410f38058c37ffff000066420f38058c38ffff0000660f38058c70f2ff0f00660f38058cb0f4ff0f00660f38058cf0f8ff0f00660f38058cc4f8ff0f0066410f38058cc7f8ff0f0066420f38058cfcf8ff0f0066430f38058cfef8ff0f0066440f38053c250000000066440f38053c25ff00000066440f38053df6ffffff66440f38053df500000066440f38053df5ff000066440f38053866440f38053866440f3805b8ffff000066450f3805bfffff000066440f38053c3066440f3805bc30ffff000066450f3805bc37ffff000066460f3805bc38ffff000066440f3805bc70f2ff0f0066440f3805bcb0f4ff0f0066440f3805bcf0f8ff0f0066440f3805bcc4f8ff0f0066450f3805bcc7f8ff0f0066460f3805bcfcf8ff0f0066470f3805bcfef8ff0f00

bits 64

phsubw mm0, mm0
phsubw mm0, mm1
phsubw mm0, mm7
phsubw mm1, mm0
phsubw mm1, mm1
phsubw mm1, mm7
phsubw mm7, mm0
phsubw mm7, mm1
phsubw mm7, mm7
phsubw mm0, qword [0x0]
phsubw mm0, qword [0xFF]
phsubw mm0, qword [rel $ + 0x0]
phsubw mm0, qword [rel $ + 0xFF]
phsubw mm0, qword [rel $ + 0xFFFF]
phsubw mm0, qword [rax]
phsubw mm0, qword [rax + 0x0]
phsubw mm0, qword [rax + 0xFFFF]
phsubw mm0, qword [r15 + 0xFFFF]
phsubw mm0, qword [rax + rsi * 1  + 0x0]
phsubw mm0, qword [rax + rsi + 0xFFFF]
phsubw mm0, qword [r15 + rsi + 0xFFFF]
phsubw mm0, qword [rax + r15 + 0xFFFF]
phsubw mm0, qword [rax + rsi * 2 + 0xFFFF2]
phsubw mm0, qword [rax + rsi * 4 + 0xFFFF4]
phsubw mm0, qword [rax + rsi * 8 + 0xFFFF8]
phsubw mm0, qword [rsp + rax * 8 + 0xFFFF8]
phsubw mm0, qword [r15 + rax * 8 + 0xFFFF8]
phsubw mm0, qword [rsp + r15 * 8 + 0xFFFF8]
phsubw mm0, qword [r14 + r15 * 8 + 0xFFFF8]
phsubw mm1, qword [0x0]
phsubw mm1, qword [0xFF]
phsubw mm1, qword [rel $ + 0x0]
phsubw mm1, qword [rel $ + 0xFF]
phsubw mm1, qword [rel $ + 0xFFFF]
phsubw mm1, qword [rax]
phsubw mm1, qword [rax + 0x0]
phsubw mm1, qword [rax + 0xFFFF]
phsubw mm1, qword [r15 + 0xFFFF]
phsubw mm1, qword [rax + rsi * 1  + 0x0]
phsubw mm1, qword [rax + rsi + 0xFFFF]
phsubw mm1, qword [r15 + rsi + 0xFFFF]
phsubw mm1, qword [rax + r15 + 0xFFFF]
phsubw mm1, qword [rax + rsi * 2 + 0xFFFF2]
phsubw mm1, qword [rax + rsi * 4 + 0xFFFF4]
phsubw mm1, qword [rax + rsi * 8 + 0xFFFF8]
phsubw mm1, qword [rsp + rax * 8 + 0xFFFF8]
phsubw mm1, qword [r15 + rax * 8 + 0xFFFF8]
phsubw mm1, qword [rsp + r15 * 8 + 0xFFFF8]
phsubw mm1, qword [r14 + r15 * 8 + 0xFFFF8]
phsubw mm7, qword [0x0]
phsubw mm7, qword [0xFF]
phsubw mm7, qword [rel $ + 0x0]
phsubw mm7, qword [rel $ + 0xFF]
phsubw mm7, qword [rel $ + 0xFFFF]
phsubw mm7, qword [rax]
phsubw mm7, qword [rax + 0x0]
phsubw mm7, qword [rax + 0xFFFF]
phsubw mm7, qword [r15 + 0xFFFF]
phsubw mm7, qword [rax + rsi * 1  + 0x0]
phsubw mm7, qword [rax + rsi + 0xFFFF]
phsubw mm7, qword [r15 + rsi + 0xFFFF]
phsubw mm7, qword [rax + r15 + 0xFFFF]
phsubw mm7, qword [rax + rsi * 2 + 0xFFFF2]
phsubw mm7, qword [rax + rsi * 4 + 0xFFFF4]
phsubw mm7, qword [rax + rsi * 8 + 0xFFFF8]
phsubw mm7, qword [rsp + rax * 8 + 0xFFFF8]
phsubw mm7, qword [r15 + rax * 8 + 0xFFFF8]
phsubw mm7, qword [rsp + r15 * 8 + 0xFFFF8]
phsubw mm7, qword [r14 + r15 * 8 + 0xFFFF8]
phsubw xmm0, xmm0
phsubw xmm0, xmm1
phsubw xmm0, xmm15
phsubw xmm1, xmm0
phsubw xmm1, xmm1
phsubw xmm1, xmm15
phsubw xmm15, xmm0
phsubw xmm15, xmm1
phsubw xmm15, xmm15
phsubw xmm0, [0x0]
phsubw xmm0, [0xFF]
phsubw xmm0, [rel $ + 0x0]
phsubw xmm0, [rel $ + 0xFF]
phsubw xmm0, [rel $ + 0xFFFF]
phsubw xmm0, [rax]
phsubw xmm0, [rax + 0x0]
phsubw xmm0, [rax + 0xFFFF]
phsubw xmm0, [r15 + 0xFFFF]
phsubw xmm0, [rax + rsi * 1  + 0x0]
phsubw xmm0, [rax + rsi + 0xFFFF]
phsubw xmm0, [r15 + rsi + 0xFFFF]
phsubw xmm0, [rax + r15 + 0xFFFF]
phsubw xmm0, [rax + rsi * 2 + 0xFFFF2]
phsubw xmm0, [rax + rsi * 4 + 0xFFFF4]
phsubw xmm0, [rax + rsi * 8 + 0xFFFF8]
phsubw xmm0, [rsp + rax * 8 + 0xFFFF8]
phsubw xmm0, [r15 + rax * 8 + 0xFFFF8]
phsubw xmm0, [rsp + r15 * 8 + 0xFFFF8]
phsubw xmm0, [r14 + r15 * 8 + 0xFFFF8]
phsubw xmm1, [0x0]
phsubw xmm1, [0xFF]
phsubw xmm1, [rel $ + 0x0]
phsubw xmm1, [rel $ + 0xFF]
phsubw xmm1, [rel $ + 0xFFFF]
phsubw xmm1, [rax]
phsubw xmm1, [rax + 0x0]
phsubw xmm1, [rax + 0xFFFF]
phsubw xmm1, [r15 + 0xFFFF]
phsubw xmm1, [rax + rsi * 1  + 0x0]
phsubw xmm1, [rax + rsi + 0xFFFF]
phsubw xmm1, [r15 + rsi + 0xFFFF]
phsubw xmm1, [rax + r15 + 0xFFFF]
phsubw xmm1, [rax + rsi * 2 + 0xFFFF2]
phsubw xmm1, [rax + rsi * 4 + 0xFFFF4]
phsubw xmm1, [rax + rsi * 8 + 0xFFFF8]
phsubw xmm1, [rsp + rax * 8 + 0xFFFF8]
phsubw xmm1, [r15 + rax * 8 + 0xFFFF8]
phsubw xmm1, [rsp + r15 * 8 + 0xFFFF8]
phsubw xmm1, [r14 + r15 * 8 + 0xFFFF8]
phsubw xmm15, [0x0]
phsubw xmm15, [0xFF]
phsubw xmm15, [rel $ + 0x0]
phsubw xmm15, [rel $ + 0xFF]
phsubw xmm15, [rel $ + 0xFFFF]
phsubw xmm15, [rax]
phsubw xmm15, [rax + 0x0]
phsubw xmm15, [rax + 0xFFFF]
phsubw xmm15, [r15 + 0xFFFF]
phsubw xmm15, [rax + rsi * 1  + 0x0]
phsubw xmm15, [rax + rsi + 0xFFFF]
phsubw xmm15, [r15 + rsi + 0xFFFF]
phsubw xmm15, [rax + r15 + 0xFFFF]
phsubw xmm15, [rax + rsi * 2 + 0xFFFF2]
phsubw xmm15, [rax + rsi * 4 + 0xFFFF4]
phsubw xmm15, [rax + rsi * 8 + 0xFFFF8]
phsubw xmm15, [rsp + rax * 8 + 0xFFFF8]
phsubw xmm15, [r15 + rax * 8 + 0xFFFF8]
phsubw xmm15, [rsp + r15 * 8 + 0xFFFF8]
phsubw xmm15, [r14 + r15 * 8 + 0xFFFF8]
