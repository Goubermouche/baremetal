; expect: 0fae0c25000000000fae0c25ff0000000fae0df9ffffff0fae0df80000000fae0df8ff00000fae080fae080fae88ffff0000410fae8fffff00000fae0c300fae8c30ffff0000410fae8c37ffff0000420fae8c38ffff00000fae8c70f2ff0f000fae8cb0f4ff0f000fae8cf0f8ff0f000fae8cc4f8ff0f00410fae8cc7f8ff0f00420fae8cfcf8ff0f00430fae8cfef8ff0f00

bits 64

fxrstor [0x0]
fxrstor [0xFF]
fxrstor [rel $ + 0x0]
fxrstor [rel $ + 0xFF]
fxrstor [rel $ + 0xFFFF]
fxrstor [rax]
fxrstor [rax + 0x0]
fxrstor [rax + 0xFFFF]
fxrstor [r15 + 0xFFFF]
fxrstor [rax + rsi * 1  + 0x0]
fxrstor [rax + rsi + 0xFFFF]
fxrstor [r15 + rsi + 0xFFFF]
fxrstor [rax + r15 + 0xFFFF]
fxrstor [rax + rsi * 2 + 0xFFFF2]
fxrstor [rax + rsi * 4 + 0xFFFF4]
fxrstor [rax + rsi * 8 + 0xFFFF8]
fxrstor [rsp + rax * 8 + 0xFFFF8]
fxrstor [r15 + rax * 8 + 0xFFFF8]
fxrstor [rsp + r15 * 8 + 0xFFFF8]
fxrstor [r14 + r15 * 8 + 0xFFFF8]
