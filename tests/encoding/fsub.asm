; expect: d8242500000000d82425ff000000d825faffffffd825f9000000d825f9ff0000d820d820d8a0ffff000041d8a7ffff0000d82430d8a430ffff000041d8a437ffff000042d8a438ffff0000d8a470f2ff0f00d8a4b0f4ff0f00d8a4f0f8ff0f00d8a4c4f8ff0f0041d8a4c7f8ff0f0042d8a4fcf8ff0f0043d8a4fef8ff0f00dc242500000000dc2425ff000000dc25faffffffdc25f9000000dc25f9ff0000dc20dc20dca0ffff000041dca7ffff0000dc2430dca430ffff000041dca437ffff000042dca438ffff0000dca470f2ff0f00dca4b0f4ff0f00dca4f0f8ff0f00dca4c4f8ff0f0041dca4c7f8ff0f0042dca4fcf8ff0f0043dca4fef8ff0f00dce8d8e1d8e7dce9dcef

bits 64

fsub dword [0x0]
fsub dword [0xFF]
fsub dword [rel $ + 0x0]
fsub dword [rel $ + 0xFF]
fsub dword [rel $ + 0xFFFF]
fsub dword [rax]
fsub dword [rax + 0x0]
fsub dword [rax + 0xFFFF]
fsub dword [r15 + 0xFFFF]
fsub dword [rax + rsi * 1  + 0x0]
fsub dword [rax + rsi + 0xFFFF]
fsub dword [r15 + rsi + 0xFFFF]
fsub dword [rax + r15 + 0xFFFF]
fsub dword [rax + rsi * 2 + 0xFFFF2]
fsub dword [rax + rsi * 4 + 0xFFFF4]
fsub dword [rax + rsi * 8 + 0xFFFF8]
fsub dword [rsp + rax * 8 + 0xFFFF8]
fsub dword [r15 + rax * 8 + 0xFFFF8]
fsub dword [rsp + r15 * 8 + 0xFFFF8]
fsub dword [r14 + r15 * 8 + 0xFFFF8]
fsub qword [0x0]
fsub qword [0xFF]
fsub qword [rel $ + 0x0]
fsub qword [rel $ + 0xFF]
fsub qword [rel $ + 0xFFFF]
fsub qword [rax]
fsub qword [rax + 0x0]
fsub qword [rax + 0xFFFF]
fsub qword [r15 + 0xFFFF]
fsub qword [rax + rsi * 1  + 0x0]
fsub qword [rax + rsi + 0xFFFF]
fsub qword [r15 + rsi + 0xFFFF]
fsub qword [rax + r15 + 0xFFFF]
fsub qword [rax + rsi * 2 + 0xFFFF2]
fsub qword [rax + rsi * 4 + 0xFFFF4]
fsub qword [rax + rsi * 8 + 0xFFFF8]
fsub qword [rsp + rax * 8 + 0xFFFF8]
fsub qword [r15 + rax * 8 + 0xFFFF8]
fsub qword [rsp + r15 * 8 + 0xFFFF8]
fsub qword [r14 + r15 * 8 + 0xFFFF8]
fsub st0, st0
fsub st0, st1
fsub st0, st7
fsub st1, st0
fsub st7, st0
