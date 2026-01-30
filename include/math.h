#ifndef MATH_H
#define MATH_H

#include <gbdk/platform.h>

#include <stdint.h>
#include <stdbool.h>

#include "asm/types.h"

#define IS_NEG(a) ((uint8_t)(a)&0x80)

#define U_LESS_THAN(A, B) ((A) - (B)&0x8000u)
#define UBYTE_LESS_THAN(A, B) ((A) - (B)&0x80u)

#define U_GT_THAN(A, B) ((B) - (A)&0x8000u)
#define UBYTE_GT_THAN(A, B) ((B) - (A)&0x80u)

#define DISTANCE(A, B) (U_LESS_THAN(A, B) ? (B - A) : (A - B))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(a, min, max) (((a) < (min)) ? (min) : (((a) > (max)) ? (max) : (a)))

#define SET_BIT(N, POS) N |= 1 << POS
#define UNSET_BIT(N, POS) N &= ~(1 << POS)
#define GET_BIT(N, POS) ((N & (1 << POS)) != 0)

#define SET_BIT_MASK(N, MASK) N |= MASK
#define UNSET_BIT_MASK(N, MASK) N &= ~MASK
#define GET_BIT_MASK(N, MASK) (N & MASK)

#define MOD_2(a) ((a)&1)
#define MOD_4(a) ((a)&3)
#define MOD_8(a) ((a)&7)
#define MOD_16(a) ((a)&15)
#define MOD_32(a) ((a)&31)
#define MOD_64(a) ((a)&63)
#define MOD_128(a) ((a)&127)

#define MUL_16(a) ((a) << 4)
#define MUL_8(a) ((a) << 3)
#define MUL_4(a) ((a) << 2)
#define MUL_2(a) ((a) << 1)

#define DIV_16(a) ((a) >> 4)
#define DIV_8(a) ((a) >> 3)
#define DIV_4(a) ((a) >> 2)
#define DIV_2(a) ((a) >> 1)

#define ANGLE_UP        0
#define ANGLE_RIGHT     64
#define ANGLE_DOWN      128
#define ANGLE_LEFT      192

#define ANGLE_0DEG      0
#define ANGLE_45DEG     32
#define ANGLE_90DEG     64
#define ANGLE_135DEG    96
#define ANGLE_180DEG    128
#define ANGLE_225DEG    160
#define ANGLE_270DEG    192
#define ANGLE_315DEG    224

#define FLIPPED_DIR(dir) MOD_4((dir) + 2)
#define IS_DIR_HORIZONTAL(dir) ((dir)&01)
#define IS_DIR_VERTICAL(dir) (!((dir)&01))

#define N_DIRECTIONS    4

#define SUBPX_TO_PX(a)      ((a) >> 5)
#define SUBPX_TO_TILE(a)    ((UBYTE)((a) >> 8))
#define SUBPX_TO_TILE16(a)  ((UBYTE)((a) >> 9))

#define PX_TO_SUBPX(a)      ((a) << 5)
#define TILE_TO_SUBPX(a)    (((UBYTE)(a)) << 8)
#define TILE16_TO_SUBPX(a)  (((UBYTE)(a)) << 9)

#define PX_TO_TILE(a)       ((UBYTE)((a) >> 3))
#define PX_TO_TILE16(a)     ((UBYTE)((a) >> 4))
#define TILE_TO_PX(a)       (((UBYTE)(a)) << 3)
#define TILE16_TO_PX(a)     (((UBYTE)(a)) << 4)

#define SUBPX_SNAP_PX(a)     ((a) & 0xFFE0)
#define SUBPX_SNAP_TILE(a)   ((a) & 0xFF00)
#define SUBPX_SNAP_TILE16(a) ((a) & 0xFE00)
#define PX_SNAP_TILE(a)     ((a) & 0xFFF8)

#define SUBPX_TILE_REMAINDER(a) ((UBYTE)((a) & 0xFF))
#define SUBPX_PX_REMAINDER(a)   ((UBYTE)((a) & 0x1F))
#define PX_TILE_REMAINDER(a)    ((UBYTE)((a) & 0x7))

#define EXCLUSIVE_OFFSET(x) ((x) + 1)

#define WORD_MIN            -32768
#define WORD_MAX            32767
#define UWORD_MIN           0
#define UWORD_MAX           65535
#define BYTE_MIN            -128
#define BYTE_MAX            127
#define UBYTE_MIN           0
#define UBYTE_MAX           255

typedef struct upoint16_t {
    uint16_t x, y;
} upoint16_t;

typedef struct point16_t {
    int16_t x, y;
} point16_t;

typedef struct point8_t {
    int8_t x, y;
} point8_t;

typedef struct rect_t {
    int8_t left, right, top, bottom;
} rect_t;

typedef struct rect16_t {
    int16_t left, right, top, bottom;
} rect16_t;

typedef struct urect16_t {
    uint16_t left, right, top, bottom;
} urect16_t;

typedef enum {
    DIR_DOWN = 0,
    DIR_RIGHT,
    DIR_UP,
    DIR_LEFT,
    DIR_NONE
} direction_e;

int8_t SIN(uint8_t a) BANKED;
int8_t COS(uint8_t a) BANKED;

inline void point_translate_dir(upoint16_t *point, direction_e dir, uint8_t speed) {
    if(dir == DIR_RIGHT)
        point->x += speed;
    else if(dir == DIR_LEFT)
        point->x -= speed;
    else if(dir == DIR_DOWN)
        point->y += speed;
    else if(dir == DIR_UP)
        point->y -= speed;
}

inline void point_translate_dir_word(upoint16_t *point, direction_e dir, uint16_t speed) {
    if(dir == DIR_RIGHT)
        point->x += speed;
    else if(dir == DIR_LEFT)
        point->x -= speed;
    else if(dir == DIR_DOWN)
        point->y += speed;
    else if(dir == DIR_UP)
        point->y -= speed;
}

inline void upoint_translate_angle(upoint16_t *point, uint8_t angle, uint8_t speed) {
    point->x += ((SIN(angle) * (speed)) >> 7);
    point->y -= ((COS(angle) * (speed)) >> 7);
}

inline void point_translate_angle_to_delta(point16_t *point, uint8_t angle, uint8_t speed) {
    point->x = ((SIN(angle) * (speed)) >> 7);
    point->y = -((COS(angle) * (speed)) >> 7);
}

// Saturating addition of a signed 16-bit delta onto an unsigned 16-bit base.
// Clamps to 0 or UINT16_MAX without ever using a 32-bit type.
inline uint16_t saturating_add_u16(uint16_t base, int16_t delta) {
    if (delta >= 0) {
        uint16_t udelta = (uint16_t)delta;
        // if base + udelta would wrap past UINT16_MAX, clamp to UINT16_MAX
        if (base > UINT16_MAX - udelta) {
            return UINT16_MAX;
        }
        return base + udelta;
    } else {
        uint16_t mag = (uint16_t)(-delta);
        // if subtracting would underflow below 0, clamp to 0
        if (mag > base) {
            return 0;
        }
        return base - mag;
    }
}

uint8_t isqrt(uint16_t x) BANKED;
uint8_t atan2(int16_t y, int16_t x) BANKED;

#endif
