; expect: 0fffc90fffcb410fffcf0fffd90fffdb410fffdf440ffff9440ffffb450fffff0fff0c25000000000fff0c25ff0000000fff0df9ffffff0fff0df80000000fff0df8ff00000fff080fff080fff88ffff0000410fff8fffff00000fff0c300fff8c30ffff0000410fff8c37ffff0000420fff8c38ffff00000fff8c70f2ff0f000fff8cb0f4ff0f000fff8cf0f8ff0f000fff8cc4f8ff0f00410fff8cc7f8ff0f00420fff8cfcf8ff0f00430fff8cfef8ff0f000fff1c25000000000fff1c25ff0000000fff1df9ffffff0fff1df80000000fff1df8ff00000fff180fff180fff98ffff0000410fff9fffff00000fff1c300fff9c30ffff0000410fff9c37ffff0000420fff9c38ffff00000fff9c70f2ff0f000fff9cb0f4ff0f000fff9cf0f8ff0f000fff9cc4f8ff0f00410fff9cc7f8ff0f00420fff9cfcf8ff0f00430fff9cfef8ff0f00440fff3c2500000000440fff3c25ff000000440fff3df8ffffff440fff3df7000000440fff3df7ff0000440fff38440fff38440fffb8ffff0000450fffbfffff0000440fff3c30440fffbc30ffff0000450fffbc37ffff0000460fffbc38ffff0000440fffbc70f2ff0f00440fffbcb0f4ff0f00440fffbcf0f8ff0f00440fffbcc4f8ff0f00450fffbcc7f8ff0f00460fffbcfcf8ff0f00470fffbcfef8ff0f00

bits 64

ud0 ecx, ecx
ud0 ecx, ebx
ud0 ecx, r15d
ud0 ebx, ecx
ud0 ebx, ebx
ud0 ebx, r15d
ud0 r15d, ecx
ud0 r15d, ebx
ud0 r15d, r15d
ud0 ecx, dword [0x0]
ud0 ecx, dword [0xFF]
ud0 ecx, dword [rel $ + 0x0]
ud0 ecx, dword [rel $ + 0xFF]
ud0 ecx, dword [rel $ + 0xFFFF]
ud0 ecx, dword [rax]
ud0 ecx, dword [rax + 0x0]
ud0 ecx, dword [rax + 0xFFFF]
ud0 ecx, dword [r15 + 0xFFFF]
ud0 ecx, dword [rax + rsi * 1  + 0x0]
ud0 ecx, dword [rax + rsi + 0xFFFF]
ud0 ecx, dword [r15 + rsi + 0xFFFF]
ud0 ecx, dword [rax + r15 + 0xFFFF]
ud0 ecx, dword [rax + rsi * 2 + 0xFFFF2]
ud0 ecx, dword [rax + rsi * 4 + 0xFFFF4]
ud0 ecx, dword [rax + rsi * 8 + 0xFFFF8]
ud0 ecx, dword [rsp + rax * 8 + 0xFFFF8]
ud0 ecx, dword [r15 + rax * 8 + 0xFFFF8]
ud0 ecx, dword [rsp + r15 * 8 + 0xFFFF8]
ud0 ecx, dword [r14 + r15 * 8 + 0xFFFF8]
ud0 ebx, dword [0x0]
ud0 ebx, dword [0xFF]
ud0 ebx, dword [rel $ + 0x0]
ud0 ebx, dword [rel $ + 0xFF]
ud0 ebx, dword [rel $ + 0xFFFF]
ud0 ebx, dword [rax]
ud0 ebx, dword [rax + 0x0]
ud0 ebx, dword [rax + 0xFFFF]
ud0 ebx, dword [r15 + 0xFFFF]
ud0 ebx, dword [rax + rsi * 1  + 0x0]
ud0 ebx, dword [rax + rsi + 0xFFFF]
ud0 ebx, dword [r15 + rsi + 0xFFFF]
ud0 ebx, dword [rax + r15 + 0xFFFF]
ud0 ebx, dword [rax + rsi * 2 + 0xFFFF2]
ud0 ebx, dword [rax + rsi * 4 + 0xFFFF4]
ud0 ebx, dword [rax + rsi * 8 + 0xFFFF8]
ud0 ebx, dword [rsp + rax * 8 + 0xFFFF8]
ud0 ebx, dword [r15 + rax * 8 + 0xFFFF8]
ud0 ebx, dword [rsp + r15 * 8 + 0xFFFF8]
ud0 ebx, dword [r14 + r15 * 8 + 0xFFFF8]
ud0 r15d, dword [0x0]
ud0 r15d, dword [0xFF]
ud0 r15d, dword [rel $ + 0x0]
ud0 r15d, dword [rel $ + 0xFF]
ud0 r15d, dword [rel $ + 0xFFFF]
ud0 r15d, dword [rax]
ud0 r15d, dword [rax + 0x0]
ud0 r15d, dword [rax + 0xFFFF]
ud0 r15d, dword [r15 + 0xFFFF]
ud0 r15d, dword [rax + rsi * 1  + 0x0]
ud0 r15d, dword [rax + rsi + 0xFFFF]
ud0 r15d, dword [r15 + rsi + 0xFFFF]
ud0 r15d, dword [rax + r15 + 0xFFFF]
ud0 r15d, dword [rax + rsi * 2 + 0xFFFF2]
ud0 r15d, dword [rax + rsi * 4 + 0xFFFF4]
ud0 r15d, dword [rax + rsi * 8 + 0xFFFF8]
ud0 r15d, dword [rsp + rax * 8 + 0xFFFF8]
ud0 r15d, dword [r15 + rax * 8 + 0xFFFF8]
ud0 r15d, dword [rsp + r15 * 8 + 0xFFFF8]
ud0 r15d, dword [r14 + r15 * 8 + 0xFFFF8]
