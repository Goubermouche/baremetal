; expect: 7efe7eff0f8e7affffff7e7d0f8eeeffffff0f8ee9ffffff0f8e62ffffff0f8e5b000000

bits 64

jng $+0
jng $+1
jng $+-128
jng $+127
jng 0
jng 1
jng -128
jng 127
