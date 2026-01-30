#pragma bank 255
// SpriteSheet: drumkit

#include "gbs_types.h"
#include "data/sprite_drumkit_tileset.h"


BANKREF(sprite_drumkit)

#define SPRITE_25_STATE_DEFAULT 0
#define SPRITE_25_STATE_EXPLODE 0
#define SPRITE_25_STATE_OPEN 0

const metasprite_t sprite_drumkit_metasprite_0[]  = {
    { 8, 24, 0, 0 }, { 0, -8, 2, 0 }, { 0, -8, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_drumkit_metasprites[] = {
    sprite_drumkit_metasprite_0
};

const struct animation_t sprite_drumkit_animations[] = {
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

const UWORD sprite_drumkit_animations_lookup[] = {
    SPRITE_25_STATE_DEFAULT
};

const struct spritesheet_t sprite_drumkit = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_drumkit_metasprites,
    .animations = sprite_drumkit_animations,
    .animations_lookup = sprite_drumkit_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(-8),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(24) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_drumkit_tileset),
    .cgb_tileset = { NULL, NULL }
};
