; expect: 62f2fdc9ccc862f2fdc9ccc962d2fdc9cccf6292fdc9cccf62f2fdcaccd062f2fdcaccd162d2fdcaccd76292fdcaccd76272fdcfccf86272fdcfccf96252fdcfccff6212fdcfccff62f2fdc9cc0c250000000062f2fdc9cc0c25ff00000062f2fdc9cc0df6ffffff62f2fdc9cc0df500000062f2fdc9cc0df5ff000062f2fdc9cc0862f2fdc9cc0862f2fdc9cc88ffff000062d2fdc9cc8fffff000062f2fdc9cc0c3062f2fdc9cc8c30ffff000062d2fdc9cc8c37ffff000062b2fdc9cc8c38ffff000062f2fdc9cc8c70f2ff0f0062f2fdc9cc8cb0f4ff0f0062f2fdc9cc8cf0f8ff0f0062f2fdc9cc8cc4f8ff0f0062d2fdc9cc8cc7f8ff0f0062b2fdc9cc8cfcf8ff0f006292fdc9cc8cfef8ff0f0062f2fdcacc14250000000062f2fdcacc1425ff00000062f2fdcacc15f6ffffff62f2fdcacc15f500000062f2fdcacc15f5ff000062f2fdcacc1062f2fdcacc1062f2fdcacc90ffff000062d2fdcacc97ffff000062f2fdcacc143062f2fdcacc9430ffff000062d2fdcacc9437ffff000062b2fdcacc9438ffff000062f2fdcacc9470f2ff0f0062f2fdcacc94b0f4ff0f0062f2fdcacc94f0f8ff0f0062f2fdcacc94c4f8ff0f0062d2fdcacc94c7f8ff0f0062b2fdcacc94fcf8ff0f006292fdcacc94fef8ff0f006272fdcfcc3c25000000006272fdcfcc3c25ff0000006272fdcfcc3df6ffffff6272fdcfcc3df50000006272fdcfcc3df5ff00006272fdcfcc386272fdcfcc386272fdcfccb8ffff00006252fdcfccbfffff00006272fdcfcc3c306272fdcfccbc30ffff00006252fdcfccbc37ffff00006232fdcfccbc38ffff00006272fdcfccbc70f2ff0f006272fdcfccbcb0f4ff0f006272fdcfccbcf0f8ff0f006272fdcfccbcc4f8ff0f006252fdcfccbcc7f8ff0f006232fdcfccbcfcf8ff0f006212fdcfccbcfef8ff0f0062f2fdd9cc0862f2fddacc106272fddfcc38

vrsqrt28pd zmm1{k1}{z}, zmm0
vrsqrt28pd zmm1{k1}{z}, zmm1
vrsqrt28pd zmm1{k1}{z}, zmm15
vrsqrt28pd zmm1{k1}{z}, zmm31
vrsqrt28pd zmm2{k2}{z}, zmm0
vrsqrt28pd zmm2{k2}{z}, zmm1
vrsqrt28pd zmm2{k2}{z}, zmm15
vrsqrt28pd zmm2{k2}{z}, zmm31
vrsqrt28pd zmm15{k7}{z}, zmm0
vrsqrt28pd zmm15{k7}{z}, zmm1
vrsqrt28pd zmm15{k7}{z}, zmm15
vrsqrt28pd zmm15{k7}{z}, zmm31
vrsqrt28pd zmm1{k1}{z}, [0x0]
vrsqrt28pd zmm1{k1}{z}, [0xFF]
vrsqrt28pd zmm1{k1}{z}, [rel $ + 0x0]
vrsqrt28pd zmm1{k1}{z}, [rel $ + 0xFF]
vrsqrt28pd zmm1{k1}{z}, [rel $ + 0xFFFF]
vrsqrt28pd zmm1{k1}{z}, [rax]
vrsqrt28pd zmm1{k1}{z}, [rax + 0x0]
vrsqrt28pd zmm1{k1}{z}, [rax + 0xFFFF]
vrsqrt28pd zmm1{k1}{z}, [r15 + 0xFFFF]
vrsqrt28pd zmm1{k1}{z}, [rax + rsi * 1  + 0x0]
vrsqrt28pd zmm1{k1}{z}, [rax + rsi + 0xFFFF]
vrsqrt28pd zmm1{k1}{z}, [r15 + rsi + 0xFFFF]
vrsqrt28pd zmm1{k1}{z}, [rax + r15 + 0xFFFF]
vrsqrt28pd zmm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vrsqrt28pd zmm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vrsqrt28pd zmm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vrsqrt28pd zmm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vrsqrt28pd zmm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vrsqrt28pd zmm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrsqrt28pd zmm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrsqrt28pd zmm2{k2}{z}, [0x0]
vrsqrt28pd zmm2{k2}{z}, [0xFF]
vrsqrt28pd zmm2{k2}{z}, [rel $ + 0x0]
vrsqrt28pd zmm2{k2}{z}, [rel $ + 0xFF]
vrsqrt28pd zmm2{k2}{z}, [rel $ + 0xFFFF]
vrsqrt28pd zmm2{k2}{z}, [rax]
vrsqrt28pd zmm2{k2}{z}, [rax + 0x0]
vrsqrt28pd zmm2{k2}{z}, [rax + 0xFFFF]
vrsqrt28pd zmm2{k2}{z}, [r15 + 0xFFFF]
vrsqrt28pd zmm2{k2}{z}, [rax + rsi * 1  + 0x0]
vrsqrt28pd zmm2{k2}{z}, [rax + rsi + 0xFFFF]
vrsqrt28pd zmm2{k2}{z}, [r15 + rsi + 0xFFFF]
vrsqrt28pd zmm2{k2}{z}, [rax + r15 + 0xFFFF]
vrsqrt28pd zmm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vrsqrt28pd zmm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vrsqrt28pd zmm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vrsqrt28pd zmm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vrsqrt28pd zmm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vrsqrt28pd zmm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrsqrt28pd zmm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrsqrt28pd zmm15{k7}{z}, [0x0]
vrsqrt28pd zmm15{k7}{z}, [0xFF]
vrsqrt28pd zmm15{k7}{z}, [rel $ + 0x0]
vrsqrt28pd zmm15{k7}{z}, [rel $ + 0xFF]
vrsqrt28pd zmm15{k7}{z}, [rel $ + 0xFFFF]
vrsqrt28pd zmm15{k7}{z}, [rax]
vrsqrt28pd zmm15{k7}{z}, [rax + 0x0]
vrsqrt28pd zmm15{k7}{z}, [rax + 0xFFFF]
vrsqrt28pd zmm15{k7}{z}, [r15 + 0xFFFF]
vrsqrt28pd zmm15{k7}{z}, [rax + rsi * 1  + 0x0]
vrsqrt28pd zmm15{k7}{z}, [rax + rsi + 0xFFFF]
vrsqrt28pd zmm15{k7}{z}, [r15 + rsi + 0xFFFF]
vrsqrt28pd zmm15{k7}{z}, [rax + r15 + 0xFFFF]
vrsqrt28pd zmm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vrsqrt28pd zmm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vrsqrt28pd zmm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vrsqrt28pd zmm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vrsqrt28pd zmm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vrsqrt28pd zmm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vrsqrt28pd zmm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vrsqrt28pd zmm1{k1}{z}, [rax]{1to8}
vrsqrt28pd zmm2{k2}{z}, [rax]{1to8}
vrsqrt28pd zmm15{k7}{z}, [rax]{1to8}