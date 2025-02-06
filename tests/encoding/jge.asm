; expect: 7dfe7dff0f8d7affffff7d7d0f8deeffffff0f8de9ffffff0f8d62ffffff0f8d5b000000

bits 64

jge $+0
jge $+1
jge $+-128
jge $+127
jge 0
jge 1
jge -128
jge 127
