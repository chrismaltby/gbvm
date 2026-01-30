#pragma bank 255
// SpriteSheet: player_platform

#include "gbs_types.h"
#include "data/sprite_player_platform_tileset.h"


BANKREF(sprite_player_platform)

#define SPRITE_5_STATE_DEFAULT 0
#define SPRITE_5_STATE_EXPLODE 0
#define SPRITE_5_STATE_OPEN 0

const metasprite_t sprite_player_platform_metasprite_0[]  = {
    { -4, 8, 0, 32 }, { 0, 8, 2, 32 }, { 12, -8, 10, 32 }, { 0, 8, 12, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_1[]  = {
    { -4, 16, 0, 0 }, { 0, -8, 2, 0 }, { 12, 8, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_2[]  = {
    { -3, 16, 0, 0 }, { 0, -8, 2, 0 }, { 11, 8, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_3[]  = {
    { -4, 16, 8, 0 }, { 0, -8, 2, 0 }, { 12, 8, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_4[]  = {
    { -4, 16, 0, 0 }, { 0, -8, 2, 0 }, { 12, 8, 10, 0 }, { 0, -8, 12, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_5[]  = {
    { -4, 8, 0, 32 }, { 0, 8, 2, 32 }, { 12, -8, 4, 32 }, { 0, 8, 6, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_6[]  = {
    { -3, 8, 0, 32 }, { 0, 8, 2, 32 }, { 11, -8, 4, 32 }, { 0, 8, 6, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_7[]  = {
    { -4, 8, 8, 32 }, { 0, 8, 2, 32 }, { 12, -8, 4, 32 }, { 0, 8, 6, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_8[]  = {
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_9[]  = {
    { -4, 16, 0, 0 }, { 0, -8, 2, 0 }, { 12, 8, 14, 0 }, { 0, -8, 16, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_10[]  = {
    { -4, 16, 0, 0 }, { 0, -8, 2, 0 }, { 12, 8, 18, 0 }, { 0, -8, 20, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_11[]  = {
    { -4, 16, 0, 0 }, { 0, -8, 2, 0 }, { 12, 8, 22, 0 }, { 0, -8, 24, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_12[]  = {
    { -4, 16, 26, 0 }, { 0, -8, 28, 0 }, { 12, 8, 30, 0 }, { 0, -8, 32, 0 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_13[]  = {
    { -4, 16, 26, 0 }, { 0, -8, 28, 0 }, { 12, 0, 30, 32 }, { 0, 8, 32, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_14[]  = {
    { -4, 8, 0, 32 }, { 0, 8, 2, 32 }, { 12, -8, 14, 32 }, { 0, 8, 16, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_15[]  = {
    { -4, 8, 0, 32 }, { 0, 8, 2, 32 }, { 12, -8, 18, 32 }, { 0, 8, 20, 32 },
    {metasprite_end}
};

const metasprite_t sprite_player_platform_metasprite_16[]  = {
    { -4, 8, 0, 32 }, { 0, 8, 2, 32 }, { 12, -8, 22, 32 }, { 0, 8, 24, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_player_platform_metasprites[] = {
    sprite_player_platform_metasprite_0,
    sprite_player_platform_metasprite_1,
    sprite_player_platform_metasprite_1,
    sprite_player_platform_metasprite_2,
    sprite_player_platform_metasprite_2,
    sprite_player_platform_metasprite_1,
    sprite_player_platform_metasprite_3,
    sprite_player_platform_metasprite_4,
    sprite_player_platform_metasprite_5,
    sprite_player_platform_metasprite_5,
    sprite_player_platform_metasprite_6,
    sprite_player_platform_metasprite_6,
    sprite_player_platform_metasprite_5,
    sprite_player_platform_metasprite_7,
    sprite_player_platform_metasprite_8,
    sprite_player_platform_metasprite_9,
    sprite_player_platform_metasprite_10,
    sprite_player_platform_metasprite_11,
    sprite_player_platform_metasprite_12,
    sprite_player_platform_metasprite_13,
    sprite_player_platform_metasprite_14,
    sprite_player_platform_metasprite_15,
    sprite_player_platform_metasprite_16
};

const struct animation_t sprite_player_platform_animations[] = {
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 1,
        .end = 6
    },
    {
        .start = 7,
        .end = 7
    },
    {
        .start = 8,
        .end = 13
    },
    {
        .start = 14,
        .end = 14
    },
    {
        .start = 15,
        .end = 17
    },
    {
        .start = 18,
        .end = 19
    },
    {
        .start = 20,
        .end = 22
    }
};

const UWORD sprite_player_platform_animations_lookup[] = {
    SPRITE_5_STATE_DEFAULT
};

const struct spritesheet_t sprite_player_platform = {
    .n_metasprites = 23,
    .emote_origin = {
        .x = 0,
        .y = -32
    },
    .metasprites = sprite_player_platform_metasprites,
    .animations = sprite_player_platform_animations,
    .animations_lookup = sprite_player_platform_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-16)
    },
    .tileset = TO_FAR_PTR_T(sprite_player_platform_tileset),
    .cgb_tileset = { NULL, NULL }
};
