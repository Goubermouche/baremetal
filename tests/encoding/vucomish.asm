; expect: 62f57c082ec062f57c082ec162d57c082ec762957c082ec762f57c082ec862f57c082ec962d57c082ecf62957c082ecf62757c082ef862757c082ef962557c082eff62157c082eff62657c082ef862657c082ef962457c082eff62057c082eff62f57c082e04250000000062f57c082e0425ff00000062f57c082e05f6ffffff62f57c082e05f500000062f57c082e05f5ff000062f57c082e0062f57c082e0062f57c082e80ffff000062d57c082e87ffff000062f57c082e043062f57c082e8430ffff000062d57c082e8437ffff000062b57c082e8438ffff000062f57c082e8470f2ff0f0062f57c082e84b0f4ff0f0062f57c082e84f0f8ff0f0062f57c082e84c4f8ff0f0062d57c082e84c7f8ff0f0062b57c082e84fcf8ff0f0062957c082e84fef8ff0f0062f57c082e0c250000000062f57c082e0c25ff00000062f57c082e0df6ffffff62f57c082e0df500000062f57c082e0df5ff000062f57c082e0862f57c082e0862f57c082e88ffff000062d57c082e8fffff000062f57c082e0c3062f57c082e8c30ffff000062d57c082e8c37ffff000062b57c082e8c38ffff000062f57c082e8c70f2ff0f0062f57c082e8cb0f4ff0f0062f57c082e8cf0f8ff0f0062f57c082e8cc4f8ff0f0062d57c082e8cc7f8ff0f0062b57c082e8cfcf8ff0f0062957c082e8cfef8ff0f0062757c082e3c250000000062757c082e3c25ff00000062757c082e3df6ffffff62757c082e3df500000062757c082e3df5ff000062757c082e3862757c082e3862757c082eb8ffff000062557c082ebfffff000062757c082e3c3062757c082ebc30ffff000062557c082ebc37ffff000062357c082ebc38ffff000062757c082ebc70f2ff0f0062757c082ebcb0f4ff0f0062757c082ebcf0f8ff0f0062757c082ebcc4f8ff0f0062557c082ebcc7f8ff0f0062357c082ebcfcf8ff0f0062157c082ebcfef8ff0f0062657c082e3c250000000062657c082e3c25ff00000062657c082e3df6ffffff62657c082e3df500000062657c082e3df5ff000062657c082e3862657c082e3862657c082eb8ffff000062457c082ebfffff000062657c082e3c3062657c082ebc30ffff000062457c082ebc37ffff000062257c082ebc38ffff000062657c082ebc70f2ff0f0062657c082ebcb0f4ff0f0062657c082ebcf0f8ff0f0062657c082ebcc4f8ff0f0062457c082ebcc7f8ff0f0062257c082ebcfcf8ff0f0062057c082ebcfef8ff0f00

bits 64

vucomish xmm0, xmm0
vucomish xmm0, xmm1
vucomish xmm0, xmm15
vucomish xmm0, xmm31
vucomish xmm1, xmm0
vucomish xmm1, xmm1
vucomish xmm1, xmm15
vucomish xmm1, xmm31
vucomish xmm15, xmm0
vucomish xmm15, xmm1
vucomish xmm15, xmm15
vucomish xmm15, xmm31
vucomish xmm31, xmm0
vucomish xmm31, xmm1
vucomish xmm31, xmm15
vucomish xmm31, xmm31
vucomish xmm0, word [0x0]
vucomish xmm0, word [0xFF]
vucomish xmm0, word [rel $ + 0x0]
vucomish xmm0, word [rel $ + 0xFF]
vucomish xmm0, word [rel $ + 0xFFFF]
vucomish xmm0, word [rax]
vucomish xmm0, word [rax + 0x0]
vucomish xmm0, word [rax + 0xFFFF]
vucomish xmm0, word [r15 + 0xFFFF]
vucomish xmm0, word [rax + rsi * 1  + 0x0]
vucomish xmm0, word [rax + rsi + 0xFFFF]
vucomish xmm0, word [r15 + rsi + 0xFFFF]
vucomish xmm0, word [rax + r15 + 0xFFFF]
vucomish xmm0, word [rax + rsi * 2 + 0xFFFF2]
vucomish xmm0, word [rax + rsi * 4 + 0xFFFF4]
vucomish xmm0, word [rax + rsi * 8 + 0xFFFF8]
vucomish xmm0, word [rsp + rax * 8 + 0xFFFF8]
vucomish xmm0, word [r15 + rax * 8 + 0xFFFF8]
vucomish xmm0, word [rsp + r15 * 8 + 0xFFFF8]
vucomish xmm0, word [r14 + r15 * 8 + 0xFFFF8]
vucomish xmm1, word [0x0]
vucomish xmm1, word [0xFF]
vucomish xmm1, word [rel $ + 0x0]
vucomish xmm1, word [rel $ + 0xFF]
vucomish xmm1, word [rel $ + 0xFFFF]
vucomish xmm1, word [rax]
vucomish xmm1, word [rax + 0x0]
vucomish xmm1, word [rax + 0xFFFF]
vucomish xmm1, word [r15 + 0xFFFF]
vucomish xmm1, word [rax + rsi * 1  + 0x0]
vucomish xmm1, word [rax + rsi + 0xFFFF]
vucomish xmm1, word [r15 + rsi + 0xFFFF]
vucomish xmm1, word [rax + r15 + 0xFFFF]
vucomish xmm1, word [rax + rsi * 2 + 0xFFFF2]
vucomish xmm1, word [rax + rsi * 4 + 0xFFFF4]
vucomish xmm1, word [rax + rsi * 8 + 0xFFFF8]
vucomish xmm1, word [rsp + rax * 8 + 0xFFFF8]
vucomish xmm1, word [r15 + rax * 8 + 0xFFFF8]
vucomish xmm1, word [rsp + r15 * 8 + 0xFFFF8]
vucomish xmm1, word [r14 + r15 * 8 + 0xFFFF8]
vucomish xmm15, word [0x0]
vucomish xmm15, word [0xFF]
vucomish xmm15, word [rel $ + 0x0]
vucomish xmm15, word [rel $ + 0xFF]
vucomish xmm15, word [rel $ + 0xFFFF]
vucomish xmm15, word [rax]
vucomish xmm15, word [rax + 0x0]
vucomish xmm15, word [rax + 0xFFFF]
vucomish xmm15, word [r15 + 0xFFFF]
vucomish xmm15, word [rax + rsi * 1  + 0x0]
vucomish xmm15, word [rax + rsi + 0xFFFF]
vucomish xmm15, word [r15 + rsi + 0xFFFF]
vucomish xmm15, word [rax + r15 + 0xFFFF]
vucomish xmm15, word [rax + rsi * 2 + 0xFFFF2]
vucomish xmm15, word [rax + rsi * 4 + 0xFFFF4]
vucomish xmm15, word [rax + rsi * 8 + 0xFFFF8]
vucomish xmm15, word [rsp + rax * 8 + 0xFFFF8]
vucomish xmm15, word [r15 + rax * 8 + 0xFFFF8]
vucomish xmm15, word [rsp + r15 * 8 + 0xFFFF8]
vucomish xmm15, word [r14 + r15 * 8 + 0xFFFF8]
vucomish xmm31, word [0x0]
vucomish xmm31, word [0xFF]
vucomish xmm31, word [rel $ + 0x0]
vucomish xmm31, word [rel $ + 0xFF]
vucomish xmm31, word [rel $ + 0xFFFF]
vucomish xmm31, word [rax]
vucomish xmm31, word [rax + 0x0]
vucomish xmm31, word [rax + 0xFFFF]
vucomish xmm31, word [r15 + 0xFFFF]
vucomish xmm31, word [rax + rsi * 1  + 0x0]
vucomish xmm31, word [rax + rsi + 0xFFFF]
vucomish xmm31, word [r15 + rsi + 0xFFFF]
vucomish xmm31, word [rax + r15 + 0xFFFF]
vucomish xmm31, word [rax + rsi * 2 + 0xFFFF2]
vucomish xmm31, word [rax + rsi * 4 + 0xFFFF4]
vucomish xmm31, word [rax + rsi * 8 + 0xFFFF8]
vucomish xmm31, word [rsp + rax * 8 + 0xFFFF8]
vucomish xmm31, word [r15 + rax * 8 + 0xFFFF8]
vucomish xmm31, word [rsp + r15 * 8 + 0xFFFF8]
vucomish xmm31, word [r14 + r15 * 8 + 0xFFFF8]
