; expect: 660f71f000660f71f001660f71f064660f71f07f660f71f080660f71f100660f71f101660f71f164660f71f17f660f71f18066410f71f70066410f71f70166410f71f76466410f71f77f66410f71f780660ff1c0660ff1c166410ff1c7660ff1c8660ff1c966410ff1cf66440ff1f866440ff1f966450ff1ff660ff1042500000000660ff10425ff000000660ff105f8ffffff660ff105f7000000660ff105f7ff0000660ff100660ff100660ff180ffff000066410ff187ffff0000660ff10430660ff18430ffff000066410ff18437ffff000066420ff18438ffff0000660ff18470f2ff0f00660ff184b0f4ff0f00660ff184f0f8ff0f00660ff184c4f8ff0f0066410ff184c7f8ff0f0066420ff184fcf8ff0f0066430ff184fef8ff0f00660ff10c2500000000660ff10c25ff000000660ff10df8ffffff660ff10df7000000660ff10df7ff0000660ff108660ff108660ff188ffff000066410ff18fffff0000660ff10c30660ff18c30ffff000066410ff18c37ffff000066420ff18c38ffff0000660ff18c70f2ff0f00660ff18cb0f4ff0f00660ff18cf0f8ff0f00660ff18cc4f8ff0f0066410ff18cc7f8ff0f0066420ff18cfcf8ff0f0066430ff18cfef8ff0f0066440ff13c250000000066440ff13c25ff00000066440ff13df7ffffff66440ff13df600000066440ff13df6ff000066440ff13866440ff13866440ff1b8ffff000066450ff1bfffff000066440ff13c3066440ff1bc30ffff000066450ff1bc37ffff000066460ff1bc38ffff000066440ff1bc70f2ff0f0066440ff1bcb0f4ff0f0066440ff1bcf0f8ff0f0066440ff1bcc4f8ff0f0066450ff1bcc7f8ff0f0066460ff1bcfcf8ff0f0066470ff1bcfef8ff0f00

psllw xmm0, 0
psllw xmm0, 1
psllw xmm0, 100
psllw xmm0, 127
psllw xmm0, -128
psllw xmm1, 0
psllw xmm1, 1
psllw xmm1, 100
psllw xmm1, 127
psllw xmm1, -128
psllw xmm15, 0
psllw xmm15, 1
psllw xmm15, 100
psllw xmm15, 127
psllw xmm15, -128
psllw xmm0, xmm0
psllw xmm0, xmm1
psllw xmm0, xmm15
psllw xmm1, xmm0
psllw xmm1, xmm1
psllw xmm1, xmm15
psllw xmm15, xmm0
psllw xmm15, xmm1
psllw xmm15, xmm15
psllw xmm0, [0x0]
psllw xmm0, [0xFF]
psllw xmm0, [rel $ + 0x0]
psllw xmm0, [rel $ + 0xFF]
psllw xmm0, [rel $ + 0xFFFF]
psllw xmm0, [rax]
psllw xmm0, [rax + 0x0]
psllw xmm0, [rax + 0xFFFF]
psllw xmm0, [r15 + 0xFFFF]
psllw xmm0, [rax + rsi * 1  + 0x0]
psllw xmm0, [rax + rsi + 0xFFFF]
psllw xmm0, [r15 + rsi + 0xFFFF]
psllw xmm0, [rax + r15 + 0xFFFF]
psllw xmm0, [rax + rsi * 2 + 0xFFFF2]
psllw xmm0, [rax + rsi * 4 + 0xFFFF4]
psllw xmm0, [rax + rsi * 8 + 0xFFFF8]
psllw xmm0, [rsp + rax * 8 + 0xFFFF8]
psllw xmm0, [r15 + rax * 8 + 0xFFFF8]
psllw xmm0, [rsp + r15 * 8 + 0xFFFF8]
psllw xmm0, [r14 + r15 * 8 + 0xFFFF8]
psllw xmm1, [0x0]
psllw xmm1, [0xFF]
psllw xmm1, [rel $ + 0x0]
psllw xmm1, [rel $ + 0xFF]
psllw xmm1, [rel $ + 0xFFFF]
psllw xmm1, [rax]
psllw xmm1, [rax + 0x0]
psllw xmm1, [rax + 0xFFFF]
psllw xmm1, [r15 + 0xFFFF]
psllw xmm1, [rax + rsi * 1  + 0x0]
psllw xmm1, [rax + rsi + 0xFFFF]
psllw xmm1, [r15 + rsi + 0xFFFF]
psllw xmm1, [rax + r15 + 0xFFFF]
psllw xmm1, [rax + rsi * 2 + 0xFFFF2]
psllw xmm1, [rax + rsi * 4 + 0xFFFF4]
psllw xmm1, [rax + rsi * 8 + 0xFFFF8]
psllw xmm1, [rsp + rax * 8 + 0xFFFF8]
psllw xmm1, [r15 + rax * 8 + 0xFFFF8]
psllw xmm1, [rsp + r15 * 8 + 0xFFFF8]
psllw xmm1, [r14 + r15 * 8 + 0xFFFF8]
psllw xmm15, [0x0]
psllw xmm15, [0xFF]
psllw xmm15, [rel $ + 0x0]
psllw xmm15, [rel $ + 0xFF]
psllw xmm15, [rel $ + 0xFFFF]
psllw xmm15, [rax]
psllw xmm15, [rax + 0x0]
psllw xmm15, [rax + 0xFFFF]
psllw xmm15, [r15 + 0xFFFF]
psllw xmm15, [rax + rsi * 1  + 0x0]
psllw xmm15, [rax + rsi + 0xFFFF]
psllw xmm15, [r15 + rsi + 0xFFFF]
psllw xmm15, [rax + r15 + 0xFFFF]
psllw xmm15, [rax + rsi * 2 + 0xFFFF2]
psllw xmm15, [rax + rsi * 4 + 0xFFFF4]
psllw xmm15, [rax + rsi * 8 + 0xFFFF8]
psllw xmm15, [rsp + rax * 8 + 0xFFFF8]
psllw xmm15, [r15 + rax * 8 + 0xFFFF8]
psllw xmm15, [rsp + r15 * 8 + 0xFFFF8]
psllw xmm15, [r14 + r15 * 8 + 0xFFFF8]