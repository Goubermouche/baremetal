; expect: 0f16c00f16c1410f16c70f16c80f16c9410f16cf440f16f8440f16f9450f16ff

movlhps xmm0, xmm0
movlhps xmm0, xmm1
movlhps xmm0, xmm15
movlhps xmm1, xmm0
movlhps xmm1, xmm1
movlhps xmm1, xmm15
movlhps xmm15, xmm0
movlhps xmm15, xmm1
movlhps xmm15, xmm15