#pragma bank 255
// SpriteSheet: player

#include "gbs_types.h"
#include "data/sprite_player_tileset.h"


BANKREF(sprite_player)

#define SPRITE_0_STATE_DEFAULT 0
#define SPRITE_0_STATE_IN_GRASS 8
#define SPRITE_0_STATE_SURPRISED 16

const metasprite_t sprite_player_metasprite_0[]  = {
    { 8, 16, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_1[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_2[]  = {
    { 8, 16, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_3[]  = {
    { 8, 8, 0, 32 }, { 0, 8, 2, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_4[]  = {
    { 8, 16, 20, 0 }, { 0, -8, 22, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_5[]  = {
    { 8, 16, 12, 0 }, { 0, -8, 14, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_6[]  = {
    { 8, 16, 16, 0 }, { 0, -8, 18, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_7[]  = {
    { 8, 8, 12, 32 }, { 0, 8, 14, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_8[]  = {
    { 8, 16, 28, 0 }, { 0, -8, 30, 0 }, { 0, 8, 8, 128 }, { 0, -8, 10, 128 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_9[]  = {
    { 8, 16, 24, 0 }, { 0, -8, 26, 0 }, { 0, 8, 0, 128 }, { 0, -8, 2, 128 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_10[]  = {
    { 8, 8, 24, 32 }, { 0, 8, 26, 32 }, { 0, -8, 0, 160 }, { 0, 8, 2, 160 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_11[]  = {
    { 8, 16, 28, 0 }, { 0, -8, 30, 0 }, { 0, 8, 20, 128 }, { 0, -8, 22, 128 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_12[]  = {
    { 8, 16, 24, 0 }, { 0, -8, 26, 0 }, { 0, 8, 12, 128 }, { 0, -8, 14, 128 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_13[]  = {
    { 8, 16, 32, 0 }, { 0, -8, 34, 0 }, { 0, 8, 4, 128 }, { 0, -8, 6, 128 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_14[]  = {
    { 8, 16, 32, 0 }, { 0, -8, 34, 0 }, { 0, 8, 16, 128 }, { 0, -8, 18, 128 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_15[]  = {
    { 8, 8, 24, 32 }, { 0, 8, 26, 32 }, { 0, -8, 12, 160 }, { 0, 8, 14, 160 },
    {metasprite_end}
};

const metasprite_t sprite_player_metasprite_16[]  = {
    { 8, 16, 36, 0 }, { 0, -8, 36, 32 }, { 0, 8, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_player_metasprites[] = {
    sprite_player_metasprite_0,
    sprite_player_metasprite_1,
    sprite_player_metasprite_2,
    sprite_player_metasprite_3,
    sprite_player_metasprite_0,
    sprite_player_metasprite_4,
    sprite_player_metasprite_1,
    sprite_player_metasprite_5,
    sprite_player_metasprite_2,
    sprite_player_metasprite_6,
    sprite_player_metasprite_3,
    sprite_player_metasprite_7,
    sprite_player_metasprite_8,
    sprite_player_metasprite_9,
    sprite_player_metasprite_10,
    sprite_player_metasprite_8,
    sprite_player_metasprite_11,
    sprite_player_metasprite_9,
    sprite_player_metasprite_12,
    sprite_player_metasprite_13,
    sprite_player_metasprite_14,
    sprite_player_metasprite_10,
    sprite_player_metasprite_15,
    sprite_player_metasprite_16
};

const struct animation_t sprite_player_animations[] = {
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 1,
        .end = 1
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 3,
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
        .start = 8,
        .end = 9
    },
    {
        .start = 10,
        .end = 11
    },
    {
        .start = 12,
        .end = 12
    },
    {
        .start = 13,
        .end = 13
    },
    {
        .start = 2,
        .end = 2
    },
    {
        .start = 14,
        .end = 14
    },
    {
        .start = 15,
        .end = 16
    },
    {
        .start = 17,
        .end = 18
    },
    {
        .start = 19,
        .end = 20
    },
    {
        .start = 21,
        .end = 22
    },
    {
        .start = 23,
        .end = 23
    },
    {
        .start = 23,
        .end = 23
    },
    {
        .start = 23,
        .end = 23
    },
    {
        .start = 23,
        .end = 23
    },
    {
        .start = 23,
        .end = 23
    },
    {
        .start = 23,
        .end = 23
    },
    {
        .start = 23,
        .end = 23
    },
    {
        .start = 23,
        .end = 23
    }
};

const UWORD sprite_player_animations_lookup[] = {
    SPRITE_0_STATE_DEFAULT,
    SPRITE_0_STATE_IN_GRASS,
    SPRITE_0_STATE_SURPRISED
};

const struct spritesheet_t sprite_player = {
    .n_metasprites = 24,
    .emote_origin = {
        .x = 0,
        .y = -32
    },
    .metasprites = sprite_player_metasprites,
    .animations = sprite_player_animations,
    .animations_lookup = sprite_player_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(0)
    },
    .tileset = TO_FAR_PTR_T(sprite_player_tileset),
    .cgb_tileset = { NULL, NULL }
};
