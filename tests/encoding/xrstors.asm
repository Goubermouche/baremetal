; expect: 0fc71c25000000000fc71c25ff0000000fc71df9ffffff0fc71df80000000fc71df8ff00000fc7180fc7180fc798ffff0000410fc79fffff00000fc71c300fc79c30ffff0000410fc79c37ffff0000420fc79c38ffff00000fc79c70f2ff0f000fc79cb0f4ff0f000fc79cf0f8ff0f000fc79cc4f8ff0f00410fc79cc7f8ff0f00420fc79cfcf8ff0f00430fc79cfef8ff0f00

bits 64

xrstors [0x0]
xrstors [0xFF]
xrstors [rel $ + 0x0]
xrstors [rel $ + 0xFF]
xrstors [rel $ + 0xFFFF]
xrstors [rax]
xrstors [rax + 0x0]
xrstors [rax + 0xFFFF]
xrstors [r15 + 0xFFFF]
xrstors [rax + rsi * 1  + 0x0]
xrstors [rax + rsi + 0xFFFF]
xrstors [r15 + rsi + 0xFFFF]
xrstors [rax + r15 + 0xFFFF]
xrstors [rax + rsi * 2 + 0xFFFF2]
xrstors [rax + rsi * 4 + 0xFFFF4]
xrstors [rax + rsi * 8 + 0xFFFF8]
xrstors [rsp + rax * 8 + 0xFFFF8]
xrstors [r15 + rax * 8 + 0xFFFF8]
xrstors [rsp + r15 * 8 + 0xFFFF8]
xrstors [r14 + r15 * 8 + 0xFFFF8]
