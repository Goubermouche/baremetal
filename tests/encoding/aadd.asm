; expect: 0f38fc0c25000000000f38fc1c2500000000440f38fc3c25000000000f38fc0c25ff0000000f38fc1c25ff000000440f38fc3c25ff0000000f38fc0df8ffffff0f38fc1df8ffffff440f38fc3df7ffffff0f38fc0df70000000f38fc1df7000000440f38fc3df60000000f38fc0df7ff00000f38fc1df7ff0000440f38fc3df6ff00000f38fc080f38fc18440f38fc380f38fc080f38fc18440f38fc380f38fc88ffff00000f38fc98ffff0000440f38fcb8ffff0000410f38fc8fffff0000410f38fc9fffff0000450f38fcbfffff00000f38fc0c300f38fc1c30440f38fc3c300f38fc8c30ffff00000f38fc9c30ffff0000440f38fcbc30ffff0000410f38fc8c37ffff0000410f38fc9c37ffff0000450f38fcbc37ffff0000420f38fc8c38ffff0000420f38fc9c38ffff0000460f38fcbc38ffff00000f38fc8c70f2ff0f000f38fc9c70f2ff0f00440f38fcbc70f2ff0f000f38fc8cb0f4ff0f000f38fc9cb0f4ff0f00440f38fcbcb0f4ff0f000f38fc8cf0f8ff0f000f38fc9cf0f8ff0f00440f38fcbcf0f8ff0f000f38fc8cc4f8ff0f000f38fc9cc4f8ff0f00440f38fcbcc4f8ff0f00410f38fc8cc7f8ff0f00410f38fc9cc7f8ff0f00450f38fcbcc7f8ff0f00420f38fc8cfcf8ff0f00420f38fc9cfcf8ff0f00460f38fcbcfcf8ff0f00430f38fc8cfef8ff0f00430f38fc9cfef8ff0f00470f38fcbcfef8ff0f00480f38fc0c2500000000480f38fc1c25000000004c0f38fc3c2500000000480f38fc0c25ff000000480f38fc1c25ff0000004c0f38fc3c25ff000000480f38fc0df7ffffff480f38fc1df7ffffff4c0f38fc3df7ffffff480f38fc0df6000000480f38fc1df60000004c0f38fc3df6000000480f38fc0df6ff0000480f38fc1df6ff00004c0f38fc3df6ff0000480f38fc08480f38fc184c0f38fc38480f38fc08480f38fc184c0f38fc38480f38fc88ffff0000480f38fc98ffff00004c0f38fcb8ffff0000490f38fc8fffff0000490f38fc9fffff00004d0f38fcbfffff0000480f38fc0c30480f38fc1c304c0f38fc3c30480f38fc8c30ffff0000480f38fc9c30ffff00004c0f38fcbc30ffff0000490f38fc8c37ffff0000490f38fc9c37ffff00004d0f38fcbc37ffff00004a0f38fc8c38ffff00004a0f38fc9c38ffff00004e0f38fcbc38ffff0000480f38fc8c70f2ff0f00480f38fc9c70f2ff0f004c0f38fcbc70f2ff0f00480f38fc8cb0f4ff0f00480f38fc9cb0f4ff0f004c0f38fcbcb0f4ff0f00480f38fc8cf0f8ff0f00480f38fc9cf0f8ff0f004c0f38fcbcf0f8ff0f00480f38fc8cc4f8ff0f00480f38fc9cc4f8ff0f004c0f38fcbcc4f8ff0f00490f38fc8cc7f8ff0f00490f38fc9cc7f8ff0f004d0f38fcbcc7f8ff0f004a0f38fc8cfcf8ff0f004a0f38fc9cfcf8ff0f004e0f38fcbcfcf8ff0f004b0f38fc8cfef8ff0f004b0f38fc9cfef8ff0f004f0f38fcbcfef8ff0f00

bits 64

aadd dword [0x0], ecx
aadd dword [0x0], ebx
aadd dword [0x0], r15d
aadd dword [0xFF], ecx
aadd dword [0xFF], ebx
aadd dword [0xFF], r15d
aadd dword [rel $ + 0x0], ecx
aadd dword [rel $ + 0x0], ebx
aadd dword [rel $ + 0x0], r15d
aadd dword [rel $ + 0xFF], ecx
aadd dword [rel $ + 0xFF], ebx
aadd dword [rel $ + 0xFF], r15d
aadd dword [rel $ + 0xFFFF], ecx
aadd dword [rel $ + 0xFFFF], ebx
aadd dword [rel $ + 0xFFFF], r15d
aadd dword [rax], ecx
aadd dword [rax], ebx
aadd dword [rax], r15d
aadd dword [rax + 0x0], ecx
aadd dword [rax + 0x0], ebx
aadd dword [rax + 0x0], r15d
aadd dword [rax + 0xFFFF], ecx
aadd dword [rax + 0xFFFF], ebx
aadd dword [rax + 0xFFFF], r15d
aadd dword [r15 + 0xFFFF], ecx
aadd dword [r15 + 0xFFFF], ebx
aadd dword [r15 + 0xFFFF], r15d
aadd dword [rax + rsi * 1  + 0x0], ecx
aadd dword [rax + rsi * 1  + 0x0], ebx
aadd dword [rax + rsi * 1  + 0x0], r15d
aadd dword [rax + rsi + 0xFFFF], ecx
aadd dword [rax + rsi + 0xFFFF], ebx
aadd dword [rax + rsi + 0xFFFF], r15d
aadd dword [r15 + rsi + 0xFFFF], ecx
aadd dword [r15 + rsi + 0xFFFF], ebx
aadd dword [r15 + rsi + 0xFFFF], r15d
aadd dword [rax + r15 + 0xFFFF], ecx
aadd dword [rax + r15 + 0xFFFF], ebx
aadd dword [rax + r15 + 0xFFFF], r15d
aadd dword [rax + rsi * 2 + 0xFFFF2], ecx
aadd dword [rax + rsi * 2 + 0xFFFF2], ebx
aadd dword [rax + rsi * 2 + 0xFFFF2], r15d
aadd dword [rax + rsi * 4 + 0xFFFF4], ecx
aadd dword [rax + rsi * 4 + 0xFFFF4], ebx
aadd dword [rax + rsi * 4 + 0xFFFF4], r15d
aadd dword [rax + rsi * 8 + 0xFFFF8], ecx
aadd dword [rax + rsi * 8 + 0xFFFF8], ebx
aadd dword [rax + rsi * 8 + 0xFFFF8], r15d
aadd dword [rsp + rax * 8 + 0xFFFF8], ecx
aadd dword [rsp + rax * 8 + 0xFFFF8], ebx
aadd dword [rsp + rax * 8 + 0xFFFF8], r15d
aadd dword [r15 + rax * 8 + 0xFFFF8], ecx
aadd dword [r15 + rax * 8 + 0xFFFF8], ebx
aadd dword [r15 + rax * 8 + 0xFFFF8], r15d
aadd dword [rsp + r15 * 8 + 0xFFFF8], ecx
aadd dword [rsp + r15 * 8 + 0xFFFF8], ebx
aadd dword [rsp + r15 * 8 + 0xFFFF8], r15d
aadd dword [r14 + r15 * 8 + 0xFFFF8], ecx
aadd dword [r14 + r15 * 8 + 0xFFFF8], ebx
aadd dword [r14 + r15 * 8 + 0xFFFF8], r15d
aadd qword [0x0], rcx
aadd qword [0x0], rbx
aadd qword [0x0], r15
aadd qword [0xFF], rcx
aadd qword [0xFF], rbx
aadd qword [0xFF], r15
aadd qword [rel $ + 0x0], rcx
aadd qword [rel $ + 0x0], rbx
aadd qword [rel $ + 0x0], r15
aadd qword [rel $ + 0xFF], rcx
aadd qword [rel $ + 0xFF], rbx
aadd qword [rel $ + 0xFF], r15
aadd qword [rel $ + 0xFFFF], rcx
aadd qword [rel $ + 0xFFFF], rbx
aadd qword [rel $ + 0xFFFF], r15
aadd qword [rax], rcx
aadd qword [rax], rbx
aadd qword [rax], r15
aadd qword [rax + 0x0], rcx
aadd qword [rax + 0x0], rbx
aadd qword [rax + 0x0], r15
aadd qword [rax + 0xFFFF], rcx
aadd qword [rax + 0xFFFF], rbx
aadd qword [rax + 0xFFFF], r15
aadd qword [r15 + 0xFFFF], rcx
aadd qword [r15 + 0xFFFF], rbx
aadd qword [r15 + 0xFFFF], r15
aadd qword [rax + rsi * 1  + 0x0], rcx
aadd qword [rax + rsi * 1  + 0x0], rbx
aadd qword [rax + rsi * 1  + 0x0], r15
aadd qword [rax + rsi + 0xFFFF], rcx
aadd qword [rax + rsi + 0xFFFF], rbx
aadd qword [rax + rsi + 0xFFFF], r15
aadd qword [r15 + rsi + 0xFFFF], rcx
aadd qword [r15 + rsi + 0xFFFF], rbx
aadd qword [r15 + rsi + 0xFFFF], r15
aadd qword [rax + r15 + 0xFFFF], rcx
aadd qword [rax + r15 + 0xFFFF], rbx
aadd qword [rax + r15 + 0xFFFF], r15
aadd qword [rax + rsi * 2 + 0xFFFF2], rcx
aadd qword [rax + rsi * 2 + 0xFFFF2], rbx
aadd qword [rax + rsi * 2 + 0xFFFF2], r15
aadd qword [rax + rsi * 4 + 0xFFFF4], rcx
aadd qword [rax + rsi * 4 + 0xFFFF4], rbx
aadd qword [rax + rsi * 4 + 0xFFFF4], r15
aadd qword [rax + rsi * 8 + 0xFFFF8], rcx
aadd qword [rax + rsi * 8 + 0xFFFF8], rbx
aadd qword [rax + rsi * 8 + 0xFFFF8], r15
aadd qword [rsp + rax * 8 + 0xFFFF8], rcx
aadd qword [rsp + rax * 8 + 0xFFFF8], rbx
aadd qword [rsp + rax * 8 + 0xFFFF8], r15
aadd qword [r15 + rax * 8 + 0xFFFF8], rcx
aadd qword [r15 + rax * 8 + 0xFFFF8], rbx
aadd qword [r15 + rax * 8 + 0xFFFF8], r15
aadd qword [rsp + r15 * 8 + 0xFFFF8], rcx
aadd qword [rsp + r15 * 8 + 0xFFFF8], rbx
aadd qword [rsp + r15 * 8 + 0xFFFF8], r15
aadd qword [r14 + r15 * 8 + 0xFFFF8], rcx
aadd qword [r14 + r15 * 8 + 0xFFFF8], rbx
aadd qword [r14 + r15 * 8 + 0xFFFF8], r15
