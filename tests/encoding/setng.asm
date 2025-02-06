; expect: 0f9ec10f9ec20f9ec30f9e0425000000000f9e0425ff0000000f9e05f9ffffff0f9e05f80000000f9e05f8ff00000f9e000f9e000f9e80ffff0000410f9e87ffff00000f9e04300f9e8430ffff0000410f9e8437ffff0000420f9e8438ffff00000f9e8470f2ff0f000f9e84b0f4ff0f000f9e84f0f8ff0f000f9e84c4f8ff0f00410f9e84c7f8ff0f00420f9e84fcf8ff0f00430f9e84fef8ff0f00

bits 64

setng cl
setng dl
setng bl
setng byte [0x0]
setng byte [0xFF]
setng byte [rel $ + 0x0]
setng byte [rel $ + 0xFF]
setng byte [rel $ + 0xFFFF]
setng byte [rax]
setng byte [rax + 0x0]
setng byte [rax + 0xFFFF]
setng byte [r15 + 0xFFFF]
setng byte [rax + rsi * 1  + 0x0]
setng byte [rax + rsi + 0xFFFF]
setng byte [r15 + rsi + 0xFFFF]
setng byte [rax + r15 + 0xFFFF]
setng byte [rax + rsi * 2 + 0xFFFF2]
setng byte [rax + rsi * 4 + 0xFFFF4]
setng byte [rax + rsi * 8 + 0xFFFF8]
setng byte [rsp + rax * 8 + 0xFFFF8]
setng byte [r15 + rax * 8 + 0xFFFF8]
setng byte [rsp + r15 * 8 + 0xFFFF8]
setng byte [r14 + r15 * 8 + 0xFFFF8]
