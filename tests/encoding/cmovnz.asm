; expect: 660f45c9660f45ca660f45cb66410f45cf660f45d1660f45d2660f45d366410f45d7660f45d9660f45da660f45db66410f45df66440f45f966440f45fa66440f45fb66450f45ff660f450c2500000000660f450c25ff000000660f450df8ffffff660f450df7000000660f450df7ff0000660f4508660f4508660f4588ffff000066410f458fffff0000660f450c30660f458c30ffff000066410f458c37ffff000066420f458c38ffff0000660f458c70f2ff0f00660f458cb0f4ff0f00660f458cf0f8ff0f00660f458cc4f8ff0f0066410f458cc7f8ff0f0066420f458cfcf8ff0f0066430f458cfef8ff0f00660f45142500000000660f451425ff000000660f4515f8ffffff660f4515f7000000660f4515f7ff0000660f4510660f4510660f4590ffff000066410f4597ffff0000660f451430660f459430ffff000066410f459437ffff000066420f459438ffff0000660f459470f2ff0f00660f4594b0f4ff0f00660f4594f0f8ff0f00660f4594c4f8ff0f0066410f4594c7f8ff0f0066420f4594fcf8ff0f0066430f4594fef8ff0f00660f451c2500000000660f451c25ff000000660f451df8ffffff660f451df7000000660f451df7ff0000660f4518660f4518660f4598ffff000066410f459fffff0000660f451c30660f459c30ffff000066410f459c37ffff000066420f459c38ffff0000660f459c70f2ff0f00660f459cb0f4ff0f00660f459cf0f8ff0f00660f459cc4f8ff0f0066410f459cc7f8ff0f0066420f459cfcf8ff0f0066430f459cfef8ff0f0066440f453c250000000066440f453c25ff00000066440f453df7ffffff66440f453df600000066440f453df6ff000066440f453866440f453866440f45b8ffff000066450f45bfffff000066440f453c3066440f45bc30ffff000066450f45bc37ffff000066460f45bc38ffff000066440f45bc70f2ff0f0066440f45bcb0f4ff0f0066440f45bcf0f8ff0f0066440f45bcc4f8ff0f0066450f45bcc7f8ff0f0066460f45bcfcf8ff0f0066470f45bcfef8ff0f000f45c90f45cb410f45cf0f45d90f45db410f45df440f45f9440f45fb450f45ff0f450c25000000000f450c25ff0000000f450df9ffffff0f450df80000000f450df8ff00000f45080f45080f4588ffff0000410f458fffff00000f450c300f458c30ffff0000410f458c37ffff0000420f458c38ffff00000f458c70f2ff0f000f458cb0f4ff0f000f458cf0f8ff0f000f458cc4f8ff0f00410f458cc7f8ff0f00420f458cfcf8ff0f00430f458cfef8ff0f000f451c25000000000f451c25ff0000000f451df9ffffff0f451df80000000f451df8ff00000f45180f45180f4598ffff0000410f459fffff00000f451c300f459c30ffff0000410f459c37ffff0000420f459c38ffff00000f459c70f2ff0f000f459cb0f4ff0f000f459cf0f8ff0f000f459cc4f8ff0f00410f459cc7f8ff0f00420f459cfcf8ff0f00430f459cfef8ff0f00440f453c2500000000440f453c25ff000000440f453df8ffffff440f453df7000000440f453df7ff0000440f4538440f4538440f45b8ffff0000450f45bfffff0000440f453c30440f45bc30ffff0000450f45bc37ffff0000460f45bc38ffff0000440f45bc70f2ff0f00440f45bcb0f4ff0f00440f45bcf0f8ff0f00440f45bcc4f8ff0f00450f45bcc7f8ff0f00460f45bcfcf8ff0f00470f45bcfef8ff0f00480f45c9480f45cb490f45cf480f45d9480f45db490f45df4c0f45f94c0f45fb4d0f45ff480f450c2500000000480f450c25ff000000480f450df8ffffff480f450df7000000480f450df7ff0000480f4508480f4508480f4588ffff0000490f458fffff0000480f450c30480f458c30ffff0000490f458c37ffff00004a0f458c38ffff0000480f458c70f2ff0f00480f458cb0f4ff0f00480f458cf0f8ff0f00480f458cc4f8ff0f00490f458cc7f8ff0f004a0f458cfcf8ff0f004b0f458cfef8ff0f00480f451c2500000000480f451c25ff000000480f451df8ffffff480f451df7000000480f451df7ff0000480f4518480f4518480f4598ffff0000490f459fffff0000480f451c30480f459c30ffff0000490f459c37ffff00004a0f459c38ffff0000480f459c70f2ff0f00480f459cb0f4ff0f00480f459cf0f8ff0f00480f459cc4f8ff0f00490f459cc7f8ff0f004a0f459cfcf8ff0f004b0f459cfef8ff0f004c0f453c25000000004c0f453c25ff0000004c0f453df8ffffff4c0f453df70000004c0f453df7ff00004c0f45384c0f45384c0f45b8ffff00004d0f45bfffff00004c0f453c304c0f45bc30ffff00004d0f45bc37ffff00004e0f45bc38ffff00004c0f45bc70f2ff0f004c0f45bcb0f4ff0f004c0f45bcf0f8ff0f004c0f45bcc4f8ff0f004d0f45bcc7f8ff0f004e0f45bcfcf8ff0f004f0f45bcfef8ff0f00

bits 64

cmovnz cx, cx
cmovnz cx, dx
cmovnz cx, bx
cmovnz cx, r15w
cmovnz dx, cx
cmovnz dx, dx
cmovnz dx, bx
cmovnz dx, r15w
cmovnz bx, cx
cmovnz bx, dx
cmovnz bx, bx
cmovnz bx, r15w
cmovnz r15w, cx
cmovnz r15w, dx
cmovnz r15w, bx
cmovnz r15w, r15w
cmovnz cx, word [0x0]
cmovnz cx, word [0xFF]
cmovnz cx, word [rel $ + 0x0]
cmovnz cx, word [rel $ + 0xFF]
cmovnz cx, word [rel $ + 0xFFFF]
cmovnz cx, word [rax]
cmovnz cx, word [rax + 0x0]
cmovnz cx, word [rax + 0xFFFF]
cmovnz cx, word [r15 + 0xFFFF]
cmovnz cx, word [rax + rsi * 1  + 0x0]
cmovnz cx, word [rax + rsi + 0xFFFF]
cmovnz cx, word [r15 + rsi + 0xFFFF]
cmovnz cx, word [rax + r15 + 0xFFFF]
cmovnz cx, word [rax + rsi * 2 + 0xFFFF2]
cmovnz cx, word [rax + rsi * 4 + 0xFFFF4]
cmovnz cx, word [rax + rsi * 8 + 0xFFFF8]
cmovnz cx, word [rsp + rax * 8 + 0xFFFF8]
cmovnz cx, word [r15 + rax * 8 + 0xFFFF8]
cmovnz cx, word [rsp + r15 * 8 + 0xFFFF8]
cmovnz cx, word [r14 + r15 * 8 + 0xFFFF8]
cmovnz dx, word [0x0]
cmovnz dx, word [0xFF]
cmovnz dx, word [rel $ + 0x0]
cmovnz dx, word [rel $ + 0xFF]
cmovnz dx, word [rel $ + 0xFFFF]
cmovnz dx, word [rax]
cmovnz dx, word [rax + 0x0]
cmovnz dx, word [rax + 0xFFFF]
cmovnz dx, word [r15 + 0xFFFF]
cmovnz dx, word [rax + rsi * 1  + 0x0]
cmovnz dx, word [rax + rsi + 0xFFFF]
cmovnz dx, word [r15 + rsi + 0xFFFF]
cmovnz dx, word [rax + r15 + 0xFFFF]
cmovnz dx, word [rax + rsi * 2 + 0xFFFF2]
cmovnz dx, word [rax + rsi * 4 + 0xFFFF4]
cmovnz dx, word [rax + rsi * 8 + 0xFFFF8]
cmovnz dx, word [rsp + rax * 8 + 0xFFFF8]
cmovnz dx, word [r15 + rax * 8 + 0xFFFF8]
cmovnz dx, word [rsp + r15 * 8 + 0xFFFF8]
cmovnz dx, word [r14 + r15 * 8 + 0xFFFF8]
cmovnz bx, word [0x0]
cmovnz bx, word [0xFF]
cmovnz bx, word [rel $ + 0x0]
cmovnz bx, word [rel $ + 0xFF]
cmovnz bx, word [rel $ + 0xFFFF]
cmovnz bx, word [rax]
cmovnz bx, word [rax + 0x0]
cmovnz bx, word [rax + 0xFFFF]
cmovnz bx, word [r15 + 0xFFFF]
cmovnz bx, word [rax + rsi * 1  + 0x0]
cmovnz bx, word [rax + rsi + 0xFFFF]
cmovnz bx, word [r15 + rsi + 0xFFFF]
cmovnz bx, word [rax + r15 + 0xFFFF]
cmovnz bx, word [rax + rsi * 2 + 0xFFFF2]
cmovnz bx, word [rax + rsi * 4 + 0xFFFF4]
cmovnz bx, word [rax + rsi * 8 + 0xFFFF8]
cmovnz bx, word [rsp + rax * 8 + 0xFFFF8]
cmovnz bx, word [r15 + rax * 8 + 0xFFFF8]
cmovnz bx, word [rsp + r15 * 8 + 0xFFFF8]
cmovnz bx, word [r14 + r15 * 8 + 0xFFFF8]
cmovnz r15w, word [0x0]
cmovnz r15w, word [0xFF]
cmovnz r15w, word [rel $ + 0x0]
cmovnz r15w, word [rel $ + 0xFF]
cmovnz r15w, word [rel $ + 0xFFFF]
cmovnz r15w, word [rax]
cmovnz r15w, word [rax + 0x0]
cmovnz r15w, word [rax + 0xFFFF]
cmovnz r15w, word [r15 + 0xFFFF]
cmovnz r15w, word [rax + rsi * 1  + 0x0]
cmovnz r15w, word [rax + rsi + 0xFFFF]
cmovnz r15w, word [r15 + rsi + 0xFFFF]
cmovnz r15w, word [rax + r15 + 0xFFFF]
cmovnz r15w, word [rax + rsi * 2 + 0xFFFF2]
cmovnz r15w, word [rax + rsi * 4 + 0xFFFF4]
cmovnz r15w, word [rax + rsi * 8 + 0xFFFF8]
cmovnz r15w, word [rsp + rax * 8 + 0xFFFF8]
cmovnz r15w, word [r15 + rax * 8 + 0xFFFF8]
cmovnz r15w, word [rsp + r15 * 8 + 0xFFFF8]
cmovnz r15w, word [r14 + r15 * 8 + 0xFFFF8]
cmovnz ecx, ecx
cmovnz ecx, ebx
cmovnz ecx, r15d
cmovnz ebx, ecx
cmovnz ebx, ebx
cmovnz ebx, r15d
cmovnz r15d, ecx
cmovnz r15d, ebx
cmovnz r15d, r15d
cmovnz ecx, dword [0x0]
cmovnz ecx, dword [0xFF]
cmovnz ecx, dword [rel $ + 0x0]
cmovnz ecx, dword [rel $ + 0xFF]
cmovnz ecx, dword [rel $ + 0xFFFF]
cmovnz ecx, dword [rax]
cmovnz ecx, dword [rax + 0x0]
cmovnz ecx, dword [rax + 0xFFFF]
cmovnz ecx, dword [r15 + 0xFFFF]
cmovnz ecx, dword [rax + rsi * 1  + 0x0]
cmovnz ecx, dword [rax + rsi + 0xFFFF]
cmovnz ecx, dword [r15 + rsi + 0xFFFF]
cmovnz ecx, dword [rax + r15 + 0xFFFF]
cmovnz ecx, dword [rax + rsi * 2 + 0xFFFF2]
cmovnz ecx, dword [rax + rsi * 4 + 0xFFFF4]
cmovnz ecx, dword [rax + rsi * 8 + 0xFFFF8]
cmovnz ecx, dword [rsp + rax * 8 + 0xFFFF8]
cmovnz ecx, dword [r15 + rax * 8 + 0xFFFF8]
cmovnz ecx, dword [rsp + r15 * 8 + 0xFFFF8]
cmovnz ecx, dword [r14 + r15 * 8 + 0xFFFF8]
cmovnz ebx, dword [0x0]
cmovnz ebx, dword [0xFF]
cmovnz ebx, dword [rel $ + 0x0]
cmovnz ebx, dword [rel $ + 0xFF]
cmovnz ebx, dword [rel $ + 0xFFFF]
cmovnz ebx, dword [rax]
cmovnz ebx, dword [rax + 0x0]
cmovnz ebx, dword [rax + 0xFFFF]
cmovnz ebx, dword [r15 + 0xFFFF]
cmovnz ebx, dword [rax + rsi * 1  + 0x0]
cmovnz ebx, dword [rax + rsi + 0xFFFF]
cmovnz ebx, dword [r15 + rsi + 0xFFFF]
cmovnz ebx, dword [rax + r15 + 0xFFFF]
cmovnz ebx, dword [rax + rsi * 2 + 0xFFFF2]
cmovnz ebx, dword [rax + rsi * 4 + 0xFFFF4]
cmovnz ebx, dword [rax + rsi * 8 + 0xFFFF8]
cmovnz ebx, dword [rsp + rax * 8 + 0xFFFF8]
cmovnz ebx, dword [r15 + rax * 8 + 0xFFFF8]
cmovnz ebx, dword [rsp + r15 * 8 + 0xFFFF8]
cmovnz ebx, dword [r14 + r15 * 8 + 0xFFFF8]
cmovnz r15d, dword [0x0]
cmovnz r15d, dword [0xFF]
cmovnz r15d, dword [rel $ + 0x0]
cmovnz r15d, dword [rel $ + 0xFF]
cmovnz r15d, dword [rel $ + 0xFFFF]
cmovnz r15d, dword [rax]
cmovnz r15d, dword [rax + 0x0]
cmovnz r15d, dword [rax + 0xFFFF]
cmovnz r15d, dword [r15 + 0xFFFF]
cmovnz r15d, dword [rax + rsi * 1  + 0x0]
cmovnz r15d, dword [rax + rsi + 0xFFFF]
cmovnz r15d, dword [r15 + rsi + 0xFFFF]
cmovnz r15d, dword [rax + r15 + 0xFFFF]
cmovnz r15d, dword [rax + rsi * 2 + 0xFFFF2]
cmovnz r15d, dword [rax + rsi * 4 + 0xFFFF4]
cmovnz r15d, dword [rax + rsi * 8 + 0xFFFF8]
cmovnz r15d, dword [rsp + rax * 8 + 0xFFFF8]
cmovnz r15d, dword [r15 + rax * 8 + 0xFFFF8]
cmovnz r15d, dword [rsp + r15 * 8 + 0xFFFF8]
cmovnz r15d, dword [r14 + r15 * 8 + 0xFFFF8]
cmovnz rcx, rcx
cmovnz rcx, rbx
cmovnz rcx, r15
cmovnz rbx, rcx
cmovnz rbx, rbx
cmovnz rbx, r15
cmovnz r15, rcx
cmovnz r15, rbx
cmovnz r15, r15
cmovnz rcx, qword [0x0]
cmovnz rcx, qword [0xFF]
cmovnz rcx, qword [rel $ + 0x0]
cmovnz rcx, qword [rel $ + 0xFF]
cmovnz rcx, qword [rel $ + 0xFFFF]
cmovnz rcx, qword [rax]
cmovnz rcx, qword [rax + 0x0]
cmovnz rcx, qword [rax + 0xFFFF]
cmovnz rcx, qword [r15 + 0xFFFF]
cmovnz rcx, qword [rax + rsi * 1  + 0x0]
cmovnz rcx, qword [rax + rsi + 0xFFFF]
cmovnz rcx, qword [r15 + rsi + 0xFFFF]
cmovnz rcx, qword [rax + r15 + 0xFFFF]
cmovnz rcx, qword [rax + rsi * 2 + 0xFFFF2]
cmovnz rcx, qword [rax + rsi * 4 + 0xFFFF4]
cmovnz rcx, qword [rax + rsi * 8 + 0xFFFF8]
cmovnz rcx, qword [rsp + rax * 8 + 0xFFFF8]
cmovnz rcx, qword [r15 + rax * 8 + 0xFFFF8]
cmovnz rcx, qword [rsp + r15 * 8 + 0xFFFF8]
cmovnz rcx, qword [r14 + r15 * 8 + 0xFFFF8]
cmovnz rbx, qword [0x0]
cmovnz rbx, qword [0xFF]
cmovnz rbx, qword [rel $ + 0x0]
cmovnz rbx, qword [rel $ + 0xFF]
cmovnz rbx, qword [rel $ + 0xFFFF]
cmovnz rbx, qword [rax]
cmovnz rbx, qword [rax + 0x0]
cmovnz rbx, qword [rax + 0xFFFF]
cmovnz rbx, qword [r15 + 0xFFFF]
cmovnz rbx, qword [rax + rsi * 1  + 0x0]
cmovnz rbx, qword [rax + rsi + 0xFFFF]
cmovnz rbx, qword [r15 + rsi + 0xFFFF]
cmovnz rbx, qword [rax + r15 + 0xFFFF]
cmovnz rbx, qword [rax + rsi * 2 + 0xFFFF2]
cmovnz rbx, qword [rax + rsi * 4 + 0xFFFF4]
cmovnz rbx, qword [rax + rsi * 8 + 0xFFFF8]
cmovnz rbx, qword [rsp + rax * 8 + 0xFFFF8]
cmovnz rbx, qword [r15 + rax * 8 + 0xFFFF8]
cmovnz rbx, qword [rsp + r15 * 8 + 0xFFFF8]
cmovnz rbx, qword [r14 + r15 * 8 + 0xFFFF8]
cmovnz r15, qword [0x0]
cmovnz r15, qword [0xFF]
cmovnz r15, qword [rel $ + 0x0]
cmovnz r15, qword [rel $ + 0xFF]
cmovnz r15, qword [rel $ + 0xFFFF]
cmovnz r15, qword [rax]
cmovnz r15, qword [rax + 0x0]
cmovnz r15, qword [rax + 0xFFFF]
cmovnz r15, qword [r15 + 0xFFFF]
cmovnz r15, qword [rax + rsi * 1  + 0x0]
cmovnz r15, qword [rax + rsi + 0xFFFF]
cmovnz r15, qword [r15 + rsi + 0xFFFF]
cmovnz r15, qword [rax + r15 + 0xFFFF]
cmovnz r15, qword [rax + rsi * 2 + 0xFFFF2]
cmovnz r15, qword [rax + rsi * 4 + 0xFFFF4]
cmovnz r15, qword [rax + rsi * 8 + 0xFFFF8]
cmovnz r15, qword [rsp + rax * 8 + 0xFFFF8]
cmovnz r15, qword [r15 + rax * 8 + 0xFFFF8]
cmovnz r15, qword [rsp + r15 * 8 + 0xFFFF8]
cmovnz r15, qword [r14 + r15 * 8 + 0xFFFF8]
