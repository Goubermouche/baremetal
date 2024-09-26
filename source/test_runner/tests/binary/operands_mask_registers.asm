; expect: 62f1fd09c2c80062f1fd0fc2d00062f17e89e6c862117e8fe6ff62f17c59c2080062f10454c23880
bits 64 

vcmppd k1 {k1}, xmm0, xmm0, 0
vcmppd k2 {k7}, xmm0, xmm0, 0

vcvtdq2pd xmm1{k1}{z}, xmm0
vcvtdq2pd xmm15{k7}{z}, xmm31

vcmpps k1 {k1}, zmm0, [rax]{1to16}, 0
vcmpps k7 {k4}, zmm31, [rax]{1to16}, -128
