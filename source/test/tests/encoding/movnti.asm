; expect: 0fc30c25000000000fc31c2500000000440fc33c25000000000fc30c25ff0000000fc31c25ff000000440fc33c25ff0000000fc30df9ffffff0fc31df9ffffff440fc33df8ffffff0fc30df80000000fc31df8000000440fc33df70000000fc30df8ff00000fc31df8ff0000440fc33df7ff00000fc3080fc318440fc3380fc3080fc318440fc3380fc388ffff00000fc398ffff0000440fc3b8ffff0000410fc38fffff0000410fc39fffff0000450fc3bfffff00000fc30c300fc31c30440fc33c300fc38c30ffff00000fc39c30ffff0000440fc3bc30ffff0000410fc38c37ffff0000410fc39c37ffff0000450fc3bc37ffff0000420fc38c38ffff0000420fc39c38ffff0000460fc3bc38ffff00000fc38c70f2ff0f000fc39c70f2ff0f00440fc3bc70f2ff0f000fc38cb0f4ff0f000fc39cb0f4ff0f00440fc3bcb0f4ff0f000fc38cf0f8ff0f000fc39cf0f8ff0f00440fc3bcf0f8ff0f000fc38cc4f8ff0f000fc39cc4f8ff0f00440fc3bcc4f8ff0f00410fc38cc7f8ff0f00410fc39cc7f8ff0f00450fc3bcc7f8ff0f00420fc38cfcf8ff0f00420fc39cfcf8ff0f00460fc3bcfcf8ff0f00430fc38cfef8ff0f00430fc39cfef8ff0f00470fc3bcfef8ff0f00480fc30c2500000000480fc31c25000000004c0fc33c2500000000480fc30c25ff000000480fc31c25ff0000004c0fc33c25ff000000480fc30df8ffffff480fc31df8ffffff4c0fc33df8ffffff480fc30df7000000480fc31df70000004c0fc33df7000000480fc30df7ff0000480fc31df7ff00004c0fc33df7ff0000480fc308480fc3184c0fc338480fc308480fc3184c0fc338480fc388ffff0000480fc398ffff00004c0fc3b8ffff0000490fc38fffff0000490fc39fffff00004d0fc3bfffff0000480fc30c30480fc31c304c0fc33c30480fc38c30ffff0000480fc39c30ffff00004c0fc3bc30ffff0000490fc38c37ffff0000490fc39c37ffff00004d0fc3bc37ffff00004a0fc38c38ffff00004a0fc39c38ffff00004e0fc3bc38ffff0000480fc38c70f2ff0f00480fc39c70f2ff0f004c0fc3bc70f2ff0f00480fc38cb0f4ff0f00480fc39cb0f4ff0f004c0fc3bcb0f4ff0f00480fc38cf0f8ff0f00480fc39cf0f8ff0f004c0fc3bcf0f8ff0f00480fc38cc4f8ff0f00480fc39cc4f8ff0f004c0fc3bcc4f8ff0f00490fc38cc7f8ff0f00490fc39cc7f8ff0f004d0fc3bcc7f8ff0f004a0fc38cfcf8ff0f004a0fc39cfcf8ff0f004e0fc3bcfcf8ff0f004b0fc38cfef8ff0f004b0fc39cfef8ff0f004f0fc3bcfef8ff0f00

movnti dword [0x0], ecx
movnti dword [0x0], ebx
movnti dword [0x0], r15d
movnti dword [0xFF], ecx
movnti dword [0xFF], ebx
movnti dword [0xFF], r15d
movnti dword [rel $ + 0x0], ecx
movnti dword [rel $ + 0x0], ebx
movnti dword [rel $ + 0x0], r15d
movnti dword [rel $ + 0xFF], ecx
movnti dword [rel $ + 0xFF], ebx
movnti dword [rel $ + 0xFF], r15d
movnti dword [rel $ + 0xFFFF], ecx
movnti dword [rel $ + 0xFFFF], ebx
movnti dword [rel $ + 0xFFFF], r15d
movnti dword [rax], ecx
movnti dword [rax], ebx
movnti dword [rax], r15d
movnti dword [rax + 0x0], ecx
movnti dword [rax + 0x0], ebx
movnti dword [rax + 0x0], r15d
movnti dword [rax + 0xFFFF], ecx
movnti dword [rax + 0xFFFF], ebx
movnti dword [rax + 0xFFFF], r15d
movnti dword [r15 + 0xFFFF], ecx
movnti dword [r15 + 0xFFFF], ebx
movnti dword [r15 + 0xFFFF], r15d
movnti dword [rax + rsi * 1  + 0x0], ecx
movnti dword [rax + rsi * 1  + 0x0], ebx
movnti dword [rax + rsi * 1  + 0x0], r15d
movnti dword [rax + rsi + 0xFFFF], ecx
movnti dword [rax + rsi + 0xFFFF], ebx
movnti dword [rax + rsi + 0xFFFF], r15d
movnti dword [r15 + rsi + 0xFFFF], ecx
movnti dword [r15 + rsi + 0xFFFF], ebx
movnti dword [r15 + rsi + 0xFFFF], r15d
movnti dword [rax + r15 + 0xFFFF], ecx
movnti dword [rax + r15 + 0xFFFF], ebx
movnti dword [rax + r15 + 0xFFFF], r15d
movnti dword [rax + rsi * 2 + 0xFFFF2], ecx
movnti dword [rax + rsi * 2 + 0xFFFF2], ebx
movnti dword [rax + rsi * 2 + 0xFFFF2], r15d
movnti dword [rax + rsi * 4 + 0xFFFF4], ecx
movnti dword [rax + rsi * 4 + 0xFFFF4], ebx
movnti dword [rax + rsi * 4 + 0xFFFF4], r15d
movnti dword [rax + rsi * 8 + 0xFFFF8], ecx
movnti dword [rax + rsi * 8 + 0xFFFF8], ebx
movnti dword [rax + rsi * 8 + 0xFFFF8], r15d
movnti dword [rsp + rax * 8 + 0xFFFF8], ecx
movnti dword [rsp + rax * 8 + 0xFFFF8], ebx
movnti dword [rsp + rax * 8 + 0xFFFF8], r15d
movnti dword [r15 + rax * 8 + 0xFFFF8], ecx
movnti dword [r15 + rax * 8 + 0xFFFF8], ebx
movnti dword [r15 + rax * 8 + 0xFFFF8], r15d
movnti dword [rsp + r15 * 8 + 0xFFFF8], ecx
movnti dword [rsp + r15 * 8 + 0xFFFF8], ebx
movnti dword [rsp + r15 * 8 + 0xFFFF8], r15d
movnti dword [r14 + r15 * 8 + 0xFFFF8], ecx
movnti dword [r14 + r15 * 8 + 0xFFFF8], ebx
movnti dword [r14 + r15 * 8 + 0xFFFF8], r15d
movnti qword [0x0], rcx
movnti qword [0x0], rbx
movnti qword [0x0], r15
movnti qword [0xFF], rcx
movnti qword [0xFF], rbx
movnti qword [0xFF], r15
movnti qword [rel $ + 0x0], rcx
movnti qword [rel $ + 0x0], rbx
movnti qword [rel $ + 0x0], r15
movnti qword [rel $ + 0xFF], rcx
movnti qword [rel $ + 0xFF], rbx
movnti qword [rel $ + 0xFF], r15
movnti qword [rel $ + 0xFFFF], rcx
movnti qword [rel $ + 0xFFFF], rbx
movnti qword [rel $ + 0xFFFF], r15
movnti qword [rax], rcx
movnti qword [rax], rbx
movnti qword [rax], r15
movnti qword [rax + 0x0], rcx
movnti qword [rax + 0x0], rbx
movnti qword [rax + 0x0], r15
movnti qword [rax + 0xFFFF], rcx
movnti qword [rax + 0xFFFF], rbx
movnti qword [rax + 0xFFFF], r15
movnti qword [r15 + 0xFFFF], rcx
movnti qword [r15 + 0xFFFF], rbx
movnti qword [r15 + 0xFFFF], r15
movnti qword [rax + rsi * 1  + 0x0], rcx
movnti qword [rax + rsi * 1  + 0x0], rbx
movnti qword [rax + rsi * 1  + 0x0], r15
movnti qword [rax + rsi + 0xFFFF], rcx
movnti qword [rax + rsi + 0xFFFF], rbx
movnti qword [rax + rsi + 0xFFFF], r15
movnti qword [r15 + rsi + 0xFFFF], rcx
movnti qword [r15 + rsi + 0xFFFF], rbx
movnti qword [r15 + rsi + 0xFFFF], r15
movnti qword [rax + r15 + 0xFFFF], rcx
movnti qword [rax + r15 + 0xFFFF], rbx
movnti qword [rax + r15 + 0xFFFF], r15
movnti qword [rax + rsi * 2 + 0xFFFF2], rcx
movnti qword [rax + rsi * 2 + 0xFFFF2], rbx
movnti qword [rax + rsi * 2 + 0xFFFF2], r15
movnti qword [rax + rsi * 4 + 0xFFFF4], rcx
movnti qword [rax + rsi * 4 + 0xFFFF4], rbx
movnti qword [rax + rsi * 4 + 0xFFFF4], r15
movnti qword [rax + rsi * 8 + 0xFFFF8], rcx
movnti qword [rax + rsi * 8 + 0xFFFF8], rbx
movnti qword [rax + rsi * 8 + 0xFFFF8], r15
movnti qword [rsp + rax * 8 + 0xFFFF8], rcx
movnti qword [rsp + rax * 8 + 0xFFFF8], rbx
movnti qword [rsp + rax * 8 + 0xFFFF8], r15
movnti qword [r15 + rax * 8 + 0xFFFF8], rcx
movnti qword [r15 + rax * 8 + 0xFFFF8], rbx
movnti qword [r15 + rax * 8 + 0xFFFF8], r15
movnti qword [rsp + r15 * 8 + 0xFFFF8], rcx
movnti qword [rsp + r15 * 8 + 0xFFFF8], rbx
movnti qword [rsp + r15 * 8 + 0xFFFF8], r15
movnti qword [r14 + r15 * 8 + 0xFFFF8], rcx
movnti qword [r14 + r15 * 8 + 0xFFFF8], rbx
movnti qword [r14 + r15 * 8 + 0xFFFF8], r15