; expect: 0f10c00f10c1410f10c70f10c80f10c9410f10cf440f10f8440f10f9450f10ff0f100425000000000f100425ff0000000f1005f9ffffff0f1005f80000000f1005f8ff00000f10000f10000f1080ffff0000410f1087ffff00000f1004300f108430ffff0000410f108437ffff0000420f108438ffff00000f108470f2ff0f000f1084b0f4ff0f000f1084f0f8ff0f000f1084c4f8ff0f00410f1084c7f8ff0f00420f1084fcf8ff0f00430f1084fef8ff0f000f100c25000000000f100c25ff0000000f100df9ffffff0f100df80000000f100df8ff00000f10080f10080f1088ffff0000410f108fffff00000f100c300f108c30ffff0000410f108c37ffff0000420f108c38ffff00000f108c70f2ff0f000f108cb0f4ff0f000f108cf0f8ff0f000f108cc4f8ff0f00410f108cc7f8ff0f00420f108cfcf8ff0f00430f108cfef8ff0f00440f103c2500000000440f103c25ff000000440f103df8ffffff440f103df7000000440f103df7ff0000440f1038440f1038440f10b8ffff0000450f10bfffff0000440f103c30440f10bc30ffff0000450f10bc37ffff0000460f10bc38ffff0000440f10bc70f2ff0f00440f10bcb0f4ff0f00440f10bcf0f8ff0f00440f10bcc4f8ff0f00450f10bcc7f8ff0f00460f10bcfcf8ff0f00470f10bcfef8ff0f000f110425000000000f110c2500000000440f113c25000000000f110425ff0000000f110c25ff000000440f113c25ff0000000f1105f9ffffff0f110df9ffffff440f113df8ffffff0f1105f80000000f110df8000000440f113df70000000f1105f8ff00000f110df8ff0000440f113df7ff00000f11000f1108440f11380f11000f1108440f11380f1180ffff00000f1188ffff0000440f11b8ffff0000410f1187ffff0000410f118fffff0000450f11bfffff00000f1104300f110c30440f113c300f118430ffff00000f118c30ffff0000440f11bc30ffff0000410f118437ffff0000410f118c37ffff0000450f11bc37ffff0000420f118438ffff0000420f118c38ffff0000460f11bc38ffff00000f118470f2ff0f000f118c70f2ff0f00440f11bc70f2ff0f000f1184b0f4ff0f000f118cb0f4ff0f00440f11bcb0f4ff0f000f1184f0f8ff0f000f118cf0f8ff0f00440f11bcf0f8ff0f000f1184c4f8ff0f000f118cc4f8ff0f00440f11bcc4f8ff0f00410f1184c7f8ff0f00410f118cc7f8ff0f00450f11bcc7f8ff0f00420f1184fcf8ff0f00420f118cfcf8ff0f00460f11bcfcf8ff0f00430f1184fef8ff0f00430f118cfef8ff0f00470f11bcfef8ff0f00

bits 64

movups xmm0, xmm0
movups xmm0, xmm1
movups xmm0, xmm15
movups xmm1, xmm0
movups xmm1, xmm1
movups xmm1, xmm15
movups xmm15, xmm0
movups xmm15, xmm1
movups xmm15, xmm15
movups xmm0, [0x0]
movups xmm0, [0xFF]
movups xmm0, [rel $ + 0x0]
movups xmm0, [rel $ + 0xFF]
movups xmm0, [rel $ + 0xFFFF]
movups xmm0, [rax]
movups xmm0, [rax + 0x0]
movups xmm0, [rax + 0xFFFF]
movups xmm0, [r15 + 0xFFFF]
movups xmm0, [rax + rsi * 1  + 0x0]
movups xmm0, [rax + rsi + 0xFFFF]
movups xmm0, [r15 + rsi + 0xFFFF]
movups xmm0, [rax + r15 + 0xFFFF]
movups xmm0, [rax + rsi * 2 + 0xFFFF2]
movups xmm0, [rax + rsi * 4 + 0xFFFF4]
movups xmm0, [rax + rsi * 8 + 0xFFFF8]
movups xmm0, [rsp + rax * 8 + 0xFFFF8]
movups xmm0, [r15 + rax * 8 + 0xFFFF8]
movups xmm0, [rsp + r15 * 8 + 0xFFFF8]
movups xmm0, [r14 + r15 * 8 + 0xFFFF8]
movups xmm1, [0x0]
movups xmm1, [0xFF]
movups xmm1, [rel $ + 0x0]
movups xmm1, [rel $ + 0xFF]
movups xmm1, [rel $ + 0xFFFF]
movups xmm1, [rax]
movups xmm1, [rax + 0x0]
movups xmm1, [rax + 0xFFFF]
movups xmm1, [r15 + 0xFFFF]
movups xmm1, [rax + rsi * 1  + 0x0]
movups xmm1, [rax + rsi + 0xFFFF]
movups xmm1, [r15 + rsi + 0xFFFF]
movups xmm1, [rax + r15 + 0xFFFF]
movups xmm1, [rax + rsi * 2 + 0xFFFF2]
movups xmm1, [rax + rsi * 4 + 0xFFFF4]
movups xmm1, [rax + rsi * 8 + 0xFFFF8]
movups xmm1, [rsp + rax * 8 + 0xFFFF8]
movups xmm1, [r15 + rax * 8 + 0xFFFF8]
movups xmm1, [rsp + r15 * 8 + 0xFFFF8]
movups xmm1, [r14 + r15 * 8 + 0xFFFF8]
movups xmm15, [0x0]
movups xmm15, [0xFF]
movups xmm15, [rel $ + 0x0]
movups xmm15, [rel $ + 0xFF]
movups xmm15, [rel $ + 0xFFFF]
movups xmm15, [rax]
movups xmm15, [rax + 0x0]
movups xmm15, [rax + 0xFFFF]
movups xmm15, [r15 + 0xFFFF]
movups xmm15, [rax + rsi * 1  + 0x0]
movups xmm15, [rax + rsi + 0xFFFF]
movups xmm15, [r15 + rsi + 0xFFFF]
movups xmm15, [rax + r15 + 0xFFFF]
movups xmm15, [rax + rsi * 2 + 0xFFFF2]
movups xmm15, [rax + rsi * 4 + 0xFFFF4]
movups xmm15, [rax + rsi * 8 + 0xFFFF8]
movups xmm15, [rsp + rax * 8 + 0xFFFF8]
movups xmm15, [r15 + rax * 8 + 0xFFFF8]
movups xmm15, [rsp + r15 * 8 + 0xFFFF8]
movups xmm15, [r14 + r15 * 8 + 0xFFFF8]
movups [0x0], xmm0
movups [0x0], xmm1
movups [0x0], xmm15
movups [0xFF], xmm0
movups [0xFF], xmm1
movups [0xFF], xmm15
movups [rel $ + 0x0], xmm0
movups [rel $ + 0x0], xmm1
movups [rel $ + 0x0], xmm15
movups [rel $ + 0xFF], xmm0
movups [rel $ + 0xFF], xmm1
movups [rel $ + 0xFF], xmm15
movups [rel $ + 0xFFFF], xmm0
movups [rel $ + 0xFFFF], xmm1
movups [rel $ + 0xFFFF], xmm15
movups [rax], xmm0
movups [rax], xmm1
movups [rax], xmm15
movups [rax + 0x0], xmm0
movups [rax + 0x0], xmm1
movups [rax + 0x0], xmm15
movups [rax + 0xFFFF], xmm0
movups [rax + 0xFFFF], xmm1
movups [rax + 0xFFFF], xmm15
movups [r15 + 0xFFFF], xmm0
movups [r15 + 0xFFFF], xmm1
movups [r15 + 0xFFFF], xmm15
movups [rax + rsi * 1  + 0x0], xmm0
movups [rax + rsi * 1  + 0x0], xmm1
movups [rax + rsi * 1  + 0x0], xmm15
movups [rax + rsi + 0xFFFF], xmm0
movups [rax + rsi + 0xFFFF], xmm1
movups [rax + rsi + 0xFFFF], xmm15
movups [r15 + rsi + 0xFFFF], xmm0
movups [r15 + rsi + 0xFFFF], xmm1
movups [r15 + rsi + 0xFFFF], xmm15
movups [rax + r15 + 0xFFFF], xmm0
movups [rax + r15 + 0xFFFF], xmm1
movups [rax + r15 + 0xFFFF], xmm15
movups [rax + rsi * 2 + 0xFFFF2], xmm0
movups [rax + rsi * 2 + 0xFFFF2], xmm1
movups [rax + rsi * 2 + 0xFFFF2], xmm15
movups [rax + rsi * 4 + 0xFFFF4], xmm0
movups [rax + rsi * 4 + 0xFFFF4], xmm1
movups [rax + rsi * 4 + 0xFFFF4], xmm15
movups [rax + rsi * 8 + 0xFFFF8], xmm0
movups [rax + rsi * 8 + 0xFFFF8], xmm1
movups [rax + rsi * 8 + 0xFFFF8], xmm15
movups [rsp + rax * 8 + 0xFFFF8], xmm0
movups [rsp + rax * 8 + 0xFFFF8], xmm1
movups [rsp + rax * 8 + 0xFFFF8], xmm15
movups [r15 + rax * 8 + 0xFFFF8], xmm0
movups [r15 + rax * 8 + 0xFFFF8], xmm1
movups [r15 + rax * 8 + 0xFFFF8], xmm15
movups [rsp + r15 * 8 + 0xFFFF8], xmm0
movups [rsp + r15 * 8 + 0xFFFF8], xmm1
movups [rsp + r15 * 8 + 0xFFFF8], xmm15
movups [r14 + r15 * 8 + 0xFFFF8], xmm0
movups [r14 + r15 * 8 + 0xFFFF8], xmm1
movups [r14 + r15 * 8 + 0xFFFF8], xmm15
