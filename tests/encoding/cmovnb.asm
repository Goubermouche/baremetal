; expect: 660f43c9660f43ca660f43cb66410f43cf660f43d1660f43d2660f43d366410f43d7660f43d9660f43da660f43db66410f43df66440f43f966440f43fa66440f43fb66450f43ff660f430c2500000000660f430c25ff000000660f430df8ffffff660f430df7000000660f430df7ff0000660f4308660f4308660f4388ffff000066410f438fffff0000660f430c30660f438c30ffff000066410f438c37ffff000066420f438c38ffff0000660f438c70f2ff0f00660f438cb0f4ff0f00660f438cf0f8ff0f00660f438cc4f8ff0f0066410f438cc7f8ff0f0066420f438cfcf8ff0f0066430f438cfef8ff0f00660f43142500000000660f431425ff000000660f4315f8ffffff660f4315f7000000660f4315f7ff0000660f4310660f4310660f4390ffff000066410f4397ffff0000660f431430660f439430ffff000066410f439437ffff000066420f439438ffff0000660f439470f2ff0f00660f4394b0f4ff0f00660f4394f0f8ff0f00660f4394c4f8ff0f0066410f4394c7f8ff0f0066420f4394fcf8ff0f0066430f4394fef8ff0f00660f431c2500000000660f431c25ff000000660f431df8ffffff660f431df7000000660f431df7ff0000660f4318660f4318660f4398ffff000066410f439fffff0000660f431c30660f439c30ffff000066410f439c37ffff000066420f439c38ffff0000660f439c70f2ff0f00660f439cb0f4ff0f00660f439cf0f8ff0f00660f439cc4f8ff0f0066410f439cc7f8ff0f0066420f439cfcf8ff0f0066430f439cfef8ff0f0066440f433c250000000066440f433c25ff00000066440f433df7ffffff66440f433df600000066440f433df6ff000066440f433866440f433866440f43b8ffff000066450f43bfffff000066440f433c3066440f43bc30ffff000066450f43bc37ffff000066460f43bc38ffff000066440f43bc70f2ff0f0066440f43bcb0f4ff0f0066440f43bcf0f8ff0f0066440f43bcc4f8ff0f0066450f43bcc7f8ff0f0066460f43bcfcf8ff0f0066470f43bcfef8ff0f000f43c90f43cb410f43cf0f43d90f43db410f43df440f43f9440f43fb450f43ff0f430c25000000000f430c25ff0000000f430df9ffffff0f430df80000000f430df8ff00000f43080f43080f4388ffff0000410f438fffff00000f430c300f438c30ffff0000410f438c37ffff0000420f438c38ffff00000f438c70f2ff0f000f438cb0f4ff0f000f438cf0f8ff0f000f438cc4f8ff0f00410f438cc7f8ff0f00420f438cfcf8ff0f00430f438cfef8ff0f000f431c25000000000f431c25ff0000000f431df9ffffff0f431df80000000f431df8ff00000f43180f43180f4398ffff0000410f439fffff00000f431c300f439c30ffff0000410f439c37ffff0000420f439c38ffff00000f439c70f2ff0f000f439cb0f4ff0f000f439cf0f8ff0f000f439cc4f8ff0f00410f439cc7f8ff0f00420f439cfcf8ff0f00430f439cfef8ff0f00440f433c2500000000440f433c25ff000000440f433df8ffffff440f433df7000000440f433df7ff0000440f4338440f4338440f43b8ffff0000450f43bfffff0000440f433c30440f43bc30ffff0000450f43bc37ffff0000460f43bc38ffff0000440f43bc70f2ff0f00440f43bcb0f4ff0f00440f43bcf0f8ff0f00440f43bcc4f8ff0f00450f43bcc7f8ff0f00460f43bcfcf8ff0f00470f43bcfef8ff0f00480f43c9480f43cb490f43cf480f43d9480f43db490f43df4c0f43f94c0f43fb4d0f43ff480f430c2500000000480f430c25ff000000480f430df8ffffff480f430df7000000480f430df7ff0000480f4308480f4308480f4388ffff0000490f438fffff0000480f430c30480f438c30ffff0000490f438c37ffff00004a0f438c38ffff0000480f438c70f2ff0f00480f438cb0f4ff0f00480f438cf0f8ff0f00480f438cc4f8ff0f00490f438cc7f8ff0f004a0f438cfcf8ff0f004b0f438cfef8ff0f00480f431c2500000000480f431c25ff000000480f431df8ffffff480f431df7000000480f431df7ff0000480f4318480f4318480f4398ffff0000490f439fffff0000480f431c30480f439c30ffff0000490f439c37ffff00004a0f439c38ffff0000480f439c70f2ff0f00480f439cb0f4ff0f00480f439cf0f8ff0f00480f439cc4f8ff0f00490f439cc7f8ff0f004a0f439cfcf8ff0f004b0f439cfef8ff0f004c0f433c25000000004c0f433c25ff0000004c0f433df8ffffff4c0f433df70000004c0f433df7ff00004c0f43384c0f43384c0f43b8ffff00004d0f43bfffff00004c0f433c304c0f43bc30ffff00004d0f43bc37ffff00004e0f43bc38ffff00004c0f43bc70f2ff0f004c0f43bcb0f4ff0f004c0f43bcf0f8ff0f004c0f43bcc4f8ff0f004d0f43bcc7f8ff0f004e0f43bcfcf8ff0f004f0f43bcfef8ff0f00

bits 64

cmovnb cx, cx
cmovnb cx, dx
cmovnb cx, bx
cmovnb cx, r15w
cmovnb dx, cx
cmovnb dx, dx
cmovnb dx, bx
cmovnb dx, r15w
cmovnb bx, cx
cmovnb bx, dx
cmovnb bx, bx
cmovnb bx, r15w
cmovnb r15w, cx
cmovnb r15w, dx
cmovnb r15w, bx
cmovnb r15w, r15w
cmovnb cx, word [0x0]
cmovnb cx, word [0xFF]
cmovnb cx, word [rel $ + 0x0]
cmovnb cx, word [rel $ + 0xFF]
cmovnb cx, word [rel $ + 0xFFFF]
cmovnb cx, word [rax]
cmovnb cx, word [rax + 0x0]
cmovnb cx, word [rax + 0xFFFF]
cmovnb cx, word [r15 + 0xFFFF]
cmovnb cx, word [rax + rsi * 1  + 0x0]
cmovnb cx, word [rax + rsi + 0xFFFF]
cmovnb cx, word [r15 + rsi + 0xFFFF]
cmovnb cx, word [rax + r15 + 0xFFFF]
cmovnb cx, word [rax + rsi * 2 + 0xFFFF2]
cmovnb cx, word [rax + rsi * 4 + 0xFFFF4]
cmovnb cx, word [rax + rsi * 8 + 0xFFFF8]
cmovnb cx, word [rsp + rax * 8 + 0xFFFF8]
cmovnb cx, word [r15 + rax * 8 + 0xFFFF8]
cmovnb cx, word [rsp + r15 * 8 + 0xFFFF8]
cmovnb cx, word [r14 + r15 * 8 + 0xFFFF8]
cmovnb dx, word [0x0]
cmovnb dx, word [0xFF]
cmovnb dx, word [rel $ + 0x0]
cmovnb dx, word [rel $ + 0xFF]
cmovnb dx, word [rel $ + 0xFFFF]
cmovnb dx, word [rax]
cmovnb dx, word [rax + 0x0]
cmovnb dx, word [rax + 0xFFFF]
cmovnb dx, word [r15 + 0xFFFF]
cmovnb dx, word [rax + rsi * 1  + 0x0]
cmovnb dx, word [rax + rsi + 0xFFFF]
cmovnb dx, word [r15 + rsi + 0xFFFF]
cmovnb dx, word [rax + r15 + 0xFFFF]
cmovnb dx, word [rax + rsi * 2 + 0xFFFF2]
cmovnb dx, word [rax + rsi * 4 + 0xFFFF4]
cmovnb dx, word [rax + rsi * 8 + 0xFFFF8]
cmovnb dx, word [rsp + rax * 8 + 0xFFFF8]
cmovnb dx, word [r15 + rax * 8 + 0xFFFF8]
cmovnb dx, word [rsp + r15 * 8 + 0xFFFF8]
cmovnb dx, word [r14 + r15 * 8 + 0xFFFF8]
cmovnb bx, word [0x0]
cmovnb bx, word [0xFF]
cmovnb bx, word [rel $ + 0x0]
cmovnb bx, word [rel $ + 0xFF]
cmovnb bx, word [rel $ + 0xFFFF]
cmovnb bx, word [rax]
cmovnb bx, word [rax + 0x0]
cmovnb bx, word [rax + 0xFFFF]
cmovnb bx, word [r15 + 0xFFFF]
cmovnb bx, word [rax + rsi * 1  + 0x0]
cmovnb bx, word [rax + rsi + 0xFFFF]
cmovnb bx, word [r15 + rsi + 0xFFFF]
cmovnb bx, word [rax + r15 + 0xFFFF]
cmovnb bx, word [rax + rsi * 2 + 0xFFFF2]
cmovnb bx, word [rax + rsi * 4 + 0xFFFF4]
cmovnb bx, word [rax + rsi * 8 + 0xFFFF8]
cmovnb bx, word [rsp + rax * 8 + 0xFFFF8]
cmovnb bx, word [r15 + rax * 8 + 0xFFFF8]
cmovnb bx, word [rsp + r15 * 8 + 0xFFFF8]
cmovnb bx, word [r14 + r15 * 8 + 0xFFFF8]
cmovnb r15w, word [0x0]
cmovnb r15w, word [0xFF]
cmovnb r15w, word [rel $ + 0x0]
cmovnb r15w, word [rel $ + 0xFF]
cmovnb r15w, word [rel $ + 0xFFFF]
cmovnb r15w, word [rax]
cmovnb r15w, word [rax + 0x0]
cmovnb r15w, word [rax + 0xFFFF]
cmovnb r15w, word [r15 + 0xFFFF]
cmovnb r15w, word [rax + rsi * 1  + 0x0]
cmovnb r15w, word [rax + rsi + 0xFFFF]
cmovnb r15w, word [r15 + rsi + 0xFFFF]
cmovnb r15w, word [rax + r15 + 0xFFFF]
cmovnb r15w, word [rax + rsi * 2 + 0xFFFF2]
cmovnb r15w, word [rax + rsi * 4 + 0xFFFF4]
cmovnb r15w, word [rax + rsi * 8 + 0xFFFF8]
cmovnb r15w, word [rsp + rax * 8 + 0xFFFF8]
cmovnb r15w, word [r15 + rax * 8 + 0xFFFF8]
cmovnb r15w, word [rsp + r15 * 8 + 0xFFFF8]
cmovnb r15w, word [r14 + r15 * 8 + 0xFFFF8]
cmovnb ecx, ecx
cmovnb ecx, ebx
cmovnb ecx, r15d
cmovnb ebx, ecx
cmovnb ebx, ebx
cmovnb ebx, r15d
cmovnb r15d, ecx
cmovnb r15d, ebx
cmovnb r15d, r15d
cmovnb ecx, dword [0x0]
cmovnb ecx, dword [0xFF]
cmovnb ecx, dword [rel $ + 0x0]
cmovnb ecx, dword [rel $ + 0xFF]
cmovnb ecx, dword [rel $ + 0xFFFF]
cmovnb ecx, dword [rax]
cmovnb ecx, dword [rax + 0x0]
cmovnb ecx, dword [rax + 0xFFFF]
cmovnb ecx, dword [r15 + 0xFFFF]
cmovnb ecx, dword [rax + rsi * 1  + 0x0]
cmovnb ecx, dword [rax + rsi + 0xFFFF]
cmovnb ecx, dword [r15 + rsi + 0xFFFF]
cmovnb ecx, dword [rax + r15 + 0xFFFF]
cmovnb ecx, dword [rax + rsi * 2 + 0xFFFF2]
cmovnb ecx, dword [rax + rsi * 4 + 0xFFFF4]
cmovnb ecx, dword [rax + rsi * 8 + 0xFFFF8]
cmovnb ecx, dword [rsp + rax * 8 + 0xFFFF8]
cmovnb ecx, dword [r15 + rax * 8 + 0xFFFF8]
cmovnb ecx, dword [rsp + r15 * 8 + 0xFFFF8]
cmovnb ecx, dword [r14 + r15 * 8 + 0xFFFF8]
cmovnb ebx, dword [0x0]
cmovnb ebx, dword [0xFF]
cmovnb ebx, dword [rel $ + 0x0]
cmovnb ebx, dword [rel $ + 0xFF]
cmovnb ebx, dword [rel $ + 0xFFFF]
cmovnb ebx, dword [rax]
cmovnb ebx, dword [rax + 0x0]
cmovnb ebx, dword [rax + 0xFFFF]
cmovnb ebx, dword [r15 + 0xFFFF]
cmovnb ebx, dword [rax + rsi * 1  + 0x0]
cmovnb ebx, dword [rax + rsi + 0xFFFF]
cmovnb ebx, dword [r15 + rsi + 0xFFFF]
cmovnb ebx, dword [rax + r15 + 0xFFFF]
cmovnb ebx, dword [rax + rsi * 2 + 0xFFFF2]
cmovnb ebx, dword [rax + rsi * 4 + 0xFFFF4]
cmovnb ebx, dword [rax + rsi * 8 + 0xFFFF8]
cmovnb ebx, dword [rsp + rax * 8 + 0xFFFF8]
cmovnb ebx, dword [r15 + rax * 8 + 0xFFFF8]
cmovnb ebx, dword [rsp + r15 * 8 + 0xFFFF8]
cmovnb ebx, dword [r14 + r15 * 8 + 0xFFFF8]
cmovnb r15d, dword [0x0]
cmovnb r15d, dword [0xFF]
cmovnb r15d, dword [rel $ + 0x0]
cmovnb r15d, dword [rel $ + 0xFF]
cmovnb r15d, dword [rel $ + 0xFFFF]
cmovnb r15d, dword [rax]
cmovnb r15d, dword [rax + 0x0]
cmovnb r15d, dword [rax + 0xFFFF]
cmovnb r15d, dword [r15 + 0xFFFF]
cmovnb r15d, dword [rax + rsi * 1  + 0x0]
cmovnb r15d, dword [rax + rsi + 0xFFFF]
cmovnb r15d, dword [r15 + rsi + 0xFFFF]
cmovnb r15d, dword [rax + r15 + 0xFFFF]
cmovnb r15d, dword [rax + rsi * 2 + 0xFFFF2]
cmovnb r15d, dword [rax + rsi * 4 + 0xFFFF4]
cmovnb r15d, dword [rax + rsi * 8 + 0xFFFF8]
cmovnb r15d, dword [rsp + rax * 8 + 0xFFFF8]
cmovnb r15d, dword [r15 + rax * 8 + 0xFFFF8]
cmovnb r15d, dword [rsp + r15 * 8 + 0xFFFF8]
cmovnb r15d, dword [r14 + r15 * 8 + 0xFFFF8]
cmovnb rcx, rcx
cmovnb rcx, rbx
cmovnb rcx, r15
cmovnb rbx, rcx
cmovnb rbx, rbx
cmovnb rbx, r15
cmovnb r15, rcx
cmovnb r15, rbx
cmovnb r15, r15
cmovnb rcx, qword [0x0]
cmovnb rcx, qword [0xFF]
cmovnb rcx, qword [rel $ + 0x0]
cmovnb rcx, qword [rel $ + 0xFF]
cmovnb rcx, qword [rel $ + 0xFFFF]
cmovnb rcx, qword [rax]
cmovnb rcx, qword [rax + 0x0]
cmovnb rcx, qword [rax + 0xFFFF]
cmovnb rcx, qword [r15 + 0xFFFF]
cmovnb rcx, qword [rax + rsi * 1  + 0x0]
cmovnb rcx, qword [rax + rsi + 0xFFFF]
cmovnb rcx, qword [r15 + rsi + 0xFFFF]
cmovnb rcx, qword [rax + r15 + 0xFFFF]
cmovnb rcx, qword [rax + rsi * 2 + 0xFFFF2]
cmovnb rcx, qword [rax + rsi * 4 + 0xFFFF4]
cmovnb rcx, qword [rax + rsi * 8 + 0xFFFF8]
cmovnb rcx, qword [rsp + rax * 8 + 0xFFFF8]
cmovnb rcx, qword [r15 + rax * 8 + 0xFFFF8]
cmovnb rcx, qword [rsp + r15 * 8 + 0xFFFF8]
cmovnb rcx, qword [r14 + r15 * 8 + 0xFFFF8]
cmovnb rbx, qword [0x0]
cmovnb rbx, qword [0xFF]
cmovnb rbx, qword [rel $ + 0x0]
cmovnb rbx, qword [rel $ + 0xFF]
cmovnb rbx, qword [rel $ + 0xFFFF]
cmovnb rbx, qword [rax]
cmovnb rbx, qword [rax + 0x0]
cmovnb rbx, qword [rax + 0xFFFF]
cmovnb rbx, qword [r15 + 0xFFFF]
cmovnb rbx, qword [rax + rsi * 1  + 0x0]
cmovnb rbx, qword [rax + rsi + 0xFFFF]
cmovnb rbx, qword [r15 + rsi + 0xFFFF]
cmovnb rbx, qword [rax + r15 + 0xFFFF]
cmovnb rbx, qword [rax + rsi * 2 + 0xFFFF2]
cmovnb rbx, qword [rax + rsi * 4 + 0xFFFF4]
cmovnb rbx, qword [rax + rsi * 8 + 0xFFFF8]
cmovnb rbx, qword [rsp + rax * 8 + 0xFFFF8]
cmovnb rbx, qword [r15 + rax * 8 + 0xFFFF8]
cmovnb rbx, qword [rsp + r15 * 8 + 0xFFFF8]
cmovnb rbx, qword [r14 + r15 * 8 + 0xFFFF8]
cmovnb r15, qword [0x0]
cmovnb r15, qword [0xFF]
cmovnb r15, qword [rel $ + 0x0]
cmovnb r15, qword [rel $ + 0xFF]
cmovnb r15, qword [rel $ + 0xFFFF]
cmovnb r15, qword [rax]
cmovnb r15, qword [rax + 0x0]
cmovnb r15, qword [rax + 0xFFFF]
cmovnb r15, qword [r15 + 0xFFFF]
cmovnb r15, qword [rax + rsi * 1  + 0x0]
cmovnb r15, qword [rax + rsi + 0xFFFF]
cmovnb r15, qword [r15 + rsi + 0xFFFF]
cmovnb r15, qword [rax + r15 + 0xFFFF]
cmovnb r15, qword [rax + rsi * 2 + 0xFFFF2]
cmovnb r15, qword [rax + rsi * 4 + 0xFFFF4]
cmovnb r15, qword [rax + rsi * 8 + 0xFFFF8]
cmovnb r15, qword [rsp + rax * 8 + 0xFFFF8]
cmovnb r15, qword [r15 + rax * 8 + 0xFFFF8]
cmovnb r15, qword [rsp + r15 * 8 + 0xFFFF8]
cmovnb r15, qword [r14 + r15 * 8 + 0xFFFF8]
