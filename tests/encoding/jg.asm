; expect: 7ffe7fff0f8f7affffff7f7d0f8feeffffff0f8fe9ffffff0f8f62ffffff0f8f5b000000

bits 64

jg $+0
jg $+1
jg $+-128
jg $+127
jg 0
jg 1
jg -128
jg 127
