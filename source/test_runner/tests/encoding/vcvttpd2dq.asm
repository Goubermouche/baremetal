; expect: c5f9e6c0c5f9e6c1c4c179e6c7c5f9e6c8c5f9e6c9c4c179e6cfc579e6f8c579e6f9c44179e6ffc5f9e6042500000000c5f9e60425ff000000c5f9e605f8ffffffc5f9e605f7000000c5f9e605f7ff0000c5f9e600c5f9e600c5f9e680ffff0000c4c179e687ffff0000c5f9e60430c5f9e68430ffff0000c4c179e68437ffff0000c4a179e68438ffff0000c5f9e68470f2ff0f00c5f9e684b0f4ff0f00c5f9e684f0f8ff0f00c5f9e684c4f8ff0f00c4c179e684c7f8ff0f00c4a179e684fcf8ff0f00c48179e684fef8ff0f00c5f9e60c2500000000c5f9e60c25ff000000c5f9e60df8ffffffc5f9e60df7000000c5f9e60df7ff0000c5f9e608c5f9e608c5f9e688ffff0000c4c179e68fffff0000c5f9e60c30c5f9e68c30ffff0000c4c179e68c37ffff0000c4a179e68c38ffff0000c5f9e68c70f2ff0f00c5f9e68cb0f4ff0f00c5f9e68cf0f8ff0f00c5f9e68cc4f8ff0f00c4c179e68cc7f8ff0f00c4a179e68cfcf8ff0f00c48179e68cfef8ff0f00c579e63c2500000000c579e63c25ff000000c579e63df8ffffffc579e63df7000000c579e63df7ff0000c579e638c579e638c579e6b8ffff0000c44179e6bfffff0000c579e63c30c579e6bc30ffff0000c44179e6bc37ffff0000c42179e6bc38ffff0000c579e6bc70f2ff0f00c579e6bcb0f4ff0f00c579e6bcf0f8ff0f00c579e6bcc4f8ff0f00c44179e6bcc7f8ff0f00c42179e6bcfcf8ff0f00c40179e6bcfef8ff0f00c5fde6c0c5fde6c1c4c17de6c7c5fde6c8c5fde6c9c4c17de6cfc57de6f8c57de6f9c4417de6ff62f1fdc9e6c862f1fdc9e6c962d1fdc9e6cf6291fdc9e6cf62f1fdcae6d062f1fdcae6d162d1fdcae6d76291fdcae6d76271fdcfe6f86271fdcfe6f96251fdcfe6ff6211fdcfe6ff62f1fdc9e60c250000000062f1fdc9e60c25ff00000062f1fdc9e60df6ffffff62f1fdc9e60df500000062f1fdc9e60df5ff000062f1fdc9e60862f1fdc9e60862f1fdc9e688ffff000062d1fdc9e68fffff000062f1fdc9e60c3062f1fdc9e68c30ffff000062d1fdc9e68c37ffff000062b1fdc9e68c38ffff000062f1fdc9e68c70f2ff0f0062f1fdc9e68cb0f4ff0f0062f1fdc9e68cf0f8ff0f0062f1fdc9e68cc4f8ff0f0062d1fdc9e68cc7f8ff0f0062b1fdc9e68cfcf8ff0f006291fdc9e68cfef8ff0f0062f1fdcae614250000000062f1fdcae61425ff00000062f1fdcae615f6ffffff62f1fdcae615f500000062f1fdcae615f5ff000062f1fdcae61062f1fdcae61062f1fdcae690ffff000062d1fdcae697ffff000062f1fdcae6143062f1fdcae69430ffff000062d1fdcae69437ffff000062b1fdcae69438ffff000062f1fdcae69470f2ff0f0062f1fdcae694b0f4ff0f0062f1fdcae694f0f8ff0f0062f1fdcae694c4f8ff0f0062d1fdcae694c7f8ff0f0062b1fdcae694fcf8ff0f006291fdcae694fef8ff0f006271fdcfe63c25000000006271fdcfe63c25ff0000006271fdcfe63df6ffffff6271fdcfe63df50000006271fdcfe63df5ff00006271fdcfe6386271fdcfe6386271fdcfe6b8ffff00006251fdcfe6bfffff00006271fdcfe63c306271fdcfe6bc30ffff00006251fdcfe6bc37ffff00006231fdcfe6bc38ffff00006271fdcfe6bc70f2ff0f006271fdcfe6bcb0f4ff0f006271fdcfe6bcf0f8ff0f006271fdcfe6bcc4f8ff0f006251fdcfe6bcc7f8ff0f006231fdcfe6bcfcf8ff0f006211fdcfe6bcfef8ff0f0062f1fdd9e60862f1fddae6106271fddfe638

vcvttpd2dq xmm0, xmm0
vcvttpd2dq xmm0, xmm1
vcvttpd2dq xmm0, xmm15
vcvttpd2dq xmm1, xmm0
vcvttpd2dq xmm1, xmm1
vcvttpd2dq xmm1, xmm15
vcvttpd2dq xmm15, xmm0
vcvttpd2dq xmm15, xmm1
vcvttpd2dq xmm15, xmm15
vcvttpd2dq xmm0, [0x0]
vcvttpd2dq xmm0, [0xFF]
vcvttpd2dq xmm0, [rel $ + 0x0]
vcvttpd2dq xmm0, [rel $ + 0xFF]
vcvttpd2dq xmm0, [rel $ + 0xFFFF]
vcvttpd2dq xmm0, [rax]
vcvttpd2dq xmm0, [rax + 0x0]
vcvttpd2dq xmm0, [rax + 0xFFFF]
vcvttpd2dq xmm0, [r15 + 0xFFFF]
vcvttpd2dq xmm0, [rax + rsi * 1  + 0x0]
vcvttpd2dq xmm0, [rax + rsi + 0xFFFF]
vcvttpd2dq xmm0, [r15 + rsi + 0xFFFF]
vcvttpd2dq xmm0, [rax + r15 + 0xFFFF]
vcvttpd2dq xmm0, [rax + rsi * 2 + 0xFFFF2]
vcvttpd2dq xmm0, [rax + rsi * 4 + 0xFFFF4]
vcvttpd2dq xmm0, [rax + rsi * 8 + 0xFFFF8]
vcvttpd2dq xmm0, [rsp + rax * 8 + 0xFFFF8]
vcvttpd2dq xmm0, [r15 + rax * 8 + 0xFFFF8]
vcvttpd2dq xmm0, [rsp + r15 * 8 + 0xFFFF8]
vcvttpd2dq xmm0, [r14 + r15 * 8 + 0xFFFF8]
vcvttpd2dq xmm1, [0x0]
vcvttpd2dq xmm1, [0xFF]
vcvttpd2dq xmm1, [rel $ + 0x0]
vcvttpd2dq xmm1, [rel $ + 0xFF]
vcvttpd2dq xmm1, [rel $ + 0xFFFF]
vcvttpd2dq xmm1, [rax]
vcvttpd2dq xmm1, [rax + 0x0]
vcvttpd2dq xmm1, [rax + 0xFFFF]
vcvttpd2dq xmm1, [r15 + 0xFFFF]
vcvttpd2dq xmm1, [rax + rsi * 1  + 0x0]
vcvttpd2dq xmm1, [rax + rsi + 0xFFFF]
vcvttpd2dq xmm1, [r15 + rsi + 0xFFFF]
vcvttpd2dq xmm1, [rax + r15 + 0xFFFF]
vcvttpd2dq xmm1, [rax + rsi * 2 + 0xFFFF2]
vcvttpd2dq xmm1, [rax + rsi * 4 + 0xFFFF4]
vcvttpd2dq xmm1, [rax + rsi * 8 + 0xFFFF8]
vcvttpd2dq xmm1, [rsp + rax * 8 + 0xFFFF8]
vcvttpd2dq xmm1, [r15 + rax * 8 + 0xFFFF8]
vcvttpd2dq xmm1, [rsp + r15 * 8 + 0xFFFF8]
vcvttpd2dq xmm1, [r14 + r15 * 8 + 0xFFFF8]
vcvttpd2dq xmm15, [0x0]
vcvttpd2dq xmm15, [0xFF]
vcvttpd2dq xmm15, [rel $ + 0x0]
vcvttpd2dq xmm15, [rel $ + 0xFF]
vcvttpd2dq xmm15, [rel $ + 0xFFFF]
vcvttpd2dq xmm15, [rax]
vcvttpd2dq xmm15, [rax + 0x0]
vcvttpd2dq xmm15, [rax + 0xFFFF]
vcvttpd2dq xmm15, [r15 + 0xFFFF]
vcvttpd2dq xmm15, [rax + rsi * 1  + 0x0]
vcvttpd2dq xmm15, [rax + rsi + 0xFFFF]
vcvttpd2dq xmm15, [r15 + rsi + 0xFFFF]
vcvttpd2dq xmm15, [rax + r15 + 0xFFFF]
vcvttpd2dq xmm15, [rax + rsi * 2 + 0xFFFF2]
vcvttpd2dq xmm15, [rax + rsi * 4 + 0xFFFF4]
vcvttpd2dq xmm15, [rax + rsi * 8 + 0xFFFF8]
vcvttpd2dq xmm15, [rsp + rax * 8 + 0xFFFF8]
vcvttpd2dq xmm15, [r15 + rax * 8 + 0xFFFF8]
vcvttpd2dq xmm15, [rsp + r15 * 8 + 0xFFFF8]
vcvttpd2dq xmm15, [r14 + r15 * 8 + 0xFFFF8]
vcvttpd2dq xmm0, ymm0
vcvttpd2dq xmm0, ymm1
vcvttpd2dq xmm0, ymm15
vcvttpd2dq xmm1, ymm0
vcvttpd2dq xmm1, ymm1
vcvttpd2dq xmm1, ymm15
vcvttpd2dq xmm15, ymm0
vcvttpd2dq xmm15, ymm1
vcvttpd2dq xmm15, ymm15
vcvttpd2dq ymm1{k1}{z}, zmm0
vcvttpd2dq ymm1{k1}{z}, zmm1
vcvttpd2dq ymm1{k1}{z}, zmm15
vcvttpd2dq ymm1{k1}{z}, zmm31
vcvttpd2dq ymm2{k2}{z}, zmm0
vcvttpd2dq ymm2{k2}{z}, zmm1
vcvttpd2dq ymm2{k2}{z}, zmm15
vcvttpd2dq ymm2{k2}{z}, zmm31
vcvttpd2dq ymm15{k7}{z}, zmm0
vcvttpd2dq ymm15{k7}{z}, zmm1
vcvttpd2dq ymm15{k7}{z}, zmm15
vcvttpd2dq ymm15{k7}{z}, zmm31
vcvttpd2dq ymm1{k1}{z}, [0x0]
vcvttpd2dq ymm1{k1}{z}, [0xFF]
vcvttpd2dq ymm1{k1}{z}, [rel $ + 0x0]
vcvttpd2dq ymm1{k1}{z}, [rel $ + 0xFF]
vcvttpd2dq ymm1{k1}{z}, [rel $ + 0xFFFF]
vcvttpd2dq ymm1{k1}{z}, [rax]
vcvttpd2dq ymm1{k1}{z}, [rax + 0x0]
vcvttpd2dq ymm1{k1}{z}, [rax + 0xFFFF]
vcvttpd2dq ymm1{k1}{z}, [r15 + 0xFFFF]
vcvttpd2dq ymm1{k1}{z}, [rax + rsi * 1  + 0x0]
vcvttpd2dq ymm1{k1}{z}, [rax + rsi + 0xFFFF]
vcvttpd2dq ymm1{k1}{z}, [r15 + rsi + 0xFFFF]
vcvttpd2dq ymm1{k1}{z}, [rax + r15 + 0xFFFF]
vcvttpd2dq ymm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvttpd2dq ymm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvttpd2dq ymm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvttpd2dq ymm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvttpd2dq ymm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvttpd2dq ymm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvttpd2dq ymm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvttpd2dq ymm2{k2}{z}, [0x0]
vcvttpd2dq ymm2{k2}{z}, [0xFF]
vcvttpd2dq ymm2{k2}{z}, [rel $ + 0x0]
vcvttpd2dq ymm2{k2}{z}, [rel $ + 0xFF]
vcvttpd2dq ymm2{k2}{z}, [rel $ + 0xFFFF]
vcvttpd2dq ymm2{k2}{z}, [rax]
vcvttpd2dq ymm2{k2}{z}, [rax + 0x0]
vcvttpd2dq ymm2{k2}{z}, [rax + 0xFFFF]
vcvttpd2dq ymm2{k2}{z}, [r15 + 0xFFFF]
vcvttpd2dq ymm2{k2}{z}, [rax + rsi * 1  + 0x0]
vcvttpd2dq ymm2{k2}{z}, [rax + rsi + 0xFFFF]
vcvttpd2dq ymm2{k2}{z}, [r15 + rsi + 0xFFFF]
vcvttpd2dq ymm2{k2}{z}, [rax + r15 + 0xFFFF]
vcvttpd2dq ymm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvttpd2dq ymm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvttpd2dq ymm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvttpd2dq ymm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvttpd2dq ymm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvttpd2dq ymm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvttpd2dq ymm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvttpd2dq ymm15{k7}{z}, [0x0]
vcvttpd2dq ymm15{k7}{z}, [0xFF]
vcvttpd2dq ymm15{k7}{z}, [rel $ + 0x0]
vcvttpd2dq ymm15{k7}{z}, [rel $ + 0xFF]
vcvttpd2dq ymm15{k7}{z}, [rel $ + 0xFFFF]
vcvttpd2dq ymm15{k7}{z}, [rax]
vcvttpd2dq ymm15{k7}{z}, [rax + 0x0]
vcvttpd2dq ymm15{k7}{z}, [rax + 0xFFFF]
vcvttpd2dq ymm15{k7}{z}, [r15 + 0xFFFF]
vcvttpd2dq ymm15{k7}{z}, [rax + rsi * 1  + 0x0]
vcvttpd2dq ymm15{k7}{z}, [rax + rsi + 0xFFFF]
vcvttpd2dq ymm15{k7}{z}, [r15 + rsi + 0xFFFF]
vcvttpd2dq ymm15{k7}{z}, [rax + r15 + 0xFFFF]
vcvttpd2dq ymm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvttpd2dq ymm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvttpd2dq ymm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvttpd2dq ymm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvttpd2dq ymm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvttpd2dq ymm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvttpd2dq ymm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvttpd2dq ymm1{k1}{z}, [rax]{1to8}
vcvttpd2dq ymm2{k2}{z}, [rax]{1to8}
vcvttpd2dq ymm15{k7}{z}, [rax]{1to8}