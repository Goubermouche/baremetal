; expect: f30f52c0f30f52c1f3410f52c7f30f52c8f30f52c9f3410f52cff3440f52f8f3440f52f9f3450f52fff30f52042500000000f30f520425ff000000f30f5205f8fffffff30f5205f7000000f30f5205f7ff0000f30f5200f30f5200f30f5280ffff0000f3410f5287ffff0000f30f520430f30f528430ffff0000f3410f528437ffff0000f3420f528438ffff0000f30f528470f2ff0f00f30f5284b0f4ff0f00f30f5284f0f8ff0f00f30f5284c4f8ff0f00f3410f5284c7f8ff0f00f3420f5284fcf8ff0f00f3430f5284fef8ff0f00f30f520c2500000000f30f520c25ff000000f30f520df8fffffff30f520df7000000f30f520df7ff0000f30f5208f30f5208f30f5288ffff0000f3410f528fffff0000f30f520c30f30f528c30ffff0000f3410f528c37ffff0000f3420f528c38ffff0000f30f528c70f2ff0f00f30f528cb0f4ff0f00f30f528cf0f8ff0f00f30f528cc4f8ff0f00f3410f528cc7f8ff0f00f3420f528cfcf8ff0f00f3430f528cfef8ff0f00f3440f523c2500000000f3440f523c25ff000000f3440f523df7fffffff3440f523df6000000f3440f523df6ff0000f3440f5238f3440f5238f3440f52b8ffff0000f3450f52bfffff0000f3440f523c30f3440f52bc30ffff0000f3450f52bc37ffff0000f3460f52bc38ffff0000f3440f52bc70f2ff0f00f3440f52bcb0f4ff0f00f3440f52bcf0f8ff0f00f3440f52bcc4f8ff0f00f3450f52bcc7f8ff0f00f3460f52bcfcf8ff0f00f3470f52bcfef8ff0f00

bits 64

rsqrtss xmm0, xmm0
rsqrtss xmm0, xmm1
rsqrtss xmm0, xmm15
rsqrtss xmm1, xmm0
rsqrtss xmm1, xmm1
rsqrtss xmm1, xmm15
rsqrtss xmm15, xmm0
rsqrtss xmm15, xmm1
rsqrtss xmm15, xmm15
rsqrtss xmm0, dword [0x0]
rsqrtss xmm0, dword [0xFF]
rsqrtss xmm0, dword [rel $ + 0x0]
rsqrtss xmm0, dword [rel $ + 0xFF]
rsqrtss xmm0, dword [rel $ + 0xFFFF]
rsqrtss xmm0, dword [rax]
rsqrtss xmm0, dword [rax + 0x0]
rsqrtss xmm0, dword [rax + 0xFFFF]
rsqrtss xmm0, dword [r15 + 0xFFFF]
rsqrtss xmm0, dword [rax + rsi * 1  + 0x0]
rsqrtss xmm0, dword [rax + rsi + 0xFFFF]
rsqrtss xmm0, dword [r15 + rsi + 0xFFFF]
rsqrtss xmm0, dword [rax + r15 + 0xFFFF]
rsqrtss xmm0, dword [rax + rsi * 2 + 0xFFFF2]
rsqrtss xmm0, dword [rax + rsi * 4 + 0xFFFF4]
rsqrtss xmm0, dword [rax + rsi * 8 + 0xFFFF8]
rsqrtss xmm0, dword [rsp + rax * 8 + 0xFFFF8]
rsqrtss xmm0, dword [r15 + rax * 8 + 0xFFFF8]
rsqrtss xmm0, dword [rsp + r15 * 8 + 0xFFFF8]
rsqrtss xmm0, dword [r14 + r15 * 8 + 0xFFFF8]
rsqrtss xmm1, dword [0x0]
rsqrtss xmm1, dword [0xFF]
rsqrtss xmm1, dword [rel $ + 0x0]
rsqrtss xmm1, dword [rel $ + 0xFF]
rsqrtss xmm1, dword [rel $ + 0xFFFF]
rsqrtss xmm1, dword [rax]
rsqrtss xmm1, dword [rax + 0x0]
rsqrtss xmm1, dword [rax + 0xFFFF]
rsqrtss xmm1, dword [r15 + 0xFFFF]
rsqrtss xmm1, dword [rax + rsi * 1  + 0x0]
rsqrtss xmm1, dword [rax + rsi + 0xFFFF]
rsqrtss xmm1, dword [r15 + rsi + 0xFFFF]
rsqrtss xmm1, dword [rax + r15 + 0xFFFF]
rsqrtss xmm1, dword [rax + rsi * 2 + 0xFFFF2]
rsqrtss xmm1, dword [rax + rsi * 4 + 0xFFFF4]
rsqrtss xmm1, dword [rax + rsi * 8 + 0xFFFF8]
rsqrtss xmm1, dword [rsp + rax * 8 + 0xFFFF8]
rsqrtss xmm1, dword [r15 + rax * 8 + 0xFFFF8]
rsqrtss xmm1, dword [rsp + r15 * 8 + 0xFFFF8]
rsqrtss xmm1, dword [r14 + r15 * 8 + 0xFFFF8]
rsqrtss xmm15, dword [0x0]
rsqrtss xmm15, dword [0xFF]
rsqrtss xmm15, dword [rel $ + 0x0]
rsqrtss xmm15, dword [rel $ + 0xFF]
rsqrtss xmm15, dword [rel $ + 0xFFFF]
rsqrtss xmm15, dword [rax]
rsqrtss xmm15, dword [rax + 0x0]
rsqrtss xmm15, dword [rax + 0xFFFF]
rsqrtss xmm15, dword [r15 + 0xFFFF]
rsqrtss xmm15, dword [rax + rsi * 1  + 0x0]
rsqrtss xmm15, dword [rax + rsi + 0xFFFF]
rsqrtss xmm15, dword [r15 + rsi + 0xFFFF]
rsqrtss xmm15, dword [rax + r15 + 0xFFFF]
rsqrtss xmm15, dword [rax + rsi * 2 + 0xFFFF2]
rsqrtss xmm15, dword [rax + rsi * 4 + 0xFFFF4]
rsqrtss xmm15, dword [rax + rsi * 8 + 0xFFFF8]
rsqrtss xmm15, dword [rsp + rax * 8 + 0xFFFF8]
rsqrtss xmm15, dword [r15 + rax * 8 + 0xFFFF8]
rsqrtss xmm15, dword [rsp + r15 * 8 + 0xFFFF8]
rsqrtss xmm15, dword [r14 + r15 * 8 + 0xFFFF8]
