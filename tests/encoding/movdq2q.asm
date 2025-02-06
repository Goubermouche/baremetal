; expect: f20fd6c0f20fd6c1f2410fd6c7f20fd6c8f20fd6c9f2410fd6cff20fd6f8f20fd6f9f2410fd6ff

bits 64

movdq2q mm0, xmm0
movdq2q mm0, xmm1
movdq2q mm0, xmm15
movdq2q mm1, xmm0
movdq2q mm1, xmm1
movdq2q mm1, xmm15
movdq2q mm7, xmm0
movdq2q mm7, xmm1
movdq2q mm7, xmm15
