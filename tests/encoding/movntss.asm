; expect: f30f2b042500000000f30f2b0c2500000000f3440f2b3c2500000000f30f2b0425ff000000f30f2b0c25ff000000f3440f2b3c25ff000000f30f2b05f8fffffff30f2b0df8fffffff3440f2b3df7fffffff30f2b05f7000000f30f2b0df7000000f3440f2b3df6000000f30f2b05f7ff0000f30f2b0df7ff0000f3440f2b3df6ff0000f30f2b00f30f2b08f3440f2b38f30f2b00f30f2b08f3440f2b38f30f2b80ffff0000f30f2b88ffff0000f3440f2bb8ffff0000f3410f2b87ffff0000f3410f2b8fffff0000f3450f2bbfffff0000f30f2b0430f30f2b0c30f3440f2b3c30f30f2b8430ffff0000f30f2b8c30ffff0000f3440f2bbc30ffff0000f3410f2b8437ffff0000f3410f2b8c37ffff0000f3450f2bbc37ffff0000f3420f2b8438ffff0000f3420f2b8c38ffff0000f3460f2bbc38ffff0000f30f2b8470f2ff0f00f30f2b8c70f2ff0f00f3440f2bbc70f2ff0f00f30f2b84b0f4ff0f00f30f2b8cb0f4ff0f00f3440f2bbcb0f4ff0f00f30f2b84f0f8ff0f00f30f2b8cf0f8ff0f00f3440f2bbcf0f8ff0f00f30f2b84c4f8ff0f00f30f2b8cc4f8ff0f00f3440f2bbcc4f8ff0f00f3410f2b84c7f8ff0f00f3410f2b8cc7f8ff0f00f3450f2bbcc7f8ff0f00f3420f2b84fcf8ff0f00f3420f2b8cfcf8ff0f00f3460f2bbcfcf8ff0f00f3430f2b84fef8ff0f00f3430f2b8cfef8ff0f00f3470f2bbcfef8ff0f00

movntss dword [0x0], xmm0
movntss dword [0x0], xmm1
movntss dword [0x0], xmm15
movntss dword [0xFF], xmm0
movntss dword [0xFF], xmm1
movntss dword [0xFF], xmm15
movntss dword [rel $ + 0x0], xmm0
movntss dword [rel $ + 0x0], xmm1
movntss dword [rel $ + 0x0], xmm15
movntss dword [rel $ + 0xFF], xmm0
movntss dword [rel $ + 0xFF], xmm1
movntss dword [rel $ + 0xFF], xmm15
movntss dword [rel $ + 0xFFFF], xmm0
movntss dword [rel $ + 0xFFFF], xmm1
movntss dword [rel $ + 0xFFFF], xmm15
movntss dword [rax], xmm0
movntss dword [rax], xmm1
movntss dword [rax], xmm15
movntss dword [rax + 0x0], xmm0
movntss dword [rax + 0x0], xmm1
movntss dword [rax + 0x0], xmm15
movntss dword [rax + 0xFFFF], xmm0
movntss dword [rax + 0xFFFF], xmm1
movntss dword [rax + 0xFFFF], xmm15
movntss dword [r15 + 0xFFFF], xmm0
movntss dword [r15 + 0xFFFF], xmm1
movntss dword [r15 + 0xFFFF], xmm15
movntss dword [rax + rsi * 1  + 0x0], xmm0
movntss dword [rax + rsi * 1  + 0x0], xmm1
movntss dword [rax + rsi * 1  + 0x0], xmm15
movntss dword [rax + rsi + 0xFFFF], xmm0
movntss dword [rax + rsi + 0xFFFF], xmm1
movntss dword [rax + rsi + 0xFFFF], xmm15
movntss dword [r15 + rsi + 0xFFFF], xmm0
movntss dword [r15 + rsi + 0xFFFF], xmm1
movntss dword [r15 + rsi + 0xFFFF], xmm15
movntss dword [rax + r15 + 0xFFFF], xmm0
movntss dword [rax + r15 + 0xFFFF], xmm1
movntss dword [rax + r15 + 0xFFFF], xmm15
movntss dword [rax + rsi * 2 + 0xFFFF2], xmm0
movntss dword [rax + rsi * 2 + 0xFFFF2], xmm1
movntss dword [rax + rsi * 2 + 0xFFFF2], xmm15
movntss dword [rax + rsi * 4 + 0xFFFF4], xmm0
movntss dword [rax + rsi * 4 + 0xFFFF4], xmm1
movntss dword [rax + rsi * 4 + 0xFFFF4], xmm15
movntss dword [rax + rsi * 8 + 0xFFFF8], xmm0
movntss dword [rax + rsi * 8 + 0xFFFF8], xmm1
movntss dword [rax + rsi * 8 + 0xFFFF8], xmm15
movntss dword [rsp + rax * 8 + 0xFFFF8], xmm0
movntss dword [rsp + rax * 8 + 0xFFFF8], xmm1
movntss dword [rsp + rax * 8 + 0xFFFF8], xmm15
movntss dword [r15 + rax * 8 + 0xFFFF8], xmm0
movntss dword [r15 + rax * 8 + 0xFFFF8], xmm1
movntss dword [r15 + rax * 8 + 0xFFFF8], xmm15
movntss dword [rsp + r15 * 8 + 0xFFFF8], xmm0
movntss dword [rsp + r15 * 8 + 0xFFFF8], xmm1
movntss dword [rsp + r15 * 8 + 0xFFFF8], xmm15
movntss dword [r14 + r15 * 8 + 0xFFFF8], xmm0
movntss dword [r14 + r15 * 8 + 0xFFFF8], xmm1
movntss dword [r14 + r15 * 8 + 0xFFFF8], xmm15