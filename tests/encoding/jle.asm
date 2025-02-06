; expect: 7efe7eff0f8e7affffff7e7d0f8eeeffffff0f8ee9ffffff0f8e62ffffff0f8e5b000000

bits 64

jle $+0
jle $+1
jle $+-128
jle $+127
jle 0
jle 1
jle -128
jle 127
