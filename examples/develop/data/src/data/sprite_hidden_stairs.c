#pragma bank 255
// SpriteSheet: hidden_stairs

#include "gbs_types.h"
#include "data/sprite_hidden_stairs_tileset.h"


BANKREF(sprite_hidden_stairs)

#define SPRITE_8_STATE_DEFAULT 0
#define SPRITE_8_STATE_OPEN 0

const metasprite_t sprite_hidden_stairs_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 0, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_hidden_stairs_metasprites[] = {
    sprite_hidden_stairs_metasprite_0
};

const struct animation_t sprite_hidden_stairs_animations[] = {
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    },
    {
        .start = 0,
        .end = 0
    }
};

const UWORD sprite_hidden_stairs_animations_lookup[] = {
    SPRITE_8_STATE_DEFAULT
};

const struct spritesheet_t sprite_hidden_stairs = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_hidden_stairs_metasprites,
    .animations = sprite_hidden_stairs_animations,
    .animations_lookup = sprite_hidden_stairs_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_hidden_stairs_tileset),
    .cgb_tileset = { NULL, NULL }
};
