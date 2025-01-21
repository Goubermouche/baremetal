; expect: c5f990c9c5f990cac5f990cfc5f990d1c5f990d2c5f990d7c5f990f9c5f990fac5f990ffc5f9900c2500000000c5f9900c25ff000000c5f9900df8ffffffc5f9900df7000000c5f9900df7ff0000c5f99008c5f99008c5f99088ffff0000c4c179908fffff0000c5f9900c30c5f9908c30ffff0000c4c179908c37ffff0000c4a179908c38ffff0000c5f9908c70f2ff0f00c5f9908cb0f4ff0f00c5f9908cf0f8ff0f00c5f9908cc4f8ff0f00c4c179908cc7f8ff0f00c4a179908cfcf8ff0f00c48179908cfef8ff0f00c5f990142500000000c5f9901425ff000000c5f99015f8ffffffc5f99015f7000000c5f99015f7ff0000c5f99010c5f99010c5f99090ffff0000c4c1799097ffff0000c5f9901430c5f9909430ffff0000c4c179909437ffff0000c4a179909438ffff0000c5f9909470f2ff0f00c5f99094b0f4ff0f00c5f99094f0f8ff0f00c5f99094c4f8ff0f00c4c1799094c7f8ff0f00c4a1799094fcf8ff0f00c481799094fef8ff0f00c5f9903c2500000000c5f9903c25ff000000c5f9903df8ffffffc5f9903df7000000c5f9903df7ff0000c5f99038c5f99038c5f990b8ffff0000c4c17990bfffff0000c5f9903c30c5f990bc30ffff0000c4c17990bc37ffff0000c4a17990bc38ffff0000c5f990bc70f2ff0f00c5f990bcb0f4ff0f00c5f990bcf0f8ff0f00c5f990bcc4f8ff0f00c4c17990bcc7f8ff0f00c4a17990bcfcf8ff0f00c4817990bcfef8ff0f00c5f992c9c5f992cbc4c17992cfc5f992d1c5f992d3c4c17992d7c5f992f9c5f992fbc4c17992ffc5f9910c2500000000c5f991142500000000c5f9913c2500000000c5f9910c25ff000000c5f9911425ff000000c5f9913c25ff000000c5f9910df8ffffffc5f99115f8ffffffc5f9913df8ffffffc5f9910df7000000c5f99115f7000000c5f9913df7000000c5f9910df7ff0000c5f99115f7ff0000c5f9913df7ff0000c5f99108c5f99110c5f99138c5f99108c5f99110c5f99138c5f99188ffff0000c5f99190ffff0000c5f991b8ffff0000c4c179918fffff0000c4c1799197ffff0000c4c17991bfffff0000c5f9910c30c5f9911430c5f9913c30c5f9918c30ffff0000c5f9919430ffff0000c5f991bc30ffff0000c4c179918c37ffff0000c4c179919437ffff0000c4c17991bc37ffff0000c4a179918c38ffff0000c4a179919438ffff0000c4a17991bc38ffff0000c5f9918c70f2ff0f00c5f9919470f2ff0f00c5f991bc70f2ff0f00c5f9918cb0f4ff0f00c5f99194b0f4ff0f00c5f991bcb0f4ff0f00c5f9918cf0f8ff0f00c5f99194f0f8ff0f00c5f991bcf0f8ff0f00c5f9918cc4f8ff0f00c5f99194c4f8ff0f00c5f991bcc4f8ff0f00c4c179918cc7f8ff0f00c4c1799194c7f8ff0f00c4c17991bcc7f8ff0f00c4a179918cfcf8ff0f00c4a1799194fcf8ff0f00c4a17991bcfcf8ff0f00c48179918cfef8ff0f00c481799194fef8ff0f00c4817991bcfef8ff0f00c5f993c9c5f993cac5f993cfc5f993d9c5f993dac5f993dfc57993f9c57993fac57993ff

kmovb k1, k1
kmovb k1, k2
kmovb k1, k7
kmovb k2, k1
kmovb k2, k2
kmovb k2, k7
kmovb k7, k1
kmovb k7, k2
kmovb k7, k7
kmovb k1, byte [0x0]
kmovb k1, byte [0xFF]
kmovb k1, byte [rel $ + 0x0]
kmovb k1, byte [rel $ + 0xFF]
kmovb k1, byte [rel $ + 0xFFFF]
kmovb k1, byte [rax]
kmovb k1, byte [rax + 0x0]
kmovb k1, byte [rax + 0xFFFF]
kmovb k1, byte [r15 + 0xFFFF]
kmovb k1, byte [rax + rsi * 1  + 0x0]
kmovb k1, byte [rax + rsi + 0xFFFF]
kmovb k1, byte [r15 + rsi + 0xFFFF]
kmovb k1, byte [rax + r15 + 0xFFFF]
kmovb k1, byte [rax + rsi * 2 + 0xFFFF2]
kmovb k1, byte [rax + rsi * 4 + 0xFFFF4]
kmovb k1, byte [rax + rsi * 8 + 0xFFFF8]
kmovb k1, byte [rsp + rax * 8 + 0xFFFF8]
kmovb k1, byte [r15 + rax * 8 + 0xFFFF8]
kmovb k1, byte [rsp + r15 * 8 + 0xFFFF8]
kmovb k1, byte [r14 + r15 * 8 + 0xFFFF8]
kmovb k2, byte [0x0]
kmovb k2, byte [0xFF]
kmovb k2, byte [rel $ + 0x0]
kmovb k2, byte [rel $ + 0xFF]
kmovb k2, byte [rel $ + 0xFFFF]
kmovb k2, byte [rax]
kmovb k2, byte [rax + 0x0]
kmovb k2, byte [rax + 0xFFFF]
kmovb k2, byte [r15 + 0xFFFF]
kmovb k2, byte [rax + rsi * 1  + 0x0]
kmovb k2, byte [rax + rsi + 0xFFFF]
kmovb k2, byte [r15 + rsi + 0xFFFF]
kmovb k2, byte [rax + r15 + 0xFFFF]
kmovb k2, byte [rax + rsi * 2 + 0xFFFF2]
kmovb k2, byte [rax + rsi * 4 + 0xFFFF4]
kmovb k2, byte [rax + rsi * 8 + 0xFFFF8]
kmovb k2, byte [rsp + rax * 8 + 0xFFFF8]
kmovb k2, byte [r15 + rax * 8 + 0xFFFF8]
kmovb k2, byte [rsp + r15 * 8 + 0xFFFF8]
kmovb k2, byte [r14 + r15 * 8 + 0xFFFF8]
kmovb k7, byte [0x0]
kmovb k7, byte [0xFF]
kmovb k7, byte [rel $ + 0x0]
kmovb k7, byte [rel $ + 0xFF]
kmovb k7, byte [rel $ + 0xFFFF]
kmovb k7, byte [rax]
kmovb k7, byte [rax + 0x0]
kmovb k7, byte [rax + 0xFFFF]
kmovb k7, byte [r15 + 0xFFFF]
kmovb k7, byte [rax + rsi * 1  + 0x0]
kmovb k7, byte [rax + rsi + 0xFFFF]
kmovb k7, byte [r15 + rsi + 0xFFFF]
kmovb k7, byte [rax + r15 + 0xFFFF]
kmovb k7, byte [rax + rsi * 2 + 0xFFFF2]
kmovb k7, byte [rax + rsi * 4 + 0xFFFF4]
kmovb k7, byte [rax + rsi * 8 + 0xFFFF8]
kmovb k7, byte [rsp + rax * 8 + 0xFFFF8]
kmovb k7, byte [r15 + rax * 8 + 0xFFFF8]
kmovb k7, byte [rsp + r15 * 8 + 0xFFFF8]
kmovb k7, byte [r14 + r15 * 8 + 0xFFFF8]
kmovb k1, ecx
kmovb k1, ebx
kmovb k1, r15d
kmovb k2, ecx
kmovb k2, ebx
kmovb k2, r15d
kmovb k7, ecx
kmovb k7, ebx
kmovb k7, r15d
kmovb byte [0x0], k1
kmovb byte [0x0], k2
kmovb byte [0x0], k7
kmovb byte [0xFF], k1
kmovb byte [0xFF], k2
kmovb byte [0xFF], k7
kmovb byte [rel $ + 0x0], k1
kmovb byte [rel $ + 0x0], k2
kmovb byte [rel $ + 0x0], k7
kmovb byte [rel $ + 0xFF], k1
kmovb byte [rel $ + 0xFF], k2
kmovb byte [rel $ + 0xFF], k7
kmovb byte [rel $ + 0xFFFF], k1
kmovb byte [rel $ + 0xFFFF], k2
kmovb byte [rel $ + 0xFFFF], k7
kmovb byte [rax], k1
kmovb byte [rax], k2
kmovb byte [rax], k7
kmovb byte [rax + 0x0], k1
kmovb byte [rax + 0x0], k2
kmovb byte [rax + 0x0], k7
kmovb byte [rax + 0xFFFF], k1
kmovb byte [rax + 0xFFFF], k2
kmovb byte [rax + 0xFFFF], k7
kmovb byte [r15 + 0xFFFF], k1
kmovb byte [r15 + 0xFFFF], k2
kmovb byte [r15 + 0xFFFF], k7
kmovb byte [rax + rsi * 1  + 0x0], k1
kmovb byte [rax + rsi * 1  + 0x0], k2
kmovb byte [rax + rsi * 1  + 0x0], k7
kmovb byte [rax + rsi + 0xFFFF], k1
kmovb byte [rax + rsi + 0xFFFF], k2
kmovb byte [rax + rsi + 0xFFFF], k7
kmovb byte [r15 + rsi + 0xFFFF], k1
kmovb byte [r15 + rsi + 0xFFFF], k2
kmovb byte [r15 + rsi + 0xFFFF], k7
kmovb byte [rax + r15 + 0xFFFF], k1
kmovb byte [rax + r15 + 0xFFFF], k2
kmovb byte [rax + r15 + 0xFFFF], k7
kmovb byte [rax + rsi * 2 + 0xFFFF2], k1
kmovb byte [rax + rsi * 2 + 0xFFFF2], k2
kmovb byte [rax + rsi * 2 + 0xFFFF2], k7
kmovb byte [rax + rsi * 4 + 0xFFFF4], k1
kmovb byte [rax + rsi * 4 + 0xFFFF4], k2
kmovb byte [rax + rsi * 4 + 0xFFFF4], k7
kmovb byte [rax + rsi * 8 + 0xFFFF8], k1
kmovb byte [rax + rsi * 8 + 0xFFFF8], k2
kmovb byte [rax + rsi * 8 + 0xFFFF8], k7
kmovb byte [rsp + rax * 8 + 0xFFFF8], k1
kmovb byte [rsp + rax * 8 + 0xFFFF8], k2
kmovb byte [rsp + rax * 8 + 0xFFFF8], k7
kmovb byte [r15 + rax * 8 + 0xFFFF8], k1
kmovb byte [r15 + rax * 8 + 0xFFFF8], k2
kmovb byte [r15 + rax * 8 + 0xFFFF8], k7
kmovb byte [rsp + r15 * 8 + 0xFFFF8], k1
kmovb byte [rsp + r15 * 8 + 0xFFFF8], k2
kmovb byte [rsp + r15 * 8 + 0xFFFF8], k7
kmovb byte [r14 + r15 * 8 + 0xFFFF8], k1
kmovb byte [r14 + r15 * 8 + 0xFFFF8], k2
kmovb byte [r14 + r15 * 8 + 0xFFFF8], k7
kmovb ecx, k1
kmovb ecx, k2
kmovb ecx, k7
kmovb ebx, k1
kmovb ebx, k2
kmovb ebx, k7
kmovb r15d, k1
kmovb r15d, k2
kmovb r15d, k7