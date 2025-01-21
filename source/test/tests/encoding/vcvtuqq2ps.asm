; expect: 62f1ffc97ac862f1ffc97ac962d1ffc97acf6291ffc97acf62f1ffca7ad062f1ffca7ad162d1ffca7ad76291ffca7ad76271ffcf7af86271ffcf7af96251ffcf7aff6211ffcf7aff62f1ffc97a0c250000000062f1ffc97a0c25ff00000062f1ffc97a0df6ffffff62f1ffc97a0df500000062f1ffc97a0df5ff000062f1ffc97a0862f1ffc97a0862f1ffc97a88ffff000062d1ffc97a8fffff000062f1ffc97a0c3062f1ffc97a8c30ffff000062d1ffc97a8c37ffff000062b1ffc97a8c38ffff000062f1ffc97a8c70f2ff0f0062f1ffc97a8cb0f4ff0f0062f1ffc97a8cf0f8ff0f0062f1ffc97a8cc4f8ff0f0062d1ffc97a8cc7f8ff0f0062b1ffc97a8cfcf8ff0f006291ffc97a8cfef8ff0f0062f1ffca7a14250000000062f1ffca7a1425ff00000062f1ffca7a15f6ffffff62f1ffca7a15f500000062f1ffca7a15f5ff000062f1ffca7a1062f1ffca7a1062f1ffca7a90ffff000062d1ffca7a97ffff000062f1ffca7a143062f1ffca7a9430ffff000062d1ffca7a9437ffff000062b1ffca7a9438ffff000062f1ffca7a9470f2ff0f0062f1ffca7a94b0f4ff0f0062f1ffca7a94f0f8ff0f0062f1ffca7a94c4f8ff0f0062d1ffca7a94c7f8ff0f0062b1ffca7a94fcf8ff0f006291ffca7a94fef8ff0f006271ffcf7a3c25000000006271ffcf7a3c25ff0000006271ffcf7a3df6ffffff6271ffcf7a3df50000006271ffcf7a3df5ff00006271ffcf7a386271ffcf7a386271ffcf7ab8ffff00006251ffcf7abfffff00006271ffcf7a3c306271ffcf7abc30ffff00006251ffcf7abc37ffff00006231ffcf7abc38ffff00006271ffcf7abc70f2ff0f006271ffcf7abcb0f4ff0f006271ffcf7abcf0f8ff0f006271ffcf7abcc4f8ff0f006251ffcf7abcc7f8ff0f006231ffcf7abcfcf8ff0f006211ffcf7abcfef8ff0f0062f1ffd97a0862f1ffda7a106271ffdf7a38

vcvtuqq2ps ymm1{k1}{z}, zmm0
vcvtuqq2ps ymm1{k1}{z}, zmm1
vcvtuqq2ps ymm1{k1}{z}, zmm15
vcvtuqq2ps ymm1{k1}{z}, zmm31
vcvtuqq2ps ymm2{k2}{z}, zmm0
vcvtuqq2ps ymm2{k2}{z}, zmm1
vcvtuqq2ps ymm2{k2}{z}, zmm15
vcvtuqq2ps ymm2{k2}{z}, zmm31
vcvtuqq2ps ymm15{k7}{z}, zmm0
vcvtuqq2ps ymm15{k7}{z}, zmm1
vcvtuqq2ps ymm15{k7}{z}, zmm15
vcvtuqq2ps ymm15{k7}{z}, zmm31
vcvtuqq2ps ymm1{k1}{z}, [0x0]
vcvtuqq2ps ymm1{k1}{z}, [0xFF]
vcvtuqq2ps ymm1{k1}{z}, [rel $ + 0x0]
vcvtuqq2ps ymm1{k1}{z}, [rel $ + 0xFF]
vcvtuqq2ps ymm1{k1}{z}, [rel $ + 0xFFFF]
vcvtuqq2ps ymm1{k1}{z}, [rax]
vcvtuqq2ps ymm1{k1}{z}, [rax + 0x0]
vcvtuqq2ps ymm1{k1}{z}, [rax + 0xFFFF]
vcvtuqq2ps ymm1{k1}{z}, [r15 + 0xFFFF]
vcvtuqq2ps ymm1{k1}{z}, [rax + rsi * 1  + 0x0]
vcvtuqq2ps ymm1{k1}{z}, [rax + rsi + 0xFFFF]
vcvtuqq2ps ymm1{k1}{z}, [r15 + rsi + 0xFFFF]
vcvtuqq2ps ymm1{k1}{z}, [rax + r15 + 0xFFFF]
vcvtuqq2ps ymm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtuqq2ps ymm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtuqq2ps ymm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtuqq2ps ymm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtuqq2ps ymm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtuqq2ps ymm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtuqq2ps ymm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtuqq2ps ymm2{k2}{z}, [0x0]
vcvtuqq2ps ymm2{k2}{z}, [0xFF]
vcvtuqq2ps ymm2{k2}{z}, [rel $ + 0x0]
vcvtuqq2ps ymm2{k2}{z}, [rel $ + 0xFF]
vcvtuqq2ps ymm2{k2}{z}, [rel $ + 0xFFFF]
vcvtuqq2ps ymm2{k2}{z}, [rax]
vcvtuqq2ps ymm2{k2}{z}, [rax + 0x0]
vcvtuqq2ps ymm2{k2}{z}, [rax + 0xFFFF]
vcvtuqq2ps ymm2{k2}{z}, [r15 + 0xFFFF]
vcvtuqq2ps ymm2{k2}{z}, [rax + rsi * 1  + 0x0]
vcvtuqq2ps ymm2{k2}{z}, [rax + rsi + 0xFFFF]
vcvtuqq2ps ymm2{k2}{z}, [r15 + rsi + 0xFFFF]
vcvtuqq2ps ymm2{k2}{z}, [rax + r15 + 0xFFFF]
vcvtuqq2ps ymm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtuqq2ps ymm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtuqq2ps ymm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtuqq2ps ymm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtuqq2ps ymm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtuqq2ps ymm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtuqq2ps ymm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtuqq2ps ymm15{k7}{z}, [0x0]
vcvtuqq2ps ymm15{k7}{z}, [0xFF]
vcvtuqq2ps ymm15{k7}{z}, [rel $ + 0x0]
vcvtuqq2ps ymm15{k7}{z}, [rel $ + 0xFF]
vcvtuqq2ps ymm15{k7}{z}, [rel $ + 0xFFFF]
vcvtuqq2ps ymm15{k7}{z}, [rax]
vcvtuqq2ps ymm15{k7}{z}, [rax + 0x0]
vcvtuqq2ps ymm15{k7}{z}, [rax + 0xFFFF]
vcvtuqq2ps ymm15{k7}{z}, [r15 + 0xFFFF]
vcvtuqq2ps ymm15{k7}{z}, [rax + rsi * 1  + 0x0]
vcvtuqq2ps ymm15{k7}{z}, [rax + rsi + 0xFFFF]
vcvtuqq2ps ymm15{k7}{z}, [r15 + rsi + 0xFFFF]
vcvtuqq2ps ymm15{k7}{z}, [rax + r15 + 0xFFFF]
vcvtuqq2ps ymm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtuqq2ps ymm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtuqq2ps ymm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtuqq2ps ymm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtuqq2ps ymm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtuqq2ps ymm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtuqq2ps ymm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtuqq2ps ymm1{k1}{z}, [rax]{1to8}
vcvtuqq2ps ymm2{k2}{z}, [rax]{1to8}
vcvtuqq2ps ymm15{k7}{z}, [rax]{1to8}