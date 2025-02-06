; expect: 73fe73ff0f837affffff737d0f83eeffffff0f83e9ffffff0f8362ffffff0f835b000000

bits 64

jae $+0
jae $+1
jae $+-128
jae $+127
jae 0
jae 1
jae -128
jae 127
