; expect: c4e2790fc0c4e2790fc1c4c2790fc7c4e2790fc8c4e2790fc9c4c2790fcfc462790ff8c462790ff9c442790fffc4e2790f042500000000c4e2790f0425ff000000c4e2790f05f7ffffffc4e2790f05f6000000c4e2790f05f6ff0000c4e2790f00c4e2790f00c4e2790f80ffff0000c4c2790f87ffff0000c4e2790f0430c4e2790f8430ffff0000c4c2790f8437ffff0000c4a2790f8438ffff0000c4e2790f8470f2ff0f00c4e2790f84b0f4ff0f00c4e2790f84f0f8ff0f00c4e2790f84c4f8ff0f00c4c2790f84c7f8ff0f00c4a2790f84fcf8ff0f00c482790f84fef8ff0f00c4e2790f0c2500000000c4e2790f0c25ff000000c4e2790f0df7ffffffc4e2790f0df6000000c4e2790f0df6ff0000c4e2790f08c4e2790f08c4e2790f88ffff0000c4c2790f8fffff0000c4e2790f0c30c4e2790f8c30ffff0000c4c2790f8c37ffff0000c4a2790f8c38ffff0000c4e2790f8c70f2ff0f00c4e2790f8cb0f4ff0f00c4e2790f8cf0f8ff0f00c4e2790f8cc4f8ff0f00c4c2790f8cc7f8ff0f00c4a2790f8cfcf8ff0f00c482790f8cfef8ff0f00c462790f3c2500000000c462790f3c25ff000000c462790f3df7ffffffc462790f3df6000000c462790f3df6ff0000c462790f38c462790f38c462790fb8ffff0000c442790fbfffff0000c462790f3c30c462790fbc30ffff0000c442790fbc37ffff0000c422790fbc38ffff0000c462790fbc70f2ff0f00c462790fbcb0f4ff0f00c462790fbcf0f8ff0f00c462790fbcc4f8ff0f00c442790fbcc7f8ff0f00c422790fbcfcf8ff0f00c402790fbcfef8ff0f00c4e27d0fc0c4e27d0fc1c4c27d0fc7c4e27d0fc8c4e27d0fc9c4c27d0fcfc4627d0ff8c4627d0ff9c4427d0fffc4e27d0f042500000000c4e27d0f0425ff000000c4e27d0f05f7ffffffc4e27d0f05f6000000c4e27d0f05f6ff0000c4e27d0f00c4e27d0f00c4e27d0f80ffff0000c4c27d0f87ffff0000c4e27d0f0430c4e27d0f8430ffff0000c4c27d0f8437ffff0000c4a27d0f8438ffff0000c4e27d0f8470f2ff0f00c4e27d0f84b0f4ff0f00c4e27d0f84f0f8ff0f00c4e27d0f84c4f8ff0f00c4c27d0f84c7f8ff0f00c4a27d0f84fcf8ff0f00c4827d0f84fef8ff0f00c4e27d0f0c2500000000c4e27d0f0c25ff000000c4e27d0f0df7ffffffc4e27d0f0df6000000c4e27d0f0df6ff0000c4e27d0f08c4e27d0f08c4e27d0f88ffff0000c4c27d0f8fffff0000c4e27d0f0c30c4e27d0f8c30ffff0000c4c27d0f8c37ffff0000c4a27d0f8c38ffff0000c4e27d0f8c70f2ff0f00c4e27d0f8cb0f4ff0f00c4e27d0f8cf0f8ff0f00c4e27d0f8cc4f8ff0f00c4c27d0f8cc7f8ff0f00c4a27d0f8cfcf8ff0f00c4827d0f8cfef8ff0f00c4627d0f3c2500000000c4627d0f3c25ff000000c4627d0f3df7ffffffc4627d0f3df6000000c4627d0f3df6ff0000c4627d0f38c4627d0f38c4627d0fb8ffff0000c4427d0fbfffff0000c4627d0f3c30c4627d0fbc30ffff0000c4427d0fbc37ffff0000c4227d0fbc38ffff0000c4627d0fbc70f2ff0f00c4627d0fbcb0f4ff0f00c4627d0fbcf0f8ff0f00c4627d0fbcc4f8ff0f00c4427d0fbcc7f8ff0f00c4227d0fbcfcf8ff0f00c4027d0fbcfef8ff0f00

bits 64

vtestpd xmm0, xmm0
vtestpd xmm0, xmm1
vtestpd xmm0, xmm15
vtestpd xmm1, xmm0
vtestpd xmm1, xmm1
vtestpd xmm1, xmm15
vtestpd xmm15, xmm0
vtestpd xmm15, xmm1
vtestpd xmm15, xmm15
vtestpd xmm0, [0x0]
vtestpd xmm0, [0xFF]
vtestpd xmm0, [rel $ + 0x0]
vtestpd xmm0, [rel $ + 0xFF]
vtestpd xmm0, [rel $ + 0xFFFF]
vtestpd xmm0, [rax]
vtestpd xmm0, [rax + 0x0]
vtestpd xmm0, [rax + 0xFFFF]
vtestpd xmm0, [r15 + 0xFFFF]
vtestpd xmm0, [rax + rsi * 1  + 0x0]
vtestpd xmm0, [rax + rsi + 0xFFFF]
vtestpd xmm0, [r15 + rsi + 0xFFFF]
vtestpd xmm0, [rax + r15 + 0xFFFF]
vtestpd xmm0, [rax + rsi * 2 + 0xFFFF2]
vtestpd xmm0, [rax + rsi * 4 + 0xFFFF4]
vtestpd xmm0, [rax + rsi * 8 + 0xFFFF8]
vtestpd xmm0, [rsp + rax * 8 + 0xFFFF8]
vtestpd xmm0, [r15 + rax * 8 + 0xFFFF8]
vtestpd xmm0, [rsp + r15 * 8 + 0xFFFF8]
vtestpd xmm0, [r14 + r15 * 8 + 0xFFFF8]
vtestpd xmm1, [0x0]
vtestpd xmm1, [0xFF]
vtestpd xmm1, [rel $ + 0x0]
vtestpd xmm1, [rel $ + 0xFF]
vtestpd xmm1, [rel $ + 0xFFFF]
vtestpd xmm1, [rax]
vtestpd xmm1, [rax + 0x0]
vtestpd xmm1, [rax + 0xFFFF]
vtestpd xmm1, [r15 + 0xFFFF]
vtestpd xmm1, [rax + rsi * 1  + 0x0]
vtestpd xmm1, [rax + rsi + 0xFFFF]
vtestpd xmm1, [r15 + rsi + 0xFFFF]
vtestpd xmm1, [rax + r15 + 0xFFFF]
vtestpd xmm1, [rax + rsi * 2 + 0xFFFF2]
vtestpd xmm1, [rax + rsi * 4 + 0xFFFF4]
vtestpd xmm1, [rax + rsi * 8 + 0xFFFF8]
vtestpd xmm1, [rsp + rax * 8 + 0xFFFF8]
vtestpd xmm1, [r15 + rax * 8 + 0xFFFF8]
vtestpd xmm1, [rsp + r15 * 8 + 0xFFFF8]
vtestpd xmm1, [r14 + r15 * 8 + 0xFFFF8]
vtestpd xmm15, [0x0]
vtestpd xmm15, [0xFF]
vtestpd xmm15, [rel $ + 0x0]
vtestpd xmm15, [rel $ + 0xFF]
vtestpd xmm15, [rel $ + 0xFFFF]
vtestpd xmm15, [rax]
vtestpd xmm15, [rax + 0x0]
vtestpd xmm15, [rax + 0xFFFF]
vtestpd xmm15, [r15 + 0xFFFF]
vtestpd xmm15, [rax + rsi * 1  + 0x0]
vtestpd xmm15, [rax + rsi + 0xFFFF]
vtestpd xmm15, [r15 + rsi + 0xFFFF]
vtestpd xmm15, [rax + r15 + 0xFFFF]
vtestpd xmm15, [rax + rsi * 2 + 0xFFFF2]
vtestpd xmm15, [rax + rsi * 4 + 0xFFFF4]
vtestpd xmm15, [rax + rsi * 8 + 0xFFFF8]
vtestpd xmm15, [rsp + rax * 8 + 0xFFFF8]
vtestpd xmm15, [r15 + rax * 8 + 0xFFFF8]
vtestpd xmm15, [rsp + r15 * 8 + 0xFFFF8]
vtestpd xmm15, [r14 + r15 * 8 + 0xFFFF8]
vtestpd ymm0, ymm0
vtestpd ymm0, ymm1
vtestpd ymm0, ymm15
vtestpd ymm1, ymm0
vtestpd ymm1, ymm1
vtestpd ymm1, ymm15
vtestpd ymm15, ymm0
vtestpd ymm15, ymm1
vtestpd ymm15, ymm15
vtestpd ymm0, [0x0]
vtestpd ymm0, [0xFF]
vtestpd ymm0, [rel $ + 0x0]
vtestpd ymm0, [rel $ + 0xFF]
vtestpd ymm0, [rel $ + 0xFFFF]
vtestpd ymm0, [rax]
vtestpd ymm0, [rax + 0x0]
vtestpd ymm0, [rax + 0xFFFF]
vtestpd ymm0, [r15 + 0xFFFF]
vtestpd ymm0, [rax + rsi * 1  + 0x0]
vtestpd ymm0, [rax + rsi + 0xFFFF]
vtestpd ymm0, [r15 + rsi + 0xFFFF]
vtestpd ymm0, [rax + r15 + 0xFFFF]
vtestpd ymm0, [rax + rsi * 2 + 0xFFFF2]
vtestpd ymm0, [rax + rsi * 4 + 0xFFFF4]
vtestpd ymm0, [rax + rsi * 8 + 0xFFFF8]
vtestpd ymm0, [rsp + rax * 8 + 0xFFFF8]
vtestpd ymm0, [r15 + rax * 8 + 0xFFFF8]
vtestpd ymm0, [rsp + r15 * 8 + 0xFFFF8]
vtestpd ymm0, [r14 + r15 * 8 + 0xFFFF8]
vtestpd ymm1, [0x0]
vtestpd ymm1, [0xFF]
vtestpd ymm1, [rel $ + 0x0]
vtestpd ymm1, [rel $ + 0xFF]
vtestpd ymm1, [rel $ + 0xFFFF]
vtestpd ymm1, [rax]
vtestpd ymm1, [rax + 0x0]
vtestpd ymm1, [rax + 0xFFFF]
vtestpd ymm1, [r15 + 0xFFFF]
vtestpd ymm1, [rax + rsi * 1  + 0x0]
vtestpd ymm1, [rax + rsi + 0xFFFF]
vtestpd ymm1, [r15 + rsi + 0xFFFF]
vtestpd ymm1, [rax + r15 + 0xFFFF]
vtestpd ymm1, [rax + rsi * 2 + 0xFFFF2]
vtestpd ymm1, [rax + rsi * 4 + 0xFFFF4]
vtestpd ymm1, [rax + rsi * 8 + 0xFFFF8]
vtestpd ymm1, [rsp + rax * 8 + 0xFFFF8]
vtestpd ymm1, [r15 + rax * 8 + 0xFFFF8]
vtestpd ymm1, [rsp + r15 * 8 + 0xFFFF8]
vtestpd ymm1, [r14 + r15 * 8 + 0xFFFF8]
vtestpd ymm15, [0x0]
vtestpd ymm15, [0xFF]
vtestpd ymm15, [rel $ + 0x0]
vtestpd ymm15, [rel $ + 0xFF]
vtestpd ymm15, [rel $ + 0xFFFF]
vtestpd ymm15, [rax]
vtestpd ymm15, [rax + 0x0]
vtestpd ymm15, [rax + 0xFFFF]
vtestpd ymm15, [r15 + 0xFFFF]
vtestpd ymm15, [rax + rsi * 1  + 0x0]
vtestpd ymm15, [rax + rsi + 0xFFFF]
vtestpd ymm15, [r15 + rsi + 0xFFFF]
vtestpd ymm15, [rax + r15 + 0xFFFF]
vtestpd ymm15, [rax + rsi * 2 + 0xFFFF2]
vtestpd ymm15, [rax + rsi * 4 + 0xFFFF4]
vtestpd ymm15, [rax + rsi * 8 + 0xFFFF8]
vtestpd ymm15, [rsp + rax * 8 + 0xFFFF8]
vtestpd ymm15, [r15 + rax * 8 + 0xFFFF8]
vtestpd ymm15, [rsp + r15 * 8 + 0xFFFF8]
vtestpd ymm15, [r14 + r15 * 8 + 0xFFFF8]
