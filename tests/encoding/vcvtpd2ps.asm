; expect: c5f95ac0c5f95ac1c4c1795ac7c5f95ac8c5f95ac9c4c1795acfc5795af8c5795af9c441795affc5f95a042500000000c5f95a0425ff000000c5f95a05f8ffffffc5f95a05f7000000c5f95a05f7ff0000c5f95a00c5f95a00c5f95a80ffff0000c4c1795a87ffff0000c5f95a0430c5f95a8430ffff0000c4c1795a8437ffff0000c4a1795a8438ffff0000c5f95a8470f2ff0f00c5f95a84b0f4ff0f00c5f95a84f0f8ff0f00c5f95a84c4f8ff0f00c4c1795a84c7f8ff0f00c4a1795a84fcf8ff0f00c481795a84fef8ff0f00c5f95a0c2500000000c5f95a0c25ff000000c5f95a0df8ffffffc5f95a0df7000000c5f95a0df7ff0000c5f95a08c5f95a08c5f95a88ffff0000c4c1795a8fffff0000c5f95a0c30c5f95a8c30ffff0000c4c1795a8c37ffff0000c4a1795a8c38ffff0000c5f95a8c70f2ff0f00c5f95a8cb0f4ff0f00c5f95a8cf0f8ff0f00c5f95a8cc4f8ff0f00c4c1795a8cc7f8ff0f00c4a1795a8cfcf8ff0f00c481795a8cfef8ff0f00c5795a3c2500000000c5795a3c25ff000000c5795a3df8ffffffc5795a3df7000000c5795a3df7ff0000c5795a38c5795a38c5795ab8ffff0000c441795abfffff0000c5795a3c30c5795abc30ffff0000c441795abc37ffff0000c421795abc38ffff0000c5795abc70f2ff0f00c5795abcb0f4ff0f00c5795abcf0f8ff0f00c5795abcc4f8ff0f00c441795abcc7f8ff0f00c421795abcfcf8ff0f00c401795abcfef8ff0f00c5fd5ac0c5fd5ac1c4c17d5ac7c5fd5ac8c5fd5ac9c4c17d5acfc57d5af8c57d5af9c4417d5aff62f1fdc95ac862f1fdc95ac962d1fdc95acf6291fdc95acf62f1fdca5ad062f1fdca5ad162d1fdca5ad76291fdca5ad76271fdcf5af86271fdcf5af96251fdcf5aff6211fdcf5aff62f1fdc95a0c250000000062f1fdc95a0c25ff00000062f1fdc95a0df6ffffff62f1fdc95a0df500000062f1fdc95a0df5ff000062f1fdc95a0862f1fdc95a0862f1fdc95a88ffff000062d1fdc95a8fffff000062f1fdc95a0c3062f1fdc95a8c30ffff000062d1fdc95a8c37ffff000062b1fdc95a8c38ffff000062f1fdc95a8c70f2ff0f0062f1fdc95a8cb0f4ff0f0062f1fdc95a8cf0f8ff0f0062f1fdc95a8cc4f8ff0f0062d1fdc95a8cc7f8ff0f0062b1fdc95a8cfcf8ff0f006291fdc95a8cfef8ff0f0062f1fdca5a14250000000062f1fdca5a1425ff00000062f1fdca5a15f6ffffff62f1fdca5a15f500000062f1fdca5a15f5ff000062f1fdca5a1062f1fdca5a1062f1fdca5a90ffff000062d1fdca5a97ffff000062f1fdca5a143062f1fdca5a9430ffff000062d1fdca5a9437ffff000062b1fdca5a9438ffff000062f1fdca5a9470f2ff0f0062f1fdca5a94b0f4ff0f0062f1fdca5a94f0f8ff0f0062f1fdca5a94c4f8ff0f0062d1fdca5a94c7f8ff0f0062b1fdca5a94fcf8ff0f006291fdca5a94fef8ff0f006271fdcf5a3c25000000006271fdcf5a3c25ff0000006271fdcf5a3df6ffffff6271fdcf5a3df50000006271fdcf5a3df5ff00006271fdcf5a386271fdcf5a386271fdcf5ab8ffff00006251fdcf5abfffff00006271fdcf5a3c306271fdcf5abc30ffff00006251fdcf5abc37ffff00006231fdcf5abc38ffff00006271fdcf5abc70f2ff0f006271fdcf5abcb0f4ff0f006271fdcf5abcf0f8ff0f006271fdcf5abcc4f8ff0f006251fdcf5abcc7f8ff0f006231fdcf5abcfcf8ff0f006211fdcf5abcfef8ff0f0062f1fdd95a0862f1fdda5a106271fddf5a38

bits 64

vcvtpd2ps xmm0, xmm0
vcvtpd2ps xmm0, xmm1
vcvtpd2ps xmm0, xmm15
vcvtpd2ps xmm1, xmm0
vcvtpd2ps xmm1, xmm1
vcvtpd2ps xmm1, xmm15
vcvtpd2ps xmm15, xmm0
vcvtpd2ps xmm15, xmm1
vcvtpd2ps xmm15, xmm15
vcvtpd2ps xmm0, [0x0]
vcvtpd2ps xmm0, [0xFF]
vcvtpd2ps xmm0, [rel $ + 0x0]
vcvtpd2ps xmm0, [rel $ + 0xFF]
vcvtpd2ps xmm0, [rel $ + 0xFFFF]
vcvtpd2ps xmm0, [rax]
vcvtpd2ps xmm0, [rax + 0x0]
vcvtpd2ps xmm0, [rax + 0xFFFF]
vcvtpd2ps xmm0, [r15 + 0xFFFF]
vcvtpd2ps xmm0, [rax + rsi * 1  + 0x0]
vcvtpd2ps xmm0, [rax + rsi + 0xFFFF]
vcvtpd2ps xmm0, [r15 + rsi + 0xFFFF]
vcvtpd2ps xmm0, [rax + r15 + 0xFFFF]
vcvtpd2ps xmm0, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2ps xmm0, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2ps xmm0, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2ps xmm0, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2ps xmm0, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2ps xmm0, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2ps xmm0, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2ps xmm1, [0x0]
vcvtpd2ps xmm1, [0xFF]
vcvtpd2ps xmm1, [rel $ + 0x0]
vcvtpd2ps xmm1, [rel $ + 0xFF]
vcvtpd2ps xmm1, [rel $ + 0xFFFF]
vcvtpd2ps xmm1, [rax]
vcvtpd2ps xmm1, [rax + 0x0]
vcvtpd2ps xmm1, [rax + 0xFFFF]
vcvtpd2ps xmm1, [r15 + 0xFFFF]
vcvtpd2ps xmm1, [rax + rsi * 1  + 0x0]
vcvtpd2ps xmm1, [rax + rsi + 0xFFFF]
vcvtpd2ps xmm1, [r15 + rsi + 0xFFFF]
vcvtpd2ps xmm1, [rax + r15 + 0xFFFF]
vcvtpd2ps xmm1, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2ps xmm1, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2ps xmm1, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2ps xmm1, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2ps xmm1, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2ps xmm1, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2ps xmm1, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2ps xmm15, [0x0]
vcvtpd2ps xmm15, [0xFF]
vcvtpd2ps xmm15, [rel $ + 0x0]
vcvtpd2ps xmm15, [rel $ + 0xFF]
vcvtpd2ps xmm15, [rel $ + 0xFFFF]
vcvtpd2ps xmm15, [rax]
vcvtpd2ps xmm15, [rax + 0x0]
vcvtpd2ps xmm15, [rax + 0xFFFF]
vcvtpd2ps xmm15, [r15 + 0xFFFF]
vcvtpd2ps xmm15, [rax + rsi * 1  + 0x0]
vcvtpd2ps xmm15, [rax + rsi + 0xFFFF]
vcvtpd2ps xmm15, [r15 + rsi + 0xFFFF]
vcvtpd2ps xmm15, [rax + r15 + 0xFFFF]
vcvtpd2ps xmm15, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2ps xmm15, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2ps xmm15, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2ps xmm15, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2ps xmm15, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2ps xmm15, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2ps xmm15, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2ps xmm0, ymm0
vcvtpd2ps xmm0, ymm1
vcvtpd2ps xmm0, ymm15
vcvtpd2ps xmm1, ymm0
vcvtpd2ps xmm1, ymm1
vcvtpd2ps xmm1, ymm15
vcvtpd2ps xmm15, ymm0
vcvtpd2ps xmm15, ymm1
vcvtpd2ps xmm15, ymm15
vcvtpd2ps ymm1{k1}{z}, zmm0
vcvtpd2ps ymm1{k1}{z}, zmm1
vcvtpd2ps ymm1{k1}{z}, zmm15
vcvtpd2ps ymm1{k1}{z}, zmm31
vcvtpd2ps ymm2{k2}{z}, zmm0
vcvtpd2ps ymm2{k2}{z}, zmm1
vcvtpd2ps ymm2{k2}{z}, zmm15
vcvtpd2ps ymm2{k2}{z}, zmm31
vcvtpd2ps ymm15{k7}{z}, zmm0
vcvtpd2ps ymm15{k7}{z}, zmm1
vcvtpd2ps ymm15{k7}{z}, zmm15
vcvtpd2ps ymm15{k7}{z}, zmm31
vcvtpd2ps ymm1{k1}{z}, [0x0]
vcvtpd2ps ymm1{k1}{z}, [0xFF]
vcvtpd2ps ymm1{k1}{z}, [rel $ + 0x0]
vcvtpd2ps ymm1{k1}{z}, [rel $ + 0xFF]
vcvtpd2ps ymm1{k1}{z}, [rel $ + 0xFFFF]
vcvtpd2ps ymm1{k1}{z}, [rax]
vcvtpd2ps ymm1{k1}{z}, [rax + 0x0]
vcvtpd2ps ymm1{k1}{z}, [rax + 0xFFFF]
vcvtpd2ps ymm1{k1}{z}, [r15 + 0xFFFF]
vcvtpd2ps ymm1{k1}{z}, [rax + rsi * 1  + 0x0]
vcvtpd2ps ymm1{k1}{z}, [rax + rsi + 0xFFFF]
vcvtpd2ps ymm1{k1}{z}, [r15 + rsi + 0xFFFF]
vcvtpd2ps ymm1{k1}{z}, [rax + r15 + 0xFFFF]
vcvtpd2ps ymm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2ps ymm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2ps ymm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2ps ymm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2ps ymm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2ps ymm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2ps ymm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2ps ymm2{k2}{z}, [0x0]
vcvtpd2ps ymm2{k2}{z}, [0xFF]
vcvtpd2ps ymm2{k2}{z}, [rel $ + 0x0]
vcvtpd2ps ymm2{k2}{z}, [rel $ + 0xFF]
vcvtpd2ps ymm2{k2}{z}, [rel $ + 0xFFFF]
vcvtpd2ps ymm2{k2}{z}, [rax]
vcvtpd2ps ymm2{k2}{z}, [rax + 0x0]
vcvtpd2ps ymm2{k2}{z}, [rax + 0xFFFF]
vcvtpd2ps ymm2{k2}{z}, [r15 + 0xFFFF]
vcvtpd2ps ymm2{k2}{z}, [rax + rsi * 1  + 0x0]
vcvtpd2ps ymm2{k2}{z}, [rax + rsi + 0xFFFF]
vcvtpd2ps ymm2{k2}{z}, [r15 + rsi + 0xFFFF]
vcvtpd2ps ymm2{k2}{z}, [rax + r15 + 0xFFFF]
vcvtpd2ps ymm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2ps ymm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2ps ymm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2ps ymm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2ps ymm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2ps ymm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2ps ymm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2ps ymm15{k7}{z}, [0x0]
vcvtpd2ps ymm15{k7}{z}, [0xFF]
vcvtpd2ps ymm15{k7}{z}, [rel $ + 0x0]
vcvtpd2ps ymm15{k7}{z}, [rel $ + 0xFF]
vcvtpd2ps ymm15{k7}{z}, [rel $ + 0xFFFF]
vcvtpd2ps ymm15{k7}{z}, [rax]
vcvtpd2ps ymm15{k7}{z}, [rax + 0x0]
vcvtpd2ps ymm15{k7}{z}, [rax + 0xFFFF]
vcvtpd2ps ymm15{k7}{z}, [r15 + 0xFFFF]
vcvtpd2ps ymm15{k7}{z}, [rax + rsi * 1  + 0x0]
vcvtpd2ps ymm15{k7}{z}, [rax + rsi + 0xFFFF]
vcvtpd2ps ymm15{k7}{z}, [r15 + rsi + 0xFFFF]
vcvtpd2ps ymm15{k7}{z}, [rax + r15 + 0xFFFF]
vcvtpd2ps ymm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2ps ymm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2ps ymm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2ps ymm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2ps ymm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2ps ymm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2ps ymm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2ps ymm1{k1}{z}, [rax]{1to8}
vcvtpd2ps ymm2{k2}{z}, [rax]{1to8}
vcvtpd2ps ymm15{k7}{z}, [rax]{1to8}
