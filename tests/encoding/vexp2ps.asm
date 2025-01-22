; expect: 62f27dc9c8c862f27dc9c8c962d27dc9c8cf62927dc9c8cf62f27dcac8d062f27dcac8d162d27dcac8d762927dcac8d762727dcfc8f862727dcfc8f962527dcfc8ff62127dcfc8ff62f27dc9c80c250000000062f27dc9c80c25ff00000062f27dc9c80df6ffffff62f27dc9c80df500000062f27dc9c80df5ff000062f27dc9c80862f27dc9c80862f27dc9c888ffff000062d27dc9c88fffff000062f27dc9c80c3062f27dc9c88c30ffff000062d27dc9c88c37ffff000062b27dc9c88c38ffff000062f27dc9c88c70f2ff0f0062f27dc9c88cb0f4ff0f0062f27dc9c88cf0f8ff0f0062f27dc9c88cc4f8ff0f0062d27dc9c88cc7f8ff0f0062b27dc9c88cfcf8ff0f0062927dc9c88cfef8ff0f0062f27dcac814250000000062f27dcac81425ff00000062f27dcac815f6ffffff62f27dcac815f500000062f27dcac815f5ff000062f27dcac81062f27dcac81062f27dcac890ffff000062d27dcac897ffff000062f27dcac8143062f27dcac89430ffff000062d27dcac89437ffff000062b27dcac89438ffff000062f27dcac89470f2ff0f0062f27dcac894b0f4ff0f0062f27dcac894f0f8ff0f0062f27dcac894c4f8ff0f0062d27dcac894c7f8ff0f0062b27dcac894fcf8ff0f0062927dcac894fef8ff0f0062727dcfc83c250000000062727dcfc83c25ff00000062727dcfc83df6ffffff62727dcfc83df500000062727dcfc83df5ff000062727dcfc83862727dcfc83862727dcfc8b8ffff000062527dcfc8bfffff000062727dcfc83c3062727dcfc8bc30ffff000062527dcfc8bc37ffff000062327dcfc8bc38ffff000062727dcfc8bc70f2ff0f0062727dcfc8bcb0f4ff0f0062727dcfc8bcf0f8ff0f0062727dcfc8bcc4f8ff0f0062527dcfc8bcc7f8ff0f0062327dcfc8bcfcf8ff0f0062127dcfc8bcfef8ff0f0062f27dd9c80862f27ddac81062727ddfc838

vexp2ps zmm1{k1}{z}, zmm0
vexp2ps zmm1{k1}{z}, zmm1
vexp2ps zmm1{k1}{z}, zmm15
vexp2ps zmm1{k1}{z}, zmm31
vexp2ps zmm2{k2}{z}, zmm0
vexp2ps zmm2{k2}{z}, zmm1
vexp2ps zmm2{k2}{z}, zmm15
vexp2ps zmm2{k2}{z}, zmm31
vexp2ps zmm15{k7}{z}, zmm0
vexp2ps zmm15{k7}{z}, zmm1
vexp2ps zmm15{k7}{z}, zmm15
vexp2ps zmm15{k7}{z}, zmm31
vexp2ps zmm1{k1}{z}, [0x0]
vexp2ps zmm1{k1}{z}, [0xFF]
vexp2ps zmm1{k1}{z}, [rel $ + 0x0]
vexp2ps zmm1{k1}{z}, [rel $ + 0xFF]
vexp2ps zmm1{k1}{z}, [rel $ + 0xFFFF]
vexp2ps zmm1{k1}{z}, [rax]
vexp2ps zmm1{k1}{z}, [rax + 0x0]
vexp2ps zmm1{k1}{z}, [rax + 0xFFFF]
vexp2ps zmm1{k1}{z}, [r15 + 0xFFFF]
vexp2ps zmm1{k1}{z}, [rax + rsi * 1  + 0x0]
vexp2ps zmm1{k1}{z}, [rax + rsi + 0xFFFF]
vexp2ps zmm1{k1}{z}, [r15 + rsi + 0xFFFF]
vexp2ps zmm1{k1}{z}, [rax + r15 + 0xFFFF]
vexp2ps zmm1{k1}{z}, [rax + rsi * 2 + 0xFFFF2]
vexp2ps zmm1{k1}{z}, [rax + rsi * 4 + 0xFFFF4]
vexp2ps zmm1{k1}{z}, [rax + rsi * 8 + 0xFFFF8]
vexp2ps zmm1{k1}{z}, [rsp + rax * 8 + 0xFFFF8]
vexp2ps zmm1{k1}{z}, [r15 + rax * 8 + 0xFFFF8]
vexp2ps zmm1{k1}{z}, [rsp + r15 * 8 + 0xFFFF8]
vexp2ps zmm1{k1}{z}, [r14 + r15 * 8 + 0xFFFF8]
vexp2ps zmm2{k2}{z}, [0x0]
vexp2ps zmm2{k2}{z}, [0xFF]
vexp2ps zmm2{k2}{z}, [rel $ + 0x0]
vexp2ps zmm2{k2}{z}, [rel $ + 0xFF]
vexp2ps zmm2{k2}{z}, [rel $ + 0xFFFF]
vexp2ps zmm2{k2}{z}, [rax]
vexp2ps zmm2{k2}{z}, [rax + 0x0]
vexp2ps zmm2{k2}{z}, [rax + 0xFFFF]
vexp2ps zmm2{k2}{z}, [r15 + 0xFFFF]
vexp2ps zmm2{k2}{z}, [rax + rsi * 1  + 0x0]
vexp2ps zmm2{k2}{z}, [rax + rsi + 0xFFFF]
vexp2ps zmm2{k2}{z}, [r15 + rsi + 0xFFFF]
vexp2ps zmm2{k2}{z}, [rax + r15 + 0xFFFF]
vexp2ps zmm2{k2}{z}, [rax + rsi * 2 + 0xFFFF2]
vexp2ps zmm2{k2}{z}, [rax + rsi * 4 + 0xFFFF4]
vexp2ps zmm2{k2}{z}, [rax + rsi * 8 + 0xFFFF8]
vexp2ps zmm2{k2}{z}, [rsp + rax * 8 + 0xFFFF8]
vexp2ps zmm2{k2}{z}, [r15 + rax * 8 + 0xFFFF8]
vexp2ps zmm2{k2}{z}, [rsp + r15 * 8 + 0xFFFF8]
vexp2ps zmm2{k2}{z}, [r14 + r15 * 8 + 0xFFFF8]
vexp2ps zmm15{k7}{z}, [0x0]
vexp2ps zmm15{k7}{z}, [0xFF]
vexp2ps zmm15{k7}{z}, [rel $ + 0x0]
vexp2ps zmm15{k7}{z}, [rel $ + 0xFF]
vexp2ps zmm15{k7}{z}, [rel $ + 0xFFFF]
vexp2ps zmm15{k7}{z}, [rax]
vexp2ps zmm15{k7}{z}, [rax + 0x0]
vexp2ps zmm15{k7}{z}, [rax + 0xFFFF]
vexp2ps zmm15{k7}{z}, [r15 + 0xFFFF]
vexp2ps zmm15{k7}{z}, [rax + rsi * 1  + 0x0]
vexp2ps zmm15{k7}{z}, [rax + rsi + 0xFFFF]
vexp2ps zmm15{k7}{z}, [r15 + rsi + 0xFFFF]
vexp2ps zmm15{k7}{z}, [rax + r15 + 0xFFFF]
vexp2ps zmm15{k7}{z}, [rax + rsi * 2 + 0xFFFF2]
vexp2ps zmm15{k7}{z}, [rax + rsi * 4 + 0xFFFF4]
vexp2ps zmm15{k7}{z}, [rax + rsi * 8 + 0xFFFF8]
vexp2ps zmm15{k7}{z}, [rsp + rax * 8 + 0xFFFF8]
vexp2ps zmm15{k7}{z}, [r15 + rax * 8 + 0xFFFF8]
vexp2ps zmm15{k7}{z}, [rsp + r15 * 8 + 0xFFFF8]
vexp2ps zmm15{k7}{z}, [r14 + r15 * 8 + 0xFFFF8]
vexp2ps zmm1{k1}{z}, [rax]{1to16}
vexp2ps zmm2{k2}{z}, [rax]{1to16}
vexp2ps zmm15{k7}{z}, [rax]{1to16}