; expect: 62f2fd0ca1040d0000000062f2fd0ca10c0d000000006272fd0ca13c0d000000006262fd0ca13c0d0000000062f2fd2ca1040d0000000062f2fd2ca10c0d000000006272fd2ca13c0d000000006262fd2ca13c0d0000000062f2fd4ca1040d0000000062f2fd4ca10c0d000000006272fd4ca13c0d000000006262fd4ca13c0d00000000

bits 64

vpscatterqq [xmm1] {k4}, xmm0
vpscatterqq [xmm1] {k4}, xmm1
vpscatterqq [xmm1] {k4}, xmm15
vpscatterqq [xmm1] {k4}, xmm31
vpscatterqq [ymm1] {k4}, ymm0
vpscatterqq [ymm1] {k4}, ymm1
vpscatterqq [ymm1] {k4}, ymm15
vpscatterqq [ymm1] {k4}, ymm31
vpscatterqq [zmm1] {k4}, zmm0
vpscatterqq [zmm1] {k4}, zmm1
vpscatterqq [zmm1] {k4}, zmm15
vpscatterqq [zmm1] {k4}, zmm31
