; expect: 0fae1c25000000000fae1c25ff0000000fae1df9ffffff0fae1df80000000fae1df8ff00000fae180fae180fae98ffff0000410fae9fffff00000fae1c300fae9c30ffff0000410fae9c37ffff0000420fae9c38ffff00000fae9c70f2ff0f000fae9cb0f4ff0f000fae9cf0f8ff0f000fae9cc4f8ff0f00410fae9cc7f8ff0f00420fae9cfcf8ff0f00430fae9cfef8ff0f00

bits 64

stmxcsr dword [0x0]
stmxcsr dword [0xFF]
stmxcsr dword [rel $ + 0x0]
stmxcsr dword [rel $ + 0xFF]
stmxcsr dword [rel $ + 0xFFFF]
stmxcsr dword [rax]
stmxcsr dword [rax + 0x0]
stmxcsr dword [rax + 0xFFFF]
stmxcsr dword [r15 + 0xFFFF]
stmxcsr dword [rax + rsi * 1  + 0x0]
stmxcsr dword [rax + rsi + 0xFFFF]
stmxcsr dword [r15 + rsi + 0xFFFF]
stmxcsr dword [rax + r15 + 0xFFFF]
stmxcsr dword [rax + rsi * 2 + 0xFFFF2]
stmxcsr dword [rax + rsi * 4 + 0xFFFF4]
stmxcsr dword [rax + rsi * 8 + 0xFFFF8]
stmxcsr dword [rsp + rax * 8 + 0xFFFF8]
stmxcsr dword [r15 + rax * 8 + 0xFFFF8]
stmxcsr dword [rsp + r15 * 8 + 0xFFFF8]
stmxcsr dword [r14 + r15 * 8 + 0xFFFF8]
