; expect: 0ff4c00ff4c10ff4c70ff4c80ff4c90ff4cf0ff4f80ff4f90ff4ff660ff4c0660ff4c166410ff4c7660ff4c8660ff4c966410ff4cf66440ff4f866440ff4f966450ff4ff660ff4042500000000660ff40425ff000000660ff405f8ffffff660ff405f7000000660ff405f7ff0000660ff400660ff400660ff480ffff000066410ff487ffff0000660ff40430660ff48430ffff000066410ff48437ffff000066420ff48438ffff0000660ff48470f2ff0f00660ff484b0f4ff0f00660ff484f0f8ff0f00660ff484c4f8ff0f0066410ff484c7f8ff0f0066420ff484fcf8ff0f0066430ff484fef8ff0f00660ff40c2500000000660ff40c25ff000000660ff40df8ffffff660ff40df7000000660ff40df7ff0000660ff408660ff408660ff488ffff000066410ff48fffff0000660ff40c30660ff48c30ffff000066410ff48c37ffff000066420ff48c38ffff0000660ff48c70f2ff0f00660ff48cb0f4ff0f00660ff48cf0f8ff0f00660ff48cc4f8ff0f0066410ff48cc7f8ff0f0066420ff48cfcf8ff0f0066430ff48cfef8ff0f0066440ff43c250000000066440ff43c25ff00000066440ff43df7ffffff66440ff43df600000066440ff43df6ff000066440ff43866440ff43866440ff4b8ffff000066450ff4bfffff000066440ff43c3066440ff4bc30ffff000066450ff4bc37ffff000066460ff4bc38ffff000066440ff4bc70f2ff0f0066440ff4bcb0f4ff0f0066440ff4bcf0f8ff0f0066440ff4bcc4f8ff0f0066450ff4bcc7f8ff0f0066460ff4bcfcf8ff0f0066470ff4bcfef8ff0f00

bits 64

pmuludq mm0, mm0
pmuludq mm0, mm1
pmuludq mm0, mm7
pmuludq mm1, mm0
pmuludq mm1, mm1
pmuludq mm1, mm7
pmuludq mm7, mm0
pmuludq mm7, mm1
pmuludq mm7, mm7
pmuludq xmm0, xmm0
pmuludq xmm0, xmm1
pmuludq xmm0, xmm15
pmuludq xmm1, xmm0
pmuludq xmm1, xmm1
pmuludq xmm1, xmm15
pmuludq xmm15, xmm0
pmuludq xmm15, xmm1
pmuludq xmm15, xmm15
pmuludq xmm0, [0x0]
pmuludq xmm0, [0xFF]
pmuludq xmm0, [rel $ + 0x0]
pmuludq xmm0, [rel $ + 0xFF]
pmuludq xmm0, [rel $ + 0xFFFF]
pmuludq xmm0, [rax]
pmuludq xmm0, [rax + 0x0]
pmuludq xmm0, [rax + 0xFFFF]
pmuludq xmm0, [r15 + 0xFFFF]
pmuludq xmm0, [rax + rsi * 1  + 0x0]
pmuludq xmm0, [rax + rsi + 0xFFFF]
pmuludq xmm0, [r15 + rsi + 0xFFFF]
pmuludq xmm0, [rax + r15 + 0xFFFF]
pmuludq xmm0, [rax + rsi * 2 + 0xFFFF2]
pmuludq xmm0, [rax + rsi * 4 + 0xFFFF4]
pmuludq xmm0, [rax + rsi * 8 + 0xFFFF8]
pmuludq xmm0, [rsp + rax * 8 + 0xFFFF8]
pmuludq xmm0, [r15 + rax * 8 + 0xFFFF8]
pmuludq xmm0, [rsp + r15 * 8 + 0xFFFF8]
pmuludq xmm0, [r14 + r15 * 8 + 0xFFFF8]
pmuludq xmm1, [0x0]
pmuludq xmm1, [0xFF]
pmuludq xmm1, [rel $ + 0x0]
pmuludq xmm1, [rel $ + 0xFF]
pmuludq xmm1, [rel $ + 0xFFFF]
pmuludq xmm1, [rax]
pmuludq xmm1, [rax + 0x0]
pmuludq xmm1, [rax + 0xFFFF]
pmuludq xmm1, [r15 + 0xFFFF]
pmuludq xmm1, [rax + rsi * 1  + 0x0]
pmuludq xmm1, [rax + rsi + 0xFFFF]
pmuludq xmm1, [r15 + rsi + 0xFFFF]
pmuludq xmm1, [rax + r15 + 0xFFFF]
pmuludq xmm1, [rax + rsi * 2 + 0xFFFF2]
pmuludq xmm1, [rax + rsi * 4 + 0xFFFF4]
pmuludq xmm1, [rax + rsi * 8 + 0xFFFF8]
pmuludq xmm1, [rsp + rax * 8 + 0xFFFF8]
pmuludq xmm1, [r15 + rax * 8 + 0xFFFF8]
pmuludq xmm1, [rsp + r15 * 8 + 0xFFFF8]
pmuludq xmm1, [r14 + r15 * 8 + 0xFFFF8]
pmuludq xmm15, [0x0]
pmuludq xmm15, [0xFF]
pmuludq xmm15, [rel $ + 0x0]
pmuludq xmm15, [rel $ + 0xFF]
pmuludq xmm15, [rel $ + 0xFFFF]
pmuludq xmm15, [rax]
pmuludq xmm15, [rax + 0x0]
pmuludq xmm15, [rax + 0xFFFF]
pmuludq xmm15, [r15 + 0xFFFF]
pmuludq xmm15, [rax + rsi * 1  + 0x0]
pmuludq xmm15, [rax + rsi + 0xFFFF]
pmuludq xmm15, [r15 + rsi + 0xFFFF]
pmuludq xmm15, [rax + r15 + 0xFFFF]
pmuludq xmm15, [rax + rsi * 2 + 0xFFFF2]
pmuludq xmm15, [rax + rsi * 4 + 0xFFFF4]
pmuludq xmm15, [rax + rsi * 8 + 0xFFFF8]
pmuludq xmm15, [rsp + rax * 8 + 0xFFFF8]
pmuludq xmm15, [r15 + rax * 8 + 0xFFFF8]
pmuludq xmm15, [rsp + r15 * 8 + 0xFFFF8]
pmuludq xmm15, [r14 + r15 * 8 + 0xFFFF8]
