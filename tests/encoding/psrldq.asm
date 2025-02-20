; expect: 660f73d800660f73d801660f73d80a660f73d864660f73d87f660f73d880660f73d900660f73d901660f73d90a660f73d964660f73d97f660f73d98066410f73df0066410f73df0166410f73df0a66410f73df6466410f73df7f66410f73df80

bits 64

psrldq xmm0, 0
psrldq xmm0, 1
psrldq xmm0, 10
psrldq xmm0, 100
psrldq xmm0, 127
psrldq xmm0, -128
psrldq xmm1, 0
psrldq xmm1, 1
psrldq xmm1, 10
psrldq xmm1, 100
psrldq xmm1, 127
psrldq xmm1, -128
psrldq xmm15, 0
psrldq xmm15, 1
psrldq xmm15, 10
psrldq xmm15, 100
psrldq xmm15, 127
psrldq xmm15, -128
