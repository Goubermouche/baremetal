; expect: 0fae1425000000000fae1425ff0000000fae15f9ffffff0fae15f80000000fae15f8ff00000fae100fae100fae90ffff0000410fae97ffff00000fae14300fae9430ffff0000410fae9437ffff0000420fae9438ffff00000fae9470f2ff0f000fae94b0f4ff0f000fae94f0f8ff0f000fae94c4f8ff0f00410fae94c7f8ff0f00420fae94fcf8ff0f00430fae94fef8ff0f00

bits 64

ldmxcsr dword [0x0]
ldmxcsr dword [0xFF]
ldmxcsr dword [rel $ + 0x0]
ldmxcsr dword [rel $ + 0xFF]
ldmxcsr dword [rel $ + 0xFFFF]
ldmxcsr dword [rax]
ldmxcsr dword [rax + 0x0]
ldmxcsr dword [rax + 0xFFFF]
ldmxcsr dword [r15 + 0xFFFF]
ldmxcsr dword [rax + rsi * 1  + 0x0]
ldmxcsr dword [rax + rsi + 0xFFFF]
ldmxcsr dword [r15 + rsi + 0xFFFF]
ldmxcsr dword [rax + r15 + 0xFFFF]
ldmxcsr dword [rax + rsi * 2 + 0xFFFF2]
ldmxcsr dword [rax + rsi * 4 + 0xFFFF4]
ldmxcsr dword [rax + rsi * 8 + 0xFFFF8]
ldmxcsr dword [rsp + rax * 8 + 0xFFFF8]
ldmxcsr dword [r15 + rax * 8 + 0xFFFF8]
ldmxcsr dword [rsp + r15 * 8 + 0xFFFF8]
ldmxcsr dword [r14 + r15 * 8 + 0xFFFF8]
