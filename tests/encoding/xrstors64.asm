; expect: 480fc71c2500000000480fc71c25ff000000480fc71df8ffffff480fc71df7000000480fc71df7ff0000480fc718480fc718480fc798ffff0000490fc79fffff0000480fc71c30480fc79c30ffff0000490fc79c37ffff00004a0fc79c38ffff0000480fc79c70f2ff0f00480fc79cb0f4ff0f00480fc79cf0f8ff0f00480fc79cc4f8ff0f00490fc79cc7f8ff0f004a0fc79cfcf8ff0f004b0fc79cfef8ff0f00

bits 64

xrstors64 [0x0]
xrstors64 [0xFF]
xrstors64 [rel $ + 0x0]
xrstors64 [rel $ + 0xFF]
xrstors64 [rel $ + 0xFFFF]
xrstors64 [rax]
xrstors64 [rax + 0x0]
xrstors64 [rax + 0xFFFF]
xrstors64 [r15 + 0xFFFF]
xrstors64 [rax + rsi * 1  + 0x0]
xrstors64 [rax + rsi + 0xFFFF]
xrstors64 [r15 + rsi + 0xFFFF]
xrstors64 [rax + r15 + 0xFFFF]
xrstors64 [rax + rsi * 2 + 0xFFFF2]
xrstors64 [rax + rsi * 4 + 0xFFFF4]
xrstors64 [rax + rsi * 8 + 0xFFFF8]
xrstors64 [rsp + rax * 8 + 0xFFFF8]
xrstors64 [r15 + rax * 8 + 0xFFFF8]
xrstors64 [rsp + r15 * 8 + 0xFFFF8]
xrstors64 [r14 + r15 * 8 + 0xFFFF8]
