; expect: c4e1f990c9c4e1f990cac4e1f990cfc4e1f990d1c4e1f990d2c4e1f990d7c4e1f990f9c4e1f990fac4e1f990ffc4e1f9900c2500000000c4e1f9900c25ff000000c4e1f9900df7ffffffc4e1f9900df6000000c4e1f9900df6ff0000c4e1f99008c4e1f99008c4e1f99088ffff0000c4c1f9908fffff0000c4e1f9900c30c4e1f9908c30ffff0000c4c1f9908c37ffff0000c4a1f9908c38ffff0000c4e1f9908c70f2ff0f00c4e1f9908cb0f4ff0f00c4e1f9908cf0f8ff0f00c4e1f9908cc4f8ff0f00c4c1f9908cc7f8ff0f00c4a1f9908cfcf8ff0f00c481f9908cfef8ff0f00c4e1f990142500000000c4e1f9901425ff000000c4e1f99015f7ffffffc4e1f99015f6000000c4e1f99015f6ff0000c4e1f99010c4e1f99010c4e1f99090ffff0000c4c1f99097ffff0000c4e1f9901430c4e1f9909430ffff0000c4c1f9909437ffff0000c4a1f9909438ffff0000c4e1f9909470f2ff0f00c4e1f99094b0f4ff0f00c4e1f99094f0f8ff0f00c4e1f99094c4f8ff0f00c4c1f99094c7f8ff0f00c4a1f99094fcf8ff0f00c481f99094fef8ff0f00c4e1f9903c2500000000c4e1f9903c25ff000000c4e1f9903df7ffffffc4e1f9903df6000000c4e1f9903df6ff0000c4e1f99038c4e1f99038c4e1f990b8ffff0000c4c1f990bfffff0000c4e1f9903c30c4e1f990bc30ffff0000c4c1f990bc37ffff0000c4a1f990bc38ffff0000c4e1f990bc70f2ff0f00c4e1f990bcb0f4ff0f00c4e1f990bcf0f8ff0f00c4e1f990bcc4f8ff0f00c4c1f990bcc7f8ff0f00c4a1f990bcfcf8ff0f00c481f990bcfef8ff0f00c5fb92c9c5fb92cbc4c17b92cfc5fb92d1c5fb92d3c4c17b92d7c5fb92f9c5fb92fbc4c17b92ffc4e1f9910c2500000000c4e1f991142500000000c4e1f9913c2500000000c4e1f9910c25ff000000c4e1f9911425ff000000c4e1f9913c25ff000000c4e1f9910df7ffffffc4e1f99115f7ffffffc4e1f9913df7ffffffc4e1f9910df6000000c4e1f99115f6000000c4e1f9913df6000000c4e1f9910df6ff0000c4e1f99115f6ff0000c4e1f9913df6ff0000c4e1f99108c4e1f99110c4e1f99138c4e1f99108c4e1f99110c4e1f99138c4e1f99188ffff0000c4e1f99190ffff0000c4e1f991b8ffff0000c4c1f9918fffff0000c4c1f99197ffff0000c4c1f991bfffff0000c4e1f9910c30c4e1f9911430c4e1f9913c30c4e1f9918c30ffff0000c4e1f9919430ffff0000c4e1f991bc30ffff0000c4c1f9918c37ffff0000c4c1f9919437ffff0000c4c1f991bc37ffff0000c4a1f9918c38ffff0000c4a1f9919438ffff0000c4a1f991bc38ffff0000c4e1f9918c70f2ff0f00c4e1f9919470f2ff0f00c4e1f991bc70f2ff0f00c4e1f9918cb0f4ff0f00c4e1f99194b0f4ff0f00c4e1f991bcb0f4ff0f00c4e1f9918cf0f8ff0f00c4e1f99194f0f8ff0f00c4e1f991bcf0f8ff0f00c4e1f9918cc4f8ff0f00c4e1f99194c4f8ff0f00c4e1f991bcc4f8ff0f00c4c1f9918cc7f8ff0f00c4c1f99194c7f8ff0f00c4c1f991bcc7f8ff0f00c4a1f9918cfcf8ff0f00c4a1f99194fcf8ff0f00c4a1f991bcfcf8ff0f00c481f9918cfef8ff0f00c481f99194fef8ff0f00c481f991bcfef8ff0f00c5fb93c9c5fb93cac5fb93cfc5fb93d9c5fb93dac5fb93dfc57b93f9c57b93fac57b93ff

kmovd k1, k1
kmovd k1, k2
kmovd k1, k7
kmovd k2, k1
kmovd k2, k2
kmovd k2, k7
kmovd k7, k1
kmovd k7, k2
kmovd k7, k7
kmovd k1, dword [0x0]
kmovd k1, dword [0xFF]
kmovd k1, dword [rel $ + 0x0]
kmovd k1, dword [rel $ + 0xFF]
kmovd k1, dword [rel $ + 0xFFFF]
kmovd k1, dword [rax]
kmovd k1, dword [rax + 0x0]
kmovd k1, dword [rax + 0xFFFF]
kmovd k1, dword [r15 + 0xFFFF]
kmovd k1, dword [rax + rsi * 1  + 0x0]
kmovd k1, dword [rax + rsi + 0xFFFF]
kmovd k1, dword [r15 + rsi + 0xFFFF]
kmovd k1, dword [rax + r15 + 0xFFFF]
kmovd k1, dword [rax + rsi * 2 + 0xFFFF2]
kmovd k1, dword [rax + rsi * 4 + 0xFFFF4]
kmovd k1, dword [rax + rsi * 8 + 0xFFFF8]
kmovd k1, dword [rsp + rax * 8 + 0xFFFF8]
kmovd k1, dword [r15 + rax * 8 + 0xFFFF8]
kmovd k1, dword [rsp + r15 * 8 + 0xFFFF8]
kmovd k1, dword [r14 + r15 * 8 + 0xFFFF8]
kmovd k2, dword [0x0]
kmovd k2, dword [0xFF]
kmovd k2, dword [rel $ + 0x0]
kmovd k2, dword [rel $ + 0xFF]
kmovd k2, dword [rel $ + 0xFFFF]
kmovd k2, dword [rax]
kmovd k2, dword [rax + 0x0]
kmovd k2, dword [rax + 0xFFFF]
kmovd k2, dword [r15 + 0xFFFF]
kmovd k2, dword [rax + rsi * 1  + 0x0]
kmovd k2, dword [rax + rsi + 0xFFFF]
kmovd k2, dword [r15 + rsi + 0xFFFF]
kmovd k2, dword [rax + r15 + 0xFFFF]
kmovd k2, dword [rax + rsi * 2 + 0xFFFF2]
kmovd k2, dword [rax + rsi * 4 + 0xFFFF4]
kmovd k2, dword [rax + rsi * 8 + 0xFFFF8]
kmovd k2, dword [rsp + rax * 8 + 0xFFFF8]
kmovd k2, dword [r15 + rax * 8 + 0xFFFF8]
kmovd k2, dword [rsp + r15 * 8 + 0xFFFF8]
kmovd k2, dword [r14 + r15 * 8 + 0xFFFF8]
kmovd k7, dword [0x0]
kmovd k7, dword [0xFF]
kmovd k7, dword [rel $ + 0x0]
kmovd k7, dword [rel $ + 0xFF]
kmovd k7, dword [rel $ + 0xFFFF]
kmovd k7, dword [rax]
kmovd k7, dword [rax + 0x0]
kmovd k7, dword [rax + 0xFFFF]
kmovd k7, dword [r15 + 0xFFFF]
kmovd k7, dword [rax + rsi * 1  + 0x0]
kmovd k7, dword [rax + rsi + 0xFFFF]
kmovd k7, dword [r15 + rsi + 0xFFFF]
kmovd k7, dword [rax + r15 + 0xFFFF]
kmovd k7, dword [rax + rsi * 2 + 0xFFFF2]
kmovd k7, dword [rax + rsi * 4 + 0xFFFF4]
kmovd k7, dword [rax + rsi * 8 + 0xFFFF8]
kmovd k7, dword [rsp + rax * 8 + 0xFFFF8]
kmovd k7, dword [r15 + rax * 8 + 0xFFFF8]
kmovd k7, dword [rsp + r15 * 8 + 0xFFFF8]
kmovd k7, dword [r14 + r15 * 8 + 0xFFFF8]
kmovd k1, ecx
kmovd k1, ebx
kmovd k1, r15d
kmovd k2, ecx
kmovd k2, ebx
kmovd k2, r15d
kmovd k7, ecx
kmovd k7, ebx
kmovd k7, r15d
kmovd dword [0x0], k1
kmovd dword [0x0], k2
kmovd dword [0x0], k7
kmovd dword [0xFF], k1
kmovd dword [0xFF], k2
kmovd dword [0xFF], k7
kmovd dword [rel $ + 0x0], k1
kmovd dword [rel $ + 0x0], k2
kmovd dword [rel $ + 0x0], k7
kmovd dword [rel $ + 0xFF], k1
kmovd dword [rel $ + 0xFF], k2
kmovd dword [rel $ + 0xFF], k7
kmovd dword [rel $ + 0xFFFF], k1
kmovd dword [rel $ + 0xFFFF], k2
kmovd dword [rel $ + 0xFFFF], k7
kmovd dword [rax], k1
kmovd dword [rax], k2
kmovd dword [rax], k7
kmovd dword [rax + 0x0], k1
kmovd dword [rax + 0x0], k2
kmovd dword [rax + 0x0], k7
kmovd dword [rax + 0xFFFF], k1
kmovd dword [rax + 0xFFFF], k2
kmovd dword [rax + 0xFFFF], k7
kmovd dword [r15 + 0xFFFF], k1
kmovd dword [r15 + 0xFFFF], k2
kmovd dword [r15 + 0xFFFF], k7
kmovd dword [rax + rsi * 1  + 0x0], k1
kmovd dword [rax + rsi * 1  + 0x0], k2
kmovd dword [rax + rsi * 1  + 0x0], k7
kmovd dword [rax + rsi + 0xFFFF], k1
kmovd dword [rax + rsi + 0xFFFF], k2
kmovd dword [rax + rsi + 0xFFFF], k7
kmovd dword [r15 + rsi + 0xFFFF], k1
kmovd dword [r15 + rsi + 0xFFFF], k2
kmovd dword [r15 + rsi + 0xFFFF], k7
kmovd dword [rax + r15 + 0xFFFF], k1
kmovd dword [rax + r15 + 0xFFFF], k2
kmovd dword [rax + r15 + 0xFFFF], k7
kmovd dword [rax + rsi * 2 + 0xFFFF2], k1
kmovd dword [rax + rsi * 2 + 0xFFFF2], k2
kmovd dword [rax + rsi * 2 + 0xFFFF2], k7
kmovd dword [rax + rsi * 4 + 0xFFFF4], k1
kmovd dword [rax + rsi * 4 + 0xFFFF4], k2
kmovd dword [rax + rsi * 4 + 0xFFFF4], k7
kmovd dword [rax + rsi * 8 + 0xFFFF8], k1
kmovd dword [rax + rsi * 8 + 0xFFFF8], k2
kmovd dword [rax + rsi * 8 + 0xFFFF8], k7
kmovd dword [rsp + rax * 8 + 0xFFFF8], k1
kmovd dword [rsp + rax * 8 + 0xFFFF8], k2
kmovd dword [rsp + rax * 8 + 0xFFFF8], k7
kmovd dword [r15 + rax * 8 + 0xFFFF8], k1
kmovd dword [r15 + rax * 8 + 0xFFFF8], k2
kmovd dword [r15 + rax * 8 + 0xFFFF8], k7
kmovd dword [rsp + r15 * 8 + 0xFFFF8], k1
kmovd dword [rsp + r15 * 8 + 0xFFFF8], k2
kmovd dword [rsp + r15 * 8 + 0xFFFF8], k7
kmovd dword [r14 + r15 * 8 + 0xFFFF8], k1
kmovd dword [r14 + r15 * 8 + 0xFFFF8], k2
kmovd dword [r14 + r15 * 8 + 0xFFFF8], k7
kmovd ecx, k1
kmovd ecx, k2
kmovd ecx, k7
kmovd ebx, k1
kmovd ebx, k2
kmovd ebx, k7
kmovd r15d, k1
kmovd r15d, k2
kmovd r15d, k7