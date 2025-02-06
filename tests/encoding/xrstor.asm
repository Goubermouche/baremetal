; expect: 0fae2c25000000000fae2c25ff0000000fae2df9ffffff0fae2df80000000fae2df8ff00000fae280fae280faea8ffff0000410faeafffff00000fae2c300faeac30ffff0000410faeac37ffff0000420faeac38ffff00000faeac70f2ff0f000faeacb0f4ff0f000faeacf0f8ff0f000faeacc4f8ff0f00410faeacc7f8ff0f00420faeacfcf8ff0f00430faeacfef8ff0f00

bits 64

xrstor [0x0]
xrstor [0xFF]
xrstor [rel $ + 0x0]
xrstor [rel $ + 0xFF]
xrstor [rel $ + 0xFFFF]
xrstor [rax]
xrstor [rax + 0x0]
xrstor [rax + 0xFFFF]
xrstor [r15 + 0xFFFF]
xrstor [rax + rsi * 1  + 0x0]
xrstor [rax + rsi + 0xFFFF]
xrstor [r15 + rsi + 0xFFFF]
xrstor [rax + r15 + 0xFFFF]
xrstor [rax + rsi * 2 + 0xFFFF2]
xrstor [rax + rsi * 4 + 0xFFFF4]
xrstor [rax + rsi * 8 + 0xFFFF8]
xrstor [rsp + rax * 8 + 0xFFFF8]
xrstor [r15 + rax * 8 + 0xFFFF8]
xrstor [rsp + r15 * 8 + 0xFFFF8]
xrstor [r14 + r15 * 8 + 0xFFFF8]
