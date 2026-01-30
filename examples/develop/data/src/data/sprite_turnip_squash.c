#pragma bank 255
// SpriteSheet: turnip_squash

#include "gbs_types.h"
#include "data/sprite_turnip_squash_tileset.h"


BANKREF(sprite_turnip_squash)

#define SPRITE_16_STATE_DEFAULT 0
#define SPRITE_16_STATE_OPEN 0

const metasprite_t sprite_turnip_squash_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_turnip_squash_metasprites[] = {
    sprite_turnip_squash_metasprite_0
};

const struct animation_t sprite_turnip_squash_animations[] = {
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

const UWORD sprite_turnip_squash_animations_lookup[] = {
    SPRITE_16_STATE_DEFAULT
};

const struct spritesheet_t sprite_turnip_squash = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_turnip_squash_metasprites,
    .animations = sprite_turnip_squash_animations,
    .animations_lookup = sprite_turnip_squash_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_turnip_squash_tileset),
    .cgb_tileset = { NULL, NULL }
};
