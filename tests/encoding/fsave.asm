; expect: 9bdd3425000000009bdd3425ff0000009bdd35f9ffffff9bdd35f80000009bdd35f8ff00009bdd309bdd309bddb0ffff00009b41ddb7ffff00009bdd34309bddb430ffff00009b41ddb437ffff00009b42ddb438ffff00009bddb470f2ff0f009bddb4b0f4ff0f009bddb4f0f8ff0f009bddb4c4f8ff0f009b41ddb4c7f8ff0f009b42ddb4fcf8ff0f009b43ddb4fef8ff0f00

bits 64

fsave [0x0]
fsave [0xFF]
fsave [rel $ + 0x0]
fsave [rel $ + 0xFF]
fsave [rel $ + 0xFFFF]
fsave [rax]
fsave [rax + 0x0]
fsave [rax + 0xFFFF]
fsave [r15 + 0xFFFF]
fsave [rax + rsi * 1  + 0x0]
fsave [rax + rsi + 0xFFFF]
fsave [r15 + rsi + 0xFFFF]
fsave [rax + r15 + 0xFFFF]
fsave [rax + rsi * 2 + 0xFFFF2]
fsave [rax + rsi * 4 + 0xFFFF4]
fsave [rax + rsi * 8 + 0xFFFF8]
fsave [rsp + rax * 8 + 0xFFFF8]
fsave [r15 + rax * 8 + 0xFFFF8]
fsave [rsp + r15 * 8 + 0xFFFF8]
fsave [r14 + r15 * 8 + 0xFFFF8]
