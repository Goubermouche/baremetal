; expect: c5f82fc0c5f82fc1c4c1782fc7c5f82fc8c5f82fc9c4c1782fcfc5782ff8c5782ff9c441782fffc5f82f042500000000c5f82f0425ff000000c5f82f05f8ffffffc5f82f05f7000000c5f82f05f7ff0000c5f82f00c5f82f00c5f82f80ffff0000c4c1782f87ffff0000c5f82f0430c5f82f8430ffff0000c4c1782f8437ffff0000c4a1782f8438ffff0000c5f82f8470f2ff0f00c5f82f84b0f4ff0f00c5f82f84f0f8ff0f00c5f82f84c4f8ff0f00c4c1782f84c7f8ff0f00c4a1782f84fcf8ff0f00c481782f84fef8ff0f00c5f82f0c2500000000c5f82f0c25ff000000c5f82f0df8ffffffc5f82f0df7000000c5f82f0df7ff0000c5f82f08c5f82f08c5f82f88ffff0000c4c1782f8fffff0000c5f82f0c30c5f82f8c30ffff0000c4c1782f8c37ffff0000c4a1782f8c38ffff0000c5f82f8c70f2ff0f00c5f82f8cb0f4ff0f00c5f82f8cf0f8ff0f00c5f82f8cc4f8ff0f00c4c1782f8cc7f8ff0f00c4a1782f8cfcf8ff0f00c481782f8cfef8ff0f00c5782f3c2500000000c5782f3c25ff000000c5782f3df8ffffffc5782f3df7000000c5782f3df7ff0000c5782f38c5782f38c5782fb8ffff0000c441782fbfffff0000c5782f3c30c5782fbc30ffff0000c441782fbc37ffff0000c421782fbc38ffff0000c5782fbc70f2ff0f00c5782fbcb0f4ff0f00c5782fbcf0f8ff0f00c5782fbcc4f8ff0f00c441782fbcc7f8ff0f00c421782fbcfcf8ff0f00c401782fbcfef8ff0f0062917c082fc762917c082fcf62117c082fff62617c082ff862617c082ff962417c082fff62017c082fff62617c082f3c250000000062617c082f3c25ff00000062617c082f3df6ffffff62617c082f3df500000062617c082f3df5ff000062617c082f3862617c082f3862617c082fb8ffff000062417c082fbfffff000062617c082f3c3062617c082fbc30ffff000062417c082fbc37ffff000062217c082fbc38ffff000062617c082fbc70f2ff0f0062617c082fbcb0f4ff0f0062617c082fbcf0f8ff0f0062617c082fbcc4f8ff0f0062417c082fbcc7f8ff0f0062217c082fbcfcf8ff0f0062017c082fbcfef8ff0f00

bits 64

vcomiss xmm0, xmm0
vcomiss xmm0, xmm1
vcomiss xmm0, xmm15
vcomiss xmm1, xmm0
vcomiss xmm1, xmm1
vcomiss xmm1, xmm15
vcomiss xmm15, xmm0
vcomiss xmm15, xmm1
vcomiss xmm15, xmm15
vcomiss xmm0, dword [0x0]
vcomiss xmm0, dword [0xFF]
vcomiss xmm0, dword [rel $ + 0x0]
vcomiss xmm0, dword [rel $ + 0xFF]
vcomiss xmm0, dword [rel $ + 0xFFFF]
vcomiss xmm0, dword [rax]
vcomiss xmm0, dword [rax + 0x0]
vcomiss xmm0, dword [rax + 0xFFFF]
vcomiss xmm0, dword [r15 + 0xFFFF]
vcomiss xmm0, dword [rax + rsi * 1  + 0x0]
vcomiss xmm0, dword [rax + rsi + 0xFFFF]
vcomiss xmm0, dword [r15 + rsi + 0xFFFF]
vcomiss xmm0, dword [rax + r15 + 0xFFFF]
vcomiss xmm0, dword [rax + rsi * 2 + 0xFFFF2]
vcomiss xmm0, dword [rax + rsi * 4 + 0xFFFF4]
vcomiss xmm0, dword [rax + rsi * 8 + 0xFFFF8]
vcomiss xmm0, dword [rsp + rax * 8 + 0xFFFF8]
vcomiss xmm0, dword [r15 + rax * 8 + 0xFFFF8]
vcomiss xmm0, dword [rsp + r15 * 8 + 0xFFFF8]
vcomiss xmm0, dword [r14 + r15 * 8 + 0xFFFF8]
vcomiss xmm1, dword [0x0]
vcomiss xmm1, dword [0xFF]
vcomiss xmm1, dword [rel $ + 0x0]
vcomiss xmm1, dword [rel $ + 0xFF]
vcomiss xmm1, dword [rel $ + 0xFFFF]
vcomiss xmm1, dword [rax]
vcomiss xmm1, dword [rax + 0x0]
vcomiss xmm1, dword [rax + 0xFFFF]
vcomiss xmm1, dword [r15 + 0xFFFF]
vcomiss xmm1, dword [rax + rsi * 1  + 0x0]
vcomiss xmm1, dword [rax + rsi + 0xFFFF]
vcomiss xmm1, dword [r15 + rsi + 0xFFFF]
vcomiss xmm1, dword [rax + r15 + 0xFFFF]
vcomiss xmm1, dword [rax + rsi * 2 + 0xFFFF2]
vcomiss xmm1, dword [rax + rsi * 4 + 0xFFFF4]
vcomiss xmm1, dword [rax + rsi * 8 + 0xFFFF8]
vcomiss xmm1, dword [rsp + rax * 8 + 0xFFFF8]
vcomiss xmm1, dword [r15 + rax * 8 + 0xFFFF8]
vcomiss xmm1, dword [rsp + r15 * 8 + 0xFFFF8]
vcomiss xmm1, dword [r14 + r15 * 8 + 0xFFFF8]
vcomiss xmm15, dword [0x0]
vcomiss xmm15, dword [0xFF]
vcomiss xmm15, dword [rel $ + 0x0]
vcomiss xmm15, dword [rel $ + 0xFF]
vcomiss xmm15, dword [rel $ + 0xFFFF]
vcomiss xmm15, dword [rax]
vcomiss xmm15, dword [rax + 0x0]
vcomiss xmm15, dword [rax + 0xFFFF]
vcomiss xmm15, dword [r15 + 0xFFFF]
vcomiss xmm15, dword [rax + rsi * 1  + 0x0]
vcomiss xmm15, dword [rax + rsi + 0xFFFF]
vcomiss xmm15, dword [r15 + rsi + 0xFFFF]
vcomiss xmm15, dword [rax + r15 + 0xFFFF]
vcomiss xmm15, dword [rax + rsi * 2 + 0xFFFF2]
vcomiss xmm15, dword [rax + rsi * 4 + 0xFFFF4]
vcomiss xmm15, dword [rax + rsi * 8 + 0xFFFF8]
vcomiss xmm15, dword [rsp + rax * 8 + 0xFFFF8]
vcomiss xmm15, dword [r15 + rax * 8 + 0xFFFF8]
vcomiss xmm15, dword [rsp + r15 * 8 + 0xFFFF8]
vcomiss xmm15, dword [r14 + r15 * 8 + 0xFFFF8]
vcomiss xmm0, xmm31
vcomiss xmm1, xmm31
vcomiss xmm15, xmm31
vcomiss xmm31, xmm0
vcomiss xmm31, xmm1
vcomiss xmm31, xmm15
vcomiss xmm31, xmm31
vcomiss xmm31, dword [0x0]
vcomiss xmm31, dword [0xFF]
vcomiss xmm31, dword [rel $ + 0x0]
vcomiss xmm31, dword [rel $ + 0xFF]
vcomiss xmm31, dword [rel $ + 0xFFFF]
vcomiss xmm31, dword [rax]
vcomiss xmm31, dword [rax + 0x0]
vcomiss xmm31, dword [rax + 0xFFFF]
vcomiss xmm31, dword [r15 + 0xFFFF]
vcomiss xmm31, dword [rax + rsi * 1  + 0x0]
vcomiss xmm31, dword [rax + rsi + 0xFFFF]
vcomiss xmm31, dword [r15 + rsi + 0xFFFF]
vcomiss xmm31, dword [rax + r15 + 0xFFFF]
vcomiss xmm31, dword [rax + rsi * 2 + 0xFFFF2]
vcomiss xmm31, dword [rax + rsi * 4 + 0xFFFF4]
vcomiss xmm31, dword [rax + rsi * 8 + 0xFFFF8]
vcomiss xmm31, dword [rsp + rax * 8 + 0xFFFF8]
vcomiss xmm31, dword [r15 + rax * 8 + 0xFFFF8]
vcomiss xmm31, dword [rsp + r15 * 8 + 0xFFFF8]
vcomiss xmm31, dword [r14 + r15 * 8 + 0xFFFF8]
