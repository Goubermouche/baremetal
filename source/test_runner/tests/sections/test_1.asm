bits 64

; comment 
section .text
	mov rsi, msg0 ; another comment
	mov rsi, msg1
	mov rsi, msg2
	mov rsi, msg3

section .data
	msg0 db "Hello world!", 0x0a
	msg1 dw "Hello world!", 0x0a
	msg2 dd "Hello world!", 0x0a
	msg3 dq "Hello world!", 0x0a


