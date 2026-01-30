#pragma bank 255
// SpriteSheet: savepoint

#include "gbs_types.h"
#include "data/sprite_savepoint_tileset.h"


BANKREF(sprite_savepoint)

#define SPRITE_4_STATE_DEFAULT 0
#define SPRITE_4_STATE_EXPLODE 0
#define SPRITE_4_STATE_OPEN 0

const metasprite_t sprite_savepoint_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 0, 32 },
    {metasprite_end}
};

const metasprite_t sprite_savepoint_metasprite_1[]  = {
    { 8, 16, 2, 0 }, { 0, -8, 2, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_savepoint_metasprites[] = {
    sprite_savepoint_metasprite_0,
    sprite_savepoint_metasprite_1
};

const struct animation_t sprite_savepoint_animations[] = {
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

const UWORD sprite_savepoint_animations_lookup[] = {
    SPRITE_4_STATE_DEFAULT
};

const struct spritesheet_t sprite_savepoint = {
    .n_metasprites = 2,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_savepoint_metasprites,
    .animations = sprite_savepoint_animations,
    .animations_lookup = sprite_savepoint_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_savepoint_tileset),
    .cgb_tileset = { NULL, NULL }
};
