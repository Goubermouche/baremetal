; expect: d9342500000000d93425ff000000d935faffffffd935f9000000d935f9ff0000d930d930d9b0ffff000041d9b7ffff0000d93430d9b430ffff000041d9b437ffff000042d9b438ffff0000d9b470f2ff0f00d9b4b0f4ff0f00d9b4f0f8ff0f00d9b4c4f8ff0f0041d9b4c7f8ff0f0042d9b4fcf8ff0f0043d9b4fef8ff0f00

bits 64

fnstenv [0x0]
fnstenv [0xFF]
fnstenv [rel $ + 0x0]
fnstenv [rel $ + 0xFF]
fnstenv [rel $ + 0xFFFF]
fnstenv [rax]
fnstenv [rax + 0x0]
fnstenv [rax + 0xFFFF]
fnstenv [r15 + 0xFFFF]
fnstenv [rax + rsi * 1  + 0x0]
fnstenv [rax + rsi + 0xFFFF]
fnstenv [r15 + rsi + 0xFFFF]
fnstenv [rax + r15 + 0xFFFF]
fnstenv [rax + rsi * 2 + 0xFFFF2]
fnstenv [rax + rsi * 4 + 0xFFFF4]
fnstenv [rax + rsi * 8 + 0xFFFF8]
fnstenv [rsp + rax * 8 + 0xFFFF8]
fnstenv [r15 + rax * 8 + 0xFFFF8]
fnstenv [rsp + r15 * 8 + 0xFFFF8]
fnstenv [r14 + r15 * 8 + 0xFFFF8]
