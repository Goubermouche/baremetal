; expect: 660f2fc0660f2fc166410f2fc7660f2fc8660f2fc966410f2fcf66440f2ff866440f2ff966450f2fff660f2f042500000000660f2f0425ff000000660f2f05f8ffffff660f2f05f7000000660f2f05f7ff0000660f2f00660f2f00660f2f80ffff000066410f2f87ffff0000660f2f0430660f2f8430ffff000066410f2f8437ffff000066420f2f8438ffff0000660f2f8470f2ff0f00660f2f84b0f4ff0f00660f2f84f0f8ff0f00660f2f84c4f8ff0f0066410f2f84c7f8ff0f0066420f2f84fcf8ff0f0066430f2f84fef8ff0f00660f2f0c2500000000660f2f0c25ff000000660f2f0df8ffffff660f2f0df7000000660f2f0df7ff0000660f2f08660f2f08660f2f88ffff000066410f2f8fffff0000660f2f0c30660f2f8c30ffff000066410f2f8c37ffff000066420f2f8c38ffff0000660f2f8c70f2ff0f00660f2f8cb0f4ff0f00660f2f8cf0f8ff0f00660f2f8cc4f8ff0f0066410f2f8cc7f8ff0f0066420f2f8cfcf8ff0f0066430f2f8cfef8ff0f0066440f2f3c250000000066440f2f3c25ff00000066440f2f3df7ffffff66440f2f3df600000066440f2f3df6ff000066440f2f3866440f2f3866440f2fb8ffff000066450f2fbfffff000066440f2f3c3066440f2fbc30ffff000066450f2fbc37ffff000066460f2fbc38ffff000066440f2fbc70f2ff0f0066440f2fbcb0f4ff0f0066440f2fbcf0f8ff0f0066440f2fbcc4f8ff0f0066450f2fbcc7f8ff0f0066460f2fbcfcf8ff0f0066470f2fbcfef8ff0f00

bits 64

comisd xmm0, xmm0
comisd xmm0, xmm1
comisd xmm0, xmm15
comisd xmm1, xmm0
comisd xmm1, xmm1
comisd xmm1, xmm15
comisd xmm15, xmm0
comisd xmm15, xmm1
comisd xmm15, xmm15
comisd xmm0, qword [0x0]
comisd xmm0, qword [0xFF]
comisd xmm0, qword [rel $ + 0x0]
comisd xmm0, qword [rel $ + 0xFF]
comisd xmm0, qword [rel $ + 0xFFFF]
comisd xmm0, qword [rax]
comisd xmm0, qword [rax + 0x0]
comisd xmm0, qword [rax + 0xFFFF]
comisd xmm0, qword [r15 + 0xFFFF]
comisd xmm0, qword [rax + rsi * 1  + 0x0]
comisd xmm0, qword [rax + rsi + 0xFFFF]
comisd xmm0, qword [r15 + rsi + 0xFFFF]
comisd xmm0, qword [rax + r15 + 0xFFFF]
comisd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
comisd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
comisd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
comisd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
comisd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
comisd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
comisd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
comisd xmm1, qword [0x0]
comisd xmm1, qword [0xFF]
comisd xmm1, qword [rel $ + 0x0]
comisd xmm1, qword [rel $ + 0xFF]
comisd xmm1, qword [rel $ + 0xFFFF]
comisd xmm1, qword [rax]
comisd xmm1, qword [rax + 0x0]
comisd xmm1, qword [rax + 0xFFFF]
comisd xmm1, qword [r15 + 0xFFFF]
comisd xmm1, qword [rax + rsi * 1  + 0x0]
comisd xmm1, qword [rax + rsi + 0xFFFF]
comisd xmm1, qword [r15 + rsi + 0xFFFF]
comisd xmm1, qword [rax + r15 + 0xFFFF]
comisd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
comisd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
comisd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
comisd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
comisd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
comisd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
comisd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
comisd xmm15, qword [0x0]
comisd xmm15, qword [0xFF]
comisd xmm15, qword [rel $ + 0x0]
comisd xmm15, qword [rel $ + 0xFF]
comisd xmm15, qword [rel $ + 0xFFFF]
comisd xmm15, qword [rax]
comisd xmm15, qword [rax + 0x0]
comisd xmm15, qword [rax + 0xFFFF]
comisd xmm15, qword [r15 + 0xFFFF]
comisd xmm15, qword [rax + rsi * 1  + 0x0]
comisd xmm15, qword [rax + rsi + 0xFFFF]
comisd xmm15, qword [r15 + rsi + 0xFFFF]
comisd xmm15, qword [rax + r15 + 0xFFFF]
comisd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
comisd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
comisd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
comisd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
comisd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
comisd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
comisd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
