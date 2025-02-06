; expect: 660f7ec1660f7ec966440f7ef9660f7ec3660f7ecb66440f7efb66410f7ec766410f7ecf66450f7eff660f7e042500000000660f7e0c250000000066440f7e3c2500000000660f7e0425ff000000660f7e0c25ff00000066440f7e3c25ff000000660f7e05f8ffffff660f7e0df8ffffff66440f7e3df7ffffff660f7e05f7000000660f7e0df700000066440f7e3df6000000660f7e05f7ff0000660f7e0df7ff000066440f7e3df6ff0000660f7e00660f7e0866440f7e38660f7e00660f7e0866440f7e38660f7e80ffff0000660f7e88ffff000066440f7eb8ffff000066410f7e87ffff000066410f7e8fffff000066450f7ebfffff0000660f7e0430660f7e0c3066440f7e3c30660f7e8430ffff0000660f7e8c30ffff000066440f7ebc30ffff000066410f7e8437ffff000066410f7e8c37ffff000066450f7ebc37ffff000066420f7e8438ffff000066420f7e8c38ffff000066460f7ebc38ffff0000660f7e8470f2ff0f00660f7e8c70f2ff0f0066440f7ebc70f2ff0f00660f7e84b0f4ff0f00660f7e8cb0f4ff0f0066440f7ebcb0f4ff0f00660f7e84f0f8ff0f00660f7e8cf0f8ff0f0066440f7ebcf0f8ff0f00660f7e84c4f8ff0f00660f7e8cc4f8ff0f0066440f7ebcc4f8ff0f0066410f7e84c7f8ff0f0066410f7e8cc7f8ff0f0066450f7ebcc7f8ff0f0066420f7e84fcf8ff0f0066420f7e8cfcf8ff0f0066460f7ebcfcf8ff0f0066430f7e84fef8ff0f0066430f7e8cfef8ff0f0066470f7ebcfef8ff0f00660f6ec1660f6ec366410f6ec7660f6ec9660f6ecb66410f6ecf66440f6ef966440f6efb66450f6eff660f6e042500000000660f6e0425ff000000660f6e05f8ffffff660f6e05f7000000660f6e05f7ff0000660f6e00660f6e00660f6e80ffff000066410f6e87ffff0000660f6e0430660f6e8430ffff000066410f6e8437ffff000066420f6e8438ffff0000660f6e8470f2ff0f00660f6e84b0f4ff0f00660f6e84f0f8ff0f00660f6e84c4f8ff0f0066410f6e84c7f8ff0f0066420f6e84fcf8ff0f0066430f6e84fef8ff0f00660f6e0c2500000000660f6e0c25ff000000660f6e0df8ffffff660f6e0df7000000660f6e0df7ff0000660f6e08660f6e08660f6e88ffff000066410f6e8fffff0000660f6e0c30660f6e8c30ffff000066410f6e8c37ffff000066420f6e8c38ffff0000660f6e8c70f2ff0f00660f6e8cb0f4ff0f00660f6e8cf0f8ff0f00660f6e8cc4f8ff0f0066410f6e8cc7f8ff0f0066420f6e8cfcf8ff0f0066430f6e8cfef8ff0f0066440f6e3c250000000066440f6e3c25ff00000066440f6e3df7ffffff66440f6e3df600000066440f6e3df6ff000066440f6e3866440f6e3866440f6eb8ffff000066450f6ebfffff000066440f6e3c3066440f6ebc30ffff000066450f6ebc37ffff000066460f6ebc38ffff000066440f6ebc70f2ff0f0066440f6ebcb0f4ff0f0066440f6ebcf0f8ff0f0066440f6ebcc4f8ff0f0066450f6ebcc7f8ff0f0066460f6ebcfcf8ff0f0066470f6ebcfef8ff0f00

bits 64

movd ecx, xmm0
movd ecx, xmm1
movd ecx, xmm15
movd ebx, xmm0
movd ebx, xmm1
movd ebx, xmm15
movd r15d, xmm0
movd r15d, xmm1
movd r15d, xmm15
movd dword [0x0], xmm0
movd dword [0x0], xmm1
movd dword [0x0], xmm15
movd dword [0xFF], xmm0
movd dword [0xFF], xmm1
movd dword [0xFF], xmm15
movd dword [rel $ + 0x0], xmm0
movd dword [rel $ + 0x0], xmm1
movd dword [rel $ + 0x0], xmm15
movd dword [rel $ + 0xFF], xmm0
movd dword [rel $ + 0xFF], xmm1
movd dword [rel $ + 0xFF], xmm15
movd dword [rel $ + 0xFFFF], xmm0
movd dword [rel $ + 0xFFFF], xmm1
movd dword [rel $ + 0xFFFF], xmm15
movd dword [rax], xmm0
movd dword [rax], xmm1
movd dword [rax], xmm15
movd dword [rax + 0x0], xmm0
movd dword [rax + 0x0], xmm1
movd dword [rax + 0x0], xmm15
movd dword [rax + 0xFFFF], xmm0
movd dword [rax + 0xFFFF], xmm1
movd dword [rax + 0xFFFF], xmm15
movd dword [r15 + 0xFFFF], xmm0
movd dword [r15 + 0xFFFF], xmm1
movd dword [r15 + 0xFFFF], xmm15
movd dword [rax + rsi * 1  + 0x0], xmm0
movd dword [rax + rsi * 1  + 0x0], xmm1
movd dword [rax + rsi * 1  + 0x0], xmm15
movd dword [rax + rsi + 0xFFFF], xmm0
movd dword [rax + rsi + 0xFFFF], xmm1
movd dword [rax + rsi + 0xFFFF], xmm15
movd dword [r15 + rsi + 0xFFFF], xmm0
movd dword [r15 + rsi + 0xFFFF], xmm1
movd dword [r15 + rsi + 0xFFFF], xmm15
movd dword [rax + r15 + 0xFFFF], xmm0
movd dword [rax + r15 + 0xFFFF], xmm1
movd dword [rax + r15 + 0xFFFF], xmm15
movd dword [rax + rsi * 2 + 0xFFFF2], xmm0
movd dword [rax + rsi * 2 + 0xFFFF2], xmm1
movd dword [rax + rsi * 2 + 0xFFFF2], xmm15
movd dword [rax + rsi * 4 + 0xFFFF4], xmm0
movd dword [rax + rsi * 4 + 0xFFFF4], xmm1
movd dword [rax + rsi * 4 + 0xFFFF4], xmm15
movd dword [rax + rsi * 8 + 0xFFFF8], xmm0
movd dword [rax + rsi * 8 + 0xFFFF8], xmm1
movd dword [rax + rsi * 8 + 0xFFFF8], xmm15
movd dword [rsp + rax * 8 + 0xFFFF8], xmm0
movd dword [rsp + rax * 8 + 0xFFFF8], xmm1
movd dword [rsp + rax * 8 + 0xFFFF8], xmm15
movd dword [r15 + rax * 8 + 0xFFFF8], xmm0
movd dword [r15 + rax * 8 + 0xFFFF8], xmm1
movd dword [r15 + rax * 8 + 0xFFFF8], xmm15
movd dword [rsp + r15 * 8 + 0xFFFF8], xmm0
movd dword [rsp + r15 * 8 + 0xFFFF8], xmm1
movd dword [rsp + r15 * 8 + 0xFFFF8], xmm15
movd dword [r14 + r15 * 8 + 0xFFFF8], xmm0
movd dword [r14 + r15 * 8 + 0xFFFF8], xmm1
movd dword [r14 + r15 * 8 + 0xFFFF8], xmm15
movd xmm0, ecx
movd xmm0, ebx
movd xmm0, r15d
movd xmm1, ecx
movd xmm1, ebx
movd xmm1, r15d
movd xmm15, ecx
movd xmm15, ebx
movd xmm15, r15d
movd xmm0, dword [0x0]
movd xmm0, dword [0xFF]
movd xmm0, dword [rel $ + 0x0]
movd xmm0, dword [rel $ + 0xFF]
movd xmm0, dword [rel $ + 0xFFFF]
movd xmm0, dword [rax]
movd xmm0, dword [rax + 0x0]
movd xmm0, dword [rax + 0xFFFF]
movd xmm0, dword [r15 + 0xFFFF]
movd xmm0, dword [rax + rsi * 1  + 0x0]
movd xmm0, dword [rax + rsi + 0xFFFF]
movd xmm0, dword [r15 + rsi + 0xFFFF]
movd xmm0, dword [rax + r15 + 0xFFFF]
movd xmm0, dword [rax + rsi * 2 + 0xFFFF2]
movd xmm0, dword [rax + rsi * 4 + 0xFFFF4]
movd xmm0, dword [rax + rsi * 8 + 0xFFFF8]
movd xmm0, dword [rsp + rax * 8 + 0xFFFF8]
movd xmm0, dword [r15 + rax * 8 + 0xFFFF8]
movd xmm0, dword [rsp + r15 * 8 + 0xFFFF8]
movd xmm0, dword [r14 + r15 * 8 + 0xFFFF8]
movd xmm1, dword [0x0]
movd xmm1, dword [0xFF]
movd xmm1, dword [rel $ + 0x0]
movd xmm1, dword [rel $ + 0xFF]
movd xmm1, dword [rel $ + 0xFFFF]
movd xmm1, dword [rax]
movd xmm1, dword [rax + 0x0]
movd xmm1, dword [rax + 0xFFFF]
movd xmm1, dword [r15 + 0xFFFF]
movd xmm1, dword [rax + rsi * 1  + 0x0]
movd xmm1, dword [rax + rsi + 0xFFFF]
movd xmm1, dword [r15 + rsi + 0xFFFF]
movd xmm1, dword [rax + r15 + 0xFFFF]
movd xmm1, dword [rax + rsi * 2 + 0xFFFF2]
movd xmm1, dword [rax + rsi * 4 + 0xFFFF4]
movd xmm1, dword [rax + rsi * 8 + 0xFFFF8]
movd xmm1, dword [rsp + rax * 8 + 0xFFFF8]
movd xmm1, dword [r15 + rax * 8 + 0xFFFF8]
movd xmm1, dword [rsp + r15 * 8 + 0xFFFF8]
movd xmm1, dword [r14 + r15 * 8 + 0xFFFF8]
movd xmm15, dword [0x0]
movd xmm15, dword [0xFF]
movd xmm15, dword [rel $ + 0x0]
movd xmm15, dword [rel $ + 0xFF]
movd xmm15, dword [rel $ + 0xFFFF]
movd xmm15, dword [rax]
movd xmm15, dword [rax + 0x0]
movd xmm15, dword [rax + 0xFFFF]
movd xmm15, dword [r15 + 0xFFFF]
movd xmm15, dword [rax + rsi * 1  + 0x0]
movd xmm15, dword [rax + rsi + 0xFFFF]
movd xmm15, dword [r15 + rsi + 0xFFFF]
movd xmm15, dword [rax + r15 + 0xFFFF]
movd xmm15, dword [rax + rsi * 2 + 0xFFFF2]
movd xmm15, dword [rax + rsi * 4 + 0xFFFF4]
movd xmm15, dword [rax + rsi * 8 + 0xFFFF8]
movd xmm15, dword [rsp + rax * 8 + 0xFFFF8]
movd xmm15, dword [r15 + rax * 8 + 0xFFFF8]
movd xmm15, dword [rsp + r15 * 8 + 0xFFFF8]
movd xmm15, dword [r14 + r15 * 8 + 0xFFFF8]
