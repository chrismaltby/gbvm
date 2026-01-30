#pragma bank 255
// SpriteSheet: turnip

#include "gbs_types.h"
#include "data/sprite_turnip_tileset.h"


BANKREF(sprite_turnip)

#define SPRITE_12_STATE_DEFAULT 0
#define SPRITE_12_STATE_EXPLODE 8
#define SPRITE_12_STATE_OPEN 0

const metasprite_t sprite_turnip_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_turnip_metasprite_1[]  = {
    { 8, 16, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_turnip_metasprite_2[]  = {
    { 8, 16, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_turnip_metasprites[] = {
    sprite_turnip_metasprite_0,
    sprite_turnip_metasprite_1,
    sprite_turnip_metasprite_2
};

const struct animation_t sprite_turnip_animations[] = {
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 2,
        .end = 2
    }
};

const UWORD sprite_turnip_animations_lookup[] = {
    SPRITE_12_STATE_DEFAULT,
    SPRITE_12_STATE_EXPLODE
};

const struct spritesheet_t sprite_turnip = {
    .n_metasprites = 3,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_turnip_metasprites,
    .animations = sprite_turnip_animations,
    .animations_lookup = sprite_turnip_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_turnip_tileset),
    .cgb_tileset = { NULL, NULL }
};
