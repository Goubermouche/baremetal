; expect: 660f73f000660f73f001660f73f064660f73f07f660f73f080660f73f100660f73f101660f73f164660f73f17f660f73f18066410f73f70066410f73f70166410f73f76466410f73f77f66410f73f780660ff3c0660ff3c166410ff3c7660ff3c8660ff3c966410ff3cf66440ff3f866440ff3f966450ff3ff660ff3042500000000660ff30425ff000000660ff305f8ffffff660ff305f7000000660ff305f7ff0000660ff300660ff300660ff380ffff000066410ff387ffff0000660ff30430660ff38430ffff000066410ff38437ffff000066420ff38438ffff0000660ff38470f2ff0f00660ff384b0f4ff0f00660ff384f0f8ff0f00660ff384c4f8ff0f0066410ff384c7f8ff0f0066420ff384fcf8ff0f0066430ff384fef8ff0f00660ff30c2500000000660ff30c25ff000000660ff30df8ffffff660ff30df7000000660ff30df7ff0000660ff308660ff308660ff388ffff000066410ff38fffff0000660ff30c30660ff38c30ffff000066410ff38c37ffff000066420ff38c38ffff0000660ff38c70f2ff0f00660ff38cb0f4ff0f00660ff38cf0f8ff0f00660ff38cc4f8ff0f0066410ff38cc7f8ff0f0066420ff38cfcf8ff0f0066430ff38cfef8ff0f0066440ff33c250000000066440ff33c25ff00000066440ff33df7ffffff66440ff33df600000066440ff33df6ff000066440ff33866440ff33866440ff3b8ffff000066450ff3bfffff000066440ff33c3066440ff3bc30ffff000066450ff3bc37ffff000066460ff3bc38ffff000066440ff3bc70f2ff0f0066440ff3bcb0f4ff0f0066440ff3bcf0f8ff0f0066440ff3bcc4f8ff0f0066450ff3bcc7f8ff0f0066460ff3bcfcf8ff0f0066470ff3bcfef8ff0f00

psllq xmm0, 0
psllq xmm0, 1
psllq xmm0, 100
psllq xmm0, 127
psllq xmm0, -128
psllq xmm1, 0
psllq xmm1, 1
psllq xmm1, 100
psllq xmm1, 127
psllq xmm1, -128
psllq xmm15, 0
psllq xmm15, 1
psllq xmm15, 100
psllq xmm15, 127
psllq xmm15, -128
psllq xmm0, xmm0
psllq xmm0, xmm1
psllq xmm0, xmm15
psllq xmm1, xmm0
psllq xmm1, xmm1
psllq xmm1, xmm15
psllq xmm15, xmm0
psllq xmm15, xmm1
psllq xmm15, xmm15
psllq xmm0, [0x0]
psllq xmm0, [0xFF]
psllq xmm0, [rel $ + 0x0]
psllq xmm0, [rel $ + 0xFF]
psllq xmm0, [rel $ + 0xFFFF]
psllq xmm0, [rax]
psllq xmm0, [rax + 0x0]
psllq xmm0, [rax + 0xFFFF]
psllq xmm0, [r15 + 0xFFFF]
psllq xmm0, [rax + rsi * 1  + 0x0]
psllq xmm0, [rax + rsi + 0xFFFF]
psllq xmm0, [r15 + rsi + 0xFFFF]
psllq xmm0, [rax + r15 + 0xFFFF]
psllq xmm0, [rax + rsi * 2 + 0xFFFF2]
psllq xmm0, [rax + rsi * 4 + 0xFFFF4]
psllq xmm0, [rax + rsi * 8 + 0xFFFF8]
psllq xmm0, [rsp + rax * 8 + 0xFFFF8]
psllq xmm0, [r15 + rax * 8 + 0xFFFF8]
psllq xmm0, [rsp + r15 * 8 + 0xFFFF8]
psllq xmm0, [r14 + r15 * 8 + 0xFFFF8]
psllq xmm1, [0x0]
psllq xmm1, [0xFF]
psllq xmm1, [rel $ + 0x0]
psllq xmm1, [rel $ + 0xFF]
psllq xmm1, [rel $ + 0xFFFF]
psllq xmm1, [rax]
psllq xmm1, [rax + 0x0]
psllq xmm1, [rax + 0xFFFF]
psllq xmm1, [r15 + 0xFFFF]
psllq xmm1, [rax + rsi * 1  + 0x0]
psllq xmm1, [rax + rsi + 0xFFFF]
psllq xmm1, [r15 + rsi + 0xFFFF]
psllq xmm1, [rax + r15 + 0xFFFF]
psllq xmm1, [rax + rsi * 2 + 0xFFFF2]
psllq xmm1, [rax + rsi * 4 + 0xFFFF4]
psllq xmm1, [rax + rsi * 8 + 0xFFFF8]
psllq xmm1, [rsp + rax * 8 + 0xFFFF8]
psllq xmm1, [r15 + rax * 8 + 0xFFFF8]
psllq xmm1, [rsp + r15 * 8 + 0xFFFF8]
psllq xmm1, [r14 + r15 * 8 + 0xFFFF8]
psllq xmm15, [0x0]
psllq xmm15, [0xFF]
psllq xmm15, [rel $ + 0x0]
psllq xmm15, [rel $ + 0xFF]
psllq xmm15, [rel $ + 0xFFFF]
psllq xmm15, [rax]
psllq xmm15, [rax + 0x0]
psllq xmm15, [rax + 0xFFFF]
psllq xmm15, [r15 + 0xFFFF]
psllq xmm15, [rax + rsi * 1  + 0x0]
psllq xmm15, [rax + rsi + 0xFFFF]
psllq xmm15, [r15 + rsi + 0xFFFF]
psllq xmm15, [rax + r15 + 0xFFFF]
psllq xmm15, [rax + rsi * 2 + 0xFFFF2]
psllq xmm15, [rax + rsi * 4 + 0xFFFF4]
psllq xmm15, [rax + rsi * 8 + 0xFFFF8]
psllq xmm15, [rsp + rax * 8 + 0xFFFF8]
psllq xmm15, [r15 + rax * 8 + 0xFFFF8]
psllq xmm15, [rsp + r15 * 8 + 0xFFFF8]
psllq xmm15, [r14 + r15 * 8 + 0xFFFF8]