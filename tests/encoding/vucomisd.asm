; expect: c5f92ec0c5f92ec1c4c1792ec7c5f92ec8c5f92ec9c4c1792ecfc5792ef8c5792ef9c441792effc5f92e042500000000c5f92e0425ff000000c5f92e05f8ffffffc5f92e05f7000000c5f92e05f7ff0000c5f92e00c5f92e00c5f92e80ffff0000c4c1792e87ffff0000c5f92e0430c5f92e8430ffff0000c4c1792e8437ffff0000c4a1792e8438ffff0000c5f92e8470f2ff0f00c5f92e84b0f4ff0f00c5f92e84f0f8ff0f00c5f92e84c4f8ff0f00c4c1792e84c7f8ff0f00c4a1792e84fcf8ff0f00c481792e84fef8ff0f00c5f92e0c2500000000c5f92e0c25ff000000c5f92e0df8ffffffc5f92e0df7000000c5f92e0df7ff0000c5f92e08c5f92e08c5f92e88ffff0000c4c1792e8fffff0000c5f92e0c30c5f92e8c30ffff0000c4c1792e8c37ffff0000c4a1792e8c38ffff0000c5f92e8c70f2ff0f00c5f92e8cb0f4ff0f00c5f92e8cf0f8ff0f00c5f92e8cc4f8ff0f00c4c1792e8cc7f8ff0f00c4a1792e8cfcf8ff0f00c481792e8cfef8ff0f00c5792e3c2500000000c5792e3c25ff000000c5792e3df8ffffffc5792e3df7000000c5792e3df7ff0000c5792e38c5792e38c5792eb8ffff0000c441792ebfffff0000c5792e3c30c5792ebc30ffff0000c441792ebc37ffff0000c421792ebc38ffff0000c5792ebc70f2ff0f00c5792ebcb0f4ff0f00c5792ebcf0f8ff0f00c5792ebcc4f8ff0f00c441792ebcc7f8ff0f00c421792ebcfcf8ff0f00c401792ebcfef8ff0f006291fd082ec76291fd082ecf6211fd082eff6261fd082ef86261fd082ef96241fd082eff6201fd082eff6261fd082e3c25000000006261fd082e3c25ff0000006261fd082e3df6ffffff6261fd082e3df50000006261fd082e3df5ff00006261fd082e386261fd082e386261fd082eb8ffff00006241fd082ebfffff00006261fd082e3c306261fd082ebc30ffff00006241fd082ebc37ffff00006221fd082ebc38ffff00006261fd082ebc70f2ff0f006261fd082ebcb0f4ff0f006261fd082ebcf0f8ff0f006261fd082ebcc4f8ff0f006241fd082ebcc7f8ff0f006221fd082ebcfcf8ff0f006201fd082ebcfef8ff0f00

bits 64

vucomisd xmm0, xmm0
vucomisd xmm0, xmm1
vucomisd xmm0, xmm15
vucomisd xmm1, xmm0
vucomisd xmm1, xmm1
vucomisd xmm1, xmm15
vucomisd xmm15, xmm0
vucomisd xmm15, xmm1
vucomisd xmm15, xmm15
vucomisd xmm0, qword [0x0]
vucomisd xmm0, qword [0xFF]
vucomisd xmm0, qword [rel $ + 0x0]
vucomisd xmm0, qword [rel $ + 0xFF]
vucomisd xmm0, qword [rel $ + 0xFFFF]
vucomisd xmm0, qword [rax]
vucomisd xmm0, qword [rax + 0x0]
vucomisd xmm0, qword [rax + 0xFFFF]
vucomisd xmm0, qword [r15 + 0xFFFF]
vucomisd xmm0, qword [rax + rsi * 1  + 0x0]
vucomisd xmm0, qword [rax + rsi + 0xFFFF]
vucomisd xmm0, qword [r15 + rsi + 0xFFFF]
vucomisd xmm0, qword [rax + r15 + 0xFFFF]
vucomisd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
vucomisd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
vucomisd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
vucomisd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
vucomisd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
vucomisd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
vucomisd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
vucomisd xmm1, qword [0x0]
vucomisd xmm1, qword [0xFF]
vucomisd xmm1, qword [rel $ + 0x0]
vucomisd xmm1, qword [rel $ + 0xFF]
vucomisd xmm1, qword [rel $ + 0xFFFF]
vucomisd xmm1, qword [rax]
vucomisd xmm1, qword [rax + 0x0]
vucomisd xmm1, qword [rax + 0xFFFF]
vucomisd xmm1, qword [r15 + 0xFFFF]
vucomisd xmm1, qword [rax + rsi * 1  + 0x0]
vucomisd xmm1, qword [rax + rsi + 0xFFFF]
vucomisd xmm1, qword [r15 + rsi + 0xFFFF]
vucomisd xmm1, qword [rax + r15 + 0xFFFF]
vucomisd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
vucomisd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
vucomisd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
vucomisd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
vucomisd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
vucomisd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
vucomisd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
vucomisd xmm15, qword [0x0]
vucomisd xmm15, qword [0xFF]
vucomisd xmm15, qword [rel $ + 0x0]
vucomisd xmm15, qword [rel $ + 0xFF]
vucomisd xmm15, qword [rel $ + 0xFFFF]
vucomisd xmm15, qword [rax]
vucomisd xmm15, qword [rax + 0x0]
vucomisd xmm15, qword [rax + 0xFFFF]
vucomisd xmm15, qword [r15 + 0xFFFF]
vucomisd xmm15, qword [rax + rsi * 1  + 0x0]
vucomisd xmm15, qword [rax + rsi + 0xFFFF]
vucomisd xmm15, qword [r15 + rsi + 0xFFFF]
vucomisd xmm15, qword [rax + r15 + 0xFFFF]
vucomisd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
vucomisd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
vucomisd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
vucomisd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
vucomisd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
vucomisd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
vucomisd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
vucomisd xmm0, xmm31
vucomisd xmm1, xmm31
vucomisd xmm15, xmm31
vucomisd xmm31, xmm0
vucomisd xmm31, xmm1
vucomisd xmm31, xmm15
vucomisd xmm31, xmm31
vucomisd xmm31, qword [0x0]
vucomisd xmm31, qword [0xFF]
vucomisd xmm31, qword [rel $ + 0x0]
vucomisd xmm31, qword [rel $ + 0xFF]
vucomisd xmm31, qword [rel $ + 0xFFFF]
vucomisd xmm31, qword [rax]
vucomisd xmm31, qword [rax + 0x0]
vucomisd xmm31, qword [rax + 0xFFFF]
vucomisd xmm31, qword [r15 + 0xFFFF]
vucomisd xmm31, qword [rax + rsi * 1  + 0x0]
vucomisd xmm31, qword [rax + rsi + 0xFFFF]
vucomisd xmm31, qword [r15 + rsi + 0xFFFF]
vucomisd xmm31, qword [rax + r15 + 0xFFFF]
vucomisd xmm31, qword [rax + rsi * 2 + 0xFFFF2]
vucomisd xmm31, qword [rax + rsi * 4 + 0xFFFF4]
vucomisd xmm31, qword [rax + rsi * 8 + 0xFFFF8]
vucomisd xmm31, qword [rsp + rax * 8 + 0xFFFF8]
vucomisd xmm31, qword [r15 + rax * 8 + 0xFFFF8]
vucomisd xmm31, qword [rsp + r15 * 8 + 0xFFFF8]
vucomisd xmm31, qword [r14 + r15 * 8 + 0xFFFF8]
