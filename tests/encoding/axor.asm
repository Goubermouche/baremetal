; expect: f30f38fc0c2500000000f30f38fc1c2500000000f3440f38fc3c2500000000f30f38fc0c25ff000000f30f38fc1c25ff000000f3440f38fc3c25ff000000f30f38fc0df7fffffff30f38fc1df7fffffff3440f38fc3df6fffffff30f38fc0df6000000f30f38fc1df6000000f3440f38fc3df5000000f30f38fc0df6ff0000f30f38fc1df6ff0000f3440f38fc3df5ff0000f30f38fc08f30f38fc18f3440f38fc38f30f38fc08f30f38fc18f3440f38fc38f30f38fc88ffff0000f30f38fc98ffff0000f3440f38fcb8ffff0000f3410f38fc8fffff0000f3410f38fc9fffff0000f3450f38fcbfffff0000f30f38fc0c30f30f38fc1c30f3440f38fc3c30f30f38fc8c30ffff0000f30f38fc9c30ffff0000f3440f38fcbc30ffff0000f3410f38fc8c37ffff0000f3410f38fc9c37ffff0000f3450f38fcbc37ffff0000f3420f38fc8c38ffff0000f3420f38fc9c38ffff0000f3460f38fcbc38ffff0000f30f38fc8c70f2ff0f00f30f38fc9c70f2ff0f00f3440f38fcbc70f2ff0f00f30f38fc8cb0f4ff0f00f30f38fc9cb0f4ff0f00f3440f38fcbcb0f4ff0f00f30f38fc8cf0f8ff0f00f30f38fc9cf0f8ff0f00f3440f38fcbcf0f8ff0f00f30f38fc8cc4f8ff0f00f30f38fc9cc4f8ff0f00f3440f38fcbcc4f8ff0f00f3410f38fc8cc7f8ff0f00f3410f38fc9cc7f8ff0f00f3450f38fcbcc7f8ff0f00f3420f38fc8cfcf8ff0f00f3420f38fc9cfcf8ff0f00f3460f38fcbcfcf8ff0f00f3430f38fc8cfef8ff0f00f3430f38fc9cfef8ff0f00f3470f38fcbcfef8ff0f00f3480f38fc0c2500000000f3480f38fc1c2500000000f34c0f38fc3c2500000000f3480f38fc0c25ff000000f3480f38fc1c25ff000000f34c0f38fc3c25ff000000f3480f38fc0df6fffffff3480f38fc1df6fffffff34c0f38fc3df6fffffff3480f38fc0df5000000f3480f38fc1df5000000f34c0f38fc3df5000000f3480f38fc0df5ff0000f3480f38fc1df5ff0000f34c0f38fc3df5ff0000f3480f38fc08f3480f38fc18f34c0f38fc38f3480f38fc08f3480f38fc18f34c0f38fc38f3480f38fc88ffff0000f3480f38fc98ffff0000f34c0f38fcb8ffff0000f3490f38fc8fffff0000f3490f38fc9fffff0000f34d0f38fcbfffff0000f3480f38fc0c30f3480f38fc1c30f34c0f38fc3c30f3480f38fc8c30ffff0000f3480f38fc9c30ffff0000f34c0f38fcbc30ffff0000f3490f38fc8c37ffff0000f3490f38fc9c37ffff0000f34d0f38fcbc37ffff0000f34a0f38fc8c38ffff0000f34a0f38fc9c38ffff0000f34e0f38fcbc38ffff0000f3480f38fc8c70f2ff0f00f3480f38fc9c70f2ff0f00f34c0f38fcbc70f2ff0f00f3480f38fc8cb0f4ff0f00f3480f38fc9cb0f4ff0f00f34c0f38fcbcb0f4ff0f00f3480f38fc8cf0f8ff0f00f3480f38fc9cf0f8ff0f00f34c0f38fcbcf0f8ff0f00f3480f38fc8cc4f8ff0f00f3480f38fc9cc4f8ff0f00f34c0f38fcbcc4f8ff0f00f3490f38fc8cc7f8ff0f00f3490f38fc9cc7f8ff0f00f34d0f38fcbcc7f8ff0f00f34a0f38fc8cfcf8ff0f00f34a0f38fc9cfcf8ff0f00f34e0f38fcbcfcf8ff0f00f34b0f38fc8cfef8ff0f00f34b0f38fc9cfef8ff0f00f34f0f38fcbcfef8ff0f00

bits 64

axor dword [0x0], ecx
axor dword [0x0], ebx
axor dword [0x0], r15d
axor dword [0xFF], ecx
axor dword [0xFF], ebx
axor dword [0xFF], r15d
axor dword [rel $ + 0x0], ecx
axor dword [rel $ + 0x0], ebx
axor dword [rel $ + 0x0], r15d
axor dword [rel $ + 0xFF], ecx
axor dword [rel $ + 0xFF], ebx
axor dword [rel $ + 0xFF], r15d
axor dword [rel $ + 0xFFFF], ecx
axor dword [rel $ + 0xFFFF], ebx
axor dword [rel $ + 0xFFFF], r15d
axor dword [rax], ecx
axor dword [rax], ebx
axor dword [rax], r15d
axor dword [rax + 0x0], ecx
axor dword [rax + 0x0], ebx
axor dword [rax + 0x0], r15d
axor dword [rax + 0xFFFF], ecx
axor dword [rax + 0xFFFF], ebx
axor dword [rax + 0xFFFF], r15d
axor dword [r15 + 0xFFFF], ecx
axor dword [r15 + 0xFFFF], ebx
axor dword [r15 + 0xFFFF], r15d
axor dword [rax + rsi * 1  + 0x0], ecx
axor dword [rax + rsi * 1  + 0x0], ebx
axor dword [rax + rsi * 1  + 0x0], r15d
axor dword [rax + rsi + 0xFFFF], ecx
axor dword [rax + rsi + 0xFFFF], ebx
axor dword [rax + rsi + 0xFFFF], r15d
axor dword [r15 + rsi + 0xFFFF], ecx
axor dword [r15 + rsi + 0xFFFF], ebx
axor dword [r15 + rsi + 0xFFFF], r15d
axor dword [rax + r15 + 0xFFFF], ecx
axor dword [rax + r15 + 0xFFFF], ebx
axor dword [rax + r15 + 0xFFFF], r15d
axor dword [rax + rsi * 2 + 0xFFFF2], ecx
axor dword [rax + rsi * 2 + 0xFFFF2], ebx
axor dword [rax + rsi * 2 + 0xFFFF2], r15d
axor dword [rax + rsi * 4 + 0xFFFF4], ecx
axor dword [rax + rsi * 4 + 0xFFFF4], ebx
axor dword [rax + rsi * 4 + 0xFFFF4], r15d
axor dword [rax + rsi * 8 + 0xFFFF8], ecx
axor dword [rax + rsi * 8 + 0xFFFF8], ebx
axor dword [rax + rsi * 8 + 0xFFFF8], r15d
axor dword [rsp + rax * 8 + 0xFFFF8], ecx
axor dword [rsp + rax * 8 + 0xFFFF8], ebx
axor dword [rsp + rax * 8 + 0xFFFF8], r15d
axor dword [r15 + rax * 8 + 0xFFFF8], ecx
axor dword [r15 + rax * 8 + 0xFFFF8], ebx
axor dword [r15 + rax * 8 + 0xFFFF8], r15d
axor dword [rsp + r15 * 8 + 0xFFFF8], ecx
axor dword [rsp + r15 * 8 + 0xFFFF8], ebx
axor dword [rsp + r15 * 8 + 0xFFFF8], r15d
axor dword [r14 + r15 * 8 + 0xFFFF8], ecx
axor dword [r14 + r15 * 8 + 0xFFFF8], ebx
axor dword [r14 + r15 * 8 + 0xFFFF8], r15d
axor qword [0x0], rcx
axor qword [0x0], rbx
axor qword [0x0], r15
axor qword [0xFF], rcx
axor qword [0xFF], rbx
axor qword [0xFF], r15
axor qword [rel $ + 0x0], rcx
axor qword [rel $ + 0x0], rbx
axor qword [rel $ + 0x0], r15
axor qword [rel $ + 0xFF], rcx
axor qword [rel $ + 0xFF], rbx
axor qword [rel $ + 0xFF], r15
axor qword [rel $ + 0xFFFF], rcx
axor qword [rel $ + 0xFFFF], rbx
axor qword [rel $ + 0xFFFF], r15
axor qword [rax], rcx
axor qword [rax], rbx
axor qword [rax], r15
axor qword [rax + 0x0], rcx
axor qword [rax + 0x0], rbx
axor qword [rax + 0x0], r15
axor qword [rax + 0xFFFF], rcx
axor qword [rax + 0xFFFF], rbx
axor qword [rax + 0xFFFF], r15
axor qword [r15 + 0xFFFF], rcx
axor qword [r15 + 0xFFFF], rbx
axor qword [r15 + 0xFFFF], r15
axor qword [rax + rsi * 1  + 0x0], rcx
axor qword [rax + rsi * 1  + 0x0], rbx
axor qword [rax + rsi * 1  + 0x0], r15
axor qword [rax + rsi + 0xFFFF], rcx
axor qword [rax + rsi + 0xFFFF], rbx
axor qword [rax + rsi + 0xFFFF], r15
axor qword [r15 + rsi + 0xFFFF], rcx
axor qword [r15 + rsi + 0xFFFF], rbx
axor qword [r15 + rsi + 0xFFFF], r15
axor qword [rax + r15 + 0xFFFF], rcx
axor qword [rax + r15 + 0xFFFF], rbx
axor qword [rax + r15 + 0xFFFF], r15
axor qword [rax + rsi * 2 + 0xFFFF2], rcx
axor qword [rax + rsi * 2 + 0xFFFF2], rbx
axor qword [rax + rsi * 2 + 0xFFFF2], r15
axor qword [rax + rsi * 4 + 0xFFFF4], rcx
axor qword [rax + rsi * 4 + 0xFFFF4], rbx
axor qword [rax + rsi * 4 + 0xFFFF4], r15
axor qword [rax + rsi * 8 + 0xFFFF8], rcx
axor qword [rax + rsi * 8 + 0xFFFF8], rbx
axor qword [rax + rsi * 8 + 0xFFFF8], r15
axor qword [rsp + rax * 8 + 0xFFFF8], rcx
axor qword [rsp + rax * 8 + 0xFFFF8], rbx
axor qword [rsp + rax * 8 + 0xFFFF8], r15
axor qword [r15 + rax * 8 + 0xFFFF8], rcx
axor qword [r15 + rax * 8 + 0xFFFF8], rbx
axor qword [r15 + rax * 8 + 0xFFFF8], r15
axor qword [rsp + r15 * 8 + 0xFFFF8], rcx
axor qword [rsp + r15 * 8 + 0xFFFF8], rbx
axor qword [rsp + r15 * 8 + 0xFFFF8], r15
axor qword [r14 + r15 * 8 + 0xFFFF8], rcx
axor qword [r14 + r15 * 8 + 0xFFFF8], rbx
axor qword [r14 + r15 * 8 + 0xFFFF8], r15
