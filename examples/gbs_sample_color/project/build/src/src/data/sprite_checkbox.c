#pragma bank 255
// SpriteSheet: checkbox

#include "gbs_types.h"
#include "data/sprite_checkbox_tileset.h"


BANKREF(sprite_checkbox)

#define SPRITE_37_STATE_DEFAULT 0
#define SPRITE_37_STATE_EXPLODE 0
#define SPRITE_37_STATE_OPEN 0

const metasprite_t sprite_checkbox_metasprite_0[]  = {
    { 0, 0, 0, 0 },
    {metasprite_end}
};

const metasprite_t sprite_checkbox_metasprite_1[]  = {
    { 0, 0, 2, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_checkbox_metasprites[] = {
    sprite_checkbox_metasprite_0,
    sprite_checkbox_metasprite_1
};

const struct animation_t sprite_checkbox_animations[] = {
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
    }
};

const UWORD sprite_checkbox_animations_lookup[] = {
    SPRITE_37_STATE_DEFAULT
};

const struct spritesheet_t sprite_checkbox = {
    .n_metasprites = 2,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_checkbox_metasprites,
    .animations = sprite_checkbox_animations,
    .animations_lookup = sprite_checkbox_animations_lookup,
    .bounds = {
        .left = 0,
        .bottom = 7,
        .right = 15,
        .top = -8
    },
    .tileset = TO_FAR_PTR_T(sprite_checkbox_tileset),
    .cgb_tileset = { NULL, NULL }
};
