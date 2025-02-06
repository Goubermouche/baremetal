; expect: 7cfe7cff0f8c7affffff7c7d0f8ceeffffff0f8ce9ffffff0f8c62ffffff0f8c5b000000

bits 64

jl $+0
jl $+1
jl $+-128
jl $+127
jl 0
jl 1
jl -128
jl 127
