; expect: 62f27dc9ccc862f27dc9ccc962d27dc9cccf62927dc9cccf62f27dcaccd062f27dcaccd162d27dcaccd762927dcaccd762727dcfccf862727dcfccf962527dcfccff62127dcfccff62f27dc9cc0c250000000062f27dc9cc0c25ff00000062f27dc9cc0df6ffffff62f27dc9cc0df500000062f27dc9cc0df5ff000062f27dc9cc0862f27dc9cc0862f27dc9cc88ffff000062d27dc9cc8fffff000062f27dc9cc0c3062f27dc9cc8c30ffff000062d27dc9cc8c37ffff000062b27dc9cc8c38ffff000062f27dc9cc8c70f2ff0f0062f27dc9cc8cb0f4ff0f0062f27dc9cc8cf0f8ff0f0062f27dc9cc8cc4f8ff0f0062d27dc9cc8cc7f8ff0f0062b27dc9cc8cfcf8ff0f0062927dc9cc8cfef8ff0f0062f27dcacc14250000000062f27dcacc1425ff00000062f27dcacc15f6ffffff62f27dcacc15f500000062f27dcacc15f5ff000062f27dcacc1062f27dcacc1062f27dcacc90ffff000062d27dcacc97ffff000062f27dcacc143062f27dcacc9430ffff000062d27dcacc9437ffff000062b27dcacc9438ffff000062f27dcacc9470f2ff0f0062f27dcacc94b0f4ff0f0062f27dcacc94f0f8ff0f0062f27dcacc94c4f8ff0f0062d27dcacc94c7f8ff0f0062b27dcacc94fcf8ff0f0062927dcacc94fef8ff0f0062727dcfcc3c250000000062727dcfcc3c25ff00000062727dcfcc3df6ffffff62727dcfcc3df500000062727dcfcc3df5ff000062727dcfcc3862727dcfcc3862727dcfccb8ffff000062527dcfccbfffff000062727dcfcc3c3062727dcfccbc30ffff000062527dcfccbc37ffff000062327dcfccbc38ffff000062727dcfccbc70f2ff0f0062727dcfccbcb0f4ff0f0062727dcfccbcf0f8ff0f0062727dcfccbcc4f8ff0f0062527dcfccbcc7f8ff0f0062327dcfccbcfcf8ff0f0062127dcfccbcfef8ff0f0062f27dd9cc0862f27ddacc1062727ddfcc38

vrsqrt28ps zmm1{k1}{z}, zmm0
vrsqrt28ps zmm1{k1}{z}, zmm1
vrsqrt28ps zmm1{k1}{z}, zmm15
vrsqrt28ps zmm1{k1}{z}, zmm31
vrsqrt28ps zmm2{k2}{z}, zmm0
vrsqrt28ps zmm2{k2}{z}, zmm1
vrsqrt28ps zmm2{k2}{z}, zmm15
vrsqrt28ps zmm2{k2}{z}, zmm31
vrsqrt28ps zmm15{k7}{z}, zmm0
vrsqrt28ps zmm15{k7}{z}, zmm1
vrsqrt28ps zmm15{k7}{z}, zmm15
vrsqrt28ps zmm15{k7}{z}, zmm31
vrsqrt28ps zmm1{k1}{z}, [0x0]
vrsqrt28ps zmm1{k1}{z}, [0xFF]
vrsqrt28ps zmm1{k1}{z}, [rel $ + 0x0]
vrsqrt28ps zmm1{k1}{z}, [rel $ + 0xFF]
vrsqrt28ps zmm1{k1}{z}, [rel $ + 0xFFFF]
vrsqrt28ps zmm1{k1}{z}, [rax]
vrsqrt28ps zmm1{k1}{z}, [rax + 0x0]
vrsqrt28ps zmm1{k1}{z}, [rax + 0xFFFF]
vrsqrt28ps zmm1{k1}{z}, [r15 + 0xFFFF]
vrsqrt28ps zmm1{k1}{z}, [rax + rsi * 1  + 0x0]
vrsqrt28ps zmm1{k1}{z}, [rax + rsi + 0xFFFF]
vrsqrt28ps zmm1{k1}{z}, [r15 + rsi + 0xFFFF]
vrsqrt28ps zmm1{k1}{z}, [rax + r15 + 0xFFFF]
vrsqrt28ps zmm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vrsqrt28ps zmm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vrsqrt28ps zmm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vrsqrt28ps zmm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vrsqrt28ps zmm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vrsqrt28ps zmm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrsqrt28ps zmm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrsqrt28ps zmm2{k2}{z}, [0x0]
vrsqrt28ps zmm2{k2}{z}, [0xFF]
vrsqrt28ps zmm2{k2}{z}, [rel $ + 0x0]
vrsqrt28ps zmm2{k2}{z}, [rel $ + 0xFF]
vrsqrt28ps zmm2{k2}{z}, [rel $ + 0xFFFF]
vrsqrt28ps zmm2{k2}{z}, [rax]
vrsqrt28ps zmm2{k2}{z}, [rax + 0x0]
vrsqrt28ps zmm2{k2}{z}, [rax + 0xFFFF]
vrsqrt28ps zmm2{k2}{z}, [r15 + 0xFFFF]
vrsqrt28ps zmm2{k2}{z}, [rax + rsi * 1  + 0x0]
vrsqrt28ps zmm2{k2}{z}, [rax + rsi + 0xFFFF]
vrsqrt28ps zmm2{k2}{z}, [r15 + rsi + 0xFFFF]
vrsqrt28ps zmm2{k2}{z}, [rax + r15 + 0xFFFF]
vrsqrt28ps zmm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vrsqrt28ps zmm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vrsqrt28ps zmm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vrsqrt28ps zmm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vrsqrt28ps zmm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vrsqrt28ps zmm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrsqrt28ps zmm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrsqrt28ps zmm15{k7}{z}, [0x0]
vrsqrt28ps zmm15{k7}{z}, [0xFF]
vrsqrt28ps zmm15{k7}{z}, [rel $ + 0x0]
vrsqrt28ps zmm15{k7}{z}, [rel $ + 0xFF]
vrsqrt28ps zmm15{k7}{z}, [rel $ + 0xFFFF]
vrsqrt28ps zmm15{k7}{z}, [rax]
vrsqrt28ps zmm15{k7}{z}, [rax + 0x0]
vrsqrt28ps zmm15{k7}{z}, [rax + 0xFFFF]
vrsqrt28ps zmm15{k7}{z}, [r15 + 0xFFFF]
vrsqrt28ps zmm15{k7}{z}, [rax + rsi * 1  + 0x0]
vrsqrt28ps zmm15{k7}{z}, [rax + rsi + 0xFFFF]
vrsqrt28ps zmm15{k7}{z}, [r15 + rsi + 0xFFFF]
vrsqrt28ps zmm15{k7}{z}, [rax + r15 + 0xFFFF]
vrsqrt28ps zmm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vrsqrt28ps zmm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vrsqrt28ps zmm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vrsqrt28ps zmm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vrsqrt28ps zmm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vrsqrt28ps zmm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrsqrt28ps zmm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrsqrt28ps zmm1{k1}{z}, [rax]{1to16}
vrsqrt28ps zmm2{k2}{z}, [rax]{1to16}
vrsqrt28ps zmm15{k7}{z}, [rax]{1to16}