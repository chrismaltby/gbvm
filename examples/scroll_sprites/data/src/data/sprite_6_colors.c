#pragma bank 255
// SpriteSheet: 6-colors

#include "gbs_types.h"
#include "data/sprite_6_colors_tileset.h"


BANKREF(sprite_6_colors)

#define SPRITE_0_STATE_DEFAULT 0

const metasprite_t sprite_6_colors_metasprite_0[]  = {
    { -8, 16, 0, 7 }, { 0, -8, 2, 7 }, { 0, 8, 4, 6 }, { 0, -8, 6, 6 }, { 16, 8, 8, 7 }, { 0, -8, 8, 39 }, { 0, 8, 10, 6 }, { 0, -8, 10, 38 },
    {metasprite_end}
};

const metasprite_t sprite_6_colors_metasprite_1[]  = {
    { 8, 16, 12, 7 }, { -16, 0, 14, 7 }, { 16, -8, 16, 7 }, { -16, 0, 18, 7 }, { 16, 8, 20, 6 }, { -16, 0, 22, 6 }, { 16, -8, 24, 6 }, { -16, 0, 26, 6 },
    {metasprite_end}
};

const metasprite_t sprite_6_colors_metasprite_2[]  = {
    { 8, 16, 8, 7 }, { -16, 0, 0, 7 }, { 16, -8, 8, 39 }, { -16, 0, 2, 7 }, { 16, 8, 10, 6 }, { -16, 0, 4, 6 }, { 16, -8, 10, 38 }, { -16, 0, 6, 6 },
    {metasprite_end}
};

const metasprite_t sprite_6_colors_metasprite_3[]  = {
    { 8, 8, 12, 39 }, { 0, 8, 16, 39 }, { 0, -8, 20, 38 }, { 0, 8, 24, 38 }, { -16, 0, 14, 7 }, { 0, -8, 18, 7 }, { 0, 8, 22, 6 }, { 0, -8, 26, 6 },
    {metasprite_end}
};

const metasprite_t * const sprite_6_colors_metasprites[] = {
    sprite_6_colors_metasprite_0,
    sprite_6_colors_metasprite_1,
    sprite_6_colors_metasprite_2,
    sprite_6_colors_metasprite_3
};

const struct animation_t sprite_6_colors_animations[] = {
    {
        .start = 0,
        .end = 3
    },
    {
        .start = 0,
        .end = 3
    },
    {
        .start = 0,
        .end = 3
    },
    {
        .start = 0,
        .end = 3
    },
    {
        .start = 0,
        .end = 3
    },
    {
        .start = 0,
        .end = 3
    },
    {
        .start = 0,
        .end = 3
    },
    {
        .start = 0,
        .end = 3
    }
};

const UWORD sprite_6_colors_animations_lookup[] = {
    SPRITE_0_STATE_DEFAULT
};

const struct spritesheet_t sprite_6_colors = {
    .n_metasprites = 4,
    .emote_origin = {
        .x = 0,
        .y = -32
    },
    .metasprites = sprite_6_colors_metasprites,
    .animations = sprite_6_colors_animations,
    .animations_lookup = sprite_6_colors_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(0) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_6_colors_tileset),
    .cgb_tileset = { NULL, NULL }
};
