; expect: f20f10c0f20f10c1f2410f10c7f20f10c8f20f10c9f2410f10cff2440f10f8f2440f10f9f2450f10fff20f10042500000000f20f100425ff000000f20f1005f8fffffff20f1005f7000000f20f1005f7ff0000f20f1000f20f1000f20f1080ffff0000f2410f1087ffff0000f20f100430f20f108430ffff0000f2410f108437ffff0000f2420f108438ffff0000f20f108470f2ff0f00f20f1084b0f4ff0f00f20f1084f0f8ff0f00f20f1084c4f8ff0f00f2410f1084c7f8ff0f00f2420f1084fcf8ff0f00f2430f1084fef8ff0f00f20f100c2500000000f20f100c25ff000000f20f100df8fffffff20f100df7000000f20f100df7ff0000f20f1008f20f1008f20f1088ffff0000f2410f108fffff0000f20f100c30f20f108c30ffff0000f2410f108c37ffff0000f2420f108c38ffff0000f20f108c70f2ff0f00f20f108cb0f4ff0f00f20f108cf0f8ff0f00f20f108cc4f8ff0f00f2410f108cc7f8ff0f00f2420f108cfcf8ff0f00f2430f108cfef8ff0f00f2440f103c2500000000f2440f103c25ff000000f2440f103df7fffffff2440f103df6000000f2440f103df6ff0000f2440f1038f2440f1038f2440f10b8ffff0000f2450f10bfffff0000f2440f103c30f2440f10bc30ffff0000f2450f10bc37ffff0000f2460f10bc38ffff0000f2440f10bc70f2ff0f00f2440f10bcb0f4ff0f00f2440f10bcf0f8ff0f00f2440f10bcc4f8ff0f00f2450f10bcc7f8ff0f00f2460f10bcfcf8ff0f00f2470f10bcfef8ff0f00f20f11042500000000f20f110c2500000000f2440f113c2500000000f20f110425ff000000f20f110c25ff000000f2440f113c25ff000000f20f1105f8fffffff20f110df8fffffff2440f113df7fffffff20f1105f7000000f20f110df7000000f2440f113df6000000f20f1105f7ff0000f20f110df7ff0000f2440f113df6ff0000f20f1100f20f1108f2440f1138f20f1100f20f1108f2440f1138f20f1180ffff0000f20f1188ffff0000f2440f11b8ffff0000f2410f1187ffff0000f2410f118fffff0000f2450f11bfffff0000f20f110430f20f110c30f2440f113c30f20f118430ffff0000f20f118c30ffff0000f2440f11bc30ffff0000f2410f118437ffff0000f2410f118c37ffff0000f2450f11bc37ffff0000f2420f118438ffff0000f2420f118c38ffff0000f2460f11bc38ffff0000f20f118470f2ff0f00f20f118c70f2ff0f00f2440f11bc70f2ff0f00f20f1184b0f4ff0f00f20f118cb0f4ff0f00f2440f11bcb0f4ff0f00f20f1184f0f8ff0f00f20f118cf0f8ff0f00f2440f11bcf0f8ff0f00f20f1184c4f8ff0f00f20f118cc4f8ff0f00f2440f11bcc4f8ff0f00f2410f1184c7f8ff0f00f2410f118cc7f8ff0f00f2450f11bcc7f8ff0f00f2420f1184fcf8ff0f00f2420f118cfcf8ff0f00f2460f11bcfcf8ff0f00f2430f1184fef8ff0f00f2430f118cfef8ff0f00f2470f11bcfef8ff0f00

bits 64

movsd xmm0, xmm0
movsd xmm0, xmm1
movsd xmm0, xmm15
movsd xmm1, xmm0
movsd xmm1, xmm1
movsd xmm1, xmm15
movsd xmm15, xmm0
movsd xmm15, xmm1
movsd xmm15, xmm15
movsd xmm0, qword [0x0]
movsd xmm0, qword [0xFF]
movsd xmm0, qword [rel $ + 0x0]
movsd xmm0, qword [rel $ + 0xFF]
movsd xmm0, qword [rel $ + 0xFFFF]
movsd xmm0, qword [rax]
movsd xmm0, qword [rax + 0x0]
movsd xmm0, qword [rax + 0xFFFF]
movsd xmm0, qword [r15 + 0xFFFF]
movsd xmm0, qword [rax + rsi * 1  + 0x0]
movsd xmm0, qword [rax + rsi + 0xFFFF]
movsd xmm0, qword [r15 + rsi + 0xFFFF]
movsd xmm0, qword [rax + r15 + 0xFFFF]
movsd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
movsd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
movsd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
movsd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
movsd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
movsd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
movsd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
movsd xmm1, qword [0x0]
movsd xmm1, qword [0xFF]
movsd xmm1, qword [rel $ + 0x0]
movsd xmm1, qword [rel $ + 0xFF]
movsd xmm1, qword [rel $ + 0xFFFF]
movsd xmm1, qword [rax]
movsd xmm1, qword [rax + 0x0]
movsd xmm1, qword [rax + 0xFFFF]
movsd xmm1, qword [r15 + 0xFFFF]
movsd xmm1, qword [rax + rsi * 1  + 0x0]
movsd xmm1, qword [rax + rsi + 0xFFFF]
movsd xmm1, qword [r15 + rsi + 0xFFFF]
movsd xmm1, qword [rax + r15 + 0xFFFF]
movsd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
movsd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
movsd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
movsd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
movsd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
movsd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
movsd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
movsd xmm15, qword [0x0]
movsd xmm15, qword [0xFF]
movsd xmm15, qword [rel $ + 0x0]
movsd xmm15, qword [rel $ + 0xFF]
movsd xmm15, qword [rel $ + 0xFFFF]
movsd xmm15, qword [rax]
movsd xmm15, qword [rax + 0x0]
movsd xmm15, qword [rax + 0xFFFF]
movsd xmm15, qword [r15 + 0xFFFF]
movsd xmm15, qword [rax + rsi * 1  + 0x0]
movsd xmm15, qword [rax + rsi + 0xFFFF]
movsd xmm15, qword [r15 + rsi + 0xFFFF]
movsd xmm15, qword [rax + r15 + 0xFFFF]
movsd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
movsd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
movsd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
movsd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
movsd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
movsd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
movsd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
movsd qword [0x0], xmm0
movsd qword [0x0], xmm1
movsd qword [0x0], xmm15
movsd qword [0xFF], xmm0
movsd qword [0xFF], xmm1
movsd qword [0xFF], xmm15
movsd qword [rel $ + 0x0], xmm0
movsd qword [rel $ + 0x0], xmm1
movsd qword [rel $ + 0x0], xmm15
movsd qword [rel $ + 0xFF], xmm0
movsd qword [rel $ + 0xFF], xmm1
movsd qword [rel $ + 0xFF], xmm15
movsd qword [rel $ + 0xFFFF], xmm0
movsd qword [rel $ + 0xFFFF], xmm1
movsd qword [rel $ + 0xFFFF], xmm15
movsd qword [rax], xmm0
movsd qword [rax], xmm1
movsd qword [rax], xmm15
movsd qword [rax + 0x0], xmm0
movsd qword [rax + 0x0], xmm1
movsd qword [rax + 0x0], xmm15
movsd qword [rax + 0xFFFF], xmm0
movsd qword [rax + 0xFFFF], xmm1
movsd qword [rax + 0xFFFF], xmm15
movsd qword [r15 + 0xFFFF], xmm0
movsd qword [r15 + 0xFFFF], xmm1
movsd qword [r15 + 0xFFFF], xmm15
movsd qword [rax + rsi * 1  + 0x0], xmm0
movsd qword [rax + rsi * 1  + 0x0], xmm1
movsd qword [rax + rsi * 1  + 0x0], xmm15
movsd qword [rax + rsi + 0xFFFF], xmm0
movsd qword [rax + rsi + 0xFFFF], xmm1
movsd qword [rax + rsi + 0xFFFF], xmm15
movsd qword [r15 + rsi + 0xFFFF], xmm0
movsd qword [r15 + rsi + 0xFFFF], xmm1
movsd qword [r15 + rsi + 0xFFFF], xmm15
movsd qword [rax + r15 + 0xFFFF], xmm0
movsd qword [rax + r15 + 0xFFFF], xmm1
movsd qword [rax + r15 + 0xFFFF], xmm15
movsd qword [rax + rsi * 2 + 0xFFFF2], xmm0
movsd qword [rax + rsi * 2 + 0xFFFF2], xmm1
movsd qword [rax + rsi * 2 + 0xFFFF2], xmm15
movsd qword [rax + rsi * 4 + 0xFFFF4], xmm0
movsd qword [rax + rsi * 4 + 0xFFFF4], xmm1
movsd qword [rax + rsi * 4 + 0xFFFF4], xmm15
movsd qword [rax + rsi * 8 + 0xFFFF8], xmm0
movsd qword [rax + rsi * 8 + 0xFFFF8], xmm1
movsd qword [rax + rsi * 8 + 0xFFFF8], xmm15
movsd qword [rsp + rax * 8 + 0xFFFF8], xmm0
movsd qword [rsp + rax * 8 + 0xFFFF8], xmm1
movsd qword [rsp + rax * 8 + 0xFFFF8], xmm15
movsd qword [r15 + rax * 8 + 0xFFFF8], xmm0
movsd qword [r15 + rax * 8 + 0xFFFF8], xmm1
movsd qword [r15 + rax * 8 + 0xFFFF8], xmm15
movsd qword [rsp + r15 * 8 + 0xFFFF8], xmm0
movsd qword [rsp + r15 * 8 + 0xFFFF8], xmm1
movsd qword [rsp + r15 * 8 + 0xFFFF8], xmm15
movsd qword [r14 + r15 * 8 + 0xFFFF8], xmm0
movsd qword [r14 + r15 * 8 + 0xFFFF8], xmm1
movsd qword [r14 + r15 * 8 + 0xFFFF8], xmm15
