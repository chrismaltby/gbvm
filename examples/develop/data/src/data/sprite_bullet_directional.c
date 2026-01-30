#pragma bank 255
// SpriteSheet: bullet_directional

#include "gbs_types.h"
#include "data/sprite_bullet_directional_tileset.h"


BANKREF(sprite_bullet_directional)

#define SPRITE_17_STATE_DEFAULT 0
#define SPRITE_17_STATE_OPEN 0

const metasprite_t sprite_bullet_directional_metasprite_0[]  = {
    { 8, 16, 8, 64 }, { 0, -8, 10, 64 },
    {metasprite_end}
};

const metasprite_t sprite_bullet_directional_metasprite_1[]  = {
    { 8, 16, 12, 64 }, { 0, -8, 14, 64 },
    {metasprite_end}
};

const metasprite_t sprite_bullet_directional_metasprite_2[]  = {
    { 8, 8, 0, 0 }, { 0, 8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_bullet_directional_metasprite_3[]  = {
    { 8, 8, 4, 0 }, { 0, 8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_bullet_directional_metasprite_4[]  = {
    { 8, 16, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t sprite_bullet_directional_metasprite_5[]  = {
    { 8, 16, 12, 0 }, { 0, -8, 14, 0 },
    {metasprite_end}
};

const metasprite_t sprite_bullet_directional_metasprite_6[]  = {
    { 8, 16, 0, 32 }, { 0, -8, 2, 32 },
    {metasprite_end}
};

const metasprite_t sprite_bullet_directional_metasprite_7[]  = {
    { 8, 16, 4, 32 }, { 0, -8, 6, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_bullet_directional_metasprites[] = {
    sprite_bullet_directional_metasprite_0,
    sprite_bullet_directional_metasprite_1,
    sprite_bullet_directional_metasprite_2,
    sprite_bullet_directional_metasprite_3,
    sprite_bullet_directional_metasprite_4,
    sprite_bullet_directional_metasprite_5,
    sprite_bullet_directional_metasprite_6,
    sprite_bullet_directional_metasprite_7
};

const struct animation_t sprite_bullet_directional_animations[] = {
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 2,
        .end = 3
    },
    {
        .start = 4,
        .end = 5
    },
    {
        .start = 6,
        .end = 7
    },
    {
        .start = 0,
        .end = 1
    },
    {
        .start = 2,
        .end = 3
    },
    {
        .start = 4,
        .end = 5
    },
    {
        .start = 6,
        .end = 7
    }
};

const UWORD sprite_bullet_directional_animations_lookup[] = {
    SPRITE_17_STATE_DEFAULT
};

const struct spritesheet_t sprite_bullet_directional = {
    .n_metasprites = 8,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_bullet_directional_metasprites,
    .animations = sprite_bullet_directional_animations,
    .animations_lookup = sprite_bullet_directional_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_bullet_directional_tileset),
    .cgb_tileset = { NULL, NULL }
};
