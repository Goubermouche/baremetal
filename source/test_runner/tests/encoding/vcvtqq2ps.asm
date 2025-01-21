; expect: 62f1fcc95bc862f1fcc95bc962d1fcc95bcf6291fcc95bcf62f1fcca5bd062f1fcca5bd162d1fcca5bd76291fcca5bd76271fccf5bf86271fccf5bf96251fccf5bff6211fccf5bff62f1fcc95b0c250000000062f1fcc95b0c25ff00000062f1fcc95b0df6ffffff62f1fcc95b0df500000062f1fcc95b0df5ff000062f1fcc95b0862f1fcc95b0862f1fcc95b88ffff000062d1fcc95b8fffff000062f1fcc95b0c3062f1fcc95b8c30ffff000062d1fcc95b8c37ffff000062b1fcc95b8c38ffff000062f1fcc95b8c70f2ff0f0062f1fcc95b8cb0f4ff0f0062f1fcc95b8cf0f8ff0f0062f1fcc95b8cc4f8ff0f0062d1fcc95b8cc7f8ff0f0062b1fcc95b8cfcf8ff0f006291fcc95b8cfef8ff0f0062f1fcca5b14250000000062f1fcca5b1425ff00000062f1fcca5b15f6ffffff62f1fcca5b15f500000062f1fcca5b15f5ff000062f1fcca5b1062f1fcca5b1062f1fcca5b90ffff000062d1fcca5b97ffff000062f1fcca5b143062f1fcca5b9430ffff000062d1fcca5b9437ffff000062b1fcca5b9438ffff000062f1fcca5b9470f2ff0f0062f1fcca5b94b0f4ff0f0062f1fcca5b94f0f8ff0f0062f1fcca5b94c4f8ff0f0062d1fcca5b94c7f8ff0f0062b1fcca5b94fcf8ff0f006291fcca5b94fef8ff0f006271fccf5b3c25000000006271fccf5b3c25ff0000006271fccf5b3df6ffffff6271fccf5b3df50000006271fccf5b3df5ff00006271fccf5b386271fccf5b386271fccf5bb8ffff00006251fccf5bbfffff00006271fccf5b3c306271fccf5bbc30ffff00006251fccf5bbc37ffff00006231fccf5bbc38ffff00006271fccf5bbc70f2ff0f006271fccf5bbcb0f4ff0f006271fccf5bbcf0f8ff0f006271fccf5bbcc4f8ff0f006251fccf5bbcc7f8ff0f006231fccf5bbcfcf8ff0f006211fccf5bbcfef8ff0f0062f1fcd95b0862f1fcda5b106271fcdf5b38

vcvtqq2ps ymm1{k1}{z}, zmm0
vcvtqq2ps ymm1{k1}{z}, zmm1
vcvtqq2ps ymm1{k1}{z}, zmm15
vcvtqq2ps ymm1{k1}{z}, zmm31
vcvtqq2ps ymm2{k2}{z}, zmm0
vcvtqq2ps ymm2{k2}{z}, zmm1
vcvtqq2ps ymm2{k2}{z}, zmm15
vcvtqq2ps ymm2{k2}{z}, zmm31
vcvtqq2ps ymm15{k7}{z}, zmm0
vcvtqq2ps ymm15{k7}{z}, zmm1
vcvtqq2ps ymm15{k7}{z}, zmm15
vcvtqq2ps ymm15{k7}{z}, zmm31
vcvtqq2ps ymm1{k1}{z}, [0x0]
vcvtqq2ps ymm1{k1}{z}, [0xFF]
vcvtqq2ps ymm1{k1}{z}, [rel $ + 0x0]
vcvtqq2ps ymm1{k1}{z}, [rel $ + 0xFF]
vcvtqq2ps ymm1{k1}{z}, [rel $ + 0xFFFF]
vcvtqq2ps ymm1{k1}{z}, [rax]
vcvtqq2ps ymm1{k1}{z}, [rax + 0x0]
vcvtqq2ps ymm1{k1}{z}, [rax + 0xFFFF]
vcvtqq2ps ymm1{k1}{z}, [r15 + 0xFFFF]
vcvtqq2ps ymm1{k1}{z}, [rax + rsi * 1  + 0x0]
vcvtqq2ps ymm1{k1}{z}, [rax + rsi + 0xFFFF]
vcvtqq2ps ymm1{k1}{z}, [r15 + rsi + 0xFFFF]
vcvtqq2ps ymm1{k1}{z}, [rax + r15 + 0xFFFF]
vcvtqq2ps ymm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtqq2ps ymm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtqq2ps ymm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtqq2ps ymm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtqq2ps ymm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtqq2ps ymm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtqq2ps ymm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtqq2ps ymm2{k2}{z}, [0x0]
vcvtqq2ps ymm2{k2}{z}, [0xFF]
vcvtqq2ps ymm2{k2}{z}, [rel $ + 0x0]
vcvtqq2ps ymm2{k2}{z}, [rel $ + 0xFF]
vcvtqq2ps ymm2{k2}{z}, [rel $ + 0xFFFF]
vcvtqq2ps ymm2{k2}{z}, [rax]
vcvtqq2ps ymm2{k2}{z}, [rax + 0x0]
vcvtqq2ps ymm2{k2}{z}, [rax + 0xFFFF]
vcvtqq2ps ymm2{k2}{z}, [r15 + 0xFFFF]
vcvtqq2ps ymm2{k2}{z}, [rax + rsi * 1  + 0x0]
vcvtqq2ps ymm2{k2}{z}, [rax + rsi + 0xFFFF]
vcvtqq2ps ymm2{k2}{z}, [r15 + rsi + 0xFFFF]
vcvtqq2ps ymm2{k2}{z}, [rax + r15 + 0xFFFF]
vcvtqq2ps ymm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtqq2ps ymm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtqq2ps ymm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtqq2ps ymm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtqq2ps ymm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtqq2ps ymm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtqq2ps ymm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtqq2ps ymm15{k7}{z}, [0x0]
vcvtqq2ps ymm15{k7}{z}, [0xFF]
vcvtqq2ps ymm15{k7}{z}, [rel $ + 0x0]
vcvtqq2ps ymm15{k7}{z}, [rel $ + 0xFF]
vcvtqq2ps ymm15{k7}{z}, [rel $ + 0xFFFF]
vcvtqq2ps ymm15{k7}{z}, [rax]
vcvtqq2ps ymm15{k7}{z}, [rax + 0x0]
vcvtqq2ps ymm15{k7}{z}, [rax + 0xFFFF]
vcvtqq2ps ymm15{k7}{z}, [r15 + 0xFFFF]
vcvtqq2ps ymm15{k7}{z}, [rax + rsi * 1  + 0x0]
vcvtqq2ps ymm15{k7}{z}, [rax + rsi + 0xFFFF]
vcvtqq2ps ymm15{k7}{z}, [r15 + rsi + 0xFFFF]
vcvtqq2ps ymm15{k7}{z}, [rax + r15 + 0xFFFF]
vcvtqq2ps ymm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vcvtqq2ps ymm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vcvtqq2ps ymm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vcvtqq2ps ymm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vcvtqq2ps ymm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vcvtqq2ps ymm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vcvtqq2ps ymm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vcvtqq2ps ymm1{k1}{z}, [rax]{1to8}
vcvtqq2ps ymm2{k2}{z}, [rax]{1to8}
vcvtqq2ps ymm15{k7}{z}, [rax]{1to8}