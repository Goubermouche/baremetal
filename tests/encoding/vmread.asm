; expect: 0f78c90f78d9440f78f90f78cb0f78db440f78fb410f78cf410f78df450f78ff0f780c25000000000f781c2500000000440f783c25000000000f780c25ff0000000f781c25ff000000440f783c25ff0000000f780df9ffffff0f781df9ffffff440f783df8ffffff0f780df80000000f781df8000000440f783df70000000f780df8ff00000f781df8ff0000440f783df7ff00000f78080f7818440f78380f78080f7818440f78380f7888ffff00000f7898ffff0000440f78b8ffff0000410f788fffff0000410f789fffff0000450f78bfffff00000f780c300f781c30440f783c300f788c30ffff00000f789c30ffff0000440f78bc30ffff0000410f788c37ffff0000410f789c37ffff0000450f78bc37ffff0000420f788c38ffff0000420f789c38ffff0000460f78bc38ffff00000f788c70f2ff0f000f789c70f2ff0f00440f78bc70f2ff0f000f788cb0f4ff0f000f789cb0f4ff0f00440f78bcb0f4ff0f000f788cf0f8ff0f000f789cf0f8ff0f00440f78bcf0f8ff0f000f788cc4f8ff0f000f789cc4f8ff0f00440f78bcc4f8ff0f00410f788cc7f8ff0f00410f789cc7f8ff0f00450f78bcc7f8ff0f00420f788cfcf8ff0f00420f789cfcf8ff0f00460f78bcfcf8ff0f00430f788cfef8ff0f00430f789cfef8ff0f00470f78bcfef8ff0f00

bits 64

vmread rcx, rcx
vmread rcx, rbx
vmread rcx, r15
vmread rbx, rcx
vmread rbx, rbx
vmread rbx, r15
vmread r15, rcx
vmread r15, rbx
vmread r15, r15
vmread qword [0x0], rcx
vmread qword [0x0], rbx
vmread qword [0x0], r15
vmread qword [0xFF], rcx
vmread qword [0xFF], rbx
vmread qword [0xFF], r15
vmread qword [rel $ + 0x0], rcx
vmread qword [rel $ + 0x0], rbx
vmread qword [rel $ + 0x0], r15
vmread qword [rel $ + 0xFF], rcx
vmread qword [rel $ + 0xFF], rbx
vmread qword [rel $ + 0xFF], r15
vmread qword [rel $ + 0xFFFF], rcx
vmread qword [rel $ + 0xFFFF], rbx
vmread qword [rel $ + 0xFFFF], r15
vmread qword [rax], rcx
vmread qword [rax], rbx
vmread qword [rax], r15
vmread qword [rax + 0x0], rcx
vmread qword [rax + 0x0], rbx
vmread qword [rax + 0x0], r15
vmread qword [rax + 0xFFFF], rcx
vmread qword [rax + 0xFFFF], rbx
vmread qword [rax + 0xFFFF], r15
vmread qword [r15 + 0xFFFF], rcx
vmread qword [r15 + 0xFFFF], rbx
vmread qword [r15 + 0xFFFF], r15
vmread qword [rax + rsi * 1  + 0x0], rcx
vmread qword [rax + rsi * 1  + 0x0], rbx
vmread qword [rax + rsi * 1  + 0x0], r15
vmread qword [rax + rsi + 0xFFFF], rcx
vmread qword [rax + rsi + 0xFFFF], rbx
vmread qword [rax + rsi + 0xFFFF], r15
vmread qword [r15 + rsi + 0xFFFF], rcx
vmread qword [r15 + rsi + 0xFFFF], rbx
vmread qword [r15 + rsi + 0xFFFF], r15
vmread qword [rax + r15 + 0xFFFF], rcx
vmread qword [rax + r15 + 0xFFFF], rbx
vmread qword [rax + r15 + 0xFFFF], r15
vmread qword [rax + rsi * 2 + 0xFFFF2], rcx
vmread qword [rax + rsi * 2 + 0xFFFF2], rbx
vmread qword [rax + rsi * 2 + 0xFFFF2], r15
vmread qword [rax + rsi * 4 + 0xFFFF4], rcx
vmread qword [rax + rsi * 4 + 0xFFFF4], rbx
vmread qword [rax + rsi * 4 + 0xFFFF4], r15
vmread qword [rax + rsi * 8 + 0xFFFF8], rcx
vmread qword [rax + rsi * 8 + 0xFFFF8], rbx
vmread qword [rax + rsi * 8 + 0xFFFF8], r15
vmread qword [rsp + rax * 8 + 0xFFFF8], rcx
vmread qword [rsp + rax * 8 + 0xFFFF8], rbx
vmread qword [rsp + rax * 8 + 0xFFFF8], r15
vmread qword [r15 + rax * 8 + 0xFFFF8], rcx
vmread qword [r15 + rax * 8 + 0xFFFF8], rbx
vmread qword [r15 + rax * 8 + 0xFFFF8], r15
vmread qword [rsp + r15 * 8 + 0xFFFF8], rcx
vmread qword [rsp + r15 * 8 + 0xFFFF8], rbx
vmread qword [rsp + r15 * 8 + 0xFFFF8], r15
vmread qword [r14 + r15 * 8 + 0xFFFF8], rcx
vmread qword [r14 + r15 * 8 + 0xFFFF8], rbx
vmread qword [r14 + r15 * 8 + 0xFFFF8], r15
