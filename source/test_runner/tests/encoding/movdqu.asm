; expect: f30f6fc0f30f6fc1f3410f6fc7f30f6fc8f30f6fc9f3410f6fcff3440f6ff8f3440f6ff9f3450f6ffff30f6f042500000000f30f6f0425ff000000f30f6f05f8fffffff30f6f05f7000000f30f6f05f7ff0000f30f6f00f30f6f00f30f6f80ffff0000f3410f6f87ffff0000f30f6f0430f30f6f8430ffff0000f3410f6f8437ffff0000f3420f6f8438ffff0000f30f6f8470f2ff0f00f30f6f84b0f4ff0f00f30f6f84f0f8ff0f00f30f6f84c4f8ff0f00f3410f6f84c7f8ff0f00f3420f6f84fcf8ff0f00f3430f6f84fef8ff0f00f30f6f0c2500000000f30f6f0c25ff000000f30f6f0df8fffffff30f6f0df7000000f30f6f0df7ff0000f30f6f08f30f6f08f30f6f88ffff0000f3410f6f8fffff0000f30f6f0c30f30f6f8c30ffff0000f3410f6f8c37ffff0000f3420f6f8c38ffff0000f30f6f8c70f2ff0f00f30f6f8cb0f4ff0f00f30f6f8cf0f8ff0f00f30f6f8cc4f8ff0f00f3410f6f8cc7f8ff0f00f3420f6f8cfcf8ff0f00f3430f6f8cfef8ff0f00f3440f6f3c2500000000f3440f6f3c25ff000000f3440f6f3df7fffffff3440f6f3df6000000f3440f6f3df6ff0000f3440f6f38f3440f6f38f3440f6fb8ffff0000f3450f6fbfffff0000f3440f6f3c30f3440f6fbc30ffff0000f3450f6fbc37ffff0000f3460f6fbc38ffff0000f3440f6fbc70f2ff0f00f3440f6fbcb0f4ff0f00f3440f6fbcf0f8ff0f00f3440f6fbcc4f8ff0f00f3450f6fbcc7f8ff0f00f3460f6fbcfcf8ff0f00f3470f6fbcfef8ff0f00f30f7f042500000000f30f7f0c2500000000f3440f7f3c2500000000f30f7f0425ff000000f30f7f0c25ff000000f3440f7f3c25ff000000f30f7f05f8fffffff30f7f0df8fffffff3440f7f3df7fffffff30f7f05f7000000f30f7f0df7000000f3440f7f3df6000000f30f7f05f7ff0000f30f7f0df7ff0000f3440f7f3df6ff0000f30f7f00f30f7f08f3440f7f38f30f7f00f30f7f08f3440f7f38f30f7f80ffff0000f30f7f88ffff0000f3440f7fb8ffff0000f3410f7f87ffff0000f3410f7f8fffff0000f3450f7fbfffff0000f30f7f0430f30f7f0c30f3440f7f3c30f30f7f8430ffff0000f30f7f8c30ffff0000f3440f7fbc30ffff0000f3410f7f8437ffff0000f3410f7f8c37ffff0000f3450f7fbc37ffff0000f3420f7f8438ffff0000f3420f7f8c38ffff0000f3460f7fbc38ffff0000f30f7f8470f2ff0f00f30f7f8c70f2ff0f00f3440f7fbc70f2ff0f00f30f7f84b0f4ff0f00f30f7f8cb0f4ff0f00f3440f7fbcb0f4ff0f00f30f7f84f0f8ff0f00f30f7f8cf0f8ff0f00f3440f7fbcf0f8ff0f00f30f7f84c4f8ff0f00f30f7f8cc4f8ff0f00f3440f7fbcc4f8ff0f00f3410f7f84c7f8ff0f00f3410f7f8cc7f8ff0f00f3450f7fbcc7f8ff0f00f3420f7f84fcf8ff0f00f3420f7f8cfcf8ff0f00f3460f7fbcfcf8ff0f00f3430f7f84fef8ff0f00f3430f7f8cfef8ff0f00f3470f7fbcfef8ff0f00

movdqu xmm0, xmm0
movdqu xmm0, xmm1
movdqu xmm0, xmm15
movdqu xmm1, xmm0
movdqu xmm1, xmm1
movdqu xmm1, xmm15
movdqu xmm15, xmm0
movdqu xmm15, xmm1
movdqu xmm15, xmm15
movdqu xmm0, [0x0]
movdqu xmm0, [0xFF]
movdqu xmm0, [rel $ + 0x0]
movdqu xmm0, [rel $ + 0xFF]
movdqu xmm0, [rel $ + 0xFFFF]
movdqu xmm0, [rax]
movdqu xmm0, [rax + 0x0]
movdqu xmm0, [rax + 0xFFFF]
movdqu xmm0, [r15 + 0xFFFF]
movdqu xmm0, [rax + rsi * 1  + 0x0]
movdqu xmm0, [rax + rsi + 0xFFFF]
movdqu xmm0, [r15 + rsi + 0xFFFF]
movdqu xmm0, [rax + r15 + 0xFFFF]
movdqu xmm0, [rax + rsi * 2 + 0xFFFF2]
movdqu xmm0, [rax + rsi * 4 + 0xFFFF4]
movdqu xmm0, [rax + rsi * 8 + 0xFFFF8]
movdqu xmm0, [rsp + rax * 8 + 0xFFFF8]
movdqu xmm0, [r15 + rax * 8 + 0xFFFF8]
movdqu xmm0, [rsp + r15 * 8 + 0xFFFF8]
movdqu xmm0, [r14 + r15 * 8 + 0xFFFF8]
movdqu xmm1, [0x0]
movdqu xmm1, [0xFF]
movdqu xmm1, [rel $ + 0x0]
movdqu xmm1, [rel $ + 0xFF]
movdqu xmm1, [rel $ + 0xFFFF]
movdqu xmm1, [rax]
movdqu xmm1, [rax + 0x0]
movdqu xmm1, [rax + 0xFFFF]
movdqu xmm1, [r15 + 0xFFFF]
movdqu xmm1, [rax + rsi * 1  + 0x0]
movdqu xmm1, [rax + rsi + 0xFFFF]
movdqu xmm1, [r15 + rsi + 0xFFFF]
movdqu xmm1, [rax + r15 + 0xFFFF]
movdqu xmm1, [rax + rsi * 2 + 0xFFFF2]
movdqu xmm1, [rax + rsi * 4 + 0xFFFF4]
movdqu xmm1, [rax + rsi * 8 + 0xFFFF8]
movdqu xmm1, [rsp + rax * 8 + 0xFFFF8]
movdqu xmm1, [r15 + rax * 8 + 0xFFFF8]
movdqu xmm1, [rsp + r15 * 8 + 0xFFFF8]
movdqu xmm1, [r14 + r15 * 8 + 0xFFFF8]
movdqu xmm15, [0x0]
movdqu xmm15, [0xFF]
movdqu xmm15, [rel $ + 0x0]
movdqu xmm15, [rel $ + 0xFF]
movdqu xmm15, [rel $ + 0xFFFF]
movdqu xmm15, [rax]
movdqu xmm15, [rax + 0x0]
movdqu xmm15, [rax + 0xFFFF]
movdqu xmm15, [r15 + 0xFFFF]
movdqu xmm15, [rax + rsi * 1  + 0x0]
movdqu xmm15, [rax + rsi + 0xFFFF]
movdqu xmm15, [r15 + rsi + 0xFFFF]
movdqu xmm15, [rax + r15 + 0xFFFF]
movdqu xmm15, [rax + rsi * 2 + 0xFFFF2]
movdqu xmm15, [rax + rsi * 4 + 0xFFFF4]
movdqu xmm15, [rax + rsi * 8 + 0xFFFF8]
movdqu xmm15, [rsp + rax * 8 + 0xFFFF8]
movdqu xmm15, [r15 + rax * 8 + 0xFFFF8]
movdqu xmm15, [rsp + r15 * 8 + 0xFFFF8]
movdqu xmm15, [r14 + r15 * 8 + 0xFFFF8]
movdqu [0x0], xmm0
movdqu [0x0], xmm1
movdqu [0x0], xmm15
movdqu [0xFF], xmm0
movdqu [0xFF], xmm1
movdqu [0xFF], xmm15
movdqu [rel $ + 0x0], xmm0
movdqu [rel $ + 0x0], xmm1
movdqu [rel $ + 0x0], xmm15
movdqu [rel $ + 0xFF], xmm0
movdqu [rel $ + 0xFF], xmm1
movdqu [rel $ + 0xFF], xmm15
movdqu [rel $ + 0xFFFF], xmm0
movdqu [rel $ + 0xFFFF], xmm1
movdqu [rel $ + 0xFFFF], xmm15
movdqu [rax], xmm0
movdqu [rax], xmm1
movdqu [rax], xmm15
movdqu [rax + 0x0], xmm0
movdqu [rax + 0x0], xmm1
movdqu [rax + 0x0], xmm15
movdqu [rax + 0xFFFF], xmm0
movdqu [rax + 0xFFFF], xmm1
movdqu [rax + 0xFFFF], xmm15
movdqu [r15 + 0xFFFF], xmm0
movdqu [r15 + 0xFFFF], xmm1
movdqu [r15 + 0xFFFF], xmm15
movdqu [rax + rsi * 1  + 0x0], xmm0
movdqu [rax + rsi * 1  + 0x0], xmm1
movdqu [rax + rsi * 1  + 0x0], xmm15
movdqu [rax + rsi + 0xFFFF], xmm0
movdqu [rax + rsi + 0xFFFF], xmm1
movdqu [rax + rsi + 0xFFFF], xmm15
movdqu [r15 + rsi + 0xFFFF], xmm0
movdqu [r15 + rsi + 0xFFFF], xmm1
movdqu [r15 + rsi + 0xFFFF], xmm15
movdqu [rax + r15 + 0xFFFF], xmm0
movdqu [rax + r15 + 0xFFFF], xmm1
movdqu [rax + r15 + 0xFFFF], xmm15
movdqu [rax + rsi * 2 + 0xFFFF2], xmm0
movdqu [rax + rsi * 2 + 0xFFFF2], xmm1
movdqu [rax + rsi * 2 + 0xFFFF2], xmm15
movdqu [rax + rsi * 4 + 0xFFFF4], xmm0
movdqu [rax + rsi * 4 + 0xFFFF4], xmm1
movdqu [rax + rsi * 4 + 0xFFFF4], xmm15
movdqu [rax + rsi * 8 + 0xFFFF8], xmm0
movdqu [rax + rsi * 8 + 0xFFFF8], xmm1
movdqu [rax + rsi * 8 + 0xFFFF8], xmm15
movdqu [rsp + rax * 8 + 0xFFFF8], xmm0
movdqu [rsp + rax * 8 + 0xFFFF8], xmm1
movdqu [rsp + rax * 8 + 0xFFFF8], xmm15
movdqu [r15 + rax * 8 + 0xFFFF8], xmm0
movdqu [r15 + rax * 8 + 0xFFFF8], xmm1
movdqu [r15 + rax * 8 + 0xFFFF8], xmm15
movdqu [rsp + r15 * 8 + 0xFFFF8], xmm0
movdqu [rsp + r15 * 8 + 0xFFFF8], xmm1
movdqu [rsp + r15 * 8 + 0xFFFF8], xmm15
movdqu [r14 + r15 * 8 + 0xFFFF8], xmm0
movdqu [r14 + r15 * 8 + 0xFFFF8], xmm1
movdqu [r14 + r15 * 8 + 0xFFFF8], xmm15