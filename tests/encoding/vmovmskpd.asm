; expect: c5f950c8c5f950c9c4c17950cfc5f950d8c5f950d9c4c17950dfc57950f8c57950f9c4417950ffc5fd50c8c5fd50c9c4c17d50cfc5fd50d8c5fd50d9c4c17d50dfc57d50f8c57d50f9c4417d50ff

bits 64

vmovmskpd ecx, xmm0
vmovmskpd ecx, xmm1
vmovmskpd ecx, xmm15
vmovmskpd ebx, xmm0
vmovmskpd ebx, xmm1
vmovmskpd ebx, xmm15
vmovmskpd r15d, xmm0
vmovmskpd r15d, xmm1
vmovmskpd r15d, xmm15
vmovmskpd ecx, ymm0
vmovmskpd ecx, ymm1
vmovmskpd ecx, ymm15
vmovmskpd ebx, ymm0
vmovmskpd ebx, ymm1
vmovmskpd ebx, ymm15
vmovmskpd r15d, ymm0
vmovmskpd r15d, ymm1
vmovmskpd r15d, ymm15
