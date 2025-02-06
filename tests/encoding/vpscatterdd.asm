; expect: 62f27d0ca0040d0000000062f27d0ca00c0d0000000062727d0ca03c0d0000000062627d0ca03c0d0000000062f27d2ca0040d0000000062f27d2ca00c0d0000000062727d2ca03c0d0000000062627d2ca03c0d0000000062f27d4ca0040d0000000062f27d4ca00c0d0000000062727d4ca03c0d0000000062627d4ca03c0d00000000

bits 64

vpscatterdd [xmm1] {k4}, xmm0
vpscatterdd [xmm1] {k4}, xmm1
vpscatterdd [xmm1] {k4}, xmm15
vpscatterdd [xmm1] {k4}, xmm31
vpscatterdd [ymm1] {k4}, ymm0
vpscatterdd [ymm1] {k4}, ymm1
vpscatterdd [ymm1] {k4}, ymm15
vpscatterdd [ymm1] {k4}, ymm31
vpscatterdd [zmm1] {k4}, zmm0
vpscatterdd [zmm1] {k4}, zmm1
vpscatterdd [zmm1] {k4}, zmm15
vpscatterdd [zmm1] {k4}, zmm31
