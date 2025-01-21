; expect: 62f57d087e04250000000062f57d087e0c250000000062757d087e3c250000000062657d087e3c250000000062f57d087e0425ff00000062f57d087e0c25ff00000062757d087e3c25ff00000062657d087e3c25ff00000062f57d087e05f6ffffff62f57d087e0df6ffffff62757d087e3df6ffffff62657d087e3df6ffffff62f57d087e05f500000062f57d087e0df500000062757d087e3df500000062657d087e3df500000062f57d087e05f5ff000062f57d087e0df5ff000062757d087e3df5ff000062657d087e3df5ff000062f57d087e0062f57d087e0862757d087e3862657d087e3862f57d087e0062f57d087e0862757d087e3862657d087e3862f57d087e80ffff000062f57d087e88ffff000062757d087eb8ffff000062657d087eb8ffff000062d57d087e87ffff000062d57d087e8fffff000062557d087ebfffff000062457d087ebfffff000062f57d087e043062f57d087e0c3062757d087e3c3062657d087e3c3062f57d087e8430ffff000062f57d087e8c30ffff000062757d087ebc30ffff000062657d087ebc30ffff000062d57d087e8437ffff000062d57d087e8c37ffff000062557d087ebc37ffff000062457d087ebc37ffff000062b57d087e8438ffff000062b57d087e8c38ffff000062357d087ebc38ffff000062257d087ebc38ffff000062f57d087e8470f2ff0f0062f57d087e8c70f2ff0f0062757d087ebc70f2ff0f0062657d087ebc70f2ff0f0062f57d087e84b0f4ff0f0062f57d087e8cb0f4ff0f0062757d087ebcb0f4ff0f0062657d087ebcb0f4ff0f0062f57d087e84f0f8ff0f0062f57d087e8cf0f8ff0f0062757d087ebcf0f8ff0f0062657d087ebcf0f8ff0f0062f57d087e84c4f8ff0f0062f57d087e8cc4f8ff0f0062757d087ebcc4f8ff0f0062657d087ebcc4f8ff0f0062d57d087e84c7f8ff0f0062d57d087e8cc7f8ff0f0062557d087ebcc7f8ff0f0062457d087ebcc7f8ff0f0062b57d087e84fcf8ff0f0062b57d087e8cfcf8ff0f0062357d087ebcfcf8ff0f0062257d087ebcfcf8ff0f0062957d087e84fef8ff0f0062957d087e8cfef8ff0f0062157d087ebcfef8ff0f0062057d087ebcfef8ff0f0062f57d896e0c250000000062f57d896e0c25ff00000062f57d896e0df6ffffff62f57d896e0df500000062f57d896e0df5ff000062f57d896e0862f57d896e0862f57d896e88ffff000062d57d896e8fffff000062f57d896e0c3062f57d896e8c30ffff000062d57d896e8c37ffff000062b57d896e8c38ffff000062f57d896e8c70f2ff0f0062f57d896e8cb0f4ff0f0062f57d896e8cf0f8ff0f0062f57d896e8cc4f8ff0f0062d57d896e8cc7f8ff0f0062b57d896e8cfcf8ff0f0062957d896e8cfef8ff0f0062f57d8a6e14250000000062f57d8a6e1425ff00000062f57d8a6e15f6ffffff62f57d8a6e15f500000062f57d8a6e15f5ff000062f57d8a6e1062f57d8a6e1062f57d8a6e90ffff000062d57d8a6e97ffff000062f57d8a6e143062f57d8a6e9430ffff000062d57d8a6e9437ffff000062b57d8a6e9438ffff000062f57d8a6e9470f2ff0f0062f57d8a6e94b0f4ff0f0062f57d8a6e94f0f8ff0f0062f57d8a6e94c4f8ff0f0062d57d8a6e94c7f8ff0f0062b57d8a6e94fcf8ff0f0062957d8a6e94fef8ff0f0062757d8f6e3c250000000062757d8f6e3c25ff00000062757d8f6e3df6ffffff62757d8f6e3df500000062757d8f6e3df5ff000062757d8f6e3862757d8f6e3862757d8f6eb8ffff000062557d8f6ebfffff000062757d8f6e3c3062757d8f6ebc30ffff000062557d8f6ebc37ffff000062357d8f6ebc38ffff000062757d8f6ebc70f2ff0f0062757d8f6ebcb0f4ff0f0062757d8f6ebcf0f8ff0f0062757d8f6ebcc4f8ff0f0062557d8f6ebcc7f8ff0f0062357d8f6ebcfcf8ff0f0062157d8f6ebcfef8ff0f00

vmovw word [0x0], xmm0
vmovw word [0x0], xmm1
vmovw word [0x0], xmm15
vmovw word [0x0], xmm31
vmovw word [0xFF], xmm0
vmovw word [0xFF], xmm1
vmovw word [0xFF], xmm15
vmovw word [0xFF], xmm31
vmovw word [rel $ + 0x0], xmm0
vmovw word [rel $ + 0x0], xmm1
vmovw word [rel $ + 0x0], xmm15
vmovw word [rel $ + 0x0], xmm31
vmovw word [rel $ + 0xFF], xmm0
vmovw word [rel $ + 0xFF], xmm1
vmovw word [rel $ + 0xFF], xmm15
vmovw word [rel $ + 0xFF], xmm31
vmovw word [rel $ + 0xFFFF], xmm0
vmovw word [rel $ + 0xFFFF], xmm1
vmovw word [rel $ + 0xFFFF], xmm15
vmovw word [rel $ + 0xFFFF], xmm31
vmovw word [rax], xmm0
vmovw word [rax], xmm1
vmovw word [rax], xmm15
vmovw word [rax], xmm31
vmovw word [rax + 0x0], xmm0
vmovw word [rax + 0x0], xmm1
vmovw word [rax + 0x0], xmm15
vmovw word [rax + 0x0], xmm31
vmovw word [rax + 0xFFFF], xmm0
vmovw word [rax + 0xFFFF], xmm1
vmovw word [rax + 0xFFFF], xmm15
vmovw word [rax + 0xFFFF], xmm31
vmovw word [r15 + 0xFFFF], xmm0
vmovw word [r15 + 0xFFFF], xmm1
vmovw word [r15 + 0xFFFF], xmm15
vmovw word [r15 + 0xFFFF], xmm31
vmovw word [rax + rsi * 1  + 0x0], xmm0
vmovw word [rax + rsi * 1  + 0x0], xmm1
vmovw word [rax + rsi * 1  + 0x0], xmm15
vmovw word [rax + rsi * 1  + 0x0], xmm31
vmovw word [rax + rsi + 0xFFFF], xmm0
vmovw word [rax + rsi + 0xFFFF], xmm1
vmovw word [rax + rsi + 0xFFFF], xmm15
vmovw word [rax + rsi + 0xFFFF], xmm31
vmovw word [r15 + rsi + 0xFFFF], xmm0
vmovw word [r15 + rsi + 0xFFFF], xmm1
vmovw word [r15 + rsi + 0xFFFF], xmm15
vmovw word [r15 + rsi + 0xFFFF], xmm31
vmovw word [rax + r15 + 0xFFFF], xmm0
vmovw word [rax + r15 + 0xFFFF], xmm1
vmovw word [rax + r15 + 0xFFFF], xmm15
vmovw word [rax + r15 + 0xFFFF], xmm31
vmovw word [rax + rsi * 2 + 0xFFFF2], xmm0
vmovw word [rax + rsi * 2 + 0xFFFF2], xmm1
vmovw word [rax + rsi * 2 + 0xFFFF2], xmm15
vmovw word [rax + rsi * 2 + 0xFFFF2], xmm31
vmovw word [rax + rsi * 4 + 0xFFFF4], xmm0
vmovw word [rax + rsi * 4 + 0xFFFF4], xmm1
vmovw word [rax + rsi * 4 + 0xFFFF4], xmm15
vmovw word [rax + rsi * 4 + 0xFFFF4], xmm31
vmovw word [rax + rsi * 8 + 0xFFFF8], xmm0
vmovw word [rax + rsi * 8 + 0xFFFF8], xmm1
vmovw word [rax + rsi * 8 + 0xFFFF8], xmm15
vmovw word [rax + rsi * 8 + 0xFFFF8], xmm31
vmovw word [rsp + rax * 8 + 0xFFFF8], xmm0
vmovw word [rsp + rax * 8 + 0xFFFF8], xmm1
vmovw word [rsp + rax * 8 + 0xFFFF8], xmm15
vmovw word [rsp + rax * 8 + 0xFFFF8], xmm31
vmovw word [r15 + rax * 8 + 0xFFFF8], xmm0
vmovw word [r15 + rax * 8 + 0xFFFF8], xmm1
vmovw word [r15 + rax * 8 + 0xFFFF8], xmm15
vmovw word [r15 + rax * 8 + 0xFFFF8], xmm31
vmovw word [rsp + r15 * 8 + 0xFFFF8], xmm0
vmovw word [rsp + r15 * 8 + 0xFFFF8], xmm1
vmovw word [rsp + r15 * 8 + 0xFFFF8], xmm15
vmovw word [rsp + r15 * 8 + 0xFFFF8], xmm31
vmovw word [r14 + r15 * 8 + 0xFFFF8], xmm0
vmovw word [r14 + r15 * 8 + 0xFFFF8], xmm1
vmovw word [r14 + r15 * 8 + 0xFFFF8], xmm15
vmovw word [r14 + r15 * 8 + 0xFFFF8], xmm31
vmovw xmm1{k1}{z}, word [0x0]
vmovw xmm1{k1}{z}, word [0xFF]
vmovw xmm1{k1}{z}, word [rel $ + 0x0]
vmovw xmm1{k1}{z}, word [rel $ + 0xFF]
vmovw xmm1{k1}{z}, word [rel $ + 0xFFFF]
vmovw xmm1{k1}{z}, word [rax]
vmovw xmm1{k1}{z}, word [rax + 0x0]
vmovw xmm1{k1}{z}, word [rax + 0xFFFF]
vmovw xmm1{k1}{z}, word [r15 + 0xFFFF]
vmovw xmm1{k1}{z}, word [rax + rsi * 1  + 0x0]
vmovw xmm1{k1}{z}, word [rax + rsi + 0xFFFF]
vmovw xmm1{k1}{z}, word [r15 + rsi + 0xFFFF]
vmovw xmm1{k1}{z}, word [rax + r15 + 0xFFFF]
vmovw xmm1{k1}{z}, word [rax + rsi * 2 + 0xFFFF2]
vmovw xmm1{k1}{z}, word [rax + rsi * 4 + 0xFFFF4]
vmovw xmm1{k1}{z}, word [rax + rsi * 8 + 0xFFFF8]
vmovw xmm1{k1}{z}, word [rsp + rax * 8 + 0xFFFF8]
vmovw xmm1{k1}{z}, word [r15 + rax * 8 + 0xFFFF8]
vmovw xmm1{k1}{z}, word [rsp + r15 * 8 + 0xFFFF8]
vmovw xmm1{k1}{z}, word [r14 + r15 * 8 + 0xFFFF8]
vmovw xmm2{k2}{z}, word [0x0]
vmovw xmm2{k2}{z}, word [0xFF]
vmovw xmm2{k2}{z}, word [rel $ + 0x0]
vmovw xmm2{k2}{z}, word [rel $ + 0xFF]
vmovw xmm2{k2}{z}, word [rel $ + 0xFFFF]
vmovw xmm2{k2}{z}, word [rax]
vmovw xmm2{k2}{z}, word [rax + 0x0]
vmovw xmm2{k2}{z}, word [rax + 0xFFFF]
vmovw xmm2{k2}{z}, word [r15 + 0xFFFF]
vmovw xmm2{k2}{z}, word [rax + rsi * 1  + 0x0]
vmovw xmm2{k2}{z}, word [rax + rsi + 0xFFFF]
vmovw xmm2{k2}{z}, word [r15 + rsi + 0xFFFF]
vmovw xmm2{k2}{z}, word [rax + r15 + 0xFFFF]
vmovw xmm2{k2}{z}, word [rax + rsi * 2 + 0xFFFF2]
vmovw xmm2{k2}{z}, word [rax + rsi * 4 + 0xFFFF4]
vmovw xmm2{k2}{z}, word [rax + rsi * 8 + 0xFFFF8]
vmovw xmm2{k2}{z}, word [rsp + rax * 8 + 0xFFFF8]
vmovw xmm2{k2}{z}, word [r15 + rax * 8 + 0xFFFF8]
vmovw xmm2{k2}{z}, word [rsp + r15 * 8 + 0xFFFF8]
vmovw xmm2{k2}{z}, word [r14 + r15 * 8 + 0xFFFF8]
vmovw xmm15{k7}{z}, word [0x0]
vmovw xmm15{k7}{z}, word [0xFF]
vmovw xmm15{k7}{z}, word [rel $ + 0x0]
vmovw xmm15{k7}{z}, word [rel $ + 0xFF]
vmovw xmm15{k7}{z}, word [rel $ + 0xFFFF]
vmovw xmm15{k7}{z}, word [rax]
vmovw xmm15{k7}{z}, word [rax + 0x0]
vmovw xmm15{k7}{z}, word [rax + 0xFFFF]
vmovw xmm15{k7}{z}, word [r15 + 0xFFFF]
vmovw xmm15{k7}{z}, word [rax + rsi * 1  + 0x0]
vmovw xmm15{k7}{z}, word [rax + rsi + 0xFFFF]
vmovw xmm15{k7}{z}, word [r15 + rsi + 0xFFFF]
vmovw xmm15{k7}{z}, word [rax + r15 + 0xFFFF]
vmovw xmm15{k7}{z}, word [rax + rsi * 2 + 0xFFFF2]
vmovw xmm15{k7}{z}, word [rax + rsi * 4 + 0xFFFF4]
vmovw xmm15{k7}{z}, word [rax + rsi * 8 + 0xFFFF8]
vmovw xmm15{k7}{z}, word [rsp + rax * 8 + 0xFFFF8]
vmovw xmm15{k7}{z}, word [r15 + rax * 8 + 0xFFFF8]
vmovw xmm15{k7}{z}, word [rsp + r15 * 8 + 0xFFFF8]
vmovw xmm15{k7}{z}, word [r14 + r15 * 8 + 0xFFFF8]