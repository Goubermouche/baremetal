; expect: 660f10c0660f10c166410f10c7660f10c8660f10c966410f10cf66440f10f866440f10f966450f10ff660f10042500000000660f100425ff000000660f1005f8ffffff660f1005f7000000660f1005f7ff0000660f1000660f1000660f1080ffff000066410f1087ffff0000660f100430660f108430ffff000066410f108437ffff000066420f108438ffff0000660f108470f2ff0f00660f1084b0f4ff0f00660f1084f0f8ff0f00660f1084c4f8ff0f0066410f1084c7f8ff0f0066420f1084fcf8ff0f0066430f1084fef8ff0f00660f100c2500000000660f100c25ff000000660f100df8ffffff660f100df7000000660f100df7ff0000660f1008660f1008660f1088ffff000066410f108fffff0000660f100c30660f108c30ffff000066410f108c37ffff000066420f108c38ffff0000660f108c70f2ff0f00660f108cb0f4ff0f00660f108cf0f8ff0f00660f108cc4f8ff0f0066410f108cc7f8ff0f0066420f108cfcf8ff0f0066430f108cfef8ff0f0066440f103c250000000066440f103c25ff00000066440f103df7ffffff66440f103df600000066440f103df6ff000066440f103866440f103866440f10b8ffff000066450f10bfffff000066440f103c3066440f10bc30ffff000066450f10bc37ffff000066460f10bc38ffff000066440f10bc70f2ff0f0066440f10bcb0f4ff0f0066440f10bcf0f8ff0f0066440f10bcc4f8ff0f0066450f10bcc7f8ff0f0066460f10bcfcf8ff0f0066470f10bcfef8ff0f00660f11042500000000660f110c250000000066440f113c2500000000660f110425ff000000660f110c25ff00000066440f113c25ff000000660f1105f8ffffff660f110df8ffffff66440f113df7ffffff660f1105f7000000660f110df700000066440f113df6000000660f1105f7ff0000660f110df7ff000066440f113df6ff0000660f1100660f110866440f1138660f1100660f110866440f1138660f1180ffff0000660f1188ffff000066440f11b8ffff000066410f1187ffff000066410f118fffff000066450f11bfffff0000660f110430660f110c3066440f113c30660f118430ffff0000660f118c30ffff000066440f11bc30ffff000066410f118437ffff000066410f118c37ffff000066450f11bc37ffff000066420f118438ffff000066420f118c38ffff000066460f11bc38ffff0000660f118470f2ff0f00660f118c70f2ff0f0066440f11bc70f2ff0f00660f1184b0f4ff0f00660f118cb0f4ff0f0066440f11bcb0f4ff0f00660f1184f0f8ff0f00660f118cf0f8ff0f0066440f11bcf0f8ff0f00660f1184c4f8ff0f00660f118cc4f8ff0f0066440f11bcc4f8ff0f0066410f1184c7f8ff0f0066410f118cc7f8ff0f0066450f11bcc7f8ff0f0066420f1184fcf8ff0f0066420f118cfcf8ff0f0066460f11bcfcf8ff0f0066430f1184fef8ff0f0066430f118cfef8ff0f0066470f11bcfef8ff0f00

movupd xmm0, xmm0
movupd xmm0, xmm1
movupd xmm0, xmm15
movupd xmm1, xmm0
movupd xmm1, xmm1
movupd xmm1, xmm15
movupd xmm15, xmm0
movupd xmm15, xmm1
movupd xmm15, xmm15
movupd xmm0, [0x0]
movupd xmm0, [0xFF]
movupd xmm0, [rel $ + 0x0]
movupd xmm0, [rel $ + 0xFF]
movupd xmm0, [rel $ + 0xFFFF]
movupd xmm0, [rax]
movupd xmm0, [rax + 0x0]
movupd xmm0, [rax + 0xFFFF]
movupd xmm0, [r15 + 0xFFFF]
movupd xmm0, [rax + rsi * 1  + 0x0]
movupd xmm0, [rax + rsi + 0xFFFF]
movupd xmm0, [r15 + rsi + 0xFFFF]
movupd xmm0, [rax + r15 + 0xFFFF]
movupd xmm0, [rax + rsi * 2 + 0xFFFF2]
movupd xmm0, [rax + rsi * 4 + 0xFFFF4]
movupd xmm0, [rax + rsi * 8 + 0xFFFF8]
movupd xmm0, [rsp + rax * 8 + 0xFFFF8]
movupd xmm0, [r15 + rax * 8 + 0xFFFF8]
movupd xmm0, [rsp + r15 * 8 + 0xFFFF8]
movupd xmm0, [r14 + r15 * 8 + 0xFFFF8]
movupd xmm1, [0x0]
movupd xmm1, [0xFF]
movupd xmm1, [rel $ + 0x0]
movupd xmm1, [rel $ + 0xFF]
movupd xmm1, [rel $ + 0xFFFF]
movupd xmm1, [rax]
movupd xmm1, [rax + 0x0]
movupd xmm1, [rax + 0xFFFF]
movupd xmm1, [r15 + 0xFFFF]
movupd xmm1, [rax + rsi * 1  + 0x0]
movupd xmm1, [rax + rsi + 0xFFFF]
movupd xmm1, [r15 + rsi + 0xFFFF]
movupd xmm1, [rax + r15 + 0xFFFF]
movupd xmm1, [rax + rsi * 2 + 0xFFFF2]
movupd xmm1, [rax + rsi * 4 + 0xFFFF4]
movupd xmm1, [rax + rsi * 8 + 0xFFFF8]
movupd xmm1, [rsp + rax * 8 + 0xFFFF8]
movupd xmm1, [r15 + rax * 8 + 0xFFFF8]
movupd xmm1, [rsp + r15 * 8 + 0xFFFF8]
movupd xmm1, [r14 + r15 * 8 + 0xFFFF8]
movupd xmm15, [0x0]
movupd xmm15, [0xFF]
movupd xmm15, [rel $ + 0x0]
movupd xmm15, [rel $ + 0xFF]
movupd xmm15, [rel $ + 0xFFFF]
movupd xmm15, [rax]
movupd xmm15, [rax + 0x0]
movupd xmm15, [rax + 0xFFFF]
movupd xmm15, [r15 + 0xFFFF]
movupd xmm15, [rax + rsi * 1  + 0x0]
movupd xmm15, [rax + rsi + 0xFFFF]
movupd xmm15, [r15 + rsi + 0xFFFF]
movupd xmm15, [rax + r15 + 0xFFFF]
movupd xmm15, [rax + rsi * 2 + 0xFFFF2]
movupd xmm15, [rax + rsi * 4 + 0xFFFF4]
movupd xmm15, [rax + rsi * 8 + 0xFFFF8]
movupd xmm15, [rsp + rax * 8 + 0xFFFF8]
movupd xmm15, [r15 + rax * 8 + 0xFFFF8]
movupd xmm15, [rsp + r15 * 8 + 0xFFFF8]
movupd xmm15, [r14 + r15 * 8 + 0xFFFF8]
movupd [0x0], xmm0
movupd [0x0], xmm1
movupd [0x0], xmm15
movupd [0xFF], xmm0
movupd [0xFF], xmm1
movupd [0xFF], xmm15
movupd [rel $ + 0x0], xmm0
movupd [rel $ + 0x0], xmm1
movupd [rel $ + 0x0], xmm15
movupd [rel $ + 0xFF], xmm0
movupd [rel $ + 0xFF], xmm1
movupd [rel $ + 0xFF], xmm15
movupd [rel $ + 0xFFFF], xmm0
movupd [rel $ + 0xFFFF], xmm1
movupd [rel $ + 0xFFFF], xmm15
movupd [rax], xmm0
movupd [rax], xmm1
movupd [rax], xmm15
movupd [rax + 0x0], xmm0
movupd [rax + 0x0], xmm1
movupd [rax + 0x0], xmm15
movupd [rax + 0xFFFF], xmm0
movupd [rax + 0xFFFF], xmm1
movupd [rax + 0xFFFF], xmm15
movupd [r15 + 0xFFFF], xmm0
movupd [r15 + 0xFFFF], xmm1
movupd [r15 + 0xFFFF], xmm15
movupd [rax + rsi * 1  + 0x0], xmm0
movupd [rax + rsi * 1  + 0x0], xmm1
movupd [rax + rsi * 1  + 0x0], xmm15
movupd [rax + rsi + 0xFFFF], xmm0
movupd [rax + rsi + 0xFFFF], xmm1
movupd [rax + rsi + 0xFFFF], xmm15
movupd [r15 + rsi + 0xFFFF], xmm0
movupd [r15 + rsi + 0xFFFF], xmm1
movupd [r15 + rsi + 0xFFFF], xmm15
movupd [rax + r15 + 0xFFFF], xmm0
movupd [rax + r15 + 0xFFFF], xmm1
movupd [rax + r15 + 0xFFFF], xmm15
movupd [rax + rsi * 2 + 0xFFFF2], xmm0
movupd [rax + rsi * 2 + 0xFFFF2], xmm1
movupd [rax + rsi * 2 + 0xFFFF2], xmm15
movupd [rax + rsi * 4 + 0xFFFF4], xmm0
movupd [rax + rsi * 4 + 0xFFFF4], xmm1
movupd [rax + rsi * 4 + 0xFFFF4], xmm15
movupd [rax + rsi * 8 + 0xFFFF8], xmm0
movupd [rax + rsi * 8 + 0xFFFF8], xmm1
movupd [rax + rsi * 8 + 0xFFFF8], xmm15
movupd [rsp + rax * 8 + 0xFFFF8], xmm0
movupd [rsp + rax * 8 + 0xFFFF8], xmm1
movupd [rsp + rax * 8 + 0xFFFF8], xmm15
movupd [r15 + rax * 8 + 0xFFFF8], xmm0
movupd [r15 + rax * 8 + 0xFFFF8], xmm1
movupd [r15 + rax * 8 + 0xFFFF8], xmm15
movupd [rsp + r15 * 8 + 0xFFFF8], xmm0
movupd [rsp + r15 * 8 + 0xFFFF8], xmm1
movupd [rsp + r15 * 8 + 0xFFFF8], xmm15
movupd [r14 + r15 * 8 + 0xFFFF8], xmm0
movupd [r14 + r15 * 8 + 0xFFFF8], xmm1
movupd [r14 + r15 * 8 + 0xFFFF8], xmm15