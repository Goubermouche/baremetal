; expect: 62f2fdc95b0c250000000062f2fdc95b0c25ff00000062f2fdc95b0df6ffffff62f2fdc95b0df500000062f2fdc95b0df5ff000062f2fdc95b0862f2fdc95b0862f2fdc95b88ffff000062d2fdc95b8fffff000062f2fdc95b0c3062f2fdc95b8c30ffff000062d2fdc95b8c37ffff000062b2fdc95b8c38ffff000062f2fdc95b8c70f2ff0f0062f2fdc95b8cb0f4ff0f0062f2fdc95b8cf0f8ff0f0062f2fdc95b8cc4f8ff0f0062d2fdc95b8cc7f8ff0f0062b2fdc95b8cfcf8ff0f006292fdc95b8cfef8ff0f0062f2fdca5b14250000000062f2fdca5b1425ff00000062f2fdca5b15f6ffffff62f2fdca5b15f500000062f2fdca5b15f5ff000062f2fdca5b1062f2fdca5b1062f2fdca5b90ffff000062d2fdca5b97ffff000062f2fdca5b143062f2fdca5b9430ffff000062d2fdca5b9437ffff000062b2fdca5b9438ffff000062f2fdca5b9470f2ff0f0062f2fdca5b94b0f4ff0f0062f2fdca5b94f0f8ff0f0062f2fdca5b94c4f8ff0f0062d2fdca5b94c7f8ff0f0062b2fdca5b94fcf8ff0f006292fdca5b94fef8ff0f006272fdcf5b3c25000000006272fdcf5b3c25ff0000006272fdcf5b3df6ffffff6272fdcf5b3df50000006272fdcf5b3df5ff00006272fdcf5b386272fdcf5b386272fdcf5bb8ffff00006252fdcf5bbfffff00006272fdcf5b3c306272fdcf5bbc30ffff00006252fdcf5bbc37ffff00006232fdcf5bbc38ffff00006272fdcf5bbc70f2ff0f006272fdcf5bbcb0f4ff0f006272fdcf5bbcf0f8ff0f006272fdcf5bbcc4f8ff0f006252fdcf5bbcc7f8ff0f006232fdcf5bbcfcf8ff0f006212fdcf5bbcfef8ff0f00

bits 64

vbroadcasti64x4 zmm1{k1}{z}, [0x0]
vbroadcasti64x4 zmm1{k1}{z}, [0xFF]
vbroadcasti64x4 zmm1{k1}{z}, [rel $ + 0x0]
vbroadcasti64x4 zmm1{k1}{z}, [rel $ + 0xFF]
vbroadcasti64x4 zmm1{k1}{z}, [rel $ + 0xFFFF]
vbroadcasti64x4 zmm1{k1}{z}, [rax]
vbroadcasti64x4 zmm1{k1}{z}, [rax + 0x0]
vbroadcasti64x4 zmm1{k1}{z}, [rax + 0xFFFF]
vbroadcasti64x4 zmm1{k1}{z}, [r15 + 0xFFFF]
vbroadcasti64x4 zmm1{k1}{z}, [rax + rsi * 1  + 0x0]
vbroadcasti64x4 zmm1{k1}{z}, [rax + rsi + 0xFFFF]
vbroadcasti64x4 zmm1{k1}{z}, [r15 + rsi + 0xFFFF]
vbroadcasti64x4 zmm1{k1}{z}, [rax + r15 + 0xFFFF]
vbroadcasti64x4 zmm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vbroadcasti64x4 zmm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vbroadcasti64x4 zmm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vbroadcasti64x4 zmm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vbroadcasti64x4 zmm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vbroadcasti64x4 zmm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vbroadcasti64x4 zmm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vbroadcasti64x4 zmm2{k2}{z}, [0x0]
vbroadcasti64x4 zmm2{k2}{z}, [0xFF]
vbroadcasti64x4 zmm2{k2}{z}, [rel $ + 0x0]
vbroadcasti64x4 zmm2{k2}{z}, [rel $ + 0xFF]
vbroadcasti64x4 zmm2{k2}{z}, [rel $ + 0xFFFF]
vbroadcasti64x4 zmm2{k2}{z}, [rax]
vbroadcasti64x4 zmm2{k2}{z}, [rax + 0x0]
vbroadcasti64x4 zmm2{k2}{z}, [rax + 0xFFFF]
vbroadcasti64x4 zmm2{k2}{z}, [r15 + 0xFFFF]
vbroadcasti64x4 zmm2{k2}{z}, [rax + rsi * 1  + 0x0]
vbroadcasti64x4 zmm2{k2}{z}, [rax + rsi + 0xFFFF]
vbroadcasti64x4 zmm2{k2}{z}, [r15 + rsi + 0xFFFF]
vbroadcasti64x4 zmm2{k2}{z}, [rax + r15 + 0xFFFF]
vbroadcasti64x4 zmm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vbroadcasti64x4 zmm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vbroadcasti64x4 zmm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vbroadcasti64x4 zmm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vbroadcasti64x4 zmm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vbroadcasti64x4 zmm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vbroadcasti64x4 zmm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vbroadcasti64x4 zmm15{k7}{z}, [0x0]
vbroadcasti64x4 zmm15{k7}{z}, [0xFF]
vbroadcasti64x4 zmm15{k7}{z}, [rel $ + 0x0]
vbroadcasti64x4 zmm15{k7}{z}, [rel $ + 0xFF]
vbroadcasti64x4 zmm15{k7}{z}, [rel $ + 0xFFFF]
vbroadcasti64x4 zmm15{k7}{z}, [rax]
vbroadcasti64x4 zmm15{k7}{z}, [rax + 0x0]
vbroadcasti64x4 zmm15{k7}{z}, [rax + 0xFFFF]
vbroadcasti64x4 zmm15{k7}{z}, [r15 + 0xFFFF]
vbroadcasti64x4 zmm15{k7}{z}, [rax + rsi * 1  + 0x0]
vbroadcasti64x4 zmm15{k7}{z}, [rax + rsi + 0xFFFF]
vbroadcasti64x4 zmm15{k7}{z}, [r15 + rsi + 0xFFFF]
vbroadcasti64x4 zmm15{k7}{z}, [rax + r15 + 0xFFFF]
vbroadcasti64x4 zmm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vbroadcasti64x4 zmm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vbroadcasti64x4 zmm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vbroadcasti64x4 zmm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vbroadcasti64x4 zmm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vbroadcasti64x4 zmm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vbroadcasti64x4 zmm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
