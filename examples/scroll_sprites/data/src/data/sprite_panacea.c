#pragma bank 255
// SpriteSheet: panacea

#include "gbs_types.h"
#include "data/sprite_panacea_tileset.h"


BANKREF(sprite_panacea)

#define SPRITE_1_STATE_DEFAULT 0

const metasprite_t sprite_panacea_metasprite_0[]  = {
    { 8, 8, 4, 32 }, { 0, 8, 6, 32 },
    {metasprite_end}
};

const metasprite_t sprite_panacea_metasprite_1[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_panacea_metasprite_2[]  = {
    { 8, 16, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_panacea_metasprite_3[]  = {
    { 8, 8, 0, 32 }, { 0, 8, 2, 32 },
    {metasprite_end}
};

const metasprite_t sprite_panacea_metasprite_4[]  = {
    {metasprite_end}
};

const metasprite_t sprite_panacea_metasprite_5[]  = {
    { 8, 16, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t sprite_panacea_metasprite_6[]  = {
    { 8, 16, 12, 0 }, { 0, -8, 12, 32 },
    {metasprite_end}
};

const metasprite_t sprite_panacea_metasprite_7[]  = {
    { 8, 16, 14, 0 }, { 0, -8, 16, 0 },
    {metasprite_end}
};

const metasprite_t sprite_panacea_metasprite_8[]  = {
    { 8, 8, 8, 32 }, { 0, 8, 10, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_panacea_metasprites[] = {
    sprite_panacea_metasprite_0,
    sprite_panacea_metasprite_1,
    sprite_panacea_metasprite_2,
    sprite_panacea_metasprite_3,
    sprite_panacea_metasprite_4,
    sprite_panacea_metasprite_2,
    sprite_panacea_metasprite_5,
    sprite_panacea_metasprite_6,
    sprite_panacea_metasprite_7,
    sprite_panacea_metasprite_0,
    sprite_panacea_metasprite_8
};

const struct animation_t sprite_panacea_animations[] = {
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 3,
        .end = 3
    },
    {
        .start = 4,
        .end = 4
    },
    {
        .start = 5,
        .end = 6
    },
    {
        .start = 7,
        .end = 8
    },
    {
        .start = 9,
        .end = 10
    }
};

const UWORD sprite_panacea_animations_lookup[] = {
    SPRITE_1_STATE_DEFAULT
};

const struct spritesheet_t sprite_panacea = {
    .n_metasprites = 11,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_panacea_metasprites,
    .animations = sprite_panacea_animations,
    .animations_lookup = sprite_panacea_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_panacea_tileset),
    .cgb_tileset = { NULL, NULL }
};
