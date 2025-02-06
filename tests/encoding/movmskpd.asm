; expect: 660f50c8660f50c966410f50cf660f50d8660f50d966410f50df66440f50f866440f50f966450f50ff

bits 64

movmskpd ecx, xmm0
movmskpd ecx, xmm1
movmskpd ecx, xmm15
movmskpd ebx, xmm0
movmskpd ebx, xmm1
movmskpd ebx, xmm15
movmskpd r15d, xmm0
movmskpd r15d, xmm1
movmskpd r15d, xmm15
