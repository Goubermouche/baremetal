; expect: 660f3839c0660f3839c166410f3839c7660f3839c8660f3839c966410f3839cf66440f3839f866440f3839f966450f3839ff660f3839042500000000660f38390425ff000000660f383905f7ffffff660f383905f6000000660f383905f6ff0000660f383900660f383900660f383980ffff000066410f383987ffff0000660f38390430660f38398430ffff000066410f38398437ffff000066420f38398438ffff0000660f38398470f2ff0f00660f383984b0f4ff0f00660f383984f0f8ff0f00660f383984c4f8ff0f0066410f383984c7f8ff0f0066420f383984fcf8ff0f0066430f383984fef8ff0f00660f38390c2500000000660f38390c25ff000000660f38390df7ffffff660f38390df6000000660f38390df6ff0000660f383908660f383908660f383988ffff000066410f38398fffff0000660f38390c30660f38398c30ffff000066410f38398c37ffff000066420f38398c38ffff0000660f38398c70f2ff0f00660f38398cb0f4ff0f00660f38398cf0f8ff0f00660f38398cc4f8ff0f0066410f38398cc7f8ff0f0066420f38398cfcf8ff0f0066430f38398cfef8ff0f0066440f38393c250000000066440f38393c25ff00000066440f38393df6ffffff66440f38393df500000066440f38393df5ff000066440f38393866440f38393866440f3839b8ffff000066450f3839bfffff000066440f38393c3066440f3839bc30ffff000066450f3839bc37ffff000066460f3839bc38ffff000066440f3839bc70f2ff0f0066440f3839bcb0f4ff0f0066440f3839bcf0f8ff0f0066440f3839bcc4f8ff0f0066450f3839bcc7f8ff0f0066460f3839bcfcf8ff0f0066470f3839bcfef8ff0f00

bits 64

pminsd xmm0, xmm0
pminsd xmm0, xmm1
pminsd xmm0, xmm15
pminsd xmm1, xmm0
pminsd xmm1, xmm1
pminsd xmm1, xmm15
pminsd xmm15, xmm0
pminsd xmm15, xmm1
pminsd xmm15, xmm15
pminsd xmm0, [0x0]
pminsd xmm0, [0xFF]
pminsd xmm0, [rel $ + 0x0]
pminsd xmm0, [rel $ + 0xFF]
pminsd xmm0, [rel $ + 0xFFFF]
pminsd xmm0, [rax]
pminsd xmm0, [rax + 0x0]
pminsd xmm0, [rax + 0xFFFF]
pminsd xmm0, [r15 + 0xFFFF]
pminsd xmm0, [rax + rsi * 1  + 0x0]
pminsd xmm0, [rax + rsi + 0xFFFF]
pminsd xmm0, [r15 + rsi + 0xFFFF]
pminsd xmm0, [rax + r15 + 0xFFFF]
pminsd xmm0, [rax + rsi * 2 + 0xFFFF2]
pminsd xmm0, [rax + rsi * 4 + 0xFFFF4]
pminsd xmm0, [rax + rsi * 8 + 0xFFFF8]
pminsd xmm0, [rsp + rax * 8 + 0xFFFF8]
pminsd xmm0, [r15 + rax * 8 + 0xFFFF8]
pminsd xmm0, [rsp + r15 * 8 + 0xFFFF8]
pminsd xmm0, [r14 + r15 * 8 + 0xFFFF8]
pminsd xmm1, [0x0]
pminsd xmm1, [0xFF]
pminsd xmm1, [rel $ + 0x0]
pminsd xmm1, [rel $ + 0xFF]
pminsd xmm1, [rel $ + 0xFFFF]
pminsd xmm1, [rax]
pminsd xmm1, [rax + 0x0]
pminsd xmm1, [rax + 0xFFFF]
pminsd xmm1, [r15 + 0xFFFF]
pminsd xmm1, [rax + rsi * 1  + 0x0]
pminsd xmm1, [rax + rsi + 0xFFFF]
pminsd xmm1, [r15 + rsi + 0xFFFF]
pminsd xmm1, [rax + r15 + 0xFFFF]
pminsd xmm1, [rax + rsi * 2 + 0xFFFF2]
pminsd xmm1, [rax + rsi * 4 + 0xFFFF4]
pminsd xmm1, [rax + rsi * 8 + 0xFFFF8]
pminsd xmm1, [rsp + rax * 8 + 0xFFFF8]
pminsd xmm1, [r15 + rax * 8 + 0xFFFF8]
pminsd xmm1, [rsp + r15 * 8 + 0xFFFF8]
pminsd xmm1, [r14 + r15 * 8 + 0xFFFF8]
pminsd xmm15, [0x0]
pminsd xmm15, [0xFF]
pminsd xmm15, [rel $ + 0x0]
pminsd xmm15, [rel $ + 0xFF]
pminsd xmm15, [rel $ + 0xFFFF]
pminsd xmm15, [rax]
pminsd xmm15, [rax + 0x0]
pminsd xmm15, [rax + 0xFFFF]
pminsd xmm15, [r15 + 0xFFFF]
pminsd xmm15, [rax + rsi * 1  + 0x0]
pminsd xmm15, [rax + rsi + 0xFFFF]
pminsd xmm15, [r15 + rsi + 0xFFFF]
pminsd xmm15, [rax + r15 + 0xFFFF]
pminsd xmm15, [rax + rsi * 2 + 0xFFFF2]
pminsd xmm15, [rax + rsi * 4 + 0xFFFF4]
pminsd xmm15, [rax + rsi * 8 + 0xFFFF8]
pminsd xmm15, [rsp + rax * 8 + 0xFFFF8]
pminsd xmm15, [r15 + rax * 8 + 0xFFFF8]
pminsd xmm15, [rsp + r15 * 8 + 0xFFFF8]
pminsd xmm15, [r14 + r15 * 8 + 0xFFFF8]
