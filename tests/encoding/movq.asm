; expect: 66480f7ec166480f7ec9664c0f7ef966480f7ec366480f7ecb664c0f7efb66490f7ec766490f7ecf664d0f7eff66480f6ec166480f6ec366490f6ec766480f6ec966480f6ecb66490f6ecf664c0f6ef9664c0f6efb664d0f6efff30f7ec0f30f7ec1f3410f7ec7f30f7ec8f30f7ec9f3410f7ecff3440f7ef8f3440f7ef9f3450f7efff30f7e042500000000f30f7e0425ff000000f30f7e05f8fffffff30f7e05f7000000f30f7e05f7ff0000f30f7e00f30f7e00f30f7e80ffff0000f3410f7e87ffff0000f30f7e0430f30f7e8430ffff0000f3410f7e8437ffff0000f3420f7e8438ffff0000f30f7e8470f2ff0f00f30f7e84b0f4ff0f00f30f7e84f0f8ff0f00f30f7e84c4f8ff0f00f3410f7e84c7f8ff0f00f3420f7e84fcf8ff0f00f3430f7e84fef8ff0f00f30f7e0c2500000000f30f7e0c25ff000000f30f7e0df8fffffff30f7e0df7000000f30f7e0df7ff0000f30f7e08f30f7e08f30f7e88ffff0000f3410f7e8fffff0000f30f7e0c30f30f7e8c30ffff0000f3410f7e8c37ffff0000f3420f7e8c38ffff0000f30f7e8c70f2ff0f00f30f7e8cb0f4ff0f00f30f7e8cf0f8ff0f00f30f7e8cc4f8ff0f00f3410f7e8cc7f8ff0f00f3420f7e8cfcf8ff0f00f3430f7e8cfef8ff0f00f3440f7e3c2500000000f3440f7e3c25ff000000f3440f7e3df7fffffff3440f7e3df6000000f3440f7e3df6ff0000f3440f7e38f3440f7e38f3440f7eb8ffff0000f3450f7ebfffff0000f3440f7e3c30f3440f7ebc30ffff0000f3450f7ebc37ffff0000f3460f7ebc38ffff0000f3440f7ebc70f2ff0f00f3440f7ebcb0f4ff0f00f3440f7ebcf0f8ff0f00f3440f7ebcc4f8ff0f00f3450f7ebcc7f8ff0f00f3460f7ebcfcf8ff0f00f3470f7ebcfef8ff0f00660fd6042500000000660fd60c250000000066440fd63c2500000000660fd60425ff000000660fd60c25ff00000066440fd63c25ff000000660fd605f8ffffff660fd60df8ffffff66440fd63df7ffffff660fd605f7000000660fd60df700000066440fd63df6000000660fd605f7ff0000660fd60df7ff000066440fd63df6ff0000660fd600660fd60866440fd638660fd600660fd60866440fd638660fd680ffff0000660fd688ffff000066440fd6b8ffff000066410fd687ffff000066410fd68fffff000066450fd6bfffff0000660fd60430660fd60c3066440fd63c30660fd68430ffff0000660fd68c30ffff000066440fd6bc30ffff000066410fd68437ffff000066410fd68c37ffff000066450fd6bc37ffff000066420fd68438ffff000066420fd68c38ffff000066460fd6bc38ffff0000660fd68470f2ff0f00660fd68c70f2ff0f0066440fd6bc70f2ff0f00660fd684b0f4ff0f00660fd68cb0f4ff0f0066440fd6bcb0f4ff0f00660fd684f0f8ff0f00660fd68cf0f8ff0f0066440fd6bcf0f8ff0f00660fd684c4f8ff0f00660fd68cc4f8ff0f0066440fd6bcc4f8ff0f0066410fd684c7f8ff0f0066410fd68cc7f8ff0f0066450fd6bcc7f8ff0f0066420fd684fcf8ff0f0066420fd68cfcf8ff0f0066460fd6bcfcf8ff0f0066430fd684fef8ff0f0066430fd68cfef8ff0f0066470fd6bcfef8ff0f00

bits 64

movq rcx, xmm0
movq rcx, xmm1
movq rcx, xmm15
movq rbx, xmm0
movq rbx, xmm1
movq rbx, xmm15
movq r15, xmm0
movq r15, xmm1
movq r15, xmm15
movq xmm0, rcx
movq xmm0, rbx
movq xmm0, r15
movq xmm1, rcx
movq xmm1, rbx
movq xmm1, r15
movq xmm15, rcx
movq xmm15, rbx
movq xmm15, r15
movq xmm0, xmm0
movq xmm0, xmm1
movq xmm0, xmm15
movq xmm1, xmm0
movq xmm1, xmm1
movq xmm1, xmm15
movq xmm15, xmm0
movq xmm15, xmm1
movq xmm15, xmm15
movq xmm0, qword [0x0]
movq xmm0, qword [0xFF]
movq xmm0, qword [rel $ + 0x0]
movq xmm0, qword [rel $ + 0xFF]
movq xmm0, qword [rel $ + 0xFFFF]
movq xmm0, qword [rax]
movq xmm0, qword [rax + 0x0]
movq xmm0, qword [rax + 0xFFFF]
movq xmm0, qword [r15 + 0xFFFF]
movq xmm0, qword [rax + rsi * 1  + 0x0]
movq xmm0, qword [rax + rsi + 0xFFFF]
movq xmm0, qword [r15 + rsi + 0xFFFF]
movq xmm0, qword [rax + r15 + 0xFFFF]
movq xmm0, qword [rax + rsi * 2 + 0xFFFF2]
movq xmm0, qword [rax + rsi * 4 + 0xFFFF4]
movq xmm0, qword [rax + rsi * 8 + 0xFFFF8]
movq xmm0, qword [rsp + rax * 8 + 0xFFFF8]
movq xmm0, qword [r15 + rax * 8 + 0xFFFF8]
movq xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
movq xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
movq xmm1, qword [0x0]
movq xmm1, qword [0xFF]
movq xmm1, qword [rel $ + 0x0]
movq xmm1, qword [rel $ + 0xFF]
movq xmm1, qword [rel $ + 0xFFFF]
movq xmm1, qword [rax]
movq xmm1, qword [rax + 0x0]
movq xmm1, qword [rax + 0xFFFF]
movq xmm1, qword [r15 + 0xFFFF]
movq xmm1, qword [rax + rsi * 1  + 0x0]
movq xmm1, qword [rax + rsi + 0xFFFF]
movq xmm1, qword [r15 + rsi + 0xFFFF]
movq xmm1, qword [rax + r15 + 0xFFFF]
movq xmm1, qword [rax + rsi * 2 + 0xFFFF2]
movq xmm1, qword [rax + rsi * 4 + 0xFFFF4]
movq xmm1, qword [rax + rsi * 8 + 0xFFFF8]
movq xmm1, qword [rsp + rax * 8 + 0xFFFF8]
movq xmm1, qword [r15 + rax * 8 + 0xFFFF8]
movq xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
movq xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
movq xmm15, qword [0x0]
movq xmm15, qword [0xFF]
movq xmm15, qword [rel $ + 0x0]
movq xmm15, qword [rel $ + 0xFF]
movq xmm15, qword [rel $ + 0xFFFF]
movq xmm15, qword [rax]
movq xmm15, qword [rax + 0x0]
movq xmm15, qword [rax + 0xFFFF]
movq xmm15, qword [r15 + 0xFFFF]
movq xmm15, qword [rax + rsi * 1  + 0x0]
movq xmm15, qword [rax + rsi + 0xFFFF]
movq xmm15, qword [r15 + rsi + 0xFFFF]
movq xmm15, qword [rax + r15 + 0xFFFF]
movq xmm15, qword [rax + rsi * 2 + 0xFFFF2]
movq xmm15, qword [rax + rsi * 4 + 0xFFFF4]
movq xmm15, qword [rax + rsi * 8 + 0xFFFF8]
movq xmm15, qword [rsp + rax * 8 + 0xFFFF8]
movq xmm15, qword [r15 + rax * 8 + 0xFFFF8]
movq xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
movq xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
movq qword [0x0], xmm0
movq qword [0x0], xmm1
movq qword [0x0], xmm15
movq qword [0xFF], xmm0
movq qword [0xFF], xmm1
movq qword [0xFF], xmm15
movq qword [rel $ + 0x0], xmm0
movq qword [rel $ + 0x0], xmm1
movq qword [rel $ + 0x0], xmm15
movq qword [rel $ + 0xFF], xmm0
movq qword [rel $ + 0xFF], xmm1
movq qword [rel $ + 0xFF], xmm15
movq qword [rel $ + 0xFFFF], xmm0
movq qword [rel $ + 0xFFFF], xmm1
movq qword [rel $ + 0xFFFF], xmm15
movq qword [rax], xmm0
movq qword [rax], xmm1
movq qword [rax], xmm15
movq qword [rax + 0x0], xmm0
movq qword [rax + 0x0], xmm1
movq qword [rax + 0x0], xmm15
movq qword [rax + 0xFFFF], xmm0
movq qword [rax + 0xFFFF], xmm1
movq qword [rax + 0xFFFF], xmm15
movq qword [r15 + 0xFFFF], xmm0
movq qword [r15 + 0xFFFF], xmm1
movq qword [r15 + 0xFFFF], xmm15
movq qword [rax + rsi * 1  + 0x0], xmm0
movq qword [rax + rsi * 1  + 0x0], xmm1
movq qword [rax + rsi * 1  + 0x0], xmm15
movq qword [rax + rsi + 0xFFFF], xmm0
movq qword [rax + rsi + 0xFFFF], xmm1
movq qword [rax + rsi + 0xFFFF], xmm15
movq qword [r15 + rsi + 0xFFFF], xmm0
movq qword [r15 + rsi + 0xFFFF], xmm1
movq qword [r15 + rsi + 0xFFFF], xmm15
movq qword [rax + r15 + 0xFFFF], xmm0
movq qword [rax + r15 + 0xFFFF], xmm1
movq qword [rax + r15 + 0xFFFF], xmm15
movq qword [rax + rsi * 2 + 0xFFFF2], xmm0
movq qword [rax + rsi * 2 + 0xFFFF2], xmm1
movq qword [rax + rsi * 2 + 0xFFFF2], xmm15
movq qword [rax + rsi * 4 + 0xFFFF4], xmm0
movq qword [rax + rsi * 4 + 0xFFFF4], xmm1
movq qword [rax + rsi * 4 + 0xFFFF4], xmm15
movq qword [rax + rsi * 8 + 0xFFFF8], xmm0
movq qword [rax + rsi * 8 + 0xFFFF8], xmm1
movq qword [rax + rsi * 8 + 0xFFFF8], xmm15
movq qword [rsp + rax * 8 + 0xFFFF8], xmm0
movq qword [rsp + rax * 8 + 0xFFFF8], xmm1
movq qword [rsp + rax * 8 + 0xFFFF8], xmm15
movq qword [r15 + rax * 8 + 0xFFFF8], xmm0
movq qword [r15 + rax * 8 + 0xFFFF8], xmm1
movq qword [r15 + rax * 8 + 0xFFFF8], xmm15
movq qword [rsp + r15 * 8 + 0xFFFF8], xmm0
movq qword [rsp + r15 * 8 + 0xFFFF8], xmm1
movq qword [rsp + r15 * 8 + 0xFFFF8], xmm15
movq qword [r14 + r15 * 8 + 0xFFFF8], xmm0
movq qword [r14 + r15 * 8 + 0xFFFF8], xmm1
movq qword [r14 + r15 * 8 + 0xFFFF8], xmm15
