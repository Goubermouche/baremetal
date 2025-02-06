; expect: 62f27dc9cac862f27dc9cac962d27dc9cacf62927dc9cacf62f27dcacad062f27dcacad162d27dcacad762927dcacad762727dcfcaf862727dcfcaf962527dcfcaff62127dcfcaff62f27dc9ca0c250000000062f27dc9ca0c25ff00000062f27dc9ca0df6ffffff62f27dc9ca0df500000062f27dc9ca0df5ff000062f27dc9ca0862f27dc9ca0862f27dc9ca88ffff000062d27dc9ca8fffff000062f27dc9ca0c3062f27dc9ca8c30ffff000062d27dc9ca8c37ffff000062b27dc9ca8c38ffff000062f27dc9ca8c70f2ff0f0062f27dc9ca8cb0f4ff0f0062f27dc9ca8cf0f8ff0f0062f27dc9ca8cc4f8ff0f0062d27dc9ca8cc7f8ff0f0062b27dc9ca8cfcf8ff0f0062927dc9ca8cfef8ff0f0062f27dcaca14250000000062f27dcaca1425ff00000062f27dcaca15f6ffffff62f27dcaca15f500000062f27dcaca15f5ff000062f27dcaca1062f27dcaca1062f27dcaca90ffff000062d27dcaca97ffff000062f27dcaca143062f27dcaca9430ffff000062d27dcaca9437ffff000062b27dcaca9438ffff000062f27dcaca9470f2ff0f0062f27dcaca94b0f4ff0f0062f27dcaca94f0f8ff0f0062f27dcaca94c4f8ff0f0062d27dcaca94c7f8ff0f0062b27dcaca94fcf8ff0f0062927dcaca94fef8ff0f0062727dcfca3c250000000062727dcfca3c25ff00000062727dcfca3df6ffffff62727dcfca3df500000062727dcfca3df5ff000062727dcfca3862727dcfca3862727dcfcab8ffff000062527dcfcabfffff000062727dcfca3c3062727dcfcabc30ffff000062527dcfcabc37ffff000062327dcfcabc38ffff000062727dcfcabc70f2ff0f0062727dcfcabcb0f4ff0f0062727dcfcabcf0f8ff0f0062727dcfcabcc4f8ff0f0062527dcfcabcc7f8ff0f0062327dcfcabcfcf8ff0f0062127dcfcabcfef8ff0f0062f27dd9ca0862f27ddaca1062727ddfca38

bits 64

vrcp28ps zmm1{k1}{z}, zmm0
vrcp28ps zmm1{k1}{z}, zmm1
vrcp28ps zmm1{k1}{z}, zmm15
vrcp28ps zmm1{k1}{z}, zmm31
vrcp28ps zmm2{k2}{z}, zmm0
vrcp28ps zmm2{k2}{z}, zmm1
vrcp28ps zmm2{k2}{z}, zmm15
vrcp28ps zmm2{k2}{z}, zmm31
vrcp28ps zmm15{k7}{z}, zmm0
vrcp28ps zmm15{k7}{z}, zmm1
vrcp28ps zmm15{k7}{z}, zmm15
vrcp28ps zmm15{k7}{z}, zmm31
vrcp28ps zmm1{k1}{z}, [0x0]
vrcp28ps zmm1{k1}{z}, [0xFF]
vrcp28ps zmm1{k1}{z}, [rel $ + 0x0]
vrcp28ps zmm1{k1}{z}, [rel $ + 0xFF]
vrcp28ps zmm1{k1}{z}, [rel $ + 0xFFFF]
vrcp28ps zmm1{k1}{z}, [rax]
vrcp28ps zmm1{k1}{z}, [rax + 0x0]
vrcp28ps zmm1{k1}{z}, [rax + 0xFFFF]
vrcp28ps zmm1{k1}{z}, [r15 + 0xFFFF]
vrcp28ps zmm1{k1}{z}, [rax + rsi * 1  + 0x0]
vrcp28ps zmm1{k1}{z}, [rax + rsi + 0xFFFF]
vrcp28ps zmm1{k1}{z}, [r15 + rsi + 0xFFFF]
vrcp28ps zmm1{k1}{z}, [rax + r15 + 0xFFFF]
vrcp28ps zmm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vrcp28ps zmm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vrcp28ps zmm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vrcp28ps zmm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vrcp28ps zmm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vrcp28ps zmm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrcp28ps zmm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrcp28ps zmm2{k2}{z}, [0x0]
vrcp28ps zmm2{k2}{z}, [0xFF]
vrcp28ps zmm2{k2}{z}, [rel $ + 0x0]
vrcp28ps zmm2{k2}{z}, [rel $ + 0xFF]
vrcp28ps zmm2{k2}{z}, [rel $ + 0xFFFF]
vrcp28ps zmm2{k2}{z}, [rax]
vrcp28ps zmm2{k2}{z}, [rax + 0x0]
vrcp28ps zmm2{k2}{z}, [rax + 0xFFFF]
vrcp28ps zmm2{k2}{z}, [r15 + 0xFFFF]
vrcp28ps zmm2{k2}{z}, [rax + rsi * 1  + 0x0]
vrcp28ps zmm2{k2}{z}, [rax + rsi + 0xFFFF]
vrcp28ps zmm2{k2}{z}, [r15 + rsi + 0xFFFF]
vrcp28ps zmm2{k2}{z}, [rax + r15 + 0xFFFF]
vrcp28ps zmm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vrcp28ps zmm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vrcp28ps zmm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vrcp28ps zmm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vrcp28ps zmm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vrcp28ps zmm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrcp28ps zmm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrcp28ps zmm15{k7}{z}, [0x0]
vrcp28ps zmm15{k7}{z}, [0xFF]
vrcp28ps zmm15{k7}{z}, [rel $ + 0x0]
vrcp28ps zmm15{k7}{z}, [rel $ + 0xFF]
vrcp28ps zmm15{k7}{z}, [rel $ + 0xFFFF]
vrcp28ps zmm15{k7}{z}, [rax]
vrcp28ps zmm15{k7}{z}, [rax + 0x0]
vrcp28ps zmm15{k7}{z}, [rax + 0xFFFF]
vrcp28ps zmm15{k7}{z}, [r15 + 0xFFFF]
vrcp28ps zmm15{k7}{z}, [rax + rsi * 1  + 0x0]
vrcp28ps zmm15{k7}{z}, [rax + rsi + 0xFFFF]
vrcp28ps zmm15{k7}{z}, [r15 + rsi + 0xFFFF]
vrcp28ps zmm15{k7}{z}, [rax + r15 + 0xFFFF]
vrcp28ps zmm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vrcp28ps zmm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vrcp28ps zmm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vrcp28ps zmm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vrcp28ps zmm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vrcp28ps zmm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrcp28ps zmm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrcp28ps zmm1{k1}{z}, [rax]{1to16}
vrcp28ps zmm2{k2}{z}, [rax]{1to16}
vrcp28ps zmm15{k7}{z}, [rax]{1to16}
