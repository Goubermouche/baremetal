; expect: 7ffe7fff0f8f7affffff7f7d0f8feeffffff0f8fe9ffffff0f8f62ffffff0f8f5b000000

bits 64

jnle $+0
jnle $+1
jnle $+-128
jnle $+127
jnle 0
jnle 1
jnle -128
jnle 127
