; expect: c5fb2dc8c5fb2dc9c4c17b2dcfc5fb2dd8c5fb2dd9c4c17b2ddfc57b2df8c57b2df9c4417b2dffc5fb2d0c2500000000c5fb2d0c25ff000000c5fb2d0df8ffffffc5fb2d0df7000000c5fb2d0df7ff0000c5fb2d08c5fb2d08c5fb2d88ffff0000c4c17b2d8fffff0000c5fb2d0c30c5fb2d8c30ffff0000c4c17b2d8c37ffff0000c4a17b2d8c38ffff0000c5fb2d8c70f2ff0f00c5fb2d8cb0f4ff0f00c5fb2d8cf0f8ff0f00c5fb2d8cc4f8ff0f00c4c17b2d8cc7f8ff0f00c4a17b2d8cfcf8ff0f00c4817b2d8cfef8ff0f00c5fb2d1c2500000000c5fb2d1c25ff000000c5fb2d1df8ffffffc5fb2d1df7000000c5fb2d1df7ff0000c5fb2d18c5fb2d18c5fb2d98ffff0000c4c17b2d9fffff0000c5fb2d1c30c5fb2d9c30ffff0000c4c17b2d9c37ffff0000c4a17b2d9c38ffff0000c5fb2d9c70f2ff0f00c5fb2d9cb0f4ff0f00c5fb2d9cf0f8ff0f00c5fb2d9cc4f8ff0f00c4c17b2d9cc7f8ff0f00c4a17b2d9cfcf8ff0f00c4817b2d9cfef8ff0f00c57b2d3c2500000000c57b2d3c25ff000000c57b2d3df8ffffffc57b2d3df7000000c57b2d3df7ff0000c57b2d38c57b2d38c57b2db8ffff0000c4417b2dbfffff0000c57b2d3c30c57b2dbc30ffff0000c4417b2dbc37ffff0000c4217b2dbc38ffff0000c57b2dbc70f2ff0f00c57b2dbcb0f4ff0f00c57b2dbcf0f8ff0f00c57b2dbcc4f8ff0f00c4417b2dbcc7f8ff0f00c4217b2dbcfcf8ff0f00c4017b2dbcfef8ff0f00c4e1fb2dc8c4e1fb2dc9c4c1fb2dcfc4e1fb2dd8c4e1fb2dd9c4c1fb2ddfc461fb2df8c461fb2df9c441fb2dffc4e1fb2d0c2500000000c4e1fb2d0c25ff000000c4e1fb2d0df7ffffffc4e1fb2d0df6000000c4e1fb2d0df6ff0000c4e1fb2d08c4e1fb2d08c4e1fb2d88ffff0000c4c1fb2d8fffff0000c4e1fb2d0c30c4e1fb2d8c30ffff0000c4c1fb2d8c37ffff0000c4a1fb2d8c38ffff0000c4e1fb2d8c70f2ff0f00c4e1fb2d8cb0f4ff0f00c4e1fb2d8cf0f8ff0f00c4e1fb2d8cc4f8ff0f00c4c1fb2d8cc7f8ff0f00c4a1fb2d8cfcf8ff0f00c481fb2d8cfef8ff0f00c4e1fb2d1c2500000000c4e1fb2d1c25ff000000c4e1fb2d1df7ffffffc4e1fb2d1df6000000c4e1fb2d1df6ff0000c4e1fb2d18c4e1fb2d18c4e1fb2d98ffff0000c4c1fb2d9fffff0000c4e1fb2d1c30c4e1fb2d9c30ffff0000c4c1fb2d9c37ffff0000c4a1fb2d9c38ffff0000c4e1fb2d9c70f2ff0f00c4e1fb2d9cb0f4ff0f00c4e1fb2d9cf0f8ff0f00c4e1fb2d9cc4f8ff0f00c4c1fb2d9cc7f8ff0f00c4a1fb2d9cfcf8ff0f00c481fb2d9cfef8ff0f00c461fb2d3c2500000000c461fb2d3c25ff000000c461fb2d3df7ffffffc461fb2d3df6000000c461fb2d3df6ff0000c461fb2d38c461fb2d38c461fb2db8ffff0000c441fb2dbfffff0000c461fb2d3c30c461fb2dbc30ffff0000c441fb2dbc37ffff0000c421fb2dbc38ffff0000c461fb2dbc70f2ff0f00c461fb2dbcb0f4ff0f00c461fb2dbcf0f8ff0f00c461fb2dbcc4f8ff0f00c441fb2dbcc7f8ff0f00c421fb2dbcfcf8ff0f00c401fb2dbcfef8ff0f0062917f082dcf62917f082ddf62117f082dff6291ff082dcf6291ff082ddf6211ff082dff

bits 64

vcvtsd2si ecx, xmm0
vcvtsd2si ecx, xmm1
vcvtsd2si ecx, xmm15
vcvtsd2si ebx, xmm0
vcvtsd2si ebx, xmm1
vcvtsd2si ebx, xmm15
vcvtsd2si r15d, xmm0
vcvtsd2si r15d, xmm1
vcvtsd2si r15d, xmm15
vcvtsd2si ecx, qword [0x0]
vcvtsd2si ecx, qword [0xFF]
vcvtsd2si ecx, qword [rel $ + 0x0]
vcvtsd2si ecx, qword [rel $ + 0xFF]
vcvtsd2si ecx, qword [rel $ + 0xFFFF]
vcvtsd2si ecx, qword [rax]
vcvtsd2si ecx, qword [rax + 0x0]
vcvtsd2si ecx, qword [rax + 0xFFFF]
vcvtsd2si ecx, qword [r15 + 0xFFFF]
vcvtsd2si ecx, qword [rax + rsi * 1  + 0x0]
vcvtsd2si ecx, qword [rax + rsi + 0xFFFF]
vcvtsd2si ecx, qword [r15 + rsi + 0xFFFF]
vcvtsd2si ecx, qword [rax + r15 + 0xFFFF]
vcvtsd2si ecx, qword [rax + rsi * 2 + 0xFFFF2]
vcvtsd2si ecx, qword [rax + rsi * 4 + 0xFFFF4]
vcvtsd2si ecx, qword [rax + rsi * 8 + 0xFFFF8]
vcvtsd2si ecx, qword [rsp + rax * 8 + 0xFFFF8]
vcvtsd2si ecx, qword [r15 + rax * 8 + 0xFFFF8]
vcvtsd2si ecx, qword [rsp + r15 * 8 + 0xFFFF8]
vcvtsd2si ecx, qword [r14 + r15 * 8 + 0xFFFF8]
vcvtsd2si ebx, qword [0x0]
vcvtsd2si ebx, qword [0xFF]
vcvtsd2si ebx, qword [rel $ + 0x0]
vcvtsd2si ebx, qword [rel $ + 0xFF]
vcvtsd2si ebx, qword [rel $ + 0xFFFF]
vcvtsd2si ebx, qword [rax]
vcvtsd2si ebx, qword [rax + 0x0]
vcvtsd2si ebx, qword [rax + 0xFFFF]
vcvtsd2si ebx, qword [r15 + 0xFFFF]
vcvtsd2si ebx, qword [rax + rsi * 1  + 0x0]
vcvtsd2si ebx, qword [rax + rsi + 0xFFFF]
vcvtsd2si ebx, qword [r15 + rsi + 0xFFFF]
vcvtsd2si ebx, qword [rax + r15 + 0xFFFF]
vcvtsd2si ebx, qword [rax + rsi * 2 + 0xFFFF2]
vcvtsd2si ebx, qword [rax + rsi * 4 + 0xFFFF4]
vcvtsd2si ebx, qword [rax + rsi * 8 + 0xFFFF8]
vcvtsd2si ebx, qword [rsp + rax * 8 + 0xFFFF8]
vcvtsd2si ebx, qword [r15 + rax * 8 + 0xFFFF8]
vcvtsd2si ebx, qword [rsp + r15 * 8 + 0xFFFF8]
vcvtsd2si ebx, qword [r14 + r15 * 8 + 0xFFFF8]
vcvtsd2si r15d, qword [0x0]
vcvtsd2si r15d, qword [0xFF]
vcvtsd2si r15d, qword [rel $ + 0x0]
vcvtsd2si r15d, qword [rel $ + 0xFF]
vcvtsd2si r15d, qword [rel $ + 0xFFFF]
vcvtsd2si r15d, qword [rax]
vcvtsd2si r15d, qword [rax + 0x0]
vcvtsd2si r15d, qword [rax + 0xFFFF]
vcvtsd2si r15d, qword [r15 + 0xFFFF]
vcvtsd2si r15d, qword [rax + rsi * 1  + 0x0]
vcvtsd2si r15d, qword [rax + rsi + 0xFFFF]
vcvtsd2si r15d, qword [r15 + rsi + 0xFFFF]
vcvtsd2si r15d, qword [rax + r15 + 0xFFFF]
vcvtsd2si r15d, qword [rax + rsi * 2 + 0xFFFF2]
vcvtsd2si r15d, qword [rax + rsi * 4 + 0xFFFF4]
vcvtsd2si r15d, qword [rax + rsi * 8 + 0xFFFF8]
vcvtsd2si r15d, qword [rsp + rax * 8 + 0xFFFF8]
vcvtsd2si r15d, qword [r15 + rax * 8 + 0xFFFF8]
vcvtsd2si r15d, qword [rsp + r15 * 8 + 0xFFFF8]
vcvtsd2si r15d, qword [r14 + r15 * 8 + 0xFFFF8]
vcvtsd2si rcx, xmm0
vcvtsd2si rcx, xmm1
vcvtsd2si rcx, xmm15
vcvtsd2si rbx, xmm0
vcvtsd2si rbx, xmm1
vcvtsd2si rbx, xmm15
vcvtsd2si r15, xmm0
vcvtsd2si r15, xmm1
vcvtsd2si r15, xmm15
vcvtsd2si rcx, qword [0x0]
vcvtsd2si rcx, qword [0xFF]
vcvtsd2si rcx, qword [rel $ + 0x0]
vcvtsd2si rcx, qword [rel $ + 0xFF]
vcvtsd2si rcx, qword [rel $ + 0xFFFF]
vcvtsd2si rcx, qword [rax]
vcvtsd2si rcx, qword [rax + 0x0]
vcvtsd2si rcx, qword [rax + 0xFFFF]
vcvtsd2si rcx, qword [r15 + 0xFFFF]
vcvtsd2si rcx, qword [rax + rsi * 1  + 0x0]
vcvtsd2si rcx, qword [rax + rsi + 0xFFFF]
vcvtsd2si rcx, qword [r15 + rsi + 0xFFFF]
vcvtsd2si rcx, qword [rax + r15 + 0xFFFF]
vcvtsd2si rcx, qword [rax + rsi * 2 + 0xFFFF2]
vcvtsd2si rcx, qword [rax + rsi * 4 + 0xFFFF4]
vcvtsd2si rcx, qword [rax + rsi * 8 + 0xFFFF8]
vcvtsd2si rcx, qword [rsp + rax * 8 + 0xFFFF8]
vcvtsd2si rcx, qword [r15 + rax * 8 + 0xFFFF8]
vcvtsd2si rcx, qword [rsp + r15 * 8 + 0xFFFF8]
vcvtsd2si rcx, qword [r14 + r15 * 8 + 0xFFFF8]
vcvtsd2si rbx, qword [0x0]
vcvtsd2si rbx, qword [0xFF]
vcvtsd2si rbx, qword [rel $ + 0x0]
vcvtsd2si rbx, qword [rel $ + 0xFF]
vcvtsd2si rbx, qword [rel $ + 0xFFFF]
vcvtsd2si rbx, qword [rax]
vcvtsd2si rbx, qword [rax + 0x0]
vcvtsd2si rbx, qword [rax + 0xFFFF]
vcvtsd2si rbx, qword [r15 + 0xFFFF]
vcvtsd2si rbx, qword [rax + rsi * 1  + 0x0]
vcvtsd2si rbx, qword [rax + rsi + 0xFFFF]
vcvtsd2si rbx, qword [r15 + rsi + 0xFFFF]
vcvtsd2si rbx, qword [rax + r15 + 0xFFFF]
vcvtsd2si rbx, qword [rax + rsi * 2 + 0xFFFF2]
vcvtsd2si rbx, qword [rax + rsi * 4 + 0xFFFF4]
vcvtsd2si rbx, qword [rax + rsi * 8 + 0xFFFF8]
vcvtsd2si rbx, qword [rsp + rax * 8 + 0xFFFF8]
vcvtsd2si rbx, qword [r15 + rax * 8 + 0xFFFF8]
vcvtsd2si rbx, qword [rsp + r15 * 8 + 0xFFFF8]
vcvtsd2si rbx, qword [r14 + r15 * 8 + 0xFFFF8]
vcvtsd2si r15, qword [0x0]
vcvtsd2si r15, qword [0xFF]
vcvtsd2si r15, qword [rel $ + 0x0]
vcvtsd2si r15, qword [rel $ + 0xFF]
vcvtsd2si r15, qword [rel $ + 0xFFFF]
vcvtsd2si r15, qword [rax]
vcvtsd2si r15, qword [rax + 0x0]
vcvtsd2si r15, qword [rax + 0xFFFF]
vcvtsd2si r15, qword [r15 + 0xFFFF]
vcvtsd2si r15, qword [rax + rsi * 1  + 0x0]
vcvtsd2si r15, qword [rax + rsi + 0xFFFF]
vcvtsd2si r15, qword [r15 + rsi + 0xFFFF]
vcvtsd2si r15, qword [rax + r15 + 0xFFFF]
vcvtsd2si r15, qword [rax + rsi * 2 + 0xFFFF2]
vcvtsd2si r15, qword [rax + rsi * 4 + 0xFFFF4]
vcvtsd2si r15, qword [rax + rsi * 8 + 0xFFFF8]
vcvtsd2si r15, qword [rsp + rax * 8 + 0xFFFF8]
vcvtsd2si r15, qword [r15 + rax * 8 + 0xFFFF8]
vcvtsd2si r15, qword [rsp + r15 * 8 + 0xFFFF8]
vcvtsd2si r15, qword [r14 + r15 * 8 + 0xFFFF8]
vcvtsd2si ecx, xmm31
vcvtsd2si ebx, xmm31
vcvtsd2si r15d, xmm31
vcvtsd2si rcx, xmm31
vcvtsd2si rbx, xmm31
vcvtsd2si r15, xmm31
