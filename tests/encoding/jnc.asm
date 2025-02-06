; expect: 73fe73ff0f837affffff737d0f83eeffffff0f83e9ffffff0f8362ffffff0f835b000000

bits 64

jnc $+0
jnc $+1
jnc $+-128
jnc $+127
jnc 0
jnc 1
jnc -128
jnc 127
