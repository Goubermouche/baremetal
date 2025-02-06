; expect: 0f38f90c25000000000f38f91c2500000000440f38f93c25000000000f38f90c25ff0000000f38f91c25ff000000440f38f93c25ff0000000f38f90df8ffffff0f38f91df8ffffff440f38f93df7ffffff0f38f90df70000000f38f91df7000000440f38f93df60000000f38f90df7ff00000f38f91df7ff0000440f38f93df6ff00000f38f9080f38f918440f38f9380f38f9080f38f918440f38f9380f38f988ffff00000f38f998ffff0000440f38f9b8ffff0000410f38f98fffff0000410f38f99fffff0000450f38f9bfffff00000f38f90c300f38f91c30440f38f93c300f38f98c30ffff00000f38f99c30ffff0000440f38f9bc30ffff0000410f38f98c37ffff0000410f38f99c37ffff0000450f38f9bc37ffff0000420f38f98c38ffff0000420f38f99c38ffff0000460f38f9bc38ffff00000f38f98c70f2ff0f000f38f99c70f2ff0f00440f38f9bc70f2ff0f000f38f98cb0f4ff0f000f38f99cb0f4ff0f00440f38f9bcb0f4ff0f000f38f98cf0f8ff0f000f38f99cf0f8ff0f00440f38f9bcf0f8ff0f000f38f98cc4f8ff0f000f38f99cc4f8ff0f00440f38f9bcc4f8ff0f00410f38f98cc7f8ff0f00410f38f99cc7f8ff0f00450f38f9bcc7f8ff0f00420f38f98cfcf8ff0f00420f38f99cfcf8ff0f00460f38f9bcfcf8ff0f00430f38f98cfef8ff0f00430f38f99cfef8ff0f00470f38f9bcfef8ff0f00480f38f90c2500000000480f38f91c25000000004c0f38f93c2500000000480f38f90c25ff000000480f38f91c25ff0000004c0f38f93c25ff000000480f38f90df7ffffff480f38f91df7ffffff4c0f38f93df7ffffff480f38f90df6000000480f38f91df60000004c0f38f93df6000000480f38f90df6ff0000480f38f91df6ff00004c0f38f93df6ff0000480f38f908480f38f9184c0f38f938480f38f908480f38f9184c0f38f938480f38f988ffff0000480f38f998ffff00004c0f38f9b8ffff0000490f38f98fffff0000490f38f99fffff00004d0f38f9bfffff0000480f38f90c30480f38f91c304c0f38f93c30480f38f98c30ffff0000480f38f99c30ffff00004c0f38f9bc30ffff0000490f38f98c37ffff0000490f38f99c37ffff00004d0f38f9bc37ffff00004a0f38f98c38ffff00004a0f38f99c38ffff00004e0f38f9bc38ffff0000480f38f98c70f2ff0f00480f38f99c70f2ff0f004c0f38f9bc70f2ff0f00480f38f98cb0f4ff0f00480f38f99cb0f4ff0f004c0f38f9bcb0f4ff0f00480f38f98cf0f8ff0f00480f38f99cf0f8ff0f004c0f38f9bcf0f8ff0f00480f38f98cc4f8ff0f00480f38f99cc4f8ff0f004c0f38f9bcc4f8ff0f00490f38f98cc7f8ff0f00490f38f99cc7f8ff0f004d0f38f9bcc7f8ff0f004a0f38f98cfcf8ff0f004a0f38f99cfcf8ff0f004e0f38f9bcfcf8ff0f004b0f38f98cfef8ff0f004b0f38f99cfef8ff0f004f0f38f9bcfef8ff0f00

bits 64

movdiri dword [0x0], ecx
movdiri dword [0x0], ebx
movdiri dword [0x0], r15d
movdiri dword [0xFF], ecx
movdiri dword [0xFF], ebx
movdiri dword [0xFF], r15d
movdiri dword [rel $ + 0x0], ecx
movdiri dword [rel $ + 0x0], ebx
movdiri dword [rel $ + 0x0], r15d
movdiri dword [rel $ + 0xFF], ecx
movdiri dword [rel $ + 0xFF], ebx
movdiri dword [rel $ + 0xFF], r15d
movdiri dword [rel $ + 0xFFFF], ecx
movdiri dword [rel $ + 0xFFFF], ebx
movdiri dword [rel $ + 0xFFFF], r15d
movdiri dword [rax], ecx
movdiri dword [rax], ebx
movdiri dword [rax], r15d
movdiri dword [rax + 0x0], ecx
movdiri dword [rax + 0x0], ebx
movdiri dword [rax + 0x0], r15d
movdiri dword [rax + 0xFFFF], ecx
movdiri dword [rax + 0xFFFF], ebx
movdiri dword [rax + 0xFFFF], r15d
movdiri dword [r15 + 0xFFFF], ecx
movdiri dword [r15 + 0xFFFF], ebx
movdiri dword [r15 + 0xFFFF], r15d
movdiri dword [rax + rsi * 1  + 0x0], ecx
movdiri dword [rax + rsi * 1  + 0x0], ebx
movdiri dword [rax + rsi * 1  + 0x0], r15d
movdiri dword [rax + rsi + 0xFFFF], ecx
movdiri dword [rax + rsi + 0xFFFF], ebx
movdiri dword [rax + rsi + 0xFFFF], r15d
movdiri dword [r15 + rsi + 0xFFFF], ecx
movdiri dword [r15 + rsi + 0xFFFF], ebx
movdiri dword [r15 + rsi + 0xFFFF], r15d
movdiri dword [rax + r15 + 0xFFFF], ecx
movdiri dword [rax + r15 + 0xFFFF], ebx
movdiri dword [rax + r15 + 0xFFFF], r15d
movdiri dword [rax + rsi * 2 + 0xFFFF2], ecx
movdiri dword [rax + rsi * 2 + 0xFFFF2], ebx
movdiri dword [rax + rsi * 2 + 0xFFFF2], r15d
movdiri dword [rax + rsi * 4 + 0xFFFF4], ecx
movdiri dword [rax + rsi * 4 + 0xFFFF4], ebx
movdiri dword [rax + rsi * 4 + 0xFFFF4], r15d
movdiri dword [rax + rsi * 8 + 0xFFFF8], ecx
movdiri dword [rax + rsi * 8 + 0xFFFF8], ebx
movdiri dword [rax + rsi * 8 + 0xFFFF8], r15d
movdiri dword [rsp + rax * 8 + 0xFFFF8], ecx
movdiri dword [rsp + rax * 8 + 0xFFFF8], ebx
movdiri dword [rsp + rax * 8 + 0xFFFF8], r15d
movdiri dword [r15 + rax * 8 + 0xFFFF8], ecx
movdiri dword [r15 + rax * 8 + 0xFFFF8], ebx
movdiri dword [r15 + rax * 8 + 0xFFFF8], r15d
movdiri dword [rsp + r15 * 8 + 0xFFFF8], ecx
movdiri dword [rsp + r15 * 8 + 0xFFFF8], ebx
movdiri dword [rsp + r15 * 8 + 0xFFFF8], r15d
movdiri dword [r14 + r15 * 8 + 0xFFFF8], ecx
movdiri dword [r14 + r15 * 8 + 0xFFFF8], ebx
movdiri dword [r14 + r15 * 8 + 0xFFFF8], r15d
movdiri qword [0x0], rcx
movdiri qword [0x0], rbx
movdiri qword [0x0], r15
movdiri qword [0xFF], rcx
movdiri qword [0xFF], rbx
movdiri qword [0xFF], r15
movdiri qword [rel $ + 0x0], rcx
movdiri qword [rel $ + 0x0], rbx
movdiri qword [rel $ + 0x0], r15
movdiri qword [rel $ + 0xFF], rcx
movdiri qword [rel $ + 0xFF], rbx
movdiri qword [rel $ + 0xFF], r15
movdiri qword [rel $ + 0xFFFF], rcx
movdiri qword [rel $ + 0xFFFF], rbx
movdiri qword [rel $ + 0xFFFF], r15
movdiri qword [rax], rcx
movdiri qword [rax], rbx
movdiri qword [rax], r15
movdiri qword [rax + 0x0], rcx
movdiri qword [rax + 0x0], rbx
movdiri qword [rax + 0x0], r15
movdiri qword [rax + 0xFFFF], rcx
movdiri qword [rax + 0xFFFF], rbx
movdiri qword [rax + 0xFFFF], r15
movdiri qword [r15 + 0xFFFF], rcx
movdiri qword [r15 + 0xFFFF], rbx
movdiri qword [r15 + 0xFFFF], r15
movdiri qword [rax + rsi * 1  + 0x0], rcx
movdiri qword [rax + rsi * 1  + 0x0], rbx
movdiri qword [rax + rsi * 1  + 0x0], r15
movdiri qword [rax + rsi + 0xFFFF], rcx
movdiri qword [rax + rsi + 0xFFFF], rbx
movdiri qword [rax + rsi + 0xFFFF], r15
movdiri qword [r15 + rsi + 0xFFFF], rcx
movdiri qword [r15 + rsi + 0xFFFF], rbx
movdiri qword [r15 + rsi + 0xFFFF], r15
movdiri qword [rax + r15 + 0xFFFF], rcx
movdiri qword [rax + r15 + 0xFFFF], rbx
movdiri qword [rax + r15 + 0xFFFF], r15
movdiri qword [rax + rsi * 2 + 0xFFFF2], rcx
movdiri qword [rax + rsi * 2 + 0xFFFF2], rbx
movdiri qword [rax + rsi * 2 + 0xFFFF2], r15
movdiri qword [rax + rsi * 4 + 0xFFFF4], rcx
movdiri qword [rax + rsi * 4 + 0xFFFF4], rbx
movdiri qword [rax + rsi * 4 + 0xFFFF4], r15
movdiri qword [rax + rsi * 8 + 0xFFFF8], rcx
movdiri qword [rax + rsi * 8 + 0xFFFF8], rbx
movdiri qword [rax + rsi * 8 + 0xFFFF8], r15
movdiri qword [rsp + rax * 8 + 0xFFFF8], rcx
movdiri qword [rsp + rax * 8 + 0xFFFF8], rbx
movdiri qword [rsp + rax * 8 + 0xFFFF8], r15
movdiri qword [r15 + rax * 8 + 0xFFFF8], rcx
movdiri qword [r15 + rax * 8 + 0xFFFF8], rbx
movdiri qword [r15 + rax * 8 + 0xFFFF8], r15
movdiri qword [rsp + r15 * 8 + 0xFFFF8], rcx
movdiri qword [rsp + r15 * 8 + 0xFFFF8], rbx
movdiri qword [rsp + r15 * 8 + 0xFFFF8], r15
movdiri qword [r14 + r15 * 8 + 0xFFFF8], rcx
movdiri qword [r14 + r15 * 8 + 0xFFFF8], rbx
movdiri qword [r14 + r15 * 8 + 0xFFFF8], r15
