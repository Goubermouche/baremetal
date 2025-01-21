; expect: c5fbe6c0c5fbe6c1c4c17be6c7c5fbe6c8c5fbe6c9c4c17be6cfc57be6f8c57be6f9c4417be6ffc5fbe6042500000000c5fbe60425ff000000c5fbe605f8ffffffc5fbe605f7000000c5fbe605f7ff0000c5fbe600c5fbe600c5fbe680ffff0000c4c17be687ffff0000c5fbe60430c5fbe68430ffff0000c4c17be68437ffff0000c4a17be68438ffff0000c5fbe68470f2ff0f00c5fbe684b0f4ff0f00c5fbe684f0f8ff0f00c5fbe684c4f8ff0f00c4c17be684c7f8ff0f00c4a17be684fcf8ff0f00c4817be684fef8ff0f00c5fbe60c2500000000c5fbe60c25ff000000c5fbe60df8ffffffc5fbe60df7000000c5fbe60df7ff0000c5fbe608c5fbe608c5fbe688ffff0000c4c17be68fffff0000c5fbe60c30c5fbe68c30ffff0000c4c17be68c37ffff0000c4a17be68c38ffff0000c5fbe68c70f2ff0f00c5fbe68cb0f4ff0f00c5fbe68cf0f8ff0f00c5fbe68cc4f8ff0f00c4c17be68cc7f8ff0f00c4a17be68cfcf8ff0f00c4817be68cfef8ff0f00c57be63c2500000000c57be63c25ff000000c57be63df8ffffffc57be63df7000000c57be63df7ff0000c57be638c57be638c57be6b8ffff0000c4417be6bfffff0000c57be63c30c57be6bc30ffff0000c4417be6bc37ffff0000c4217be6bc38ffff0000c57be6bc70f2ff0f00c57be6bcb0f4ff0f00c57be6bcf0f8ff0f00c57be6bcc4f8ff0f00c4417be6bcc7f8ff0f00c4217be6bcfcf8ff0f00c4017be6bcfef8ff0f00c5ffe6c0c5ffe6c1c4c17fe6c7c5ffe6c8c5ffe6c9c4c17fe6cfc57fe6f8c57fe6f9c4417fe6ff

vcvtpd2dq xmm0, xmm0
vcvtpd2dq xmm0, xmm1
vcvtpd2dq xmm0, xmm15
vcvtpd2dq xmm1, xmm0
vcvtpd2dq xmm1, xmm1
vcvtpd2dq xmm1, xmm15
vcvtpd2dq xmm15, xmm0
vcvtpd2dq xmm15, xmm1
vcvtpd2dq xmm15, xmm15
vcvtpd2dq xmm0, [0x0]
vcvtpd2dq xmm0, [0xFF]
vcvtpd2dq xmm0, [rel $ + 0x0]
vcvtpd2dq xmm0, [rel $ + 0xFF]
vcvtpd2dq xmm0, [rel $ + 0xFFFF]
vcvtpd2dq xmm0, [rax]
vcvtpd2dq xmm0, [rax + 0x0]
vcvtpd2dq xmm0, [rax + 0xFFFF]
vcvtpd2dq xmm0, [r15 + 0xFFFF]
vcvtpd2dq xmm0, [rax + rsi * 1  + 0x0]
vcvtpd2dq xmm0, [rax + rsi + 0xFFFF]
vcvtpd2dq xmm0, [r15 + rsi + 0xFFFF]
vcvtpd2dq xmm0, [rax + r15 + 0xFFFF]
vcvtpd2dq xmm0, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2dq xmm0, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2dq xmm0, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2dq xmm0, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2dq xmm0, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2dq xmm0, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2dq xmm0, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2dq xmm1, [0x0]
vcvtpd2dq xmm1, [0xFF]
vcvtpd2dq xmm1, [rel $ + 0x0]
vcvtpd2dq xmm1, [rel $ + 0xFF]
vcvtpd2dq xmm1, [rel $ + 0xFFFF]
vcvtpd2dq xmm1, [rax]
vcvtpd2dq xmm1, [rax + 0x0]
vcvtpd2dq xmm1, [rax + 0xFFFF]
vcvtpd2dq xmm1, [r15 + 0xFFFF]
vcvtpd2dq xmm1, [rax + rsi * 1  + 0x0]
vcvtpd2dq xmm1, [rax + rsi + 0xFFFF]
vcvtpd2dq xmm1, [r15 + rsi + 0xFFFF]
vcvtpd2dq xmm1, [rax + r15 + 0xFFFF]
vcvtpd2dq xmm1, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2dq xmm1, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2dq xmm1, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2dq xmm1, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2dq xmm1, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2dq xmm1, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2dq xmm1, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2dq xmm15, [0x0]
vcvtpd2dq xmm15, [0xFF]
vcvtpd2dq xmm15, [rel $ + 0x0]
vcvtpd2dq xmm15, [rel $ + 0xFF]
vcvtpd2dq xmm15, [rel $ + 0xFFFF]
vcvtpd2dq xmm15, [rax]
vcvtpd2dq xmm15, [rax + 0x0]
vcvtpd2dq xmm15, [rax + 0xFFFF]
vcvtpd2dq xmm15, [r15 + 0xFFFF]
vcvtpd2dq xmm15, [rax + rsi * 1  + 0x0]
vcvtpd2dq xmm15, [rax + rsi + 0xFFFF]
vcvtpd2dq xmm15, [r15 + rsi + 0xFFFF]
vcvtpd2dq xmm15, [rax + r15 + 0xFFFF]
vcvtpd2dq xmm15, [rax + rsi * 2 + 0xFFFF2]
vcvtpd2dq xmm15, [rax + rsi * 4 + 0xFFFF4]
vcvtpd2dq xmm15, [rax + rsi * 8 + 0xFFFF8]
vcvtpd2dq xmm15, [rsp + rax * 8 + 0xFFFF8]
vcvtpd2dq xmm15, [r15 + rax * 8 + 0xFFFF8]
vcvtpd2dq xmm15, [rsp + r15 * 8 + 0xFFFF8]
vcvtpd2dq xmm15, [r14 + r15 * 8 + 0xFFFF8]
vcvtpd2dq xmm0, ymm0
vcvtpd2dq xmm0, ymm1
vcvtpd2dq xmm0, ymm15
vcvtpd2dq xmm1, ymm0
vcvtpd2dq xmm1, ymm1
vcvtpd2dq xmm1, ymm15
vcvtpd2dq xmm15, ymm0
vcvtpd2dq xmm15, ymm1
vcvtpd2dq xmm15, ymm15