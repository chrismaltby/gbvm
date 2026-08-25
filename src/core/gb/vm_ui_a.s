    .module     vm_ui_a
    .include    "global.s"

    .area   _DATA

__itoa_fmt_len::
    .ds 0x01

    .area   _CODE_255

.globl b_itoa_fmt
b_itoa_fmt = 255

_itoa_fmt::
	ld a, (__itoa_fmt_len)
    bit 7, d
    jr z, .utoa_fmt
	
	ld l, a
	
	; negate DE
    xor a
    sub e
    ld e, a
    sbc a
    sub d
    ld d, a
	
	; prepend a minus sign
	ld a, #'-'
    ld (bc), a
    inc bc
	
	ld a, l
	or a
	jr z, .utoa_fmt
	dec a
.utoa_fmt::             ; convert unsigned int into ascii
	; input :
	;  -  a : minimum length of the string
	;  - de : number to convert to ascii
	;  - bc : destination string
	; output :
	;  - bc : points to the null terminator of the new string
	
    sub #6
    inc a
    jr c, 1$
    
	; prepend length - 5 leading zero if length >= 6
    ld h, b
    ld l, c
    
    ld c, a
    ld a, #'0'
0$:
    ld (hl+), a
    dec c
    jr nz, 0$
    
    ld b, h
    ld c, l
	xor a
1$:
    ld hl, #-10000
    add hl, de
    jr c, 2$		; 5 digit number ?
    jr z, 4$		; length >= 5 ?
    
    ld hl, #-1000
    add hl, de
    jr c, 5$		; 4 digit number ?
    inc a
    jr z, 7$		; length = 4 ?

    ld hl, #-100
    add hl, de
    jr c, 8$		; 3 digit number ?
    inc a
    jr z, 10$		; length = 3 ?
    inc a
    ld a, e
    ld h, b
    ld l, c
    jr z, 11$		; length = 2 ?
    cp #10
    jr nc, 11$		; 2 digit number ?
	; 1 digit number
    jr 14$
2$:
    ld de, #-10000
    xor a
3$:
    inc a
    add hl, de
    jr c, 3$
4$:
    ld de, #10000
    add hl, de
    
    add #'0'
    ld (bc), a
    inc bc
5$:
    ld de, #-1000
    ccf
    sbc a
6$:
    inc a
    add hl, de
    jr c, 6$
7$:
    ld de, #1000
    add hl, de
    
    add #'0'
    ld (bc), a
    inc bc
8$:
    ld de, #-100
    ccf
    sbc a
9$:
    inc a
    add hl, de
    jr c, 9$
10$:
    add #'0'

    ld h, b
    ld b, l
    ld l, c
    
    ld (hl+), a

    inc d
    ld a, b
    sub e			; sub #-100
11$:
    ld bc, #0x350A	; ld b, #'0' + 5; ld c, #10
	sub #50
	jr c, 12$
	sub #50
	ld b, #'0' + 10
12$:
    dec b
	add c			; add #10
    jr nc, 12$
13$:
    ld (hl), b
    inc hl
14$:
    add #'0'
    ld (hl+), a
    ld (hl), d		; ld (hl), #0
	
	ld b, h
	ld c, l
	
    ret
