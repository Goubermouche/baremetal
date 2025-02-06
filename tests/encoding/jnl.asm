; expect: 7dfe7dff0f8d7affffff7d7d0f8deeffffff0f8de9ffffff0f8d62ffffff0f8d5b000000

bits 64

jnl $+0
jnl $+1
jnl $+-128
jnl $+127
jnl 0
jnl 1
jnl -128
jnl 127
