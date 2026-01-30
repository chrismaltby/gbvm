#pragma bank 255
// SpriteSheet: space_mine

#include "gbs_types.h"
#include "data/sprite_space_mine_tileset.h"


BANKREF(sprite_space_mine)

#define SPRITE_20_STATE_DEFAULT 0
#define SPRITE_20_STATE_EXPLODE 8
#define SPRITE_20_STATE_OPEN 0

const metasprite_t sprite_space_mine_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_space_mine_metasprite_1[]  = {
    { 8, 16, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_space_mine_metasprite_2[]  = {
    { 8, 16, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t sprite_space_mine_metasprite_3[]  = {
    { 8, 16, 12, 0 }, { 0, -8, 14, 0 },
    {metasprite_end}
};

const metasprite_t sprite_space_mine_metasprite_4[]  = {
    { 8, 16, 16, 0 }, { 0, -8, 18, 0 },
    {metasprite_end}
};

const metasprite_t sprite_space_mine_metasprite_5[]  = {
    { 8, 16, 20, 0 }, { 0, -8, 22, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_space_mine_metasprites[] = {
    sprite_space_mine_metasprite_0,
    sprite_space_mine_metasprite_1,
    sprite_space_mine_metasprite_2,
    sprite_space_mine_metasprite_3,
    sprite_space_mine_metasprite_4,
    sprite_space_mine_metasprite_5
};

const struct animation_t sprite_space_mine_animations[] = {
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
    },
    {
        .start = 2,
        .end = 5
    },
    {
        .start = 2,
        .end = 5
    },
    {
        .start = 2,
        .end = 5
    },
    {
        .start = 2,
        .end = 5
    },
    {
        .start = 2,
        .end = 5
    },
    {
        .start = 2,
        .end = 5
    },
    {
        .start = 2,
        .end = 5
    },
    {
        .start = 2,
        .end = 5
    }
};

const UWORD sprite_space_mine_animations_lookup[] = {
    SPRITE_20_STATE_DEFAULT,
    SPRITE_20_STATE_EXPLODE
};

const struct spritesheet_t sprite_space_mine = {
    .n_metasprites = 6,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_space_mine_metasprites,
    .animations = sprite_space_mine_animations,
    .animations_lookup = sprite_space_mine_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_space_mine_tileset),
    .cgb_tileset = { NULL, NULL }
};
