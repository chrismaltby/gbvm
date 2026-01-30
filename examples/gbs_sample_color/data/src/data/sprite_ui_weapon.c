#pragma bank 255
// SpriteSheet: ui_weapon

#include "gbs_types.h"
#include "data/sprite_ui_weapon_tileset.h"


BANKREF(sprite_ui_weapon)

#define SPRITE_18_STATE_DEFAULT 0
#define SPRITE_18_STATE_EXPLODE 0
#define SPRITE_18_STATE_OPEN 0

const metasprite_t sprite_ui_weapon_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 2, 0 },
    {metasprite_end}
};

const metasprite_t * const sprite_ui_weapon_metasprites[] = {
    sprite_ui_weapon_metasprite_0
};

const struct animation_t sprite_ui_weapon_animations[] = {
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

const UWORD sprite_ui_weapon_animations_lookup[] = {
    SPRITE_18_STATE_DEFAULT
};

const struct spritesheet_t sprite_ui_weapon = {
    .n_metasprites = 1,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_ui_weapon_metasprites,
    .animations = sprite_ui_weapon_animations,
    .animations_lookup = sprite_ui_weapon_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_ui_weapon_tileset),
    .cgb_tileset = { NULL, NULL }
};
