; expect: c4e27a4b042500000000c4e27a4b0c2500000000c4e27a4b3c2500000000c4e27a4b0425ff000000c4e27a4b0c25ff000000c4e27a4b3c25ff000000c4e27a4b0420c4e27a4b0c20c4e27a4b3c20c4e27a4b0420c4e27a4b0c20c4e27a4b3c20c4e27a4b8420ffff0000c4e27a4b8c20ffff0000c4e27a4bbc20ffff0000c4c27a4b8427ffff0000c4c27a4b8c27ffff0000c4c27a4bbc27ffff0000c4e27a4b0430c4e27a4b0c30c4e27a4b3c30c4e27a4b8430ffff0000c4e27a4b8c30ffff0000c4e27a4bbc30ffff0000c4c27a4b8437ffff0000c4c27a4b8c37ffff0000c4c27a4bbc37ffff0000c4a27a4b8438ffff0000c4a27a4b8c38ffff0000c4a27a4bbc38ffff0000c4e27a4b8470f2ff0f00c4e27a4b8c70f2ff0f00c4e27a4bbc70f2ff0f00c4e27a4b84b0f4ff0f00c4e27a4b8cb0f4ff0f00c4e27a4bbcb0f4ff0f00c4e27a4b84f0f8ff0f00c4e27a4b8cf0f8ff0f00c4e27a4bbcf0f8ff0f00c4e27a4b84c4f8ff0f00c4e27a4b8cc4f8ff0f00c4e27a4bbcc4f8ff0f00c4c27a4b84c7f8ff0f00c4c27a4b8cc7f8ff0f00c4c27a4bbcc7f8ff0f00c4a27a4b84fcf8ff0f00c4a27a4b8cfcf8ff0f00c4a27a4bbcfcf8ff0f00c4827a4b84fef8ff0f00c4827a4b8cfef8ff0f00c4827a4bbcfef8ff0f00

bits 64

tilestored [0x0], tmm0
tilestored [0x0], tmm1
tilestored [0x0], tmm7
tilestored [0xFF], tmm0
tilestored [0xFF], tmm1
tilestored [0xFF], tmm7
tilestored [rax], tmm0
tilestored [rax], tmm1
tilestored [rax], tmm7
tilestored [rax + 0x0], tmm0
tilestored [rax + 0x0], tmm1
tilestored [rax + 0x0], tmm7
tilestored [rax + 0xFFFF], tmm0
tilestored [rax + 0xFFFF], tmm1
tilestored [rax + 0xFFFF], tmm7
tilestored [r15 + 0xFFFF], tmm0
tilestored [r15 + 0xFFFF], tmm1
tilestored [r15 + 0xFFFF], tmm7
tilestored [rax + rsi * 1  + 0x0], tmm0
tilestored [rax + rsi * 1  + 0x0], tmm1
tilestored [rax + rsi * 1  + 0x0], tmm7
tilestored [rax + rsi + 0xFFFF], tmm0
tilestored [rax + rsi + 0xFFFF], tmm1
tilestored [rax + rsi + 0xFFFF], tmm7
tilestored [r15 + rsi + 0xFFFF], tmm0
tilestored [r15 + rsi + 0xFFFF], tmm1
tilestored [r15 + rsi + 0xFFFF], tmm7
tilestored [rax + r15 + 0xFFFF], tmm0
tilestored [rax + r15 + 0xFFFF], tmm1
tilestored [rax + r15 + 0xFFFF], tmm7
tilestored [rax + rsi * 2 + 0xFFFF2], tmm0
tilestored [rax + rsi * 2 + 0xFFFF2], tmm1
tilestored [rax + rsi * 2 + 0xFFFF2], tmm7
tilestored [rax + rsi * 4 + 0xFFFF4], tmm0
tilestored [rax + rsi * 4 + 0xFFFF4], tmm1
tilestored [rax + rsi * 4 + 0xFFFF4], tmm7
tilestored [rax + rsi * 8 + 0xFFFF8], tmm0
tilestored [rax + rsi * 8 + 0xFFFF8], tmm1
tilestored [rax + rsi * 8 + 0xFFFF8], tmm7
tilestored [rsp + rax * 8 + 0xFFFF8], tmm0
tilestored [rsp + rax * 8 + 0xFFFF8], tmm1
tilestored [rsp + rax * 8 + 0xFFFF8], tmm7
tilestored [r15 + rax * 8 + 0xFFFF8], tmm0
tilestored [r15 + rax * 8 + 0xFFFF8], tmm1
tilestored [r15 + rax * 8 + 0xFFFF8], tmm7
tilestored [rsp + r15 * 8 + 0xFFFF8], tmm0
tilestored [rsp + r15 * 8 + 0xFFFF8], tmm1
tilestored [rsp + r15 * 8 + 0xFFFF8], tmm7
tilestored [r14 + r15 * 8 + 0xFFFF8], tmm0
tilestored [r14 + r15 * 8 + 0xFFFF8], tmm1
tilestored [r14 + r15 * 8 + 0xFFFF8], tmm7
