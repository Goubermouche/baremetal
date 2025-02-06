; expect: c5f82ec0c5f82ec1c4c1782ec7c5f82ec8c5f82ec9c4c1782ecfc5782ef8c5782ef9c441782effc5f82e042500000000c5f82e0425ff000000c5f82e05f8ffffffc5f82e05f7000000c5f82e05f7ff0000c5f82e00c5f82e00c5f82e80ffff0000c4c1782e87ffff0000c5f82e0430c5f82e8430ffff0000c4c1782e8437ffff0000c4a1782e8438ffff0000c5f82e8470f2ff0f00c5f82e84b0f4ff0f00c5f82e84f0f8ff0f00c5f82e84c4f8ff0f00c4c1782e84c7f8ff0f00c4a1782e84fcf8ff0f00c481782e84fef8ff0f00c5f82e0c2500000000c5f82e0c25ff000000c5f82e0df8ffffffc5f82e0df7000000c5f82e0df7ff0000c5f82e08c5f82e08c5f82e88ffff0000c4c1782e8fffff0000c5f82e0c30c5f82e8c30ffff0000c4c1782e8c37ffff0000c4a1782e8c38ffff0000c5f82e8c70f2ff0f00c5f82e8cb0f4ff0f00c5f82e8cf0f8ff0f00c5f82e8cc4f8ff0f00c4c1782e8cc7f8ff0f00c4a1782e8cfcf8ff0f00c481782e8cfef8ff0f00c5782e3c2500000000c5782e3c25ff000000c5782e3df8ffffffc5782e3df7000000c5782e3df7ff0000c5782e38c5782e38c5782eb8ffff0000c441782ebfffff0000c5782e3c30c5782ebc30ffff0000c441782ebc37ffff0000c421782ebc38ffff0000c5782ebc70f2ff0f00c5782ebcb0f4ff0f00c5782ebcf0f8ff0f00c5782ebcc4f8ff0f00c441782ebcc7f8ff0f00c421782ebcfcf8ff0f00c401782ebcfef8ff0f0062917c082ec762917c082ecf62117c082eff62617c082ef862617c082ef962417c082eff62017c082eff62617c082e3c250000000062617c082e3c25ff00000062617c082e3df6ffffff62617c082e3df500000062617c082e3df5ff000062617c082e3862617c082e3862617c082eb8ffff000062417c082ebfffff000062617c082e3c3062617c082ebc30ffff000062417c082ebc37ffff000062217c082ebc38ffff000062617c082ebc70f2ff0f0062617c082ebcb0f4ff0f0062617c082ebcf0f8ff0f0062617c082ebcc4f8ff0f0062417c082ebcc7f8ff0f0062217c082ebcfcf8ff0f0062017c082ebcfef8ff0f00

bits 64

vucomiss xmm0, xmm0
vucomiss xmm0, xmm1
vucomiss xmm0, xmm15
vucomiss xmm1, xmm0
vucomiss xmm1, xmm1
vucomiss xmm1, xmm15
vucomiss xmm15, xmm0
vucomiss xmm15, xmm1
vucomiss xmm15, xmm15
vucomiss xmm0, dword [0x0]
vucomiss xmm0, dword [0xFF]
vucomiss xmm0, dword [rel $ + 0x0]
vucomiss xmm0, dword [rel $ + 0xFF]
vucomiss xmm0, dword [rel $ + 0xFFFF]
vucomiss xmm0, dword [rax]
vucomiss xmm0, dword [rax + 0x0]
vucomiss xmm0, dword [rax + 0xFFFF]
vucomiss xmm0, dword [r15 + 0xFFFF]
vucomiss xmm0, dword [rax + rsi * 1  + 0x0]
vucomiss xmm0, dword [rax + rsi + 0xFFFF]
vucomiss xmm0, dword [r15 + rsi + 0xFFFF]
vucomiss xmm0, dword [rax + r15 + 0xFFFF]
vucomiss xmm0, dword [rax + rsi * 2 + 0xFFFF2]
vucomiss xmm0, dword [rax + rsi * 4 + 0xFFFF4]
vucomiss xmm0, dword [rax + rsi * 8 + 0xFFFF8]
vucomiss xmm0, dword [rsp + rax * 8 + 0xFFFF8]
vucomiss xmm0, dword [r15 + rax * 8 + 0xFFFF8]
vucomiss xmm0, dword [rsp + r15 * 8 + 0xFFFF8]
vucomiss xmm0, dword [r14 + r15 * 8 + 0xFFFF8]
vucomiss xmm1, dword [0x0]
vucomiss xmm1, dword [0xFF]
vucomiss xmm1, dword [rel $ + 0x0]
vucomiss xmm1, dword [rel $ + 0xFF]
vucomiss xmm1, dword [rel $ + 0xFFFF]
vucomiss xmm1, dword [rax]
vucomiss xmm1, dword [rax + 0x0]
vucomiss xmm1, dword [rax + 0xFFFF]
vucomiss xmm1, dword [r15 + 0xFFFF]
vucomiss xmm1, dword [rax + rsi * 1  + 0x0]
vucomiss xmm1, dword [rax + rsi + 0xFFFF]
vucomiss xmm1, dword [r15 + rsi + 0xFFFF]
vucomiss xmm1, dword [rax + r15 + 0xFFFF]
vucomiss xmm1, dword [rax + rsi * 2 + 0xFFFF2]
vucomiss xmm1, dword [rax + rsi * 4 + 0xFFFF4]
vucomiss xmm1, dword [rax + rsi * 8 + 0xFFFF8]
vucomiss xmm1, dword [rsp + rax * 8 + 0xFFFF8]
vucomiss xmm1, dword [r15 + rax * 8 + 0xFFFF8]
vucomiss xmm1, dword [rsp + r15 * 8 + 0xFFFF8]
vucomiss xmm1, dword [r14 + r15 * 8 + 0xFFFF8]
vucomiss xmm15, dword [0x0]
vucomiss xmm15, dword [0xFF]
vucomiss xmm15, dword [rel $ + 0x0]
vucomiss xmm15, dword [rel $ + 0xFF]
vucomiss xmm15, dword [rel $ + 0xFFFF]
vucomiss xmm15, dword [rax]
vucomiss xmm15, dword [rax + 0x0]
vucomiss xmm15, dword [rax + 0xFFFF]
vucomiss xmm15, dword [r15 + 0xFFFF]
vucomiss xmm15, dword [rax + rsi * 1  + 0x0]
vucomiss xmm15, dword [rax + rsi + 0xFFFF]
vucomiss xmm15, dword [r15 + rsi + 0xFFFF]
vucomiss xmm15, dword [rax + r15 + 0xFFFF]
vucomiss xmm15, dword [rax + rsi * 2 + 0xFFFF2]
vucomiss xmm15, dword [rax + rsi * 4 + 0xFFFF4]
vucomiss xmm15, dword [rax + rsi * 8 + 0xFFFF8]
vucomiss xmm15, dword [rsp + rax * 8 + 0xFFFF8]
vucomiss xmm15, dword [r15 + rax * 8 + 0xFFFF8]
vucomiss xmm15, dword [rsp + r15 * 8 + 0xFFFF8]
vucomiss xmm15, dword [r14 + r15 * 8 + 0xFFFF8]
vucomiss xmm0, xmm31
vucomiss xmm1, xmm31
vucomiss xmm15, xmm31
vucomiss xmm31, xmm0
vucomiss xmm31, xmm1
vucomiss xmm31, xmm15
vucomiss xmm31, xmm31
vucomiss xmm31, dword [0x0]
vucomiss xmm31, dword [0xFF]
vucomiss xmm31, dword [rel $ + 0x0]
vucomiss xmm31, dword [rel $ + 0xFF]
vucomiss xmm31, dword [rel $ + 0xFFFF]
vucomiss xmm31, dword [rax]
vucomiss xmm31, dword [rax + 0x0]
vucomiss xmm31, dword [rax + 0xFFFF]
vucomiss xmm31, dword [r15 + 0xFFFF]
vucomiss xmm31, dword [rax + rsi * 1  + 0x0]
vucomiss xmm31, dword [rax + rsi + 0xFFFF]
vucomiss xmm31, dword [r15 + rsi + 0xFFFF]
vucomiss xmm31, dword [rax + r15 + 0xFFFF]
vucomiss xmm31, dword [rax + rsi * 2 + 0xFFFF2]
vucomiss xmm31, dword [rax + rsi * 4 + 0xFFFF4]
vucomiss xmm31, dword [rax + rsi * 8 + 0xFFFF8]
vucomiss xmm31, dword [rsp + rax * 8 + 0xFFFF8]
vucomiss xmm31, dword [r15 + rax * 8 + 0xFFFF8]
vucomiss xmm31, dword [rsp + r15 * 8 + 0xFFFF8]
vucomiss xmm31, dword [r14 + r15 * 8 + 0xFFFF8]
