#pragma bank 255
// SpriteSheet: button_b

#include "gbs_types.h"
#include "data/sprite_button_b_tileset.h"


BANKREF(sprite_button_b)

#define SPRITE_5_STATE_DEFAULT 0

const metasprite_t sprite_button_b_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_button_b_metasprites[] = {
    sprite_button_b_metasprite_0
};

const struct animation_t sprite_button_b_animations[] = {
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

const UWORD sprite_button_b_animations_lookup[] = {
    SPRITE_5_STATE_DEFAULT
};

const struct spritesheet_t sprite_button_b = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_button_b_metasprites,
    .animations = sprite_button_b_animations,
    .animations_lookup = sprite_button_b_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_button_b_tileset),
    .cgb_tileset = { NULL, NULL }
};
