; expect: 640210ffff9cfef001

bits 64

section .text
	db 100
	db 0b10
	db 0x10
	db 0xffff
	db 0xffffffff
	db -100
	db -0b10
	db -0x10
	db -0xffff

