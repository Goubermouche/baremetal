; expect: 62f27d0ca1040d0000000062f27d0ca10c0d0000000062727d0ca13c0d0000000062627d0ca13c0d0000000062f27d2ca1040d0000000062f27d2ca10c0d0000000062727d2ca13c0d0000000062627d2ca13c0d0000000062f27d4ca1040d0000000062f27d4ca10c0d0000000062727d4ca13c0d0000000062627d4ca13c0d00000000

vpscatterqd [xmm1] {k4}, xmm0
vpscatterqd [xmm1] {k4}, xmm1
vpscatterqd [xmm1] {k4}, xmm15
vpscatterqd [xmm1] {k4}, xmm31
vpscatterqd [ymm1] {k4}, xmm0
vpscatterqd [ymm1] {k4}, xmm1
vpscatterqd [ymm1] {k4}, xmm15
vpscatterqd [ymm1] {k4}, xmm31
vpscatterqd [zmm1] {k4}, ymm0
vpscatterqd [zmm1] {k4}, ymm1
vpscatterqd [zmm1] {k4}, ymm15
vpscatterqd [zmm1] {k4}, ymm31