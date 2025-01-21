; expect: 62f2fdc9cac862f2fdc9cac962d2fdc9cacf6292fdc9cacf62f2fdcacad062f2fdcacad162d2fdcacad76292fdcacad76272fdcfcaf86272fdcfcaf96252fdcfcaff6212fdcfcaff62f2fdc9ca0c250000000062f2fdc9ca0c25ff00000062f2fdc9ca0df6ffffff62f2fdc9ca0df500000062f2fdc9ca0df5ff000062f2fdc9ca0862f2fdc9ca0862f2fdc9ca88ffff000062d2fdc9ca8fffff000062f2fdc9ca0c3062f2fdc9ca8c30ffff000062d2fdc9ca8c37ffff000062b2fdc9ca8c38ffff000062f2fdc9ca8c70f2ff0f0062f2fdc9ca8cb0f4ff0f0062f2fdc9ca8cf0f8ff0f0062f2fdc9ca8cc4f8ff0f0062d2fdc9ca8cc7f8ff0f0062b2fdc9ca8cfcf8ff0f006292fdc9ca8cfef8ff0f0062f2fdcaca14250000000062f2fdcaca1425ff00000062f2fdcaca15f6ffffff62f2fdcaca15f500000062f2fdcaca15f5ff000062f2fdcaca1062f2fdcaca1062f2fdcaca90ffff000062d2fdcaca97ffff000062f2fdcaca143062f2fdcaca9430ffff000062d2fdcaca9437ffff000062b2fdcaca9438ffff000062f2fdcaca9470f2ff0f0062f2fdcaca94b0f4ff0f0062f2fdcaca94f0f8ff0f0062f2fdcaca94c4f8ff0f0062d2fdcaca94c7f8ff0f0062b2fdcaca94fcf8ff0f006292fdcaca94fef8ff0f006272fdcfca3c25000000006272fdcfca3c25ff0000006272fdcfca3df6ffffff6272fdcfca3df50000006272fdcfca3df5ff00006272fdcfca386272fdcfca386272fdcfcab8ffff00006252fdcfcabfffff00006272fdcfca3c306272fdcfcabc30ffff00006252fdcfcabc37ffff00006232fdcfcabc38ffff00006272fdcfcabc70f2ff0f006272fdcfcabcb0f4ff0f006272fdcfcabcf0f8ff0f006272fdcfcabcc4f8ff0f006252fdcfcabcc7f8ff0f006232fdcfcabcfcf8ff0f006212fdcfcabcfef8ff0f0062f2fdd9ca0862f2fddaca106272fddfca38

vrcp28pd zmm1{k1}{z}, zmm0
vrcp28pd zmm1{k1}{z}, zmm1
vrcp28pd zmm1{k1}{z}, zmm15
vrcp28pd zmm1{k1}{z}, zmm31
vrcp28pd zmm2{k2}{z}, zmm0
vrcp28pd zmm2{k2}{z}, zmm1
vrcp28pd zmm2{k2}{z}, zmm15
vrcp28pd zmm2{k2}{z}, zmm31
vrcp28pd zmm15{k7}{z}, zmm0
vrcp28pd zmm15{k7}{z}, zmm1
vrcp28pd zmm15{k7}{z}, zmm15
vrcp28pd zmm15{k7}{z}, zmm31
vrcp28pd zmm1{k1}{z}, [0x0]
vrcp28pd zmm1{k1}{z}, [0xFF]
vrcp28pd zmm1{k1}{z}, [rel $ + 0x0]
vrcp28pd zmm1{k1}{z}, [rel $ + 0xFF]
vrcp28pd zmm1{k1}{z}, [rel $ + 0xFFFF]
vrcp28pd zmm1{k1}{z}, [rax]
vrcp28pd zmm1{k1}{z}, [rax + 0x0]
vrcp28pd zmm1{k1}{z}, [rax + 0xFFFF]
vrcp28pd zmm1{k1}{z}, [r15 + 0xFFFF]
vrcp28pd zmm1{k1}{z}, [rax + rsi * 1  + 0x0]
vrcp28pd zmm1{k1}{z}, [rax + rsi + 0xFFFF]
vrcp28pd zmm1{k1}{z}, [r15 + rsi + 0xFFFF]
vrcp28pd zmm1{k1}{z}, [rax + r15 + 0xFFFF]
vrcp28pd zmm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vrcp28pd zmm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vrcp28pd zmm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vrcp28pd zmm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vrcp28pd zmm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vrcp28pd zmm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrcp28pd zmm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrcp28pd zmm2{k2}{z}, [0x0]
vrcp28pd zmm2{k2}{z}, [0xFF]
vrcp28pd zmm2{k2}{z}, [rel $ + 0x0]
vrcp28pd zmm2{k2}{z}, [rel $ + 0xFF]
vrcp28pd zmm2{k2}{z}, [rel $ + 0xFFFF]
vrcp28pd zmm2{k2}{z}, [rax]
vrcp28pd zmm2{k2}{z}, [rax + 0x0]
vrcp28pd zmm2{k2}{z}, [rax + 0xFFFF]
vrcp28pd zmm2{k2}{z}, [r15 + 0xFFFF]
vrcp28pd zmm2{k2}{z}, [rax + rsi * 1  + 0x0]
vrcp28pd zmm2{k2}{z}, [rax + rsi + 0xFFFF]
vrcp28pd zmm2{k2}{z}, [r15 + rsi + 0xFFFF]
vrcp28pd zmm2{k2}{z}, [rax + r15 + 0xFFFF]
vrcp28pd zmm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vrcp28pd zmm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vrcp28pd zmm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vrcp28pd zmm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vrcp28pd zmm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vrcp28pd zmm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrcp28pd zmm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrcp28pd zmm15{k7}{z}, [0x0]
vrcp28pd zmm15{k7}{z}, [0xFF]
vrcp28pd zmm15{k7}{z}, [rel $ + 0x0]
vrcp28pd zmm15{k7}{z}, [rel $ + 0xFF]
vrcp28pd zmm15{k7}{z}, [rel $ + 0xFFFF]
vrcp28pd zmm15{k7}{z}, [rax]
vrcp28pd zmm15{k7}{z}, [rax + 0x0]
vrcp28pd zmm15{k7}{z}, [rax + 0xFFFF]
vrcp28pd zmm15{k7}{z}, [r15 + 0xFFFF]
vrcp28pd zmm15{k7}{z}, [rax + rsi * 1  + 0x0]
vrcp28pd zmm15{k7}{z}, [rax + rsi + 0xFFFF]
vrcp28pd zmm15{k7}{z}, [r15 + rsi + 0xFFFF]
vrcp28pd zmm15{k7}{z}, [rax + r15 + 0xFFFF]
vrcp28pd zmm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vrcp28pd zmm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vrcp28pd zmm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vrcp28pd zmm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vrcp28pd zmm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vrcp28pd zmm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrcp28pd zmm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrcp28pd zmm1{k1}{z}, [rax]{1to8}
vrcp28pd zmm2{k2}{z}, [rax]{1to8}
vrcp28pd zmm15{k7}{z}, [rax]{1to8}