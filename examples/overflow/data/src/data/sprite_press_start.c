#pragma bank 255
// SpriteSheet: press_start

#include "gbs_types.h"
#include "data/sprite_press_start_tileset.h"


BANKREF(sprite_press_start)

#define SPRITE_1_STATE_DEFAULT 0

const metasprite_t sprite_press_start_metasprite_0[]  = {
    { 8, 32, 0, 0 }, { -16, 0, 2, 0 }, { 16, -8, 4, 0 }, { -16, 0, 6, 0 }, { 16, -8, 8, 0 }, { -16, 0, 10, 0 }, { 16, -8, 12, 0 }, { -16, 0, 14, 0 }, { 16, -8, 16, 0 }, { -16, 0, 18, 0 }, { 16, -8, 20, 0 }, { -16, 0, 22, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_press_start_metasprites[] = {
    sprite_press_start_metasprite_0
};

const struct animation_t sprite_press_start_animations[] = {
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

const UWORD sprite_press_start_animations_lookup[] = {
    SPRITE_1_STATE_DEFAULT
};

const struct spritesheet_t sprite_press_start = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -32
    },
    .metasprites = sprite_press_start_metasprites,
    .animations = sprite_press_start_animations,
    .animations_lookup = sprite_press_start_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_press_start_tileset),
    .cgb_tileset = { NULL, NULL }
};
