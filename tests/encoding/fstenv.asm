; expect: 9bd93425000000009bd93425ff0000009bd935f9ffffff9bd935f80000009bd935f8ff00009bd9309bd9309bd9b0ffff00009b41d9b7ffff00009bd934309bd9b430ffff00009b41d9b437ffff00009b42d9b438ffff00009bd9b470f2ff0f009bd9b4b0f4ff0f009bd9b4f0f8ff0f009bd9b4c4f8ff0f009b41d9b4c7f8ff0f009b42d9b4fcf8ff0f009b43d9b4fef8ff0f00

bits 64

fstenv [0x0]
fstenv [0xFF]
fstenv [rel $ + 0x0]
fstenv [rel $ + 0xFF]
fstenv [rel $ + 0xFFFF]
fstenv [rax]
fstenv [rax + 0x0]
fstenv [rax + 0xFFFF]
fstenv [r15 + 0xFFFF]
fstenv [rax + rsi * 1  + 0x0]
fstenv [rax + rsi + 0xFFFF]
fstenv [r15 + rsi + 0xFFFF]
fstenv [rax + r15 + 0xFFFF]
fstenv [rax + rsi * 2 + 0xFFFF2]
fstenv [rax + rsi * 4 + 0xFFFF4]
fstenv [rax + rsi * 8 + 0xFFFF8]
fstenv [rsp + rax * 8 + 0xFFFF8]
fstenv [r15 + rax * 8 + 0xFFFF8]
fstenv [rsp + r15 * 8 + 0xFFFF8]
fstenv [r14 + r15 * 8 + 0xFFFF8]
