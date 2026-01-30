#pragma bank 255
// SpriteSheet: portal

#include "gbs_types.h"
#include "data/sprite_portal_tileset.h"


BANKREF(sprite_portal)

#define SPRITE_1_STATE_DEFAULT 0

const metasprite_t sprite_portal_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t sprite_portal_metasprite_1[]  = {
    { 8, 16, 4, 0 }, { 0, -8, 6, 0 },
    {metasprite_end}
};

const metasprite_t sprite_portal_metasprite_2[]  = {
    { 8, 16, 8, 0 }, { 0, -8, 10, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_portal_metasprites[] = {
    sprite_portal_metasprite_0,
    sprite_portal_metasprite_1,
    sprite_portal_metasprite_2
};

const struct animation_t sprite_portal_animations[] = {
    {
        .start = 0,
        .end = 2
    },
    {
        .start = 0,
        .end = 2
    },
    {
        .start = 0,
        .end = 2
    },
    {
        .start = 0,
        .end = 2
    },
    {
        .start = 0,
        .end = 2
    },
    {
        .start = 0,
        .end = 2
    },
    {
        .start = 0,
        .end = 2
    },
    {
        .start = 0,
        .end = 2
    }
};

const UWORD sprite_portal_animations_lookup[] = {
    SPRITE_1_STATE_DEFAULT
};

const struct spritesheet_t sprite_portal = {
    .n_metasprites = 3,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_portal_metasprites,
    .animations = sprite_portal_animations,
    .animations_lookup = sprite_portal_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_portal_tileset),
    .cgb_tileset = { NULL, NULL }
};
