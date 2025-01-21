; expect: f20f2b042500000000f20f2b0c2500000000f2440f2b3c2500000000f20f2b0425ff000000f20f2b0c25ff000000f2440f2b3c25ff000000f20f2b05f8fffffff20f2b0df8fffffff2440f2b3df7fffffff20f2b05f7000000f20f2b0df7000000f2440f2b3df6000000f20f2b05f7ff0000f20f2b0df7ff0000f2440f2b3df6ff0000f20f2b00f20f2b08f2440f2b38f20f2b00f20f2b08f2440f2b38f20f2b80ffff0000f20f2b88ffff0000f2440f2bb8ffff0000f2410f2b87ffff0000f2410f2b8fffff0000f2450f2bbfffff0000f20f2b0430f20f2b0c30f2440f2b3c30f20f2b8430ffff0000f20f2b8c30ffff0000f2440f2bbc30ffff0000f2410f2b8437ffff0000f2410f2b8c37ffff0000f2450f2bbc37ffff0000f2420f2b8438ffff0000f2420f2b8c38ffff0000f2460f2bbc38ffff0000f20f2b8470f2ff0f00f20f2b8c70f2ff0f00f2440f2bbc70f2ff0f00f20f2b84b0f4ff0f00f20f2b8cb0f4ff0f00f2440f2bbcb0f4ff0f00f20f2b84f0f8ff0f00f20f2b8cf0f8ff0f00f2440f2bbcf0f8ff0f00f20f2b84c4f8ff0f00f20f2b8cc4f8ff0f00f2440f2bbcc4f8ff0f00f2410f2b84c7f8ff0f00f2410f2b8cc7f8ff0f00f2450f2bbcc7f8ff0f00f2420f2b84fcf8ff0f00f2420f2b8cfcf8ff0f00f2460f2bbcfcf8ff0f00f2430f2b84fef8ff0f00f2430f2b8cfef8ff0f00f2470f2bbcfef8ff0f00

movntsd qword [0x0], xmm0
movntsd qword [0x0], xmm1
movntsd qword [0x0], xmm15
movntsd qword [0xFF], xmm0
movntsd qword [0xFF], xmm1
movntsd qword [0xFF], xmm15
movntsd qword [rel $ + 0x0], xmm0
movntsd qword [rel $ + 0x0], xmm1
movntsd qword [rel $ + 0x0], xmm15
movntsd qword [rel $ + 0xFF], xmm0
movntsd qword [rel $ + 0xFF], xmm1
movntsd qword [rel $ + 0xFF], xmm15
movntsd qword [rel $ + 0xFFFF], xmm0
movntsd qword [rel $ + 0xFFFF], xmm1
movntsd qword [rel $ + 0xFFFF], xmm15
movntsd qword [rax], xmm0
movntsd qword [rax], xmm1
movntsd qword [rax], xmm15
movntsd qword [rax + 0x0], xmm0
movntsd qword [rax + 0x0], xmm1
movntsd qword [rax + 0x0], xmm15
movntsd qword [rax + 0xFFFF], xmm0
movntsd qword [rax + 0xFFFF], xmm1
movntsd qword [rax + 0xFFFF], xmm15
movntsd qword [r15 + 0xFFFF], xmm0
movntsd qword [r15 + 0xFFFF], xmm1
movntsd qword [r15 + 0xFFFF], xmm15
movntsd qword [rax + rsi * 1  + 0x0], xmm0
movntsd qword [rax + rsi * 1  + 0x0], xmm1
movntsd qword [rax + rsi * 1  + 0x0], xmm15
movntsd qword [rax + rsi + 0xFFFF], xmm0
movntsd qword [rax + rsi + 0xFFFF], xmm1
movntsd qword [rax + rsi + 0xFFFF], xmm15
movntsd qword [r15 + rsi + 0xFFFF], xmm0
movntsd qword [r15 + rsi + 0xFFFF], xmm1
movntsd qword [r15 + rsi + 0xFFFF], xmm15
movntsd qword [rax + r15 + 0xFFFF], xmm0
movntsd qword [rax + r15 + 0xFFFF], xmm1
movntsd qword [rax + r15 + 0xFFFF], xmm15
movntsd qword [rax + rsi * 2 + 0xFFFF2], xmm0
movntsd qword [rax + rsi * 2 + 0xFFFF2], xmm1
movntsd qword [rax + rsi * 2 + 0xFFFF2], xmm15
movntsd qword [rax + rsi * 4 + 0xFFFF4], xmm0
movntsd qword [rax + rsi * 4 + 0xFFFF4], xmm1
movntsd qword [rax + rsi * 4 + 0xFFFF4], xmm15
movntsd qword [rax + rsi * 8 + 0xFFFF8], xmm0
movntsd qword [rax + rsi * 8 + 0xFFFF8], xmm1
movntsd qword [rax + rsi * 8 + 0xFFFF8], xmm15
movntsd qword [rsp + rax * 8 + 0xFFFF8], xmm0
movntsd qword [rsp + rax * 8 + 0xFFFF8], xmm1
movntsd qword [rsp + rax * 8 + 0xFFFF8], xmm15
movntsd qword [r15 + rax * 8 + 0xFFFF8], xmm0
movntsd qword [r15 + rax * 8 + 0xFFFF8], xmm1
movntsd qword [r15 + rax * 8 + 0xFFFF8], xmm15
movntsd qword [rsp + r15 * 8 + 0xFFFF8], xmm0
movntsd qword [rsp + r15 * 8 + 0xFFFF8], xmm1
movntsd qword [rsp + r15 * 8 + 0xFFFF8], xmm15
movntsd qword [r14 + r15 * 8 + 0xFFFF8], xmm0
movntsd qword [r14 + r15 * 8 + 0xFFFF8], xmm1
movntsd qword [r14 + r15 * 8 + 0xFFFF8], xmm15