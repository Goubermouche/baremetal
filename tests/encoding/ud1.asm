; expect: 0fb9c90fb9cb410fb9cf0fb9d90fb9db410fb9df440fb9f9440fb9fb450fb9ff0fb90c25000000000fb90c25ff0000000fb90df9ffffff0fb90df80000000fb90df8ff00000fb9080fb9080fb988ffff0000410fb98fffff00000fb90c300fb98c30ffff0000410fb98c37ffff0000420fb98c38ffff00000fb98c70f2ff0f000fb98cb0f4ff0f000fb98cf0f8ff0f000fb98cc4f8ff0f00410fb98cc7f8ff0f00420fb98cfcf8ff0f00430fb98cfef8ff0f000fb91c25000000000fb91c25ff0000000fb91df9ffffff0fb91df80000000fb91df8ff00000fb9180fb9180fb998ffff0000410fb99fffff00000fb91c300fb99c30ffff0000410fb99c37ffff0000420fb99c38ffff00000fb99c70f2ff0f000fb99cb0f4ff0f000fb99cf0f8ff0f000fb99cc4f8ff0f00410fb99cc7f8ff0f00420fb99cfcf8ff0f00430fb99cfef8ff0f00440fb93c2500000000440fb93c25ff000000440fb93df8ffffff440fb93df7000000440fb93df7ff0000440fb938440fb938440fb9b8ffff0000450fb9bfffff0000440fb93c30440fb9bc30ffff0000450fb9bc37ffff0000460fb9bc38ffff0000440fb9bc70f2ff0f00440fb9bcb0f4ff0f00440fb9bcf0f8ff0f00440fb9bcc4f8ff0f00450fb9bcc7f8ff0f00460fb9bcfcf8ff0f00470fb9bcfef8ff0f00

bits 64

ud1 ecx, ecx
ud1 ecx, ebx
ud1 ecx, r15d
ud1 ebx, ecx
ud1 ebx, ebx
ud1 ebx, r15d
ud1 r15d, ecx
ud1 r15d, ebx
ud1 r15d, r15d
ud1 ecx, dword [0x0]
ud1 ecx, dword [0xFF]
ud1 ecx, dword [rel $ + 0x0]
ud1 ecx, dword [rel $ + 0xFF]
ud1 ecx, dword [rel $ + 0xFFFF]
ud1 ecx, dword [rax]
ud1 ecx, dword [rax + 0x0]
ud1 ecx, dword [rax + 0xFFFF]
ud1 ecx, dword [r15 + 0xFFFF]
ud1 ecx, dword [rax + rsi * 1  + 0x0]
ud1 ecx, dword [rax + rsi + 0xFFFF]
ud1 ecx, dword [r15 + rsi + 0xFFFF]
ud1 ecx, dword [rax + r15 + 0xFFFF]
ud1 ecx, dword [rax + rsi * 2 + 0xFFFF2]
ud1 ecx, dword [rax + rsi * 4 + 0xFFFF4]
ud1 ecx, dword [rax + rsi * 8 + 0xFFFF8]
ud1 ecx, dword [rsp + rax * 8 + 0xFFFF8]
ud1 ecx, dword [r15 + rax * 8 + 0xFFFF8]
ud1 ecx, dword [rsp + r15 * 8 + 0xFFFF8]
ud1 ecx, dword [r14 + r15 * 8 + 0xFFFF8]
ud1 ebx, dword [0x0]
ud1 ebx, dword [0xFF]
ud1 ebx, dword [rel $ + 0x0]
ud1 ebx, dword [rel $ + 0xFF]
ud1 ebx, dword [rel $ + 0xFFFF]
ud1 ebx, dword [rax]
ud1 ebx, dword [rax + 0x0]
ud1 ebx, dword [rax + 0xFFFF]
ud1 ebx, dword [r15 + 0xFFFF]
ud1 ebx, dword [rax + rsi * 1  + 0x0]
ud1 ebx, dword [rax + rsi + 0xFFFF]
ud1 ebx, dword [r15 + rsi + 0xFFFF]
ud1 ebx, dword [rax + r15 + 0xFFFF]
ud1 ebx, dword [rax + rsi * 2 + 0xFFFF2]
ud1 ebx, dword [rax + rsi * 4 + 0xFFFF4]
ud1 ebx, dword [rax + rsi * 8 + 0xFFFF8]
ud1 ebx, dword [rsp + rax * 8 + 0xFFFF8]
ud1 ebx, dword [r15 + rax * 8 + 0xFFFF8]
ud1 ebx, dword [rsp + r15 * 8 + 0xFFFF8]
ud1 ebx, dword [r14 + r15 * 8 + 0xFFFF8]
ud1 r15d, dword [0x0]
ud1 r15d, dword [0xFF]
ud1 r15d, dword [rel $ + 0x0]
ud1 r15d, dword [rel $ + 0xFF]
ud1 r15d, dword [rel $ + 0xFFFF]
ud1 r15d, dword [rax]
ud1 r15d, dword [rax + 0x0]
ud1 r15d, dword [rax + 0xFFFF]
ud1 r15d, dword [r15 + 0xFFFF]
ud1 r15d, dword [rax + rsi * 1  + 0x0]
ud1 r15d, dword [rax + rsi + 0xFFFF]
ud1 r15d, dword [r15 + rsi + 0xFFFF]
ud1 r15d, dword [rax + r15 + 0xFFFF]
ud1 r15d, dword [rax + rsi * 2 + 0xFFFF2]
ud1 r15d, dword [rax + rsi * 4 + 0xFFFF4]
ud1 r15d, dword [rax + rsi * 8 + 0xFFFF8]
ud1 r15d, dword [rsp + rax * 8 + 0xFFFF8]
ud1 r15d, dword [r15 + rax * 8 + 0xFFFF8]
ud1 r15d, dword [rsp + r15 * 8 + 0xFFFF8]
ud1 r15d, dword [r14 + r15 * 8 + 0xFFFF8]
