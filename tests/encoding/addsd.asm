; expect: f20f58c0f20f58c1f2410f58c7f20f58c8f20f58c9f2410f58cff2440f58f8f2440f58f9f2450f58fff20f58042500000000f20f580425ff000000f20f5805f8fffffff20f5805f7000000f20f5805f7ff0000f20f5800f20f5800f20f5880ffff0000f2410f5887ffff0000f20f580430f20f588430ffff0000f2410f588437ffff0000f2420f588438ffff0000f20f588470f2ff0f00f20f5884b0f4ff0f00f20f5884f0f8ff0f00f20f5884c4f8ff0f00f2410f5884c7f8ff0f00f2420f5884fcf8ff0f00f2430f5884fef8ff0f00f20f580c2500000000f20f580c25ff000000f20f580df8fffffff20f580df7000000f20f580df7ff0000f20f5808f20f5808f20f5888ffff0000f2410f588fffff0000f20f580c30f20f588c30ffff0000f2410f588c37ffff0000f2420f588c38ffff0000f20f588c70f2ff0f00f20f588cb0f4ff0f00f20f588cf0f8ff0f00f20f588cc4f8ff0f00f2410f588cc7f8ff0f00f2420f588cfcf8ff0f00f2430f588cfef8ff0f00f2440f583c2500000000f2440f583c25ff000000f2440f583df7fffffff2440f583df6000000f2440f583df6ff0000f2440f5838f2440f5838f2440f58b8ffff0000f2450f58bfffff0000f2440f583c30f2440f58bc30ffff0000f2450f58bc37ffff0000f2460f58bc38ffff0000f2440f58bc70f2ff0f00f2440f58bcb0f4ff0f00f2440f58bcf0f8ff0f00f2440f58bcc4f8ff0f00f2450f58bcc7f8ff0f00f2460f58bcfcf8ff0f00f2470f58bcfef8ff0f00

bits 64

addsd xmm0, xmm0
addsd xmm0, xmm1
addsd xmm0, xmm15
addsd xmm1, xmm0
addsd xmm1, xmm1
addsd xmm1, xmm15
addsd xmm15, xmm0
addsd xmm15, xmm1
addsd xmm15, xmm15
addsd xmm0, qword [0x0]
addsd xmm0, qword [0xFF]
addsd xmm0, qword [rel $ + 0x0]
addsd xmm0, qword [rel $ + 0xFF]
addsd xmm0, qword [rel $ + 0xFFFF]
addsd xmm0, qword [rax]
addsd xmm0, qword [rax + 0x0]
addsd xmm0, qword [rax + 0xFFFF]
addsd xmm0, qword [r15 + 0xFFFF]
addsd xmm0, qword [rax + rsi * 1  + 0x0]
addsd xmm0, qword [rax + rsi + 0xFFFF]
addsd xmm0, qword [r15 + rsi + 0xFFFF]
addsd xmm0, qword [rax + r15 + 0xFFFF]
addsd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
addsd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
addsd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
addsd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
addsd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
addsd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
addsd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
addsd xmm1, qword [0x0]
addsd xmm1, qword [0xFF]
addsd xmm1, qword [rel $ + 0x0]
addsd xmm1, qword [rel $ + 0xFF]
addsd xmm1, qword [rel $ + 0xFFFF]
addsd xmm1, qword [rax]
addsd xmm1, qword [rax + 0x0]
addsd xmm1, qword [rax + 0xFFFF]
addsd xmm1, qword [r15 + 0xFFFF]
addsd xmm1, qword [rax + rsi * 1  + 0x0]
addsd xmm1, qword [rax + rsi + 0xFFFF]
addsd xmm1, qword [r15 + rsi + 0xFFFF]
addsd xmm1, qword [rax + r15 + 0xFFFF]
addsd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
addsd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
addsd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
addsd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
addsd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
addsd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
addsd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
addsd xmm15, qword [0x0]
addsd xmm15, qword [0xFF]
addsd xmm15, qword [rel $ + 0x0]
addsd xmm15, qword [rel $ + 0xFF]
addsd xmm15, qword [rel $ + 0xFFFF]
addsd xmm15, qword [rax]
addsd xmm15, qword [rax + 0x0]
addsd xmm15, qword [rax + 0xFFFF]
addsd xmm15, qword [r15 + 0xFFFF]
addsd xmm15, qword [rax + rsi * 1  + 0x0]
addsd xmm15, qword [rax + rsi + 0xFFFF]
addsd xmm15, qword [r15 + rsi + 0xFFFF]
addsd xmm15, qword [rax + r15 + 0xFFFF]
addsd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
addsd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
addsd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
addsd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
addsd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
addsd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
addsd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
