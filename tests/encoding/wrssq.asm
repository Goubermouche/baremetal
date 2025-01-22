; expect: 480f38f60c2500000000480f38f61c25000000004c0f38f63c2500000000480f38f60c25ff000000480f38f61c25ff0000004c0f38f63c25ff000000480f38f60df7ffffff480f38f61df7ffffff4c0f38f63df7ffffff480f38f60df6000000480f38f61df60000004c0f38f63df6000000480f38f60df6ff0000480f38f61df6ff00004c0f38f63df6ff0000480f38f608480f38f6184c0f38f638480f38f608480f38f6184c0f38f638480f38f688ffff0000480f38f698ffff00004c0f38f6b8ffff0000490f38f68fffff0000490f38f69fffff00004d0f38f6bfffff0000480f38f60c30480f38f61c304c0f38f63c30480f38f68c30ffff0000480f38f69c30ffff00004c0f38f6bc30ffff0000490f38f68c37ffff0000490f38f69c37ffff00004d0f38f6bc37ffff00004a0f38f68c38ffff00004a0f38f69c38ffff00004e0f38f6bc38ffff0000480f38f68c70f2ff0f00480f38f69c70f2ff0f004c0f38f6bc70f2ff0f00480f38f68cb0f4ff0f00480f38f69cb0f4ff0f004c0f38f6bcb0f4ff0f00480f38f68cf0f8ff0f00480f38f69cf0f8ff0f004c0f38f6bcf0f8ff0f00480f38f68cc4f8ff0f00480f38f69cc4f8ff0f004c0f38f6bcc4f8ff0f00490f38f68cc7f8ff0f00490f38f69cc7f8ff0f004d0f38f6bcc7f8ff0f004a0f38f68cfcf8ff0f004a0f38f69cfcf8ff0f004e0f38f6bcfcf8ff0f004b0f38f68cfef8ff0f004b0f38f69cfef8ff0f004f0f38f6bcfef8ff0f00

wrssq qword [0x0], rcx
wrssq qword [0x0], rbx
wrssq qword [0x0], r15
wrssq qword [0xFF], rcx
wrssq qword [0xFF], rbx
wrssq qword [0xFF], r15
wrssq qword [rel $ + 0x0], rcx
wrssq qword [rel $ + 0x0], rbx
wrssq qword [rel $ + 0x0], r15
wrssq qword [rel $ + 0xFF], rcx
wrssq qword [rel $ + 0xFF], rbx
wrssq qword [rel $ + 0xFF], r15
wrssq qword [rel $ + 0xFFFF], rcx
wrssq qword [rel $ + 0xFFFF], rbx
wrssq qword [rel $ + 0xFFFF], r15
wrssq qword [rax], rcx
wrssq qword [rax], rbx
wrssq qword [rax], r15
wrssq qword [rax + 0x0], rcx
wrssq qword [rax + 0x0], rbx
wrssq qword [rax + 0x0], r15
wrssq qword [rax + 0xFFFF], rcx
wrssq qword [rax + 0xFFFF], rbx
wrssq qword [rax + 0xFFFF], r15
wrssq qword [r15 + 0xFFFF], rcx
wrssq qword [r15 + 0xFFFF], rbx
wrssq qword [r15 + 0xFFFF], r15
wrssq qword [rax + rsi * 1  + 0x0], rcx
wrssq qword [rax + rsi * 1  + 0x0], rbx
wrssq qword [rax + rsi * 1  + 0x0], r15
wrssq qword [rax + rsi + 0xFFFF], rcx
wrssq qword [rax + rsi + 0xFFFF], rbx
wrssq qword [rax + rsi + 0xFFFF], r15
wrssq qword [r15 + rsi + 0xFFFF], rcx
wrssq qword [r15 + rsi + 0xFFFF], rbx
wrssq qword [r15 + rsi + 0xFFFF], r15
wrssq qword [rax + r15 + 0xFFFF], rcx
wrssq qword [rax + r15 + 0xFFFF], rbx
wrssq qword [rax + r15 + 0xFFFF], r15
wrssq qword [rax + rsi * 2 + 0xFFFF2], rcx
wrssq qword [rax + rsi * 2 + 0xFFFF2], rbx
wrssq qword [rax + rsi * 2 + 0xFFFF2], r15
wrssq qword [rax + rsi * 4 + 0xFFFF4], rcx
wrssq qword [rax + rsi * 4 + 0xFFFF4], rbx
wrssq qword [rax + rsi * 4 + 0xFFFF4], r15
wrssq qword [rax + rsi * 8 + 0xFFFF8], rcx
wrssq qword [rax + rsi * 8 + 0xFFFF8], rbx
wrssq qword [rax + rsi * 8 + 0xFFFF8], r15
wrssq qword [rsp + rax * 8 + 0xFFFF8], rcx
wrssq qword [rsp + rax * 8 + 0xFFFF8], rbx
wrssq qword [rsp + rax * 8 + 0xFFFF8], r15
wrssq qword [r15 + rax * 8 + 0xFFFF8], rcx
wrssq qword [r15 + rax * 8 + 0xFFFF8], rbx
wrssq qword [r15 + rax * 8 + 0xFFFF8], r15
wrssq qword [rsp + r15 * 8 + 0xFFFF8], rcx
wrssq qword [rsp + r15 * 8 + 0xFFFF8], rbx
wrssq qword [rsp + r15 * 8 + 0xFFFF8], r15
wrssq qword [r14 + r15 * 8 + 0xFFFF8], rcx
wrssq qword [r14 + r15 * 8 + 0xFFFF8], rbx
wrssq qword [r14 + r15 * 8 + 0xFFFF8], r15