; expect: 660f72d000660f72d001660f72d064660f72d07f660f72d080660f72d100660f72d101660f72d164660f72d17f660f72d18066410f72d70066410f72d70166410f72d76466410f72d77f66410f72d780660fd2c0660fd2c166410fd2c7660fd2c8660fd2c966410fd2cf66440fd2f866440fd2f966450fd2ff660fd2042500000000660fd20425ff000000660fd205f8ffffff660fd205f7000000660fd205f7ff0000660fd200660fd200660fd280ffff000066410fd287ffff0000660fd20430660fd28430ffff000066410fd28437ffff000066420fd28438ffff0000660fd28470f2ff0f00660fd284b0f4ff0f00660fd284f0f8ff0f00660fd284c4f8ff0f0066410fd284c7f8ff0f0066420fd284fcf8ff0f0066430fd284fef8ff0f00660fd20c2500000000660fd20c25ff000000660fd20df8ffffff660fd20df7000000660fd20df7ff0000660fd208660fd208660fd288ffff000066410fd28fffff0000660fd20c30660fd28c30ffff000066410fd28c37ffff000066420fd28c38ffff0000660fd28c70f2ff0f00660fd28cb0f4ff0f00660fd28cf0f8ff0f00660fd28cc4f8ff0f0066410fd28cc7f8ff0f0066420fd28cfcf8ff0f0066430fd28cfef8ff0f0066440fd23c250000000066440fd23c25ff00000066440fd23df7ffffff66440fd23df600000066440fd23df6ff000066440fd23866440fd23866440fd2b8ffff000066450fd2bfffff000066440fd23c3066440fd2bc30ffff000066450fd2bc37ffff000066460fd2bc38ffff000066440fd2bc70f2ff0f0066440fd2bcb0f4ff0f0066440fd2bcf0f8ff0f0066440fd2bcc4f8ff0f0066450fd2bcc7f8ff0f0066460fd2bcfcf8ff0f0066470fd2bcfef8ff0f00

psrld xmm0, 0
psrld xmm0, 1
psrld xmm0, 100
psrld xmm0, 127
psrld xmm0, -128
psrld xmm1, 0
psrld xmm1, 1
psrld xmm1, 100
psrld xmm1, 127
psrld xmm1, -128
psrld xmm15, 0
psrld xmm15, 1
psrld xmm15, 100
psrld xmm15, 127
psrld xmm15, -128
psrld xmm0, xmm0
psrld xmm0, xmm1
psrld xmm0, xmm15
psrld xmm1, xmm0
psrld xmm1, xmm1
psrld xmm1, xmm15
psrld xmm15, xmm0
psrld xmm15, xmm1
psrld xmm15, xmm15
psrld xmm0, [0x0]
psrld xmm0, [0xFF]
psrld xmm0, [rel $ + 0x0]
psrld xmm0, [rel $ + 0xFF]
psrld xmm0, [rel $ + 0xFFFF]
psrld xmm0, [rax]
psrld xmm0, [rax + 0x0]
psrld xmm0, [rax + 0xFFFF]
psrld xmm0, [r15 + 0xFFFF]
psrld xmm0, [rax + rsi * 1  + 0x0]
psrld xmm0, [rax + rsi + 0xFFFF]
psrld xmm0, [r15 + rsi + 0xFFFF]
psrld xmm0, [rax + r15 + 0xFFFF]
psrld xmm0, [rax + rsi * 2 + 0xFFFF2]
psrld xmm0, [rax + rsi * 4 + 0xFFFF4]
psrld xmm0, [rax + rsi * 8 + 0xFFFF8]
psrld xmm0, [rsp + rax * 8 + 0xFFFF8]
psrld xmm0, [r15 + rax * 8 + 0xFFFF8]
psrld xmm0, [rsp + r15 * 8 + 0xFFFF8]
psrld xmm0, [r14 + r15 * 8 + 0xFFFF8]
psrld xmm1, [0x0]
psrld xmm1, [0xFF]
psrld xmm1, [rel $ + 0x0]
psrld xmm1, [rel $ + 0xFF]
psrld xmm1, [rel $ + 0xFFFF]
psrld xmm1, [rax]
psrld xmm1, [rax + 0x0]
psrld xmm1, [rax + 0xFFFF]
psrld xmm1, [r15 + 0xFFFF]
psrld xmm1, [rax + rsi * 1  + 0x0]
psrld xmm1, [rax + rsi + 0xFFFF]
psrld xmm1, [r15 + rsi + 0xFFFF]
psrld xmm1, [rax + r15 + 0xFFFF]
psrld xmm1, [rax + rsi * 2 + 0xFFFF2]
psrld xmm1, [rax + rsi * 4 + 0xFFFF4]
psrld xmm1, [rax + rsi * 8 + 0xFFFF8]
psrld xmm1, [rsp + rax * 8 + 0xFFFF8]
psrld xmm1, [r15 + rax * 8 + 0xFFFF8]
psrld xmm1, [rsp + r15 * 8 + 0xFFFF8]
psrld xmm1, [r14 + r15 * 8 + 0xFFFF8]
psrld xmm15, [0x0]
psrld xmm15, [0xFF]
psrld xmm15, [rel $ + 0x0]
psrld xmm15, [rel $ + 0xFF]
psrld xmm15, [rel $ + 0xFFFF]
psrld xmm15, [rax]
psrld xmm15, [rax + 0x0]
psrld xmm15, [rax + 0xFFFF]
psrld xmm15, [r15 + 0xFFFF]
psrld xmm15, [rax + rsi * 1  + 0x0]
psrld xmm15, [rax + rsi + 0xFFFF]
psrld xmm15, [r15 + rsi + 0xFFFF]
psrld xmm15, [rax + r15 + 0xFFFF]
psrld xmm15, [rax + rsi * 2 + 0xFFFF2]
psrld xmm15, [rax + rsi * 4 + 0xFFFF4]
psrld xmm15, [rax + rsi * 8 + 0xFFFF8]
psrld xmm15, [rsp + rax * 8 + 0xFFFF8]
psrld xmm15, [r15 + rax * 8 + 0xFFFF8]
psrld xmm15, [rsp + r15 * 8 + 0xFFFF8]
psrld xmm15, [r14 + r15 * 8 + 0xFFFF8]