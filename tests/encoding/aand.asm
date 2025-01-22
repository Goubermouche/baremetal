; expect: 660f38fc0c2500000000660f38fc1c250000000066440f38fc3c2500000000660f38fc0c25ff000000660f38fc1c25ff00000066440f38fc3c25ff000000660f38fc0df7ffffff660f38fc1df7ffffff66440f38fc3df6ffffff660f38fc0df6000000660f38fc1df600000066440f38fc3df5000000660f38fc0df6ff0000660f38fc1df6ff000066440f38fc3df5ff0000660f38fc08660f38fc1866440f38fc38660f38fc08660f38fc1866440f38fc38660f38fc88ffff0000660f38fc98ffff000066440f38fcb8ffff000066410f38fc8fffff000066410f38fc9fffff000066450f38fcbfffff0000660f38fc0c30660f38fc1c3066440f38fc3c30660f38fc8c30ffff0000660f38fc9c30ffff000066440f38fcbc30ffff000066410f38fc8c37ffff000066410f38fc9c37ffff000066450f38fcbc37ffff000066420f38fc8c38ffff000066420f38fc9c38ffff000066460f38fcbc38ffff0000660f38fc8c70f2ff0f00660f38fc9c70f2ff0f0066440f38fcbc70f2ff0f00660f38fc8cb0f4ff0f00660f38fc9cb0f4ff0f0066440f38fcbcb0f4ff0f00660f38fc8cf0f8ff0f00660f38fc9cf0f8ff0f0066440f38fcbcf0f8ff0f00660f38fc8cc4f8ff0f00660f38fc9cc4f8ff0f0066440f38fcbcc4f8ff0f0066410f38fc8cc7f8ff0f0066410f38fc9cc7f8ff0f0066450f38fcbcc7f8ff0f0066420f38fc8cfcf8ff0f0066420f38fc9cfcf8ff0f0066460f38fcbcfcf8ff0f0066430f38fc8cfef8ff0f0066430f38fc9cfef8ff0f0066470f38fcbcfef8ff0f0066480f38fc0c250000000066480f38fc1c2500000000664c0f38fc3c250000000066480f38fc0c25ff00000066480f38fc1c25ff000000664c0f38fc3c25ff00000066480f38fc0df6ffffff66480f38fc1df6ffffff664c0f38fc3df6ffffff66480f38fc0df500000066480f38fc1df5000000664c0f38fc3df500000066480f38fc0df5ff000066480f38fc1df5ff0000664c0f38fc3df5ff000066480f38fc0866480f38fc18664c0f38fc3866480f38fc0866480f38fc18664c0f38fc3866480f38fc88ffff000066480f38fc98ffff0000664c0f38fcb8ffff000066490f38fc8fffff000066490f38fc9fffff0000664d0f38fcbfffff000066480f38fc0c3066480f38fc1c30664c0f38fc3c3066480f38fc8c30ffff000066480f38fc9c30ffff0000664c0f38fcbc30ffff000066490f38fc8c37ffff000066490f38fc9c37ffff0000664d0f38fcbc37ffff0000664a0f38fc8c38ffff0000664a0f38fc9c38ffff0000664e0f38fcbc38ffff000066480f38fc8c70f2ff0f0066480f38fc9c70f2ff0f00664c0f38fcbc70f2ff0f0066480f38fc8cb0f4ff0f0066480f38fc9cb0f4ff0f00664c0f38fcbcb0f4ff0f0066480f38fc8cf0f8ff0f0066480f38fc9cf0f8ff0f00664c0f38fcbcf0f8ff0f0066480f38fc8cc4f8ff0f0066480f38fc9cc4f8ff0f00664c0f38fcbcc4f8ff0f0066490f38fc8cc7f8ff0f0066490f38fc9cc7f8ff0f00664d0f38fcbcc7f8ff0f00664a0f38fc8cfcf8ff0f00664a0f38fc9cfcf8ff0f00664e0f38fcbcfcf8ff0f00664b0f38fc8cfef8ff0f00664b0f38fc9cfef8ff0f00664f0f38fcbcfef8ff0f00

aand dword [0x0], ecx
aand dword [0x0], ebx
aand dword [0x0], r15d
aand dword [0xFF], ecx
aand dword [0xFF], ebx
aand dword [0xFF], r15d
aand dword [rel $ + 0x0], ecx
aand dword [rel $ + 0x0], ebx
aand dword [rel $ + 0x0], r15d
aand dword [rel $ + 0xFF], ecx
aand dword [rel $ + 0xFF], ebx
aand dword [rel $ + 0xFF], r15d
aand dword [rel $ + 0xFFFF], ecx
aand dword [rel $ + 0xFFFF], ebx
aand dword [rel $ + 0xFFFF], r15d
aand dword [rax], ecx
aand dword [rax], ebx
aand dword [rax], r15d
aand dword [rax + 0x0], ecx
aand dword [rax + 0x0], ebx
aand dword [rax + 0x0], r15d
aand dword [rax + 0xFFFF], ecx
aand dword [rax + 0xFFFF], ebx
aand dword [rax + 0xFFFF], r15d
aand dword [r15 + 0xFFFF], ecx
aand dword [r15 + 0xFFFF], ebx
aand dword [r15 + 0xFFFF], r15d
aand dword [rax + rsi * 1  + 0x0], ecx
aand dword [rax + rsi * 1  + 0x0], ebx
aand dword [rax + rsi * 1  + 0x0], r15d
aand dword [rax + rsi + 0xFFFF], ecx
aand dword [rax + rsi + 0xFFFF], ebx
aand dword [rax + rsi + 0xFFFF], r15d
aand dword [r15 + rsi + 0xFFFF], ecx
aand dword [r15 + rsi + 0xFFFF], ebx
aand dword [r15 + rsi + 0xFFFF], r15d
aand dword [rax + r15 + 0xFFFF], ecx
aand dword [rax + r15 + 0xFFFF], ebx
aand dword [rax + r15 + 0xFFFF], r15d
aand dword [rax + rsi * 2 + 0xFFFF2], ecx
aand dword [rax + rsi * 2 + 0xFFFF2], ebx
aand dword [rax + rsi * 2 + 0xFFFF2], r15d
aand dword [rax + rsi * 4 + 0xFFFF4], ecx
aand dword [rax + rsi * 4 + 0xFFFF4], ebx
aand dword [rax + rsi * 4 + 0xFFFF4], r15d
aand dword [rax + rsi * 8 + 0xFFFF8], ecx
aand dword [rax + rsi * 8 + 0xFFFF8], ebx
aand dword [rax + rsi * 8 + 0xFFFF8], r15d
aand dword [rsp + rax * 8 + 0xFFFF8], ecx
aand dword [rsp + rax * 8 + 0xFFFF8], ebx
aand dword [rsp + rax * 8 + 0xFFFF8], r15d
aand dword [r15 + rax * 8 + 0xFFFF8], ecx
aand dword [r15 + rax * 8 + 0xFFFF8], ebx
aand dword [r15 + rax * 8 + 0xFFFF8], r15d
aand dword [rsp + r15 * 8 + 0xFFFF8], ecx
aand dword [rsp + r15 * 8 + 0xFFFF8], ebx
aand dword [rsp + r15 * 8 + 0xFFFF8], r15d
aand dword [r14 + r15 * 8 + 0xFFFF8], ecx
aand dword [r14 + r15 * 8 + 0xFFFF8], ebx
aand dword [r14 + r15 * 8 + 0xFFFF8], r15d
aand qword [0x0], rcx
aand qword [0x0], rbx
aand qword [0x0], r15
aand qword [0xFF], rcx
aand qword [0xFF], rbx
aand qword [0xFF], r15
aand qword [rel $ + 0x0], rcx
aand qword [rel $ + 0x0], rbx
aand qword [rel $ + 0x0], r15
aand qword [rel $ + 0xFF], rcx
aand qword [rel $ + 0xFF], rbx
aand qword [rel $ + 0xFF], r15
aand qword [rel $ + 0xFFFF], rcx
aand qword [rel $ + 0xFFFF], rbx
aand qword [rel $ + 0xFFFF], r15
aand qword [rax], rcx
aand qword [rax], rbx
aand qword [rax], r15
aand qword [rax + 0x0], rcx
aand qword [rax + 0x0], rbx
aand qword [rax + 0x0], r15
aand qword [rax + 0xFFFF], rcx
aand qword [rax + 0xFFFF], rbx
aand qword [rax + 0xFFFF], r15
aand qword [r15 + 0xFFFF], rcx
aand qword [r15 + 0xFFFF], rbx
aand qword [r15 + 0xFFFF], r15
aand qword [rax + rsi * 1  + 0x0], rcx
aand qword [rax + rsi * 1  + 0x0], rbx
aand qword [rax + rsi * 1  + 0x0], r15
aand qword [rax + rsi + 0xFFFF], rcx
aand qword [rax + rsi + 0xFFFF], rbx
aand qword [rax + rsi + 0xFFFF], r15
aand qword [r15 + rsi + 0xFFFF], rcx
aand qword [r15 + rsi + 0xFFFF], rbx
aand qword [r15 + rsi + 0xFFFF], r15
aand qword [rax + r15 + 0xFFFF], rcx
aand qword [rax + r15 + 0xFFFF], rbx
aand qword [rax + r15 + 0xFFFF], r15
aand qword [rax + rsi * 2 + 0xFFFF2], rcx
aand qword [rax + rsi * 2 + 0xFFFF2], rbx
aand qword [rax + rsi * 2 + 0xFFFF2], r15
aand qword [rax + rsi * 4 + 0xFFFF4], rcx
aand qword [rax + rsi * 4 + 0xFFFF4], rbx
aand qword [rax + rsi * 4 + 0xFFFF4], r15
aand qword [rax + rsi * 8 + 0xFFFF8], rcx
aand qword [rax + rsi * 8 + 0xFFFF8], rbx
aand qword [rax + rsi * 8 + 0xFFFF8], r15
aand qword [rsp + rax * 8 + 0xFFFF8], rcx
aand qword [rsp + rax * 8 + 0xFFFF8], rbx
aand qword [rsp + rax * 8 + 0xFFFF8], r15
aand qword [r15 + rax * 8 + 0xFFFF8], rcx
aand qword [r15 + rax * 8 + 0xFFFF8], rbx
aand qword [r15 + rax * 8 + 0xFFFF8], r15
aand qword [rsp + r15 * 8 + 0xFFFF8], rcx
aand qword [rsp + r15 * 8 + 0xFFFF8], rbx
aand qword [rsp + r15 * 8 + 0xFFFF8], r15
aand qword [r14 + r15 * 8 + 0xFFFF8], rcx
aand qword [r14 + r15 * 8 + 0xFFFF8], rbx
aand qword [r14 + r15 * 8 + 0xFFFF8], r15