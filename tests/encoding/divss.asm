; expect: f30f5ec0f30f5ec1f3410f5ec7f30f5ec8f30f5ec9f3410f5ecff3440f5ef8f3440f5ef9f3450f5efff30f5e042500000000f30f5e0425ff000000f30f5e05f8fffffff30f5e05f7000000f30f5e05f7ff0000f30f5e00f30f5e00f30f5e80ffff0000f3410f5e87ffff0000f30f5e0430f30f5e8430ffff0000f3410f5e8437ffff0000f3420f5e8438ffff0000f30f5e8470f2ff0f00f30f5e84b0f4ff0f00f30f5e84f0f8ff0f00f30f5e84c4f8ff0f00f3410f5e84c7f8ff0f00f3420f5e84fcf8ff0f00f3430f5e84fef8ff0f00f30f5e0c2500000000f30f5e0c25ff000000f30f5e0df8fffffff30f5e0df7000000f30f5e0df7ff0000f30f5e08f30f5e08f30f5e88ffff0000f3410f5e8fffff0000f30f5e0c30f30f5e8c30ffff0000f3410f5e8c37ffff0000f3420f5e8c38ffff0000f30f5e8c70f2ff0f00f30f5e8cb0f4ff0f00f30f5e8cf0f8ff0f00f30f5e8cc4f8ff0f00f3410f5e8cc7f8ff0f00f3420f5e8cfcf8ff0f00f3430f5e8cfef8ff0f00f3440f5e3c2500000000f3440f5e3c25ff000000f3440f5e3df7fffffff3440f5e3df6000000f3440f5e3df6ff0000f3440f5e38f3440f5e38f3440f5eb8ffff0000f3450f5ebfffff0000f3440f5e3c30f3440f5ebc30ffff0000f3450f5ebc37ffff0000f3460f5ebc38ffff0000f3440f5ebc70f2ff0f00f3440f5ebcb0f4ff0f00f3440f5ebcf0f8ff0f00f3440f5ebcc4f8ff0f00f3450f5ebcc7f8ff0f00f3460f5ebcfcf8ff0f00f3470f5ebcfef8ff0f00

bits 64

divss xmm0, xmm0
divss xmm0, xmm1
divss xmm0, xmm15
divss xmm1, xmm0
divss xmm1, xmm1
divss xmm1, xmm15
divss xmm15, xmm0
divss xmm15, xmm1
divss xmm15, xmm15
divss xmm0, dword [0x0]
divss xmm0, dword [0xFF]
divss xmm0, dword [rel $ + 0x0]
divss xmm0, dword [rel $ + 0xFF]
divss xmm0, dword [rel $ + 0xFFFF]
divss xmm0, dword [rax]
divss xmm0, dword [rax + 0x0]
divss xmm0, dword [rax + 0xFFFF]
divss xmm0, dword [r15 + 0xFFFF]
divss xmm0, dword [rax + rsi * 1  + 0x0]
divss xmm0, dword [rax + rsi + 0xFFFF]
divss xmm0, dword [r15 + rsi + 0xFFFF]
divss xmm0, dword [rax + r15 + 0xFFFF]
divss xmm0, dword [rax + rsi * 2 + 0xFFFF2]
divss xmm0, dword [rax + rsi * 4 + 0xFFFF4]
divss xmm0, dword [rax + rsi * 8 + 0xFFFF8]
divss xmm0, dword [rsp + rax * 8 + 0xFFFF8]
divss xmm0, dword [r15 + rax * 8 + 0xFFFF8]
divss xmm0, dword [rsp + r15 * 8 + 0xFFFF8]
divss xmm0, dword [r14 + r15 * 8 + 0xFFFF8]
divss xmm1, dword [0x0]
divss xmm1, dword [0xFF]
divss xmm1, dword [rel $ + 0x0]
divss xmm1, dword [rel $ + 0xFF]
divss xmm1, dword [rel $ + 0xFFFF]
divss xmm1, dword [rax]
divss xmm1, dword [rax + 0x0]
divss xmm1, dword [rax + 0xFFFF]
divss xmm1, dword [r15 + 0xFFFF]
divss xmm1, dword [rax + rsi * 1  + 0x0]
divss xmm1, dword [rax + rsi + 0xFFFF]
divss xmm1, dword [r15 + rsi + 0xFFFF]
divss xmm1, dword [rax + r15 + 0xFFFF]
divss xmm1, dword [rax + rsi * 2 + 0xFFFF2]
divss xmm1, dword [rax + rsi * 4 + 0xFFFF4]
divss xmm1, dword [rax + rsi * 8 + 0xFFFF8]
divss xmm1, dword [rsp + rax * 8 + 0xFFFF8]
divss xmm1, dword [r15 + rax * 8 + 0xFFFF8]
divss xmm1, dword [rsp + r15 * 8 + 0xFFFF8]
divss xmm1, dword [r14 + r15 * 8 + 0xFFFF8]
divss xmm15, dword [0x0]
divss xmm15, dword [0xFF]
divss xmm15, dword [rel $ + 0x0]
divss xmm15, dword [rel $ + 0xFF]
divss xmm15, dword [rel $ + 0xFFFF]
divss xmm15, dword [rax]
divss xmm15, dword [rax + 0x0]
divss xmm15, dword [rax + 0xFFFF]
divss xmm15, dword [r15 + 0xFFFF]
divss xmm15, dword [rax + rsi * 1  + 0x0]
divss xmm15, dword [rax + rsi + 0xFFFF]
divss xmm15, dword [r15 + rsi + 0xFFFF]
divss xmm15, dword [rax + r15 + 0xFFFF]
divss xmm15, dword [rax + rsi * 2 + 0xFFFF2]
divss xmm15, dword [rax + rsi * 4 + 0xFFFF4]
divss xmm15, dword [rax + rsi * 8 + 0xFFFF8]
divss xmm15, dword [rsp + rax * 8 + 0xFFFF8]
divss xmm15, dword [r15 + rax * 8 + 0xFFFF8]
divss xmm15, dword [rsp + r15 * 8 + 0xFFFF8]
divss xmm15, dword [r14 + r15 * 8 + 0xFFFF8]
