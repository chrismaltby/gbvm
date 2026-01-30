#pragma bank 255
// SpriteSheet: npc008

#include "gbs_types.h"
#include "data/sprite_npc008_tileset.h"


BANKREF(sprite_npc008)

#define SPRITE_26_STATE_DEFAULT 0
#define SPRITE_26_STATE_EXPLODE 0
#define SPRITE_26_STATE_OPEN 0

const metasprite_t sprite_npc008_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_npc008_metasprite_1[]  = {
    { 8, 16, 2, 32 }, { 0, -8, 0, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_npc008_metasprites[] = {
    sprite_npc008_metasprite_0,
    sprite_npc008_metasprite_1
};

const struct animation_t sprite_npc008_animations[] = {
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

const UWORD sprite_npc008_animations_lookup[] = {
    SPRITE_26_STATE_DEFAULT
};

const struct spritesheet_t sprite_npc008 = {
    .n_metasprites = 2,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_npc008_metasprites,
    .animations = sprite_npc008_animations,
    .animations_lookup = sprite_npc008_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_npc008_tileset),
    .cgb_tileset = { NULL, NULL }
};
