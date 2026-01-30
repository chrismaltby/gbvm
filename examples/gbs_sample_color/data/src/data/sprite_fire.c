#pragma bank 255
// SpriteSheet: fire

#include "gbs_types.h"
#include "data/sprite_fire_tileset.h"


BANKREF(sprite_fire)

#define SPRITE_2_STATE_DEFAULT 0
#define SPRITE_2_STATE_EXPLODE 0
#define SPRITE_2_STATE_OPEN 0

const metasprite_t sprite_fire_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_fire_metasprite_1[]  = {
    { 8, 16, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_fire_metasprite_2[]  = {
    { 8, 16, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t sprite_fire_metasprite_3[]  = {
    { 8, 16, 12, 0 }, { 0, -8, 14, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_fire_metasprites[] = {
    sprite_fire_metasprite_0,
    sprite_fire_metasprite_1,
    sprite_fire_metasprite_2,
    sprite_fire_metasprite_3
};

const struct animation_t sprite_fire_animations[] = {
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

const UWORD sprite_fire_animations_lookup[] = {
    SPRITE_2_STATE_DEFAULT
};

const struct spritesheet_t sprite_fire = {
    .n_metasprites = 4,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_fire_metasprites,
    .animations = sprite_fire_animations,
    .animations_lookup = sprite_fire_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_fire_tileset),
    .cgb_tileset = { NULL, NULL }
};
