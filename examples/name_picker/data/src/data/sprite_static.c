#pragma bank 255
// SpriteSheet: static

#include "gbs_types.h"
#include "data/sprite_static_tileset.h"


BANKREF(sprite_static)

#define SPRITE_0_STATE_DEFAULT 0

const metasprite_t sprite_static_metasprite_0[]  = {
    { 8, 8, 0, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_static_metasprites[] = {
    sprite_static_metasprite_0
};

const struct animation_t sprite_static_animations[] = {
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
    }
};

const UWORD sprite_static_animations_lookup[] = {
    SPRITE_0_STATE_DEFAULT
};

const struct spritesheet_t sprite_static = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_static_metasprites,
    .animations = sprite_static_animations,
    .animations_lookup = sprite_static_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_static_tileset),
    .cgb_tileset = { NULL, NULL }
};
