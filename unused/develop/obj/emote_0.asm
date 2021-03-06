;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.4 #12246 (Mac OS X x86_64)
;--------------------------------------------------------
	.module emote_0
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _emote_0
	.globl ___bank_emote_0
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE_255
	.area _CODE_255
___bank_emote_0	=	0x00ff
_emote_0:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x1f	; 31
	.db #0x1f	; 31
	.db #0x3f	; 63
	.db #0x20	; 32
	.db #0x3f	; 63
	.db #0x21	; 33
	.db #0x3f	; 63
	.db #0x21	; 33
	.db #0x3f	; 63
	.db #0x21	; 33
	.db #0x3f	; 63
	.db #0x21	; 33
	.db #0x3f	; 63
	.db #0x20	; 32
	.db #0x3f	; 63
	.db #0x21	; 33
	.db #0x3f	; 63
	.db #0x21	; 33
	.db #0x23	; 35
	.db #0x3c	; 60
	.db #0x1d	; 29
	.db #0x1e	; 30
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x01	; 1
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0xf8	; 248
	.db #0xf8	; 248
	.db #0xfc	; 252
	.db #0x04	; 4
	.db #0xfc	; 252
	.db #0x84	; 132
	.db #0xfc	; 252
	.db #0x84	; 132
	.db #0xfc	; 252
	.db #0x84	; 132
	.db #0xfc	; 252
	.db #0x84	; 132
	.db #0xfc	; 252
	.db #0x04	; 4
	.db #0xfc	; 252
	.db #0x84	; 132
	.db #0xfc	; 252
	.db #0x84	; 132
	.db #0xc4	; 196
	.db #0x3c	; 60
	.db #0xb8	; 184
	.db #0x78	; 120	'x'
	.db #0x40	; 64
	.db #0xc0	; 192
	.db #0x80	; 128
	.db #0x80	; 128
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.area _INITIALIZER
	.area _CABS (ABS)
