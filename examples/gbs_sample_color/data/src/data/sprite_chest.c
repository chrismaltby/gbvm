#pragma bank 255
// SpriteSheet: chest

#include "gbs_types.h"
#include "data/sprite_chest_tileset.h"


BANKREF(sprite_chest)

#define SPRITE_6_STATE_DEFAULT 0
#define SPRITE_6_STATE_EXPLODE 0
#define SPRITE_6_STATE_OPEN 8

const metasprite_t sprite_chest_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 0, 32 },
    {metasprite_end}
};

const metasprite_t sprite_chest_metasprite_1[]  = {
    { 8, 16, 2, 0 }, { 0, -8, 2, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_chest_metasprites[] = {
    sprite_chest_metasprite_0,
    sprite_chest_metasprite_1
};

const struct animation_t sprite_chest_animations[] = {
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 1,
        .end = 1
    }
};

const UWORD sprite_chest_animations_lookup[] = {
    SPRITE_6_STATE_DEFAULT,
    SPRITE_6_STATE_EXPLODE,
    SPRITE_6_STATE_OPEN
};

const struct spritesheet_t sprite_chest = {
    .n_metasprites = 2,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_chest_metasprites,
    .animations = sprite_chest_animations,
    .animations_lookup = sprite_chest_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_chest_tileset),
    .cgb_tileset = { NULL, NULL }
};
