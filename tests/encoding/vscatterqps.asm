; expect: 62f27d0ca3040d0000000062f27d0ca30c0d0000000062727d0ca33c0d0000000062627d0ca33c0d0000000062f27d2ca3040d0000000062f27d2ca30c0d0000000062727d2ca33c0d0000000062627d2ca33c0d0000000062f27d4ca3040d0000000062f27d4ca30c0d0000000062727d4ca33c0d0000000062627d4ca33c0d00000000

bits 64

vscatterqps [xmm1] {k4}, xmm0
vscatterqps [xmm1] {k4}, xmm1
vscatterqps [xmm1] {k4}, xmm15
vscatterqps [xmm1] {k4}, xmm31
vscatterqps [ymm1] {k4}, xmm0
vscatterqps [ymm1] {k4}, xmm1
vscatterqps [ymm1] {k4}, xmm15
vscatterqps [ymm1] {k4}, xmm31
vscatterqps [zmm1] {k4}, ymm0
vscatterqps [zmm1] {k4}, ymm1
vscatterqps [zmm1] {k4}, ymm15
vscatterqps [zmm1] {k4}, ymm31
