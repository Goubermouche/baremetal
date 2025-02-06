; expect: 660f72e000660f72e001660f72e064660f72e07f660f72e080660f72e100660f72e101660f72e164660f72e17f660f72e18066410f72e70066410f72e70166410f72e76466410f72e77f66410f72e780660fe2c0660fe2c166410fe2c7660fe2c8660fe2c966410fe2cf66440fe2f866440fe2f966450fe2ff660fe2042500000000660fe20425ff000000660fe205f8ffffff660fe205f7000000660fe205f7ff0000660fe200660fe200660fe280ffff000066410fe287ffff0000660fe20430660fe28430ffff000066410fe28437ffff000066420fe28438ffff0000660fe28470f2ff0f00660fe284b0f4ff0f00660fe284f0f8ff0f00660fe284c4f8ff0f0066410fe284c7f8ff0f0066420fe284fcf8ff0f0066430fe284fef8ff0f00660fe20c2500000000660fe20c25ff000000660fe20df8ffffff660fe20df7000000660fe20df7ff0000660fe208660fe208660fe288ffff000066410fe28fffff0000660fe20c30660fe28c30ffff000066410fe28c37ffff000066420fe28c38ffff0000660fe28c70f2ff0f00660fe28cb0f4ff0f00660fe28cf0f8ff0f00660fe28cc4f8ff0f0066410fe28cc7f8ff0f0066420fe28cfcf8ff0f0066430fe28cfef8ff0f0066440fe23c250000000066440fe23c25ff00000066440fe23df7ffffff66440fe23df600000066440fe23df6ff000066440fe23866440fe23866440fe2b8ffff000066450fe2bfffff000066440fe23c3066440fe2bc30ffff000066450fe2bc37ffff000066460fe2bc38ffff000066440fe2bc70f2ff0f0066440fe2bcb0f4ff0f0066440fe2bcf0f8ff0f0066440fe2bcc4f8ff0f0066450fe2bcc7f8ff0f0066460fe2bcfcf8ff0f0066470fe2bcfef8ff0f00

bits 64

psrad xmm0, 0
psrad xmm0, 1
psrad xmm0, 100
psrad xmm0, 127
psrad xmm0, -128
psrad xmm1, 0
psrad xmm1, 1
psrad xmm1, 100
psrad xmm1, 127
psrad xmm1, -128
psrad xmm15, 0
psrad xmm15, 1
psrad xmm15, 100
psrad xmm15, 127
psrad xmm15, -128
psrad xmm0, xmm0
psrad xmm0, xmm1
psrad xmm0, xmm15
psrad xmm1, xmm0
psrad xmm1, xmm1
psrad xmm1, xmm15
psrad xmm15, xmm0
psrad xmm15, xmm1
psrad xmm15, xmm15
psrad xmm0, [0x0]
psrad xmm0, [0xFF]
psrad xmm0, [rel $ + 0x0]
psrad xmm0, [rel $ + 0xFF]
psrad xmm0, [rel $ + 0xFFFF]
psrad xmm0, [rax]
psrad xmm0, [rax + 0x0]
psrad xmm0, [rax + 0xFFFF]
psrad xmm0, [r15 + 0xFFFF]
psrad xmm0, [rax + rsi * 1  + 0x0]
psrad xmm0, [rax + rsi + 0xFFFF]
psrad xmm0, [r15 + rsi + 0xFFFF]
psrad xmm0, [rax + r15 + 0xFFFF]
psrad xmm0, [rax + rsi * 2 + 0xFFFF2]
psrad xmm0, [rax + rsi * 4 + 0xFFFF4]
psrad xmm0, [rax + rsi * 8 + 0xFFFF8]
psrad xmm0, [rsp + rax * 8 + 0xFFFF8]
psrad xmm0, [r15 + rax * 8 + 0xFFFF8]
psrad xmm0, [rsp + r15 * 8 + 0xFFFF8]
psrad xmm0, [r14 + r15 * 8 + 0xFFFF8]
psrad xmm1, [0x0]
psrad xmm1, [0xFF]
psrad xmm1, [rel $ + 0x0]
psrad xmm1, [rel $ + 0xFF]
psrad xmm1, [rel $ + 0xFFFF]
psrad xmm1, [rax]
psrad xmm1, [rax + 0x0]
psrad xmm1, [rax + 0xFFFF]
psrad xmm1, [r15 + 0xFFFF]
psrad xmm1, [rax + rsi * 1  + 0x0]
psrad xmm1, [rax + rsi + 0xFFFF]
psrad xmm1, [r15 + rsi + 0xFFFF]
psrad xmm1, [rax + r15 + 0xFFFF]
psrad xmm1, [rax + rsi * 2 + 0xFFFF2]
psrad xmm1, [rax + rsi * 4 + 0xFFFF4]
psrad xmm1, [rax + rsi * 8 + 0xFFFF8]
psrad xmm1, [rsp + rax * 8 + 0xFFFF8]
psrad xmm1, [r15 + rax * 8 + 0xFFFF8]
psrad xmm1, [rsp + r15 * 8 + 0xFFFF8]
psrad xmm1, [r14 + r15 * 8 + 0xFFFF8]
psrad xmm15, [0x0]
psrad xmm15, [0xFF]
psrad xmm15, [rel $ + 0x0]
psrad xmm15, [rel $ + 0xFF]
psrad xmm15, [rel $ + 0xFFFF]
psrad xmm15, [rax]
psrad xmm15, [rax + 0x0]
psrad xmm15, [rax + 0xFFFF]
psrad xmm15, [r15 + 0xFFFF]
psrad xmm15, [rax + rsi * 1  + 0x0]
psrad xmm15, [rax + rsi + 0xFFFF]
psrad xmm15, [r15 + rsi + 0xFFFF]
psrad xmm15, [rax + r15 + 0xFFFF]
psrad xmm15, [rax + rsi * 2 + 0xFFFF2]
psrad xmm15, [rax + rsi * 4 + 0xFFFF4]
psrad xmm15, [rax + rsi * 8 + 0xFFFF8]
psrad xmm15, [rsp + rax * 8 + 0xFFFF8]
psrad xmm15, [r15 + rax * 8 + 0xFFFF8]
psrad xmm15, [rsp + r15 * 8 + 0xFFFF8]
psrad xmm15, [r14 + r15 * 8 + 0xFFFF8]
