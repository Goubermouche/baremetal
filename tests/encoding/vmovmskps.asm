; expect: c5f850c8c5f850c9c4c17850cfc5f850d8c5f850d9c4c17850dfc57850f8c57850f9c4417850ffc5fc50c8c5fc50c9c4c17c50cfc5fc50d8c5fc50d9c4c17c50dfc57c50f8c57c50f9c4417c50ff

bits 64

vmovmskps ecx, xmm0
vmovmskps ecx, xmm1
vmovmskps ecx, xmm15
vmovmskps ebx, xmm0
vmovmskps ebx, xmm1
vmovmskps ebx, xmm15
vmovmskps r15d, xmm0
vmovmskps r15d, xmm1
vmovmskps r15d, xmm15
vmovmskps ecx, ymm0
vmovmskps ecx, ymm1
vmovmskps ecx, ymm15
vmovmskps ebx, ymm0
vmovmskps ebx, ymm1
vmovmskps ebx, ymm15
vmovmskps r15d, ymm0
vmovmskps r15d, ymm1
vmovmskps r15d, ymm15
