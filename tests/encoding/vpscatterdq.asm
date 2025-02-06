; expect: 62f2fd0ca0040d0000000062f2fd0ca00c0d000000006272fd0ca03c0d000000006262fd0ca03c0d0000000062f2fd2ca0040d0000000062f2fd2ca00c0d000000006272fd2ca03c0d000000006262fd2ca03c0d0000000062f2fd4ca0040d0000000062f2fd4ca00c0d000000006272fd4ca03c0d000000006262fd4ca03c0d00000000

bits 64

vpscatterdq [xmm1] {k4}, xmm0
vpscatterdq [xmm1] {k4}, xmm1
vpscatterdq [xmm1] {k4}, xmm15
vpscatterdq [xmm1] {k4}, xmm31
vpscatterdq [xmm1] {k4}, ymm0
vpscatterdq [xmm1] {k4}, ymm1
vpscatterdq [xmm1] {k4}, ymm15
vpscatterdq [xmm1] {k4}, ymm31
vpscatterdq [ymm1] {k4}, zmm0
vpscatterdq [ymm1] {k4}, zmm1
vpscatterdq [ymm1] {k4}, zmm15
vpscatterdq [ymm1] {k4}, zmm31
