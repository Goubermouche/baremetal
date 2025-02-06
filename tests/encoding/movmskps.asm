; expect: 0f50c80f50c9410f50cf0f50d80f50d9410f50df440f50f8440f50f9450f50ff

bits 64

movmskps ecx, xmm0
movmskps ecx, xmm1
movmskps ecx, xmm15
movmskps ebx, xmm0
movmskps ebx, xmm1
movmskps ebx, xmm15
movmskps r15d, xmm0
movmskps r15d, xmm1
movmskps r15d, xmm15
