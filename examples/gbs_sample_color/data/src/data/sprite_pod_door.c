#pragma bank 255
// SpriteSheet: pod_door

#include "gbs_types.h"
#include "data/sprite_pod_door_tileset.h"


BANKREF(sprite_pod_door)

#define SPRITE_21_STATE_DEFAULT 0
#define SPRITE_21_STATE_EXPLODE 0
#define SPRITE_21_STATE_OPEN 0

const metasprite_t sprite_pod_door_metasprite_0[]  = {
    { 8, 16, 0, 0 }, { 0, -8, 0, 32 },
    {metasprite_end}
};

const metasprite_t sprite_pod_door_metasprite_1[]  = {
    { 8, 16, 2, 0 }, { 0, -8, 2, 32 },
    {metasprite_end}
};

const metasprite_t sprite_pod_door_metasprite_2[]  = {
    { 8, 16, 4, 0 }, { 0, -8, 4, 32 },
    {metasprite_end}
};

const metasprite_t * const sprite_pod_door_metasprites[] = {
    sprite_pod_door_metasprite_0,
    sprite_pod_door_metasprite_1,
    sprite_pod_door_metasprite_2
};

const struct animation_t sprite_pod_door_animations[] = {
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

const UWORD sprite_pod_door_animations_lookup[] = {
    SPRITE_21_STATE_DEFAULT
};

const struct spritesheet_t sprite_pod_door = {
    .n_metasprites = 3,
    .emote_origin = {
        .x = 0,
        .y = -16
    },
    .metasprites = sprite_pod_door_metasprites,
    .animations = sprite_pod_door_animations,
    .animations_lookup = sprite_pod_door_animations_lookup,
    .bounds = {
        .left = PX_TO_SUBPX(0),
        .bottom = PX_TO_SUBPX(8) - 1,
        .right = PX_TO_SUBPX(16) - 1,
        .top = PX_TO_SUBPX(-8)
    },
    .tileset = TO_FAR_PTR_T(sprite_pod_door_tileset),
    .cgb_tileset = { NULL, NULL }
};
