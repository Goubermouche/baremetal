; expect: 73fe73ff0f837affffff737d0f83eeffffff0f83e9ffffff0f8362ffffff0f835b000000

bits 64

jnb $+0
jnb $+1
jnb $+-128
jnb $+127
jnb 0
jnb 1
jnb -128
jnb 127
