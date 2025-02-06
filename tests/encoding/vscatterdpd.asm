; expect: 62f2fd0ca2040d0000000062f2fd0ca20c0d000000006272fd0ca23c0d000000006262fd0ca23c0d0000000062f2fd2ca2040d0000000062f2fd2ca20c0d000000006272fd2ca23c0d000000006262fd2ca23c0d0000000062f2fd4ca2040d0000000062f2fd4ca20c0d000000006272fd4ca23c0d000000006262fd4ca23c0d00000000

bits 64

vscatterdpd [xmm1] {k4}, xmm0
vscatterdpd [xmm1] {k4}, xmm1
vscatterdpd [xmm1] {k4}, xmm15
vscatterdpd [xmm1] {k4}, xmm31
vscatterdpd [xmm1] {k4}, ymm0
vscatterdpd [xmm1] {k4}, ymm1
vscatterdpd [xmm1] {k4}, ymm15
vscatterdpd [xmm1] {k4}, ymm31
vscatterdpd [ymm1] {k4}, zmm0
vscatterdpd [ymm1] {k4}, zmm1
vscatterdpd [ymm1] {k4}, zmm15
vscatterdpd [ymm1] {k4}, zmm31
