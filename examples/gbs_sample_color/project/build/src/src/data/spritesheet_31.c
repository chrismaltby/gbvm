#pragma bank 255
// SpriteSheet: pod_door
  
#include "gbs_types.h"
#include "data/tileset_35.h"

const void __at(255) __bank_spritesheet_31;

const metasprite_t spritesheet_31_metasprite_0[]  = {
    { 0, 8, 4, 0 }, { 0, -8, 4, 32 },
    {metasprite_end}
};

const metasprite_t spritesheet_31_metasprite_1[]  = {
    { 0, 8, 0, 0 }, { 0, -8, 0, 32 },
    {metasprite_end}
};

const metasprite_t spritesheet_31_metasprite_2[]  = {
    { 0, 8, 2, 0 }, { 0, -8, 2, 32 },
    {metasprite_end}
};

const metasprite_t spritesheet_31_metasprite_3[]  = {
    { 0, 0, 0, 32 }, { 0, 8, 0, 0 },
    {metasprite_end}
};

const metasprite_t * const spritesheet_31_metasprites[] = {
    spritesheet_31_metasprite_0,
    spritesheet_31_metasprite_1,
    spritesheet_31_metasprite_2,
    spritesheet_31_metasprite_3
};

const struct spritesheet_t spritesheet_31 = {
    .n_metasprites = 4,
    .metasprites = spritesheet_31_metasprites,
    .animations = {
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
        }
    },
    .bounds = {
        .left = 0,
        .bottom = 7,
        .right = 15,
        .top = -8
    },
    .tileset = TO_FAR_PTR_T(tileset_35),
    .cgb_tileset = { NULL, NULL }
};
