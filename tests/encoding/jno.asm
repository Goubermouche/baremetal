; expect: 71fe71ff0f817affffff717d0f81eeffffff0f81e9ffffff0f8162ffffff0f815b000000

bits 64

jno $+0
jno $+1
jno $+-128
jno $+127
jno 0
jno 1
jno -128
jno 127
