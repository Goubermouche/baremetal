; expect: c5f92fc0c5f92fc1c4c1792fc7c5f92fc8c5f92fc9c4c1792fcfc5792ff8c5792ff9c441792fffc5f92f042500000000c5f92f0425ff000000c5f92f05f8ffffffc5f92f05f7000000c5f92f05f7ff0000c5f92f00c5f92f00c5f92f80ffff0000c4c1792f87ffff0000c5f92f0430c5f92f8430ffff0000c4c1792f8437ffff0000c4a1792f8438ffff0000c5f92f8470f2ff0f00c5f92f84b0f4ff0f00c5f92f84f0f8ff0f00c5f92f84c4f8ff0f00c4c1792f84c7f8ff0f00c4a1792f84fcf8ff0f00c481792f84fef8ff0f00c5f92f0c2500000000c5f92f0c25ff000000c5f92f0df8ffffffc5f92f0df7000000c5f92f0df7ff0000c5f92f08c5f92f08c5f92f88ffff0000c4c1792f8fffff0000c5f92f0c30c5f92f8c30ffff0000c4c1792f8c37ffff0000c4a1792f8c38ffff0000c5f92f8c70f2ff0f00c5f92f8cb0f4ff0f00c5f92f8cf0f8ff0f00c5f92f8cc4f8ff0f00c4c1792f8cc7f8ff0f00c4a1792f8cfcf8ff0f00c481792f8cfef8ff0f00c5792f3c2500000000c5792f3c25ff000000c5792f3df8ffffffc5792f3df7000000c5792f3df7ff0000c5792f38c5792f38c5792fb8ffff0000c441792fbfffff0000c5792f3c30c5792fbc30ffff0000c441792fbc37ffff0000c421792fbc38ffff0000c5792fbc70f2ff0f00c5792fbcb0f4ff0f00c5792fbcf0f8ff0f00c5792fbcc4f8ff0f00c441792fbcc7f8ff0f00c421792fbcfcf8ff0f00c401792fbcfef8ff0f006291fd082fc76291fd082fcf6211fd082fff6261fd082ff86261fd082ff96241fd082fff6201fd082fff6261fd082f3c25000000006261fd082f3c25ff0000006261fd082f3df6ffffff6261fd082f3df50000006261fd082f3df5ff00006261fd082f386261fd082f386261fd082fb8ffff00006241fd082fbfffff00006261fd082f3c306261fd082fbc30ffff00006241fd082fbc37ffff00006221fd082fbc38ffff00006261fd082fbc70f2ff0f006261fd082fbcb0f4ff0f006261fd082fbcf0f8ff0f006261fd082fbcc4f8ff0f006241fd082fbcc7f8ff0f006221fd082fbcfcf8ff0f006201fd082fbcfef8ff0f00

bits 64

vcomisd xmm0, xmm0
vcomisd xmm0, xmm1
vcomisd xmm0, xmm15
vcomisd xmm1, xmm0
vcomisd xmm1, xmm1
vcomisd xmm1, xmm15
vcomisd xmm15, xmm0
vcomisd xmm15, xmm1
vcomisd xmm15, xmm15
vcomisd xmm0, qword [0x0]
vcomisd xmm0, qword [0xFF]
vcomisd xmm0, qword [rel $ + 0x0]
vcomisd xmm0, qword [rel $ + 0xFF]
vcomisd xmm0, qword [rel $ + 0xFFFF]
vcomisd xmm0, qword [rax]
vcomisd xmm0, qword [rax + 0x0]
vcomisd xmm0, qword [rax + 0xFFFF]
vcomisd xmm0, qword [r15 + 0xFFFF]
vcomisd xmm0, qword [rax + rsi * 1  + 0x0]
vcomisd xmm0, qword [rax + rsi + 0xFFFF]
vcomisd xmm0, qword [r15 + rsi + 0xFFFF]
vcomisd xmm0, qword [rax + r15 + 0xFFFF]
vcomisd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
vcomisd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
vcomisd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
vcomisd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
vcomisd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
vcomisd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
vcomisd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
vcomisd xmm1, qword [0x0]
vcomisd xmm1, qword [0xFF]
vcomisd xmm1, qword [rel $ + 0x0]
vcomisd xmm1, qword [rel $ + 0xFF]
vcomisd xmm1, qword [rel $ + 0xFFFF]
vcomisd xmm1, qword [rax]
vcomisd xmm1, qword [rax + 0x0]
vcomisd xmm1, qword [rax + 0xFFFF]
vcomisd xmm1, qword [r15 + 0xFFFF]
vcomisd xmm1, qword [rax + rsi * 1  + 0x0]
vcomisd xmm1, qword [rax + rsi + 0xFFFF]
vcomisd xmm1, qword [r15 + rsi + 0xFFFF]
vcomisd xmm1, qword [rax + r15 + 0xFFFF]
vcomisd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
vcomisd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
vcomisd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
vcomisd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
vcomisd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
vcomisd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
vcomisd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
vcomisd xmm15, qword [0x0]
vcomisd xmm15, qword [0xFF]
vcomisd xmm15, qword [rel $ + 0x0]
vcomisd xmm15, qword [rel $ + 0xFF]
vcomisd xmm15, qword [rel $ + 0xFFFF]
vcomisd xmm15, qword [rax]
vcomisd xmm15, qword [rax + 0x0]
vcomisd xmm15, qword [rax + 0xFFFF]
vcomisd xmm15, qword [r15 + 0xFFFF]
vcomisd xmm15, qword [rax + rsi * 1  + 0x0]
vcomisd xmm15, qword [rax + rsi + 0xFFFF]
vcomisd xmm15, qword [r15 + rsi + 0xFFFF]
vcomisd xmm15, qword [rax + r15 + 0xFFFF]
vcomisd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
vcomisd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
vcomisd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
vcomisd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
vcomisd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
vcomisd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
vcomisd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
vcomisd xmm0, xmm31
vcomisd xmm1, xmm31
vcomisd xmm15, xmm31
vcomisd xmm31, xmm0
vcomisd xmm31, xmm1
vcomisd xmm31, xmm15
vcomisd xmm31, xmm31
vcomisd xmm31, qword [0x0]
vcomisd xmm31, qword [0xFF]
vcomisd xmm31, qword [rel $ + 0x0]
vcomisd xmm31, qword [rel $ + 0xFF]
vcomisd xmm31, qword [rel $ + 0xFFFF]
vcomisd xmm31, qword [rax]
vcomisd xmm31, qword [rax + 0x0]
vcomisd xmm31, qword [rax + 0xFFFF]
vcomisd xmm31, qword [r15 + 0xFFFF]
vcomisd xmm31, qword [rax + rsi * 1  + 0x0]
vcomisd xmm31, qword [rax + rsi + 0xFFFF]
vcomisd xmm31, qword [r15 + rsi + 0xFFFF]
vcomisd xmm31, qword [rax + r15 + 0xFFFF]
vcomisd xmm31, qword [rax + rsi * 2 + 0xFFFF2]
vcomisd xmm31, qword [rax + rsi * 4 + 0xFFFF4]
vcomisd xmm31, qword [rax + rsi * 8 + 0xFFFF8]
vcomisd xmm31, qword [rsp + rax * 8 + 0xFFFF8]
vcomisd xmm31, qword [r15 + rax * 8 + 0xFFFF8]
vcomisd xmm31, qword [rsp + r15 * 8 + 0xFFFF8]
vcomisd xmm31, qword [r14 + r15 * 8 + 0xFFFF8]
