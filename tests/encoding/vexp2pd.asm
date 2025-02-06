; expect: 62f2fdc9c8c862f2fdc9c8c962d2fdc9c8cf6292fdc9c8cf62f2fdcac8d062f2fdcac8d162d2fdcac8d76292fdcac8d76272fdcfc8f86272fdcfc8f96252fdcfc8ff6212fdcfc8ff62f2fdc9c80c250000000062f2fdc9c80c25ff00000062f2fdc9c80df6ffffff62f2fdc9c80df500000062f2fdc9c80df5ff000062f2fdc9c80862f2fdc9c80862f2fdc9c888ffff000062d2fdc9c88fffff000062f2fdc9c80c3062f2fdc9c88c30ffff000062d2fdc9c88c37ffff000062b2fdc9c88c38ffff000062f2fdc9c88c70f2ff0f0062f2fdc9c88cb0f4ff0f0062f2fdc9c88cf0f8ff0f0062f2fdc9c88cc4f8ff0f0062d2fdc9c88cc7f8ff0f0062b2fdc9c88cfcf8ff0f006292fdc9c88cfef8ff0f0062f2fdcac814250000000062f2fdcac81425ff00000062f2fdcac815f6ffffff62f2fdcac815f500000062f2fdcac815f5ff000062f2fdcac81062f2fdcac81062f2fdcac890ffff000062d2fdcac897ffff000062f2fdcac8143062f2fdcac89430ffff000062d2fdcac89437ffff000062b2fdcac89438ffff000062f2fdcac89470f2ff0f0062f2fdcac894b0f4ff0f0062f2fdcac894f0f8ff0f0062f2fdcac894c4f8ff0f0062d2fdcac894c7f8ff0f0062b2fdcac894fcf8ff0f006292fdcac894fef8ff0f006272fdcfc83c25000000006272fdcfc83c25ff0000006272fdcfc83df6ffffff6272fdcfc83df50000006272fdcfc83df5ff00006272fdcfc8386272fdcfc8386272fdcfc8b8ffff00006252fdcfc8bfffff00006272fdcfc83c306272fdcfc8bc30ffff00006252fdcfc8bc37ffff00006232fdcfc8bc38ffff00006272fdcfc8bc70f2ff0f006272fdcfc8bcb0f4ff0f006272fdcfc8bcf0f8ff0f006272fdcfc8bcc4f8ff0f006252fdcfc8bcc7f8ff0f006232fdcfc8bcfcf8ff0f006212fdcfc8bcfef8ff0f0062f2fdd9c80862f2fddac8106272fddfc838

bits 64

vexp2pd zmm1{k1}{z}, zmm0
vexp2pd zmm1{k1}{z}, zmm1
vexp2pd zmm1{k1}{z}, zmm15
vexp2pd zmm1{k1}{z}, zmm31
vexp2pd zmm2{k2}{z}, zmm0
vexp2pd zmm2{k2}{z}, zmm1
vexp2pd zmm2{k2}{z}, zmm15
vexp2pd zmm2{k2}{z}, zmm31
vexp2pd zmm15{k7}{z}, zmm0
vexp2pd zmm15{k7}{z}, zmm1
vexp2pd zmm15{k7}{z}, zmm15
vexp2pd zmm15{k7}{z}, zmm31
vexp2pd zmm1{k1}{z}, [0x0]
vexp2pd zmm1{k1}{z}, [0xFF]
vexp2pd zmm1{k1}{z}, [rel $ + 0x0]
vexp2pd zmm1{k1}{z}, [rel $ + 0xFF]
vexp2pd zmm1{k1}{z}, [rel $ + 0xFFFF]
vexp2pd zmm1{k1}{z}, [rax]
vexp2pd zmm1{k1}{z}, [rax + 0x0]
vexp2pd zmm1{k1}{z}, [rax + 0xFFFF]
vexp2pd zmm1{k1}{z}, [r15 + 0xFFFF]
vexp2pd zmm1{k1}{z}, [rax + rsi * 1  + 0x0]
vexp2pd zmm1{k1}{z}, [rax + rsi + 0xFFFF]
vexp2pd zmm1{k1}{z}, [r15 + rsi + 0xFFFF]
vexp2pd zmm1{k1}{z}, [rax + r15 + 0xFFFF]
vexp2pd zmm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vexp2pd zmm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vexp2pd zmm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vexp2pd zmm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vexp2pd zmm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vexp2pd zmm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vexp2pd zmm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vexp2pd zmm2{k2}{z}, [0x0]
vexp2pd zmm2{k2}{z}, [0xFF]
vexp2pd zmm2{k2}{z}, [rel $ + 0x0]
vexp2pd zmm2{k2}{z}, [rel $ + 0xFF]
vexp2pd zmm2{k2}{z}, [rel $ + 0xFFFF]
vexp2pd zmm2{k2}{z}, [rax]
vexp2pd zmm2{k2}{z}, [rax + 0x0]
vexp2pd zmm2{k2}{z}, [rax + 0xFFFF]
vexp2pd zmm2{k2}{z}, [r15 + 0xFFFF]
vexp2pd zmm2{k2}{z}, [rax + rsi * 1  + 0x0]
vexp2pd zmm2{k2}{z}, [rax + rsi + 0xFFFF]
vexp2pd zmm2{k2}{z}, [r15 + rsi + 0xFFFF]
vexp2pd zmm2{k2}{z}, [rax + r15 + 0xFFFF]
vexp2pd zmm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vexp2pd zmm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vexp2pd zmm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vexp2pd zmm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vexp2pd zmm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vexp2pd zmm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vexp2pd zmm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vexp2pd zmm15{k7}{z}, [0x0]
vexp2pd zmm15{k7}{z}, [0xFF]
vexp2pd zmm15{k7}{z}, [rel $ + 0x0]
vexp2pd zmm15{k7}{z}, [rel $ + 0xFF]
vexp2pd zmm15{k7}{z}, [rel $ + 0xFFFF]
vexp2pd zmm15{k7}{z}, [rax]
vexp2pd zmm15{k7}{z}, [rax + 0x0]
vexp2pd zmm15{k7}{z}, [rax + 0xFFFF]
vexp2pd zmm15{k7}{z}, [r15 + 0xFFFF]
vexp2pd zmm15{k7}{z}, [rax + rsi * 1  + 0x0]
vexp2pd zmm15{k7}{z}, [rax + rsi + 0xFFFF]
vexp2pd zmm15{k7}{z}, [r15 + rsi + 0xFFFF]
vexp2pd zmm15{k7}{z}, [rax + r15 + 0xFFFF]
vexp2pd zmm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vexp2pd zmm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vexp2pd zmm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vexp2pd zmm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vexp2pd zmm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vexp2pd zmm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vexp2pd zmm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vexp2pd zmm1{k1}{z}, [rax]{1to8}
vexp2pd zmm2{k2}{z}, [rax]{1to8}
vexp2pd zmm15{k7}{z}, [rax]{1to8}
