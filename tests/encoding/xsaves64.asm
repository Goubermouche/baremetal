; expect: 480fc72c2500000000480fc72c25ff000000480fc72df8ffffff480fc72df7000000480fc72df7ff0000480fc728480fc728480fc7a8ffff0000490fc7afffff0000480fc72c30480fc7ac30ffff0000490fc7ac37ffff00004a0fc7ac38ffff0000480fc7ac70f2ff0f00480fc7acb0f4ff0f00480fc7acf0f8ff0f00480fc7acc4f8ff0f00490fc7acc7f8ff0f004a0fc7acfcf8ff0f004b0fc7acfef8ff0f00

bits 64

xsaves64 [0x0]
xsaves64 [0xFF]
xsaves64 [rel $ + 0x0]
xsaves64 [rel $ + 0xFF]
xsaves64 [rel $ + 0xFFFF]
xsaves64 [rax]
xsaves64 [rax + 0x0]
xsaves64 [rax + 0xFFFF]
xsaves64 [r15 + 0xFFFF]
xsaves64 [rax + rsi * 1  + 0x0]
xsaves64 [rax + rsi + 0xFFFF]
xsaves64 [r15 + rsi + 0xFFFF]
xsaves64 [rax + r15 + 0xFFFF]
xsaves64 [rax + rsi * 2 + 0xFFFF2]
xsaves64 [rax + rsi * 4 + 0xFFFF4]
xsaves64 [rax + rsi * 8 + 0xFFFF8]
xsaves64 [rsp + rax * 8 + 0xFFFF8]
xsaves64 [r15 + rax * 8 + 0xFFFF8]
xsaves64 [rsp + r15 * 8 + 0xFFFF8]
xsaves64 [r14 + r15 * 8 + 0xFFFF8]
