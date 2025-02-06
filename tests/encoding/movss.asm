; expect: f30f10c0f30f10c1f3410f10c7f30f10c8f30f10c9f3410f10cff3440f10f8f3440f10f9f3450f10fff30f10042500000000f30f100425ff000000f30f1005f8fffffff30f1005f7000000f30f1005f7ff0000f30f1000f30f1000f30f1080ffff0000f3410f1087ffff0000f30f100430f30f108430ffff0000f3410f108437ffff0000f3420f108438ffff0000f30f108470f2ff0f00f30f1084b0f4ff0f00f30f1084f0f8ff0f00f30f1084c4f8ff0f00f3410f1084c7f8ff0f00f3420f1084fcf8ff0f00f3430f1084fef8ff0f00f30f100c2500000000f30f100c25ff000000f30f100df8fffffff30f100df7000000f30f100df7ff0000f30f1008f30f1008f30f1088ffff0000f3410f108fffff0000f30f100c30f30f108c30ffff0000f3410f108c37ffff0000f3420f108c38ffff0000f30f108c70f2ff0f00f30f108cb0f4ff0f00f30f108cf0f8ff0f00f30f108cc4f8ff0f00f3410f108cc7f8ff0f00f3420f108cfcf8ff0f00f3430f108cfef8ff0f00f3440f103c2500000000f3440f103c25ff000000f3440f103df7fffffff3440f103df6000000f3440f103df6ff0000f3440f1038f3440f1038f3440f10b8ffff0000f3450f10bfffff0000f3440f103c30f3440f10bc30ffff0000f3450f10bc37ffff0000f3460f10bc38ffff0000f3440f10bc70f2ff0f00f3440f10bcb0f4ff0f00f3440f10bcf0f8ff0f00f3440f10bcc4f8ff0f00f3450f10bcc7f8ff0f00f3460f10bcfcf8ff0f00f3470f10bcfef8ff0f00f30f11042500000000f30f110c2500000000f3440f113c2500000000f30f110425ff000000f30f110c25ff000000f3440f113c25ff000000f30f1105f8fffffff30f110df8fffffff3440f113df7fffffff30f1105f7000000f30f110df7000000f3440f113df6000000f30f1105f7ff0000f30f110df7ff0000f3440f113df6ff0000f30f1100f30f1108f3440f1138f30f1100f30f1108f3440f1138f30f1180ffff0000f30f1188ffff0000f3440f11b8ffff0000f3410f1187ffff0000f3410f118fffff0000f3450f11bfffff0000f30f110430f30f110c30f3440f113c30f30f118430ffff0000f30f118c30ffff0000f3440f11bc30ffff0000f3410f118437ffff0000f3410f118c37ffff0000f3450f11bc37ffff0000f3420f118438ffff0000f3420f118c38ffff0000f3460f11bc38ffff0000f30f118470f2ff0f00f30f118c70f2ff0f00f3440f11bc70f2ff0f00f30f1184b0f4ff0f00f30f118cb0f4ff0f00f3440f11bcb0f4ff0f00f30f1184f0f8ff0f00f30f118cf0f8ff0f00f3440f11bcf0f8ff0f00f30f1184c4f8ff0f00f30f118cc4f8ff0f00f3440f11bcc4f8ff0f00f3410f1184c7f8ff0f00f3410f118cc7f8ff0f00f3450f11bcc7f8ff0f00f3420f1184fcf8ff0f00f3420f118cfcf8ff0f00f3460f11bcfcf8ff0f00f3430f1184fef8ff0f00f3430f118cfef8ff0f00f3470f11bcfef8ff0f00

bits 64

movss xmm0, xmm0
movss xmm0, xmm1
movss xmm0, xmm15
movss xmm1, xmm0
movss xmm1, xmm1
movss xmm1, xmm15
movss xmm15, xmm0
movss xmm15, xmm1
movss xmm15, xmm15
movss xmm0, dword [0x0]
movss xmm0, dword [0xFF]
movss xmm0, dword [rel $ + 0x0]
movss xmm0, dword [rel $ + 0xFF]
movss xmm0, dword [rel $ + 0xFFFF]
movss xmm0, dword [rax]
movss xmm0, dword [rax + 0x0]
movss xmm0, dword [rax + 0xFFFF]
movss xmm0, dword [r15 + 0xFFFF]
movss xmm0, dword [rax + rsi * 1  + 0x0]
movss xmm0, dword [rax + rsi + 0xFFFF]
movss xmm0, dword [r15 + rsi + 0xFFFF]
movss xmm0, dword [rax + r15 + 0xFFFF]
movss xmm0, dword [rax + rsi * 2 + 0xFFFF2]
movss xmm0, dword [rax + rsi * 4 + 0xFFFF4]
movss xmm0, dword [rax + rsi * 8 + 0xFFFF8]
movss xmm0, dword [rsp + rax * 8 + 0xFFFF8]
movss xmm0, dword [r15 + rax * 8 + 0xFFFF8]
movss xmm0, dword [rsp + r15 * 8 + 0xFFFF8]
movss xmm0, dword [r14 + r15 * 8 + 0xFFFF8]
movss xmm1, dword [0x0]
movss xmm1, dword [0xFF]
movss xmm1, dword [rel $ + 0x0]
movss xmm1, dword [rel $ + 0xFF]
movss xmm1, dword [rel $ + 0xFFFF]
movss xmm1, dword [rax]
movss xmm1, dword [rax + 0x0]
movss xmm1, dword [rax + 0xFFFF]
movss xmm1, dword [r15 + 0xFFFF]
movss xmm1, dword [rax + rsi * 1  + 0x0]
movss xmm1, dword [rax + rsi + 0xFFFF]
movss xmm1, dword [r15 + rsi + 0xFFFF]
movss xmm1, dword [rax + r15 + 0xFFFF]
movss xmm1, dword [rax + rsi * 2 + 0xFFFF2]
movss xmm1, dword [rax + rsi * 4 + 0xFFFF4]
movss xmm1, dword [rax + rsi * 8 + 0xFFFF8]
movss xmm1, dword [rsp + rax * 8 + 0xFFFF8]
movss xmm1, dword [r15 + rax * 8 + 0xFFFF8]
movss xmm1, dword [rsp + r15 * 8 + 0xFFFF8]
movss xmm1, dword [r14 + r15 * 8 + 0xFFFF8]
movss xmm15, dword [0x0]
movss xmm15, dword [0xFF]
movss xmm15, dword [rel $ + 0x0]
movss xmm15, dword [rel $ + 0xFF]
movss xmm15, dword [rel $ + 0xFFFF]
movss xmm15, dword [rax]
movss xmm15, dword [rax + 0x0]
movss xmm15, dword [rax + 0xFFFF]
movss xmm15, dword [r15 + 0xFFFF]
movss xmm15, dword [rax + rsi * 1  + 0x0]
movss xmm15, dword [rax + rsi + 0xFFFF]
movss xmm15, dword [r15 + rsi + 0xFFFF]
movss xmm15, dword [rax + r15 + 0xFFFF]
movss xmm15, dword [rax + rsi * 2 + 0xFFFF2]
movss xmm15, dword [rax + rsi * 4 + 0xFFFF4]
movss xmm15, dword [rax + rsi * 8 + 0xFFFF8]
movss xmm15, dword [rsp + rax * 8 + 0xFFFF8]
movss xmm15, dword [r15 + rax * 8 + 0xFFFF8]
movss xmm15, dword [rsp + r15 * 8 + 0xFFFF8]
movss xmm15, dword [r14 + r15 * 8 + 0xFFFF8]
movss dword [0x0], xmm0
movss dword [0x0], xmm1
movss dword [0x0], xmm15
movss dword [0xFF], xmm0
movss dword [0xFF], xmm1
movss dword [0xFF], xmm15
movss dword [rel $ + 0x0], xmm0
movss dword [rel $ + 0x0], xmm1
movss dword [rel $ + 0x0], xmm15
movss dword [rel $ + 0xFF], xmm0
movss dword [rel $ + 0xFF], xmm1
movss dword [rel $ + 0xFF], xmm15
movss dword [rel $ + 0xFFFF], xmm0
movss dword [rel $ + 0xFFFF], xmm1
movss dword [rel $ + 0xFFFF], xmm15
movss dword [rax], xmm0
movss dword [rax], xmm1
movss dword [rax], xmm15
movss dword [rax + 0x0], xmm0
movss dword [rax + 0x0], xmm1
movss dword [rax + 0x0], xmm15
movss dword [rax + 0xFFFF], xmm0
movss dword [rax + 0xFFFF], xmm1
movss dword [rax + 0xFFFF], xmm15
movss dword [r15 + 0xFFFF], xmm0
movss dword [r15 + 0xFFFF], xmm1
movss dword [r15 + 0xFFFF], xmm15
movss dword [rax + rsi * 1  + 0x0], xmm0
movss dword [rax + rsi * 1  + 0x0], xmm1
movss dword [rax + rsi * 1  + 0x0], xmm15
movss dword [rax + rsi + 0xFFFF], xmm0
movss dword [rax + rsi + 0xFFFF], xmm1
movss dword [rax + rsi + 0xFFFF], xmm15
movss dword [r15 + rsi + 0xFFFF], xmm0
movss dword [r15 + rsi + 0xFFFF], xmm1
movss dword [r15 + rsi + 0xFFFF], xmm15
movss dword [rax + r15 + 0xFFFF], xmm0
movss dword [rax + r15 + 0xFFFF], xmm1
movss dword [rax + r15 + 0xFFFF], xmm15
movss dword [rax + rsi * 2 + 0xFFFF2], xmm0
movss dword [rax + rsi * 2 + 0xFFFF2], xmm1
movss dword [rax + rsi * 2 + 0xFFFF2], xmm15
movss dword [rax + rsi * 4 + 0xFFFF4], xmm0
movss dword [rax + rsi * 4 + 0xFFFF4], xmm1
movss dword [rax + rsi * 4 + 0xFFFF4], xmm15
movss dword [rax + rsi * 8 + 0xFFFF8], xmm0
movss dword [rax + rsi * 8 + 0xFFFF8], xmm1
movss dword [rax + rsi * 8 + 0xFFFF8], xmm15
movss dword [rsp + rax * 8 + 0xFFFF8], xmm0
movss dword [rsp + rax * 8 + 0xFFFF8], xmm1
movss dword [rsp + rax * 8 + 0xFFFF8], xmm15
movss dword [r15 + rax * 8 + 0xFFFF8], xmm0
movss dword [r15 + rax * 8 + 0xFFFF8], xmm1
movss dword [r15 + rax * 8 + 0xFFFF8], xmm15
movss dword [rsp + r15 * 8 + 0xFFFF8], xmm0
movss dword [rsp + r15 * 8 + 0xFFFF8], xmm1
movss dword [rsp + r15 * 8 + 0xFFFF8], xmm15
movss dword [r14 + r15 * 8 + 0xFFFF8], xmm0
movss dword [r14 + r15 * 8 + 0xFFFF8], xmm1
movss dword [r14 + r15 * 8 + 0xFFFF8], xmm15
