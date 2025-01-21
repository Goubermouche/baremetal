; expect: 62f27d0ca2040d0000000062f27d0ca20c0d0000000062727d0ca23c0d0000000062627d0ca23c0d0000000062f27d2ca2040d0000000062f27d2ca20c0d0000000062727d2ca23c0d0000000062627d2ca23c0d0000000062f27d4ca2040d0000000062f27d4ca20c0d0000000062727d4ca23c0d0000000062627d4ca23c0d00000000

vscatterdps [xmm1] {k4}, xmm0
vscatterdps [xmm1] {k4}, xmm1
vscatterdps [xmm1] {k4}, xmm15
vscatterdps [xmm1] {k4}, xmm31
vscatterdps [ymm1] {k4}, ymm0
vscatterdps [ymm1] {k4}, ymm1
vscatterdps [ymm1] {k4}, ymm15
vscatterdps [ymm1] {k4}, ymm31
vscatterdps [zmm1] {k4}, zmm0
vscatterdps [zmm1] {k4}, zmm1
vscatterdps [zmm1] {k4}, zmm15
vscatterdps [zmm1] {k4}, zmm31