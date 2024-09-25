; expect: 48be280000000000000048be350000000000000048be430000000000000048be530000000000000048656c6c6f20776f726c64210a48656c6c6f20776f726c64210a0048656c6c6f20776f726c64210a00000048656c6c6f20776f726c6421000000000a00000000000000

bits 64

section .data
	msg0 db "Hello world!", 0x0a
	msg1 dw "Hello world!", 0x0a
	msg2 dd "Hello world!", 0x0a
	msg3 dq "Hello world!", 0x0a

section .text
	mov rsi, msg0
	mov rsi, msg1
	mov rsi, msg2
	mov rsi, msg3

