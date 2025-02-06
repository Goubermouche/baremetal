; expect: 62f2fd0ca3040d0000000062f2fd0ca30c0d000000006272fd0ca33c0d000000006262fd0ca33c0d0000000062f2fd2ca3040d0000000062f2fd2ca30c0d000000006272fd2ca33c0d000000006262fd2ca33c0d0000000062f2fd4ca3040d0000000062f2fd4ca30c0d000000006272fd4ca33c0d000000006262fd4ca33c0d00000000

bits 64

vscatterqpd [xmm1] {k4}, xmm0
vscatterqpd [xmm1] {k4}, xmm1
vscatterqpd [xmm1] {k4}, xmm15
vscatterqpd [xmm1] {k4}, xmm31
vscatterqpd [ymm1] {k4}, ymm0
vscatterqpd [ymm1] {k4}, ymm1
vscatterqpd [ymm1] {k4}, ymm15
vscatterqpd [ymm1] {k4}, ymm31
vscatterqpd [zmm1] {k4}, zmm0
vscatterqpd [zmm1] {k4}, zmm1
vscatterqpd [zmm1] {k4}, zmm15
vscatterqpd [zmm1] {k4}, zmm31
