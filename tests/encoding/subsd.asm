; expect: f20f5cc0f20f5cc1f2410f5cc7f20f5cc8f20f5cc9f2410f5ccff2440f5cf8f2440f5cf9f2450f5cfff20f5c042500000000f20f5c0425ff000000f20f5c05f8fffffff20f5c05f7000000f20f5c05f7ff0000f20f5c00f20f5c00f20f5c80ffff0000f2410f5c87ffff0000f20f5c0430f20f5c8430ffff0000f2410f5c8437ffff0000f2420f5c8438ffff0000f20f5c8470f2ff0f00f20f5c84b0f4ff0f00f20f5c84f0f8ff0f00f20f5c84c4f8ff0f00f2410f5c84c7f8ff0f00f2420f5c84fcf8ff0f00f2430f5c84fef8ff0f00f20f5c0c2500000000f20f5c0c25ff000000f20f5c0df8fffffff20f5c0df7000000f20f5c0df7ff0000f20f5c08f20f5c08f20f5c88ffff0000f2410f5c8fffff0000f20f5c0c30f20f5c8c30ffff0000f2410f5c8c37ffff0000f2420f5c8c38ffff0000f20f5c8c70f2ff0f00f20f5c8cb0f4ff0f00f20f5c8cf0f8ff0f00f20f5c8cc4f8ff0f00f2410f5c8cc7f8ff0f00f2420f5c8cfcf8ff0f00f2430f5c8cfef8ff0f00f2440f5c3c2500000000f2440f5c3c25ff000000f2440f5c3df7fffffff2440f5c3df6000000f2440f5c3df6ff0000f2440f5c38f2440f5c38f2440f5cb8ffff0000f2450f5cbfffff0000f2440f5c3c30f2440f5cbc30ffff0000f2450f5cbc37ffff0000f2460f5cbc38ffff0000f2440f5cbc70f2ff0f00f2440f5cbcb0f4ff0f00f2440f5cbcf0f8ff0f00f2440f5cbcc4f8ff0f00f2450f5cbcc7f8ff0f00f2460f5cbcfcf8ff0f00f2470f5cbcfef8ff0f00

bits 64

subsd xmm0, xmm0
subsd xmm0, xmm1
subsd xmm0, xmm15
subsd xmm1, xmm0
subsd xmm1, xmm1
subsd xmm1, xmm15
subsd xmm15, xmm0
subsd xmm15, xmm1
subsd xmm15, xmm15
subsd xmm0, qword [0x0]
subsd xmm0, qword [0xFF]
subsd xmm0, qword [rel $ + 0x0]
subsd xmm0, qword [rel $ + 0xFF]
subsd xmm0, qword [rel $ + 0xFFFF]
subsd xmm0, qword [rax]
subsd xmm0, qword [rax + 0x0]
subsd xmm0, qword [rax + 0xFFFF]
subsd xmm0, qword [r15 + 0xFFFF]
subsd xmm0, qword [rax + rsi * 1  + 0x0]
subsd xmm0, qword [rax + rsi + 0xFFFF]
subsd xmm0, qword [r15 + rsi + 0xFFFF]
subsd xmm0, qword [rax + r15 + 0xFFFF]
subsd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
subsd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
subsd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
subsd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
subsd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
subsd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
subsd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
subsd xmm1, qword [0x0]
subsd xmm1, qword [0xFF]
subsd xmm1, qword [rel $ + 0x0]
subsd xmm1, qword [rel $ + 0xFF]
subsd xmm1, qword [rel $ + 0xFFFF]
subsd xmm1, qword [rax]
subsd xmm1, qword [rax + 0x0]
subsd xmm1, qword [rax + 0xFFFF]
subsd xmm1, qword [r15 + 0xFFFF]
subsd xmm1, qword [rax + rsi * 1  + 0x0]
subsd xmm1, qword [rax + rsi + 0xFFFF]
subsd xmm1, qword [r15 + rsi + 0xFFFF]
subsd xmm1, qword [rax + r15 + 0xFFFF]
subsd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
subsd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
subsd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
subsd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
subsd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
subsd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
subsd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
subsd xmm15, qword [0x0]
subsd xmm15, qword [0xFF]
subsd xmm15, qword [rel $ + 0x0]
subsd xmm15, qword [rel $ + 0xFF]
subsd xmm15, qword [rel $ + 0xFFFF]
subsd xmm15, qword [rax]
subsd xmm15, qword [rax + 0x0]
subsd xmm15, qword [rax + 0xFFFF]
subsd xmm15, qword [r15 + 0xFFFF]
subsd xmm15, qword [rax + rsi * 1  + 0x0]
subsd xmm15, qword [rax + rsi + 0xFFFF]
subsd xmm15, qword [r15 + rsi + 0xFFFF]
subsd xmm15, qword [rax + r15 + 0xFFFF]
subsd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
subsd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
subsd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
subsd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
subsd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
subsd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
subsd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
