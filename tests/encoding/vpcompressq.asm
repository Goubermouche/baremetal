; expect: 62f2fd088bc062f2fd088bc86272fd088bf86262fd088bf862f2fd088bc162f2fd088bc96272fd088bf96262fd088bf962d2fd088bc762d2fd088bcf6252fd088bff6242fd088bff6292fd088bc76292fd088bcf6212fd088bff6202fd088bff62f2fd0c8b04250000000062f2fd0c8b0c25000000006272fd0c8b3c25000000006262fd0c8b3c250000000062f2fd288bc062f2fd288bc86272fd288bf86262fd288bf862f2fd288bc162f2fd288bc96272fd288bf96262fd288bf962d2fd288bc762d2fd288bcf6252fd288bff6242fd288bff6292fd288bc76292fd288bcf6212fd288bff6202fd288bff62f2fd2c8b04250000000062f2fd2c8b0c25000000006272fd2c8b3c25000000006262fd2c8b3c250000000062f2fd488bc062f2fd488bc86272fd488bf86262fd488bf862f2fd488bc162f2fd488bc96272fd488bf96262fd488bf962d2fd488bc762d2fd488bcf6252fd488bff6242fd488bff6292fd488bc76292fd488bcf6212fd488bff6202fd488bff62f2fd4c8b04250000000062f2fd4c8b0c25000000006272fd4c8b3c25000000006262fd4c8b3c2500000000

vpcompressq xmm0, xmm0
vpcompressq xmm0, xmm1
vpcompressq xmm0, xmm15
vpcompressq xmm0, xmm31
vpcompressq xmm1, xmm0
vpcompressq xmm1, xmm1
vpcompressq xmm1, xmm15
vpcompressq xmm1, xmm31
vpcompressq xmm15, xmm0
vpcompressq xmm15, xmm1
vpcompressq xmm15, xmm15
vpcompressq xmm15, xmm31
vpcompressq xmm31, xmm0
vpcompressq xmm31, xmm1
vpcompressq xmm31, xmm15
vpcompressq xmm31, xmm31
vpcompressq [0x0] {k4}, xmm0
vpcompressq [0x0] {k4}, xmm1
vpcompressq [0x0] {k4}, xmm15
vpcompressq [0x0] {k4}, xmm31
vpcompressq ymm0, ymm0
vpcompressq ymm0, ymm1
vpcompressq ymm0, ymm15
vpcompressq ymm0, ymm31
vpcompressq ymm1, ymm0
vpcompressq ymm1, ymm1
vpcompressq ymm1, ymm15
vpcompressq ymm1, ymm31
vpcompressq ymm15, ymm0
vpcompressq ymm15, ymm1
vpcompressq ymm15, ymm15
vpcompressq ymm15, ymm31
vpcompressq ymm31, ymm0
vpcompressq ymm31, ymm1
vpcompressq ymm31, ymm15
vpcompressq ymm31, ymm31
vpcompressq [0x0] {k4}, ymm0
vpcompressq [0x0] {k4}, ymm1
vpcompressq [0x0] {k4}, ymm15
vpcompressq [0x0] {k4}, ymm31
vpcompressq zmm0, zmm0
vpcompressq zmm0, zmm1
vpcompressq zmm0, zmm15
vpcompressq zmm0, zmm31
vpcompressq zmm1, zmm0
vpcompressq zmm1, zmm1
vpcompressq zmm1, zmm15
vpcompressq zmm1, zmm31
vpcompressq zmm15, zmm0
vpcompressq zmm15, zmm1
vpcompressq zmm15, zmm15
vpcompressq zmm15, zmm31
vpcompressq zmm31, zmm0
vpcompressq zmm31, zmm1
vpcompressq zmm31, zmm15
vpcompressq zmm31, zmm31
vpcompressq [0x0] {k4}, zmm0
vpcompressq [0x0] {k4}, zmm1
vpcompressq [0x0] {k4}, zmm15
vpcompressq [0x0] {k4}, zmm31