; expect: 62f2fd0863c062f2fd0863c86272fd0863f86262fd0863f862f2fd0863c162f2fd0863c96272fd0863f96262fd0863f962d2fd0863c762d2fd0863cf6252fd0863ff6242fd0863ff6292fd0863c76292fd0863cf6212fd0863ff6202fd0863ff62f2fd0c6304250000000062f2fd0c630c25000000006272fd0c633c25000000006262fd0c633c250000000062f2fd2863c062f2fd2863c86272fd2863f86262fd2863f862f2fd2863c162f2fd2863c96272fd2863f96262fd2863f962d2fd2863c762d2fd2863cf6252fd2863ff6242fd2863ff6292fd2863c76292fd2863cf6212fd2863ff6202fd2863ff62f2fd2c6304250000000062f2fd2c630c25000000006272fd2c633c25000000006262fd2c633c250000000062f2fd4863c062f2fd4863c86272fd4863f86262fd4863f862f2fd4863c162f2fd4863c96272fd4863f96262fd4863f962d2fd4863c762d2fd4863cf6252fd4863ff6242fd4863ff6292fd4863c76292fd4863cf6212fd4863ff6202fd4863ff62f2fd4c6304250000000062f2fd4c630c25000000006272fd4c633c25000000006262fd4c633c2500000000

vpcompressw xmm0, xmm0
vpcompressw xmm0, xmm1
vpcompressw xmm0, xmm15
vpcompressw xmm0, xmm31
vpcompressw xmm1, xmm0
vpcompressw xmm1, xmm1
vpcompressw xmm1, xmm15
vpcompressw xmm1, xmm31
vpcompressw xmm15, xmm0
vpcompressw xmm15, xmm1
vpcompressw xmm15, xmm15
vpcompressw xmm15, xmm31
vpcompressw xmm31, xmm0
vpcompressw xmm31, xmm1
vpcompressw xmm31, xmm15
vpcompressw xmm31, xmm31
vpcompressw [0x0] {k4}, xmm0
vpcompressw [0x0] {k4}, xmm1
vpcompressw [0x0] {k4}, xmm15
vpcompressw [0x0] {k4}, xmm31
vpcompressw ymm0, ymm0
vpcompressw ymm0, ymm1
vpcompressw ymm0, ymm15
vpcompressw ymm0, ymm31
vpcompressw ymm1, ymm0
vpcompressw ymm1, ymm1
vpcompressw ymm1, ymm15
vpcompressw ymm1, ymm31
vpcompressw ymm15, ymm0
vpcompressw ymm15, ymm1
vpcompressw ymm15, ymm15
vpcompressw ymm15, ymm31
vpcompressw ymm31, ymm0
vpcompressw ymm31, ymm1
vpcompressw ymm31, ymm15
vpcompressw ymm31, ymm31
vpcompressw [0x0] {k4}, ymm0
vpcompressw [0x0] {k4}, ymm1
vpcompressw [0x0] {k4}, ymm15
vpcompressw [0x0] {k4}, ymm31
vpcompressw zmm0, zmm0
vpcompressw zmm0, zmm1
vpcompressw zmm0, zmm15
vpcompressw zmm0, zmm31
vpcompressw zmm1, zmm0
vpcompressw zmm1, zmm1
vpcompressw zmm1, zmm15
vpcompressw zmm1, zmm31
vpcompressw zmm15, zmm0
vpcompressw zmm15, zmm1
vpcompressw zmm15, zmm15
vpcompressw zmm15, zmm31
vpcompressw zmm31, zmm0
vpcompressw zmm31, zmm1
vpcompressw zmm31, zmm15
vpcompressw zmm31, zmm31
vpcompressw [0x0] {k4}, zmm0
vpcompressw [0x0] {k4}, zmm1
vpcompressw [0x0] {k4}, zmm15
vpcompressw [0x0] {k4}, zmm31