#pragma bank 255
// SpriteSheet: npc003

#include "gbs_types.h"
#include "data/sprite_npc003_tileset.h"


BANKREF(sprite_npc003)

#define SPRITE_28_STATE_DEFAULT 0
#define SPRITE_28_STATE_EXPLODE 0
#define SPRITE_28_STATE_OPEN 0

const metasprite_t sprite_npc003_metasprite_0[]  = {
    { 8, 16, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t sprite_npc003_metasprite_1[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_npc003_metasprite_2[]  = {
    { 8, 16, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_npc003_metasprite_3[]  = {
    { 8, 8, 0, 32 }, { 0, 8, 2, 32 },
    {metasprite_end}
};

const metasprite_t sprite_npc003_metasprite_4[]  = {
    { 8, 16, 20, 0 }, { 0, -8, 22, 0 },
    {metasprite_end}
};

const metasprite_t sprite_npc003_metasprite_5[]  = {
    { 8, 16, 12, 0 }, { 0, -8, 14, 0 },
    {metasprite_end}
};

const metasprite_t sprite_npc003_metasprite_6[]  = {
    { 8, 16, 16, 0 }, { 0, -8, 18, 0 },
    {metasprite_end}
};

const metasprite_t sprite_npc003_metasprite_7[]  = {
    { 8, 8, 12, 32 }, { 0, 8, 14, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_npc003_metasprites[] = {
    sprite_npc003_metasprite_0,
    sprite_npc003_metasprite_1,
    sprite_npc003_metasprite_2,
    sprite_npc003_metasprite_3,
    sprite_npc003_metasprite_4,
    sprite_npc003_metasprite_0,
    sprite_npc003_metasprite_5,
    sprite_npc003_metasprite_1,
    sprite_npc003_metasprite_6,
    sprite_npc003_metasprite_2,
    sprite_npc003_metasprite_7,
    sprite_npc003_metasprite_3
};

const struct animation_t sprite_npc003_animations[] = {
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
    }
};

const UWORD sprite_npc003_animations_lookup[] = {
    SPRITE_28_STATE_DEFAULT
};

const struct spritesheet_t sprite_npc003 = {
    .n_metasprites = 12,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_npc003_metasprites,
    .animations = sprite_npc003_animations,
    .animations_lookup = sprite_npc003_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_npc003_tileset),
    .cgb_tileset = { NULL, NULL }
};
