#pragma bank 255
// SpriteSheet: continue

#include "gbs_types.h"
#include "data/sprite_continue_tileset.h"


BANKREF(sprite_continue)

#define SPRITE_2_STATE_DEFAULT 0

const metasprite_t sprite_continue_metasprite_0[]  = {
    { 8, 48, 0, 0 }, { 0, -8, 2, 0 }, { 0, -8, 4, 0 }, { 0, -8, 6, 0 }, { 0, -8, 8, 0 }, { 0, -8, 10, 0 }, { 0, -8, 12, 0 }, { 0, -8, 14, 0 }, { 0, -8, 16, 0 }, { 0, -8, 18, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_continue_metasprites[] = {
    sprite_continue_metasprite_0
};

const struct animation_t sprite_continue_animations[] = {
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

const UWORD sprite_continue_animations_lookup[] = {
    SPRITE_2_STATE_DEFAULT
};

const struct spritesheet_t sprite_continue = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_continue_metasprites,
    .animations = sprite_continue_animations,
    .animations_lookup = sprite_continue_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_continue_tileset),
    .cgb_tileset = { NULL, NULL }
};
