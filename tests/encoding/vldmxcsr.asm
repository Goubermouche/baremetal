; expect: c5f8ae142500000000c5f8ae1425ff000000c5f8ae15f8ffffffc5f8ae15f7000000c5f8ae15f7ff0000c5f8ae10c5f8ae10c5f8ae90ffff0000c4c178ae97ffff0000c5f8ae1430c5f8ae9430ffff0000c4c178ae9437ffff0000c4a178ae9438ffff0000c5f8ae9470f2ff0f00c5f8ae94b0f4ff0f00c5f8ae94f0f8ff0f00c5f8ae94c4f8ff0f00c4c178ae94c7f8ff0f00c4a178ae94fcf8ff0f00c48178ae94fef8ff0f00

bits 64

vldmxcsr dword [0x0]
vldmxcsr dword [0xFF]
vldmxcsr dword [rel $ + 0x0]
vldmxcsr dword [rel $ + 0xFF]
vldmxcsr dword [rel $ + 0xFFFF]
vldmxcsr dword [rax]
vldmxcsr dword [rax + 0x0]
vldmxcsr dword [rax + 0xFFFF]
vldmxcsr dword [r15 + 0xFFFF]
vldmxcsr dword [rax + rsi * 1  + 0x0]
vldmxcsr dword [rax + rsi + 0xFFFF]
vldmxcsr dword [r15 + rsi + 0xFFFF]
vldmxcsr dword [rax + r15 + 0xFFFF]
vldmxcsr dword [rax + rsi * 2 + 0xFFFF2]
vldmxcsr dword [rax + rsi * 4 + 0xFFFF4]
vldmxcsr dword [rax + rsi * 8 + 0xFFFF8]
vldmxcsr dword [rsp + rax * 8 + 0xFFFF8]
vldmxcsr dword [r15 + rax * 8 + 0xFFFF8]
vldmxcsr dword [rsp + r15 * 8 + 0xFFFF8]
vldmxcsr dword [r14 + r15 * 8 + 0xFFFF8]
