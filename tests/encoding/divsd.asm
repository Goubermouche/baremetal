; expect: f20f5ec0f20f5ec1f2410f5ec7f20f5ec8f20f5ec9f2410f5ecff2440f5ef8f2440f5ef9f2450f5efff20f5e042500000000f20f5e0425ff000000f20f5e05f8fffffff20f5e05f7000000f20f5e05f7ff0000f20f5e00f20f5e00f20f5e80ffff0000f2410f5e87ffff0000f20f5e0430f20f5e8430ffff0000f2410f5e8437ffff0000f2420f5e8438ffff0000f20f5e8470f2ff0f00f20f5e84b0f4ff0f00f20f5e84f0f8ff0f00f20f5e84c4f8ff0f00f2410f5e84c7f8ff0f00f2420f5e84fcf8ff0f00f2430f5e84fef8ff0f00f20f5e0c2500000000f20f5e0c25ff000000f20f5e0df8fffffff20f5e0df7000000f20f5e0df7ff0000f20f5e08f20f5e08f20f5e88ffff0000f2410f5e8fffff0000f20f5e0c30f20f5e8c30ffff0000f2410f5e8c37ffff0000f2420f5e8c38ffff0000f20f5e8c70f2ff0f00f20f5e8cb0f4ff0f00f20f5e8cf0f8ff0f00f20f5e8cc4f8ff0f00f2410f5e8cc7f8ff0f00f2420f5e8cfcf8ff0f00f2430f5e8cfef8ff0f00f2440f5e3c2500000000f2440f5e3c25ff000000f2440f5e3df7fffffff2440f5e3df6000000f2440f5e3df6ff0000f2440f5e38f2440f5e38f2440f5eb8ffff0000f2450f5ebfffff0000f2440f5e3c30f2440f5ebc30ffff0000f2450f5ebc37ffff0000f2460f5ebc38ffff0000f2440f5ebc70f2ff0f00f2440f5ebcb0f4ff0f00f2440f5ebcf0f8ff0f00f2440f5ebcc4f8ff0f00f2450f5ebcc7f8ff0f00f2460f5ebcfcf8ff0f00f2470f5ebcfef8ff0f00

bits 64

divsd xmm0, xmm0
divsd xmm0, xmm1
divsd xmm0, xmm15
divsd xmm1, xmm0
divsd xmm1, xmm1
divsd xmm1, xmm15
divsd xmm15, xmm0
divsd xmm15, xmm1
divsd xmm15, xmm15
divsd xmm0, qword [0x0]
divsd xmm0, qword [0xFF]
divsd xmm0, qword [rel $ + 0x0]
divsd xmm0, qword [rel $ + 0xFF]
divsd xmm0, qword [rel $ + 0xFFFF]
divsd xmm0, qword [rax]
divsd xmm0, qword [rax + 0x0]
divsd xmm0, qword [rax + 0xFFFF]
divsd xmm0, qword [r15 + 0xFFFF]
divsd xmm0, qword [rax + rsi * 1  + 0x0]
divsd xmm0, qword [rax + rsi + 0xFFFF]
divsd xmm0, qword [r15 + rsi + 0xFFFF]
divsd xmm0, qword [rax + r15 + 0xFFFF]
divsd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
divsd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
divsd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
divsd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
divsd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
divsd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
divsd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
divsd xmm1, qword [0x0]
divsd xmm1, qword [0xFF]
divsd xmm1, qword [rel $ + 0x0]
divsd xmm1, qword [rel $ + 0xFF]
divsd xmm1, qword [rel $ + 0xFFFF]
divsd xmm1, qword [rax]
divsd xmm1, qword [rax + 0x0]
divsd xmm1, qword [rax + 0xFFFF]
divsd xmm1, qword [r15 + 0xFFFF]
divsd xmm1, qword [rax + rsi * 1  + 0x0]
divsd xmm1, qword [rax + rsi + 0xFFFF]
divsd xmm1, qword [r15 + rsi + 0xFFFF]
divsd xmm1, qword [rax + r15 + 0xFFFF]
divsd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
divsd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
divsd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
divsd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
divsd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
divsd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
divsd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
divsd xmm15, qword [0x0]
divsd xmm15, qword [0xFF]
divsd xmm15, qword [rel $ + 0x0]
divsd xmm15, qword [rel $ + 0xFF]
divsd xmm15, qword [rel $ + 0xFFFF]
divsd xmm15, qword [rax]
divsd xmm15, qword [rax + 0x0]
divsd xmm15, qword [rax + 0xFFFF]
divsd xmm15, qword [r15 + 0xFFFF]
divsd xmm15, qword [rax + rsi * 1  + 0x0]
divsd xmm15, qword [rax + rsi + 0xFFFF]
divsd xmm15, qword [r15 + rsi + 0xFFFF]
divsd xmm15, qword [rax + r15 + 0xFFFF]
divsd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
divsd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
divsd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
divsd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
divsd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
divsd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
divsd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
