; expect: 62f57c082fc062f57c082fc162d57c082fc762957c082fc762f57c082fc862f57c082fc962d57c082fcf62957c082fcf62757c082ff862757c082ff962557c082fff62157c082fff62657c082ff862657c082ff962457c082fff62057c082fff62f57c082f04250000000062f57c082f0425ff00000062f57c082f05f6ffffff62f57c082f05f500000062f57c082f05f5ff000062f57c082f0062f57c082f0062f57c082f80ffff000062d57c082f87ffff000062f57c082f043062f57c082f8430ffff000062d57c082f8437ffff000062b57c082f8438ffff000062f57c082f8470f2ff0f0062f57c082f84b0f4ff0f0062f57c082f84f0f8ff0f0062f57c082f84c4f8ff0f0062d57c082f84c7f8ff0f0062b57c082f84fcf8ff0f0062957c082f84fef8ff0f0062f57c082f0c250000000062f57c082f0c25ff00000062f57c082f0df6ffffff62f57c082f0df500000062f57c082f0df5ff000062f57c082f0862f57c082f0862f57c082f88ffff000062d57c082f8fffff000062f57c082f0c3062f57c082f8c30ffff000062d57c082f8c37ffff000062b57c082f8c38ffff000062f57c082f8c70f2ff0f0062f57c082f8cb0f4ff0f0062f57c082f8cf0f8ff0f0062f57c082f8cc4f8ff0f0062d57c082f8cc7f8ff0f0062b57c082f8cfcf8ff0f0062957c082f8cfef8ff0f0062757c082f3c250000000062757c082f3c25ff00000062757c082f3df6ffffff62757c082f3df500000062757c082f3df5ff000062757c082f3862757c082f3862757c082fb8ffff000062557c082fbfffff000062757c082f3c3062757c082fbc30ffff000062557c082fbc37ffff000062357c082fbc38ffff000062757c082fbc70f2ff0f0062757c082fbcb0f4ff0f0062757c082fbcf0f8ff0f0062757c082fbcc4f8ff0f0062557c082fbcc7f8ff0f0062357c082fbcfcf8ff0f0062157c082fbcfef8ff0f0062657c082f3c250000000062657c082f3c25ff00000062657c082f3df6ffffff62657c082f3df500000062657c082f3df5ff000062657c082f3862657c082f3862657c082fb8ffff000062457c082fbfffff000062657c082f3c3062657c082fbc30ffff000062457c082fbc37ffff000062257c082fbc38ffff000062657c082fbc70f2ff0f0062657c082fbcb0f4ff0f0062657c082fbcf0f8ff0f0062657c082fbcc4f8ff0f0062457c082fbcc7f8ff0f0062257c082fbcfcf8ff0f0062057c082fbcfef8ff0f00

bits 64

vcomish xmm0, xmm0
vcomish xmm0, xmm1
vcomish xmm0, xmm15
vcomish xmm0, xmm31
vcomish xmm1, xmm0
vcomish xmm1, xmm1
vcomish xmm1, xmm15
vcomish xmm1, xmm31
vcomish xmm15, xmm0
vcomish xmm15, xmm1
vcomish xmm15, xmm15
vcomish xmm15, xmm31
vcomish xmm31, xmm0
vcomish xmm31, xmm1
vcomish xmm31, xmm15
vcomish xmm31, xmm31
vcomish xmm0, word [0x0]
vcomish xmm0, word [0xFF]
vcomish xmm0, word [rel $ + 0x0]
vcomish xmm0, word [rel $ + 0xFF]
vcomish xmm0, word [rel $ + 0xFFFF]
vcomish xmm0, word [rax]
vcomish xmm0, word [rax + 0x0]
vcomish xmm0, word [rax + 0xFFFF]
vcomish xmm0, word [r15 + 0xFFFF]
vcomish xmm0, word [rax + rsi * 1  + 0x0]
vcomish xmm0, word [rax + rsi + 0xFFFF]
vcomish xmm0, word [r15 + rsi + 0xFFFF]
vcomish xmm0, word [rax + r15 + 0xFFFF]
vcomish xmm0, word [rax + rsi * 2 + 0xFFFF2]
vcomish xmm0, word [rax + rsi * 4 + 0xFFFF4]
vcomish xmm0, word [rax + rsi * 8 + 0xFFFF8]
vcomish xmm0, word [rsp + rax * 8 + 0xFFFF8]
vcomish xmm0, word [r15 + rax * 8 + 0xFFFF8]
vcomish xmm0, word [rsp + r15 * 8 + 0xFFFF8]
vcomish xmm0, word [r14 + r15 * 8 + 0xFFFF8]
vcomish xmm1, word [0x0]
vcomish xmm1, word [0xFF]
vcomish xmm1, word [rel $ + 0x0]
vcomish xmm1, word [rel $ + 0xFF]
vcomish xmm1, word [rel $ + 0xFFFF]
vcomish xmm1, word [rax]
vcomish xmm1, word [rax + 0x0]
vcomish xmm1, word [rax + 0xFFFF]
vcomish xmm1, word [r15 + 0xFFFF]
vcomish xmm1, word [rax + rsi * 1  + 0x0]
vcomish xmm1, word [rax + rsi + 0xFFFF]
vcomish xmm1, word [r15 + rsi + 0xFFFF]
vcomish xmm1, word [rax + r15 + 0xFFFF]
vcomish xmm1, word [rax + rsi * 2 + 0xFFFF2]
vcomish xmm1, word [rax + rsi * 4 + 0xFFFF4]
vcomish xmm1, word [rax + rsi * 8 + 0xFFFF8]
vcomish xmm1, word [rsp + rax * 8 + 0xFFFF8]
vcomish xmm1, word [r15 + rax * 8 + 0xFFFF8]
vcomish xmm1, word [rsp + r15 * 8 + 0xFFFF8]
vcomish xmm1, word [r14 + r15 * 8 + 0xFFFF8]
vcomish xmm15, word [0x0]
vcomish xmm15, word [0xFF]
vcomish xmm15, word [rel $ + 0x0]
vcomish xmm15, word [rel $ + 0xFF]
vcomish xmm15, word [rel $ + 0xFFFF]
vcomish xmm15, word [rax]
vcomish xmm15, word [rax + 0x0]
vcomish xmm15, word [rax + 0xFFFF]
vcomish xmm15, word [r15 + 0xFFFF]
vcomish xmm15, word [rax + rsi * 1  + 0x0]
vcomish xmm15, word [rax + rsi + 0xFFFF]
vcomish xmm15, word [r15 + rsi + 0xFFFF]
vcomish xmm15, word [rax + r15 + 0xFFFF]
vcomish xmm15, word [rax + rsi * 2 + 0xFFFF2]
vcomish xmm15, word [rax + rsi * 4 + 0xFFFF4]
vcomish xmm15, word [rax + rsi * 8 + 0xFFFF8]
vcomish xmm15, word [rsp + rax * 8 + 0xFFFF8]
vcomish xmm15, word [r15 + rax * 8 + 0xFFFF8]
vcomish xmm15, word [rsp + r15 * 8 + 0xFFFF8]
vcomish xmm15, word [r14 + r15 * 8 + 0xFFFF8]
vcomish xmm31, word [0x0]
vcomish xmm31, word [0xFF]
vcomish xmm31, word [rel $ + 0x0]
vcomish xmm31, word [rel $ + 0xFF]
vcomish xmm31, word [rel $ + 0xFFFF]
vcomish xmm31, word [rax]
vcomish xmm31, word [rax + 0x0]
vcomish xmm31, word [rax + 0xFFFF]
vcomish xmm31, word [r15 + 0xFFFF]
vcomish xmm31, word [rax + rsi * 1  + 0x0]
vcomish xmm31, word [rax + rsi + 0xFFFF]
vcomish xmm31, word [r15 + rsi + 0xFFFF]
vcomish xmm31, word [rax + r15 + 0xFFFF]
vcomish xmm31, word [rax + rsi * 2 + 0xFFFF2]
vcomish xmm31, word [rax + rsi * 4 + 0xFFFF4]
vcomish xmm31, word [rax + rsi * 8 + 0xFFFF8]
vcomish xmm31, word [rsp + rax * 8 + 0xFFFF8]
vcomish xmm31, word [r15 + rax * 8 + 0xFFFF8]
vcomish xmm31, word [rsp + r15 * 8 + 0xFFFF8]
vcomish xmm31, word [r14 + r15 * 8 + 0xFFFF8]
