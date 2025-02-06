; expect: d8042500000000d80425ff000000d805faffffffd805f9000000d805f9ff0000d800d800d880ffff000041d887ffff0000d80430d88430ffff000041d88437ffff000042d88438ffff0000d88470f2ff0f00d884b0f4ff0f00d884f0f8ff0f00d884c4f8ff0f0041d884c7f8ff0f0042d884fcf8ff0f0043d884fef8ff0f00dc042500000000dc0425ff000000dc05faffffffdc05f9000000dc05f9ff0000dc00dc00dc80ffff000041dc87ffff0000dc0430dc8430ffff000041dc8437ffff000042dc8438ffff0000dc8470f2ff0f00dc84b0f4ff0f00dc84f0f8ff0f00dc84c4f8ff0f0041dc84c7f8ff0f0042dc84fcf8ff0f0043dc84fef8ff0f00dcc0d8c1d8c7dcc1dcc7

bits 64

fadd dword [0x0]
fadd dword [0xFF]
fadd dword [rel $ + 0x0]
fadd dword [rel $ + 0xFF]
fadd dword [rel $ + 0xFFFF]
fadd dword [rax]
fadd dword [rax + 0x0]
fadd dword [rax + 0xFFFF]
fadd dword [r15 + 0xFFFF]
fadd dword [rax + rsi * 1  + 0x0]
fadd dword [rax + rsi + 0xFFFF]
fadd dword [r15 + rsi + 0xFFFF]
fadd dword [rax + r15 + 0xFFFF]
fadd dword [rax + rsi * 2 + 0xFFFF2]
fadd dword [rax + rsi * 4 + 0xFFFF4]
fadd dword [rax + rsi * 8 + 0xFFFF8]
fadd dword [rsp + rax * 8 + 0xFFFF8]
fadd dword [r15 + rax * 8 + 0xFFFF8]
fadd dword [rsp + r15 * 8 + 0xFFFF8]
fadd dword [r14 + r15 * 8 + 0xFFFF8]
fadd qword [0x0]
fadd qword [0xFF]
fadd qword [rel $ + 0x0]
fadd qword [rel $ + 0xFF]
fadd qword [rel $ + 0xFFFF]
fadd qword [rax]
fadd qword [rax + 0x0]
fadd qword [rax + 0xFFFF]
fadd qword [r15 + 0xFFFF]
fadd qword [rax + rsi * 1  + 0x0]
fadd qword [rax + rsi + 0xFFFF]
fadd qword [r15 + rsi + 0xFFFF]
fadd qword [rax + r15 + 0xFFFF]
fadd qword [rax + rsi * 2 + 0xFFFF2]
fadd qword [rax + rsi * 4 + 0xFFFF4]
fadd qword [rax + rsi * 8 + 0xFFFF8]
fadd qword [rsp + rax * 8 + 0xFFFF8]
fadd qword [r15 + rax * 8 + 0xFFFF8]
fadd qword [rsp + r15 * 8 + 0xFFFF8]
fadd qword [r14 + r15 * 8 + 0xFFFF8]
fadd st0, st0
fadd st0, st1
fadd st0, st7
fadd st1, st0
fadd st7, st0
