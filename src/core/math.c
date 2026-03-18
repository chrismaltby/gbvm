#pragma bank 255

#include "math.h"

#if defined(__SDCC) && defined(NINTENDO)
UBYTE isqrt(uint16_t x) NAKED BANKED {
       x;
__asm
    ldhl sp, #7
    ld a, (hl-)
    ld e, (hl)

    ld bc, #0xFFE0
    ld h, b
    ld l, b
    ld d, b

    cp #0x40
    jr c, 1$
    sub #0x40
    dec h
    ld d, #0xEF
    jr 1$
0$:
    add hl, bc
    dec d
    dec d
1$:
    add d
    jr c, 0$

    sub d
    ld d, h
    ld h, a

    ld a, e
    ld e, l
    ld l, a


2$:
    add hl, de
    dec e
    dec e
    jr c, 2$

    inc e
    rr d
    ld a, e
    rra
    cpl
    ret
__endasm;
}
#else
UBYTE isqrt(uint16_t x) BANKED {
    uint16_t m, y, b;
    m = 0x4000;
    y = 0;
    while (m != 0) {
        b = y | m;
        y >>= 1;
        if (x >= b) {
            x -= b;
            y |= m;
        }
        m >>= 2;
    }
    return (UBYTE)y;
}
#endif
