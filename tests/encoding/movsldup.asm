; expect: f30f12c0f30f12c1f3410f12c7f30f12c8f30f12c9f3410f12cff3440f12f8f3440f12f9f3450f12fff30f12042500000000f30f120425ff000000f30f1205f8fffffff30f1205f7000000f30f1205f7ff0000f30f1200f30f1200f30f1280ffff0000f3410f1287ffff0000f30f120430f30f128430ffff0000f3410f128437ffff0000f3420f128438ffff0000f30f128470f2ff0f00f30f1284b0f4ff0f00f30f1284f0f8ff0f00f30f1284c4f8ff0f00f3410f1284c7f8ff0f00f3420f1284fcf8ff0f00f3430f1284fef8ff0f00f30f120c2500000000f30f120c25ff000000f30f120df8fffffff30f120df7000000f30f120df7ff0000f30f1208f30f1208f30f1288ffff0000f3410f128fffff0000f30f120c30f30f128c30ffff0000f3410f128c37ffff0000f3420f128c38ffff0000f30f128c70f2ff0f00f30f128cb0f4ff0f00f30f128cf0f8ff0f00f30f128cc4f8ff0f00f3410f128cc7f8ff0f00f3420f128cfcf8ff0f00f3430f128cfef8ff0f00f3440f123c2500000000f3440f123c25ff000000f3440f123df7fffffff3440f123df6000000f3440f123df6ff0000f3440f1238f3440f1238f3440f12b8ffff0000f3450f12bfffff0000f3440f123c30f3440f12bc30ffff0000f3450f12bc37ffff0000f3460f12bc38ffff0000f3440f12bc70f2ff0f00f3440f12bcb0f4ff0f00f3440f12bcf0f8ff0f00f3440f12bcc4f8ff0f00f3450f12bcc7f8ff0f00f3460f12bcfcf8ff0f00f3470f12bcfef8ff0f00

bits 64

movsldup xmm0, xmm0
movsldup xmm0, xmm1
movsldup xmm0, xmm15
movsldup xmm1, xmm0
movsldup xmm1, xmm1
movsldup xmm1, xmm15
movsldup xmm15, xmm0
movsldup xmm15, xmm1
movsldup xmm15, xmm15
movsldup xmm0, [0x0]
movsldup xmm0, [0xFF]
movsldup xmm0, [rel $ + 0x0]
movsldup xmm0, [rel $ + 0xFF]
movsldup xmm0, [rel $ + 0xFFFF]
movsldup xmm0, [rax]
movsldup xmm0, [rax + 0x0]
movsldup xmm0, [rax + 0xFFFF]
movsldup xmm0, [r15 + 0xFFFF]
movsldup xmm0, [rax + rsi * 1  + 0x0]
movsldup xmm0, [rax + rsi + 0xFFFF]
movsldup xmm0, [r15 + rsi + 0xFFFF]
movsldup xmm0, [rax + r15 + 0xFFFF]
movsldup xmm0, [rax + rsi * 2 + 0xFFFF2]
movsldup xmm0, [rax + rsi * 4 + 0xFFFF4]
movsldup xmm0, [rax + rsi * 8 + 0xFFFF8]
movsldup xmm0, [rsp + rax * 8 + 0xFFFF8]
movsldup xmm0, [r15 + rax * 8 + 0xFFFF8]
movsldup xmm0, [rsp + r15 * 8 + 0xFFFF8]
movsldup xmm0, [r14 + r15 * 8 + 0xFFFF8]
movsldup xmm1, [0x0]
movsldup xmm1, [0xFF]
movsldup xmm1, [rel $ + 0x0]
movsldup xmm1, [rel $ + 0xFF]
movsldup xmm1, [rel $ + 0xFFFF]
movsldup xmm1, [rax]
movsldup xmm1, [rax + 0x0]
movsldup xmm1, [rax + 0xFFFF]
movsldup xmm1, [r15 + 0xFFFF]
movsldup xmm1, [rax + rsi * 1  + 0x0]
movsldup xmm1, [rax + rsi + 0xFFFF]
movsldup xmm1, [r15 + rsi + 0xFFFF]
movsldup xmm1, [rax + r15 + 0xFFFF]
movsldup xmm1, [rax + rsi * 2 + 0xFFFF2]
movsldup xmm1, [rax + rsi * 4 + 0xFFFF4]
movsldup xmm1, [rax + rsi * 8 + 0xFFFF8]
movsldup xmm1, [rsp + rax * 8 + 0xFFFF8]
movsldup xmm1, [r15 + rax * 8 + 0xFFFF8]
movsldup xmm1, [rsp + r15 * 8 + 0xFFFF8]
movsldup xmm1, [r14 + r15 * 8 + 0xFFFF8]
movsldup xmm15, [0x0]
movsldup xmm15, [0xFF]
movsldup xmm15, [rel $ + 0x0]
movsldup xmm15, [rel $ + 0xFF]
movsldup xmm15, [rel $ + 0xFFFF]
movsldup xmm15, [rax]
movsldup xmm15, [rax + 0x0]
movsldup xmm15, [rax + 0xFFFF]
movsldup xmm15, [r15 + 0xFFFF]
movsldup xmm15, [rax + rsi * 1  + 0x0]
movsldup xmm15, [rax + rsi + 0xFFFF]
movsldup xmm15, [r15 + rsi + 0xFFFF]
movsldup xmm15, [rax + r15 + 0xFFFF]
movsldup xmm15, [rax + rsi * 2 + 0xFFFF2]
movsldup xmm15, [rax + rsi * 4 + 0xFFFF4]
movsldup xmm15, [rax + rsi * 8 + 0xFFFF8]
movsldup xmm15, [rsp + rax * 8 + 0xFFFF8]
movsldup xmm15, [r15 + rax * 8 + 0xFFFF8]
movsldup xmm15, [rsp + r15 * 8 + 0xFFFF8]
movsldup xmm15, [r14 + r15 * 8 + 0xFFFF8]
