; expect: 660f73f800660f73f801660f73f864660f73f87f660f73f880660f73f900660f73f901660f73f964660f73f97f660f73f98066410f73ff0066410f73ff0166410f73ff6466410f73ff7f66410f73ff80

pslldq xmm0, 0
pslldq xmm0, 1
pslldq xmm0, 100
pslldq xmm0, 127
pslldq xmm0, -128
pslldq xmm1, 0
pslldq xmm1, 1
pslldq xmm1, 100
pslldq xmm1, 127
pslldq xmm1, -128
pslldq xmm15, 0
pslldq xmm15, 1
pslldq xmm15, 100
pslldq xmm15, 127
pslldq xmm15, -128