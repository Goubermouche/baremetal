; expect: d8342500000000d83425ff000000d835faffffffd835f9000000d835f9ff0000d830d830d8b0ffff000041d8b7ffff0000d83430d8b430ffff000041d8b437ffff000042d8b438ffff0000d8b470f2ff0f00d8b4b0f4ff0f00d8b4f0f8ff0f00d8b4c4f8ff0f0041d8b4c7f8ff0f0042d8b4fcf8ff0f0043d8b4fef8ff0f00dc342500000000dc3425ff000000dc35faffffffdc35f9000000dc35f9ff0000dc30dc30dcb0ffff000041dcb7ffff0000dc3430dcb430ffff000041dcb437ffff000042dcb438ffff0000dcb470f2ff0f00dcb4b0f4ff0f00dcb4f0f8ff0f00dcb4c4f8ff0f0041dcb4c7f8ff0f0042dcb4fcf8ff0f0043dcb4fef8ff0f00dcf8d8f1d8f7dcf9dcff

bits 64

fdiv dword [0x0]
fdiv dword [0xFF]
fdiv dword [rel $ + 0x0]
fdiv dword [rel $ + 0xFF]
fdiv dword [rel $ + 0xFFFF]
fdiv dword [rax]
fdiv dword [rax + 0x0]
fdiv dword [rax + 0xFFFF]
fdiv dword [r15 + 0xFFFF]
fdiv dword [rax + rsi * 1  + 0x0]
fdiv dword [rax + rsi + 0xFFFF]
fdiv dword [r15 + rsi + 0xFFFF]
fdiv dword [rax + r15 + 0xFFFF]
fdiv dword [rax + rsi * 2 + 0xFFFF2]
fdiv dword [rax + rsi * 4 + 0xFFFF4]
fdiv dword [rax + rsi * 8 + 0xFFFF8]
fdiv dword [rsp + rax * 8 + 0xFFFF8]
fdiv dword [r15 + rax * 8 + 0xFFFF8]
fdiv dword [rsp + r15 * 8 + 0xFFFF8]
fdiv dword [r14 + r15 * 8 + 0xFFFF8]
fdiv qword [0x0]
fdiv qword [0xFF]
fdiv qword [rel $ + 0x0]
fdiv qword [rel $ + 0xFF]
fdiv qword [rel $ + 0xFFFF]
fdiv qword [rax]
fdiv qword [rax + 0x0]
fdiv qword [rax + 0xFFFF]
fdiv qword [r15 + 0xFFFF]
fdiv qword [rax + rsi * 1  + 0x0]
fdiv qword [rax + rsi + 0xFFFF]
fdiv qword [r15 + rsi + 0xFFFF]
fdiv qword [rax + r15 + 0xFFFF]
fdiv qword [rax + rsi * 2 + 0xFFFF2]
fdiv qword [rax + rsi * 4 + 0xFFFF4]
fdiv qword [rax + rsi * 8 + 0xFFFF8]
fdiv qword [rsp + rax * 8 + 0xFFFF8]
fdiv qword [r15 + rax * 8 + 0xFFFF8]
fdiv qword [rsp + r15 * 8 + 0xFFFF8]
fdiv qword [r14 + r15 * 8 + 0xFFFF8]
fdiv st0, st0
fdiv st0, st1
fdiv st0, st7
fdiv st1, st0
fdiv st7, st0
