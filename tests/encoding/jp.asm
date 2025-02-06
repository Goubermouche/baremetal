; expect: 7afe7aff0f8a7affffff7a7d0f8aeeffffff0f8ae9ffffff0f8a62ffffff0f8a5b000000

bits 64

jp $+0
jp $+1
jp $+-128
jp $+127
jp 0
jp 1
jp -128
jp 127
