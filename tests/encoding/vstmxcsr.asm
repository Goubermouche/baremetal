; expect: c5f8ae1c2500000000c5f8ae1c25ff000000c5f8ae1df8ffffffc5f8ae1df7000000c5f8ae1df7ff0000c5f8ae18c5f8ae18c5f8ae98ffff0000c4c178ae9fffff0000c5f8ae1c30c5f8ae9c30ffff0000c4c178ae9c37ffff0000c4a178ae9c38ffff0000c5f8ae9c70f2ff0f00c5f8ae9cb0f4ff0f00c5f8ae9cf0f8ff0f00c5f8ae9cc4f8ff0f00c4c178ae9cc7f8ff0f00c4a178ae9cfcf8ff0f00c48178ae9cfef8ff0f00

bits 64

vstmxcsr dword [0x0]
vstmxcsr dword [0xFF]
vstmxcsr dword [rel $ + 0x0]
vstmxcsr dword [rel $ + 0xFF]
vstmxcsr dword [rel $ + 0xFFFF]
vstmxcsr dword [rax]
vstmxcsr dword [rax + 0x0]
vstmxcsr dword [rax + 0xFFFF]
vstmxcsr dword [r15 + 0xFFFF]
vstmxcsr dword [rax + rsi * 1  + 0x0]
vstmxcsr dword [rax + rsi + 0xFFFF]
vstmxcsr dword [r15 + rsi + 0xFFFF]
vstmxcsr dword [rax + r15 + 0xFFFF]
vstmxcsr dword [rax + rsi * 2 + 0xFFFF2]
vstmxcsr dword [rax + rsi * 4 + 0xFFFF4]
vstmxcsr dword [rax + rsi * 8 + 0xFFFF8]
vstmxcsr dword [rsp + rax * 8 + 0xFFFF8]
vstmxcsr dword [r15 + rax * 8 + 0xFFFF8]
vstmxcsr dword [rsp + r15 * 8 + 0xFFFF8]
vstmxcsr dword [r14 + r15 * 8 + 0xFFFF8]
