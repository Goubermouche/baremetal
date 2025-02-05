; test parser edge cases (literals)
; expect: 48656c6c6f3b20776f726c643b

bits 64

data0 db "Hello; world" ; comment
data1 db ';'            ; comment
