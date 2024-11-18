; expect: 640210ffff9cfef001

bits 64

section .text
	data0 db 100
	data1 db 0b10
	data2 db 0x10
	data3 db 0xffff
	data4 db 0xffffffff
	data5 db -100
	data6 db -0b10
	data7 db -0x10
	data8 db -0xffff

