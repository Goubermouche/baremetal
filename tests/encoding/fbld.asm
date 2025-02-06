; expect: df242500000000df2425ff000000df25faffffffdf25f9000000df25f9ff0000df20df20dfa0ffff000041dfa7ffff0000df2430dfa430ffff000041dfa437ffff000042dfa438ffff0000dfa470f2ff0f00dfa4b0f4ff0f00dfa4f0f8ff0f00dfa4c4f8ff0f0041dfa4c7f8ff0f0042dfa4fcf8ff0f0043dfa4fef8ff0f00

bits 64

fbld tword [0x0]
fbld tword [0xFF]
fbld tword [rel $ + 0x0]
fbld tword [rel $ + 0xFF]
fbld tword [rel $ + 0xFFFF]
fbld tword [rax]
fbld tword [rax + 0x0]
fbld tword [rax + 0xFFFF]
fbld tword [r15 + 0xFFFF]
fbld tword [rax + rsi * 1  + 0x0]
fbld tword [rax + rsi + 0xFFFF]
fbld tword [r15 + rsi + 0xFFFF]
fbld tword [rax + r15 + 0xFFFF]
fbld tword [rax + rsi * 2 + 0xFFFF2]
fbld tword [rax + rsi * 4 + 0xFFFF4]
fbld tword [rax + rsi * 8 + 0xFFFF8]
fbld tword [rsp + rax * 8 + 0xFFFF8]
fbld tword [r15 + rax * 8 + 0xFFFF8]
fbld tword [rsp + r15 * 8 + 0xFFFF8]
fbld tword [r14 + r15 * 8 + 0xFFFF8]
