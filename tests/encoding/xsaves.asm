; expect: 0fc72c25000000000fc72c25ff0000000fc72df9ffffff0fc72df80000000fc72df8ff00000fc7280fc7280fc7a8ffff0000410fc7afffff00000fc72c300fc7ac30ffff0000410fc7ac37ffff0000420fc7ac38ffff00000fc7ac70f2ff0f000fc7acb0f4ff0f000fc7acf0f8ff0f000fc7acc4f8ff0f00410fc7acc7f8ff0f00420fc7acfcf8ff0f00430fc7acfef8ff0f00

bits 64

xsaves [0x0]
xsaves [0xFF]
xsaves [rel $ + 0x0]
xsaves [rel $ + 0xFF]
xsaves [rel $ + 0xFFFF]
xsaves [rax]
xsaves [rax + 0x0]
xsaves [rax + 0xFFFF]
xsaves [r15 + 0xFFFF]
xsaves [rax + rsi * 1  + 0x0]
xsaves [rax + rsi + 0xFFFF]
xsaves [r15 + rsi + 0xFFFF]
xsaves [rax + r15 + 0xFFFF]
xsaves [rax + rsi * 2 + 0xFFFF2]
xsaves [rax + rsi * 4 + 0xFFFF4]
xsaves [rax + rsi * 8 + 0xFFFF8]
xsaves [rsp + rax * 8 + 0xFFFF8]
xsaves [r15 + rax * 8 + 0xFFFF8]
xsaves [rsp + r15 * 8 + 0xFFFF8]
xsaves [r14 + r15 * 8 + 0xFFFF8]
