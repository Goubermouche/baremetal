; expect: 0fd4c00fd4c10fd4c70fd4c80fd4c90fd4cf0fd4f80fd4f90fd4ff0fd40425000000000fd40425ff0000000fd405f9ffffff0fd405f80000000fd405f8ff00000fd4000fd4000fd480ffff0000410fd487ffff00000fd404300fd48430ffff0000410fd48437ffff0000420fd48438ffff00000fd48470f2ff0f000fd484b0f4ff0f000fd484f0f8ff0f000fd484c4f8ff0f00410fd484c7f8ff0f00420fd484fcf8ff0f00430fd484fef8ff0f000fd40c25000000000fd40c25ff0000000fd40df9ffffff0fd40df80000000fd40df8ff00000fd4080fd4080fd488ffff0000410fd48fffff00000fd40c300fd48c30ffff0000410fd48c37ffff0000420fd48c38ffff00000fd48c70f2ff0f000fd48cb0f4ff0f000fd48cf0f8ff0f000fd48cc4f8ff0f00410fd48cc7f8ff0f00420fd48cfcf8ff0f00430fd48cfef8ff0f000fd43c25000000000fd43c25ff0000000fd43df9ffffff0fd43df80000000fd43df8ff00000fd4380fd4380fd4b8ffff0000410fd4bfffff00000fd43c300fd4bc30ffff0000410fd4bc37ffff0000420fd4bc38ffff00000fd4bc70f2ff0f000fd4bcb0f4ff0f000fd4bcf0f8ff0f000fd4bcc4f8ff0f00410fd4bcc7f8ff0f00420fd4bcfcf8ff0f00430fd4bcfef8ff0f00660fd4c0660fd4c166410fd4c7660fd4c8660fd4c966410fd4cf66440fd4f866440fd4f966450fd4ff660fd4042500000000660fd40425ff000000660fd405f8ffffff660fd405f7000000660fd405f7ff0000660fd400660fd400660fd480ffff000066410fd487ffff0000660fd40430660fd48430ffff000066410fd48437ffff000066420fd48438ffff0000660fd48470f2ff0f00660fd484b0f4ff0f00660fd484f0f8ff0f00660fd484c4f8ff0f0066410fd484c7f8ff0f0066420fd484fcf8ff0f0066430fd484fef8ff0f00660fd40c2500000000660fd40c25ff000000660fd40df8ffffff660fd40df7000000660fd40df7ff0000660fd408660fd408660fd488ffff000066410fd48fffff0000660fd40c30660fd48c30ffff000066410fd48c37ffff000066420fd48c38ffff0000660fd48c70f2ff0f00660fd48cb0f4ff0f00660fd48cf0f8ff0f00660fd48cc4f8ff0f0066410fd48cc7f8ff0f0066420fd48cfcf8ff0f0066430fd48cfef8ff0f0066440fd43c250000000066440fd43c25ff00000066440fd43df7ffffff66440fd43df600000066440fd43df6ff000066440fd43866440fd43866440fd4b8ffff000066450fd4bfffff000066440fd43c3066440fd4bc30ffff000066450fd4bc37ffff000066460fd4bc38ffff000066440fd4bc70f2ff0f0066440fd4bcb0f4ff0f0066440fd4bcf0f8ff0f0066440fd4bcc4f8ff0f0066450fd4bcc7f8ff0f0066460fd4bcfcf8ff0f0066470fd4bcfef8ff0f00

bits 64

paddq mm0, mm0
paddq mm0, mm1
paddq mm0, mm7
paddq mm1, mm0
paddq mm1, mm1
paddq mm1, mm7
paddq mm7, mm0
paddq mm7, mm1
paddq mm7, mm7
paddq mm0, qword [0x0]
paddq mm0, qword [0xFF]
paddq mm0, qword [rel $ + 0x0]
paddq mm0, qword [rel $ + 0xFF]
paddq mm0, qword [rel $ + 0xFFFF]
paddq mm0, qword [rax]
paddq mm0, qword [rax + 0x0]
paddq mm0, qword [rax + 0xFFFF]
paddq mm0, qword [r15 + 0xFFFF]
paddq mm0, qword [rax + rsi * 1  + 0x0]
paddq mm0, qword [rax + rsi + 0xFFFF]
paddq mm0, qword [r15 + rsi + 0xFFFF]
paddq mm0, qword [rax + r15 + 0xFFFF]
paddq mm0, qword [rax + rsi * 2 + 0xFFFF2]
paddq mm0, qword [rax + rsi * 4 + 0xFFFF4]
paddq mm0, qword [rax + rsi * 8 + 0xFFFF8]
paddq mm0, qword [rsp + rax * 8 + 0xFFFF8]
paddq mm0, qword [r15 + rax * 8 + 0xFFFF8]
paddq mm0, qword [rsp + r15 * 8 + 0xFFFF8]
paddq mm0, qword [r14 + r15 * 8 + 0xFFFF8]
paddq mm1, qword [0x0]
paddq mm1, qword [0xFF]
paddq mm1, qword [rel $ + 0x0]
paddq mm1, qword [rel $ + 0xFF]
paddq mm1, qword [rel $ + 0xFFFF]
paddq mm1, qword [rax]
paddq mm1, qword [rax + 0x0]
paddq mm1, qword [rax + 0xFFFF]
paddq mm1, qword [r15 + 0xFFFF]
paddq mm1, qword [rax + rsi * 1  + 0x0]
paddq mm1, qword [rax + rsi + 0xFFFF]
paddq mm1, qword [r15 + rsi + 0xFFFF]
paddq mm1, qword [rax + r15 + 0xFFFF]
paddq mm1, qword [rax + rsi * 2 + 0xFFFF2]
paddq mm1, qword [rax + rsi * 4 + 0xFFFF4]
paddq mm1, qword [rax + rsi * 8 + 0xFFFF8]
paddq mm1, qword [rsp + rax * 8 + 0xFFFF8]
paddq mm1, qword [r15 + rax * 8 + 0xFFFF8]
paddq mm1, qword [rsp + r15 * 8 + 0xFFFF8]
paddq mm1, qword [r14 + r15 * 8 + 0xFFFF8]
paddq mm7, qword [0x0]
paddq mm7, qword [0xFF]
paddq mm7, qword [rel $ + 0x0]
paddq mm7, qword [rel $ + 0xFF]
paddq mm7, qword [rel $ + 0xFFFF]
paddq mm7, qword [rax]
paddq mm7, qword [rax + 0x0]
paddq mm7, qword [rax + 0xFFFF]
paddq mm7, qword [r15 + 0xFFFF]
paddq mm7, qword [rax + rsi * 1  + 0x0]
paddq mm7, qword [rax + rsi + 0xFFFF]
paddq mm7, qword [r15 + rsi + 0xFFFF]
paddq mm7, qword [rax + r15 + 0xFFFF]
paddq mm7, qword [rax + rsi * 2 + 0xFFFF2]
paddq mm7, qword [rax + rsi * 4 + 0xFFFF4]
paddq mm7, qword [rax + rsi * 8 + 0xFFFF8]
paddq mm7, qword [rsp + rax * 8 + 0xFFFF8]
paddq mm7, qword [r15 + rax * 8 + 0xFFFF8]
paddq mm7, qword [rsp + r15 * 8 + 0xFFFF8]
paddq mm7, qword [r14 + r15 * 8 + 0xFFFF8]
paddq xmm0, xmm0
paddq xmm0, xmm1
paddq xmm0, xmm15
paddq xmm1, xmm0
paddq xmm1, xmm1
paddq xmm1, xmm15
paddq xmm15, xmm0
paddq xmm15, xmm1
paddq xmm15, xmm15
paddq xmm0, [0x0]
paddq xmm0, [0xFF]
paddq xmm0, [rel $ + 0x0]
paddq xmm0, [rel $ + 0xFF]
paddq xmm0, [rel $ + 0xFFFF]
paddq xmm0, [rax]
paddq xmm0, [rax + 0x0]
paddq xmm0, [rax + 0xFFFF]
paddq xmm0, [r15 + 0xFFFF]
paddq xmm0, [rax + rsi * 1  + 0x0]
paddq xmm0, [rax + rsi + 0xFFFF]
paddq xmm0, [r15 + rsi + 0xFFFF]
paddq xmm0, [rax + r15 + 0xFFFF]
paddq xmm0, [rax + rsi * 2 + 0xFFFF2]
paddq xmm0, [rax + rsi * 4 + 0xFFFF4]
paddq xmm0, [rax + rsi * 8 + 0xFFFF8]
paddq xmm0, [rsp + rax * 8 + 0xFFFF8]
paddq xmm0, [r15 + rax * 8 + 0xFFFF8]
paddq xmm0, [rsp + r15 * 8 + 0xFFFF8]
paddq xmm0, [r14 + r15 * 8 + 0xFFFF8]
paddq xmm1, [0x0]
paddq xmm1, [0xFF]
paddq xmm1, [rel $ + 0x0]
paddq xmm1, [rel $ + 0xFF]
paddq xmm1, [rel $ + 0xFFFF]
paddq xmm1, [rax]
paddq xmm1, [rax + 0x0]
paddq xmm1, [rax + 0xFFFF]
paddq xmm1, [r15 + 0xFFFF]
paddq xmm1, [rax + rsi * 1  + 0x0]
paddq xmm1, [rax + rsi + 0xFFFF]
paddq xmm1, [r15 + rsi + 0xFFFF]
paddq xmm1, [rax + r15 + 0xFFFF]
paddq xmm1, [rax + rsi * 2 + 0xFFFF2]
paddq xmm1, [rax + rsi * 4 + 0xFFFF4]
paddq xmm1, [rax + rsi * 8 + 0xFFFF8]
paddq xmm1, [rsp + rax * 8 + 0xFFFF8]
paddq xmm1, [r15 + rax * 8 + 0xFFFF8]
paddq xmm1, [rsp + r15 * 8 + 0xFFFF8]
paddq xmm1, [r14 + r15 * 8 + 0xFFFF8]
paddq xmm15, [0x0]
paddq xmm15, [0xFF]
paddq xmm15, [rel $ + 0x0]
paddq xmm15, [rel $ + 0xFF]
paddq xmm15, [rel $ + 0xFFFF]
paddq xmm15, [rax]
paddq xmm15, [rax + 0x0]
paddq xmm15, [rax + 0xFFFF]
paddq xmm15, [r15 + 0xFFFF]
paddq xmm15, [rax + rsi * 1  + 0x0]
paddq xmm15, [rax + rsi + 0xFFFF]
paddq xmm15, [r15 + rsi + 0xFFFF]
paddq xmm15, [rax + r15 + 0xFFFF]
paddq xmm15, [rax + rsi * 2 + 0xFFFF2]
paddq xmm15, [rax + rsi * 4 + 0xFFFF4]
paddq xmm15, [rax + rsi * 8 + 0xFFFF8]
paddq xmm15, [rsp + rax * 8 + 0xFFFF8]
paddq xmm15, [r15 + rax * 8 + 0xFFFF8]
paddq xmm15, [rsp + r15 * 8 + 0xFFFF8]
paddq xmm15, [r14 + r15 * 8 + 0xFFFF8]
