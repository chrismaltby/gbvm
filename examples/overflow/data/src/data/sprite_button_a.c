#pragma bank 255
// SpriteSheet: button_a

#include "gbs_types.h"
#include "data/sprite_button_a_tileset.h"


BANKREF(sprite_button_a)

#define SPRITE_4_STATE_DEFAULT 0

const metasprite_t sprite_button_a_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_button_a_metasprites[] = {
    sprite_button_a_metasprite_0
};

const struct animation_t sprite_button_a_animations[] = {
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

const UWORD sprite_button_a_animations_lookup[] = {
    SPRITE_4_STATE_DEFAULT
};

const struct spritesheet_t sprite_button_a = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_button_a_metasprites,
    .animations = sprite_button_a_animations,
    .animations_lookup = sprite_button_a_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_button_a_tileset),
    .cgb_tileset = { NULL, NULL }
};
