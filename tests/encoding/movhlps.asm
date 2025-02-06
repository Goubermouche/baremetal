; expect: 0f12c00f12c1410f12c70f12c80f12c9410f12cf440f12f8440f12f9450f12ff

bits 64

movhlps xmm0, xmm0
movhlps xmm0, xmm1
movhlps xmm0, xmm15
movhlps xmm1, xmm0
movhlps xmm1, xmm1
movhlps xmm1, xmm15
movhlps xmm15, xmm0
movhlps xmm15, xmm1
movhlps xmm15, xmm15
