; expect: 660f72f000660f72f001660f72f064660f72f07f660f72f080660f72f100660f72f101660f72f164660f72f17f660f72f18066410f72f70066410f72f70166410f72f76466410f72f77f66410f72f780660ff2c0660ff2c166410ff2c7660ff2c8660ff2c966410ff2cf66440ff2f866440ff2f966450ff2ff660ff2042500000000660ff20425ff000000660ff205f8ffffff660ff205f7000000660ff205f7ff0000660ff200660ff200660ff280ffff000066410ff287ffff0000660ff20430660ff28430ffff000066410ff28437ffff000066420ff28438ffff0000660ff28470f2ff0f00660ff284b0f4ff0f00660ff284f0f8ff0f00660ff284c4f8ff0f0066410ff284c7f8ff0f0066420ff284fcf8ff0f0066430ff284fef8ff0f00660ff20c2500000000660ff20c25ff000000660ff20df8ffffff660ff20df7000000660ff20df7ff0000660ff208660ff208660ff288ffff000066410ff28fffff0000660ff20c30660ff28c30ffff000066410ff28c37ffff000066420ff28c38ffff0000660ff28c70f2ff0f00660ff28cb0f4ff0f00660ff28cf0f8ff0f00660ff28cc4f8ff0f0066410ff28cc7f8ff0f0066420ff28cfcf8ff0f0066430ff28cfef8ff0f0066440ff23c250000000066440ff23c25ff00000066440ff23df7ffffff66440ff23df600000066440ff23df6ff000066440ff23866440ff23866440ff2b8ffff000066450ff2bfffff000066440ff23c3066440ff2bc30ffff000066450ff2bc37ffff000066460ff2bc38ffff000066440ff2bc70f2ff0f0066440ff2bcb0f4ff0f0066440ff2bcf0f8ff0f0066440ff2bcc4f8ff0f0066450ff2bcc7f8ff0f0066460ff2bcfcf8ff0f0066470ff2bcfef8ff0f00

bits 64

pslld xmm0, 0
pslld xmm0, 1
pslld xmm0, 100
pslld xmm0, 127
pslld xmm0, -128
pslld xmm1, 0
pslld xmm1, 1
pslld xmm1, 100
pslld xmm1, 127
pslld xmm1, -128
pslld xmm15, 0
pslld xmm15, 1
pslld xmm15, 100
pslld xmm15, 127
pslld xmm15, -128
pslld xmm0, xmm0
pslld xmm0, xmm1
pslld xmm0, xmm15
pslld xmm1, xmm0
pslld xmm1, xmm1
pslld xmm1, xmm15
pslld xmm15, xmm0
pslld xmm15, xmm1
pslld xmm15, xmm15
pslld xmm0, [0x0]
pslld xmm0, [0xFF]
pslld xmm0, [rel $ + 0x0]
pslld xmm0, [rel $ + 0xFF]
pslld xmm0, [rel $ + 0xFFFF]
pslld xmm0, [rax]
pslld xmm0, [rax + 0x0]
pslld xmm0, [rax + 0xFFFF]
pslld xmm0, [r15 + 0xFFFF]
pslld xmm0, [rax + rsi * 1  + 0x0]
pslld xmm0, [rax + rsi + 0xFFFF]
pslld xmm0, [r15 + rsi + 0xFFFF]
pslld xmm0, [rax + r15 + 0xFFFF]
pslld xmm0, [rax + rsi * 2 + 0xFFFF2]
pslld xmm0, [rax + rsi * 4 + 0xFFFF4]
pslld xmm0, [rax + rsi * 8 + 0xFFFF8]
pslld xmm0, [rsp + rax * 8 + 0xFFFF8]
pslld xmm0, [r15 + rax * 8 + 0xFFFF8]
pslld xmm0, [rsp + r15 * 8 + 0xFFFF8]
pslld xmm0, [r14 + r15 * 8 + 0xFFFF8]
pslld xmm1, [0x0]
pslld xmm1, [0xFF]
pslld xmm1, [rel $ + 0x0]
pslld xmm1, [rel $ + 0xFF]
pslld xmm1, [rel $ + 0xFFFF]
pslld xmm1, [rax]
pslld xmm1, [rax + 0x0]
pslld xmm1, [rax + 0xFFFF]
pslld xmm1, [r15 + 0xFFFF]
pslld xmm1, [rax + rsi * 1  + 0x0]
pslld xmm1, [rax + rsi + 0xFFFF]
pslld xmm1, [r15 + rsi + 0xFFFF]
pslld xmm1, [rax + r15 + 0xFFFF]
pslld xmm1, [rax + rsi * 2 + 0xFFFF2]
pslld xmm1, [rax + rsi * 4 + 0xFFFF4]
pslld xmm1, [rax + rsi * 8 + 0xFFFF8]
pslld xmm1, [rsp + rax * 8 + 0xFFFF8]
pslld xmm1, [r15 + rax * 8 + 0xFFFF8]
pslld xmm1, [rsp + r15 * 8 + 0xFFFF8]
pslld xmm1, [r14 + r15 * 8 + 0xFFFF8]
pslld xmm15, [0x0]
pslld xmm15, [0xFF]
pslld xmm15, [rel $ + 0x0]
pslld xmm15, [rel $ + 0xFF]
pslld xmm15, [rel $ + 0xFFFF]
pslld xmm15, [rax]
pslld xmm15, [rax + 0x0]
pslld xmm15, [rax + 0xFFFF]
pslld xmm15, [r15 + 0xFFFF]
pslld xmm15, [rax + rsi * 1  + 0x0]
pslld xmm15, [rax + rsi + 0xFFFF]
pslld xmm15, [r15 + rsi + 0xFFFF]
pslld xmm15, [rax + r15 + 0xFFFF]
pslld xmm15, [rax + rsi * 2 + 0xFFFF2]
pslld xmm15, [rax + rsi * 4 + 0xFFFF4]
pslld xmm15, [rax + rsi * 8 + 0xFFFF8]
pslld xmm15, [rsp + rax * 8 + 0xFFFF8]
pslld xmm15, [r15 + rax * 8 + 0xFFFF8]
pslld xmm15, [rsp + r15 * 8 + 0xFFFF8]
pslld xmm15, [r14 + r15 * 8 + 0xFFFF8]
