; test comment edge cases
; expect: 010f05

bits 64

msg db 1 ; comment after memory definition
syscall  ; comment in instruction with no operands

; trailing comment
