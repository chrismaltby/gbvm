#pragma bank 255

// Scene: Cave
// Actors

#include "gbs_types.h"
#include "data/sprite_cat.h"
#include "data/actor_cat_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_savepoint_interact.h"

BANKREF(scene_cave_actors)

const struct actor_t scene_cave_actors[] = {
    {
        // Cat,
        .pos = {
            .x = 3328,
            .y = 1792
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_cat),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_cat_interact),
        .reserve_tiles = 4
    },
    {
        // Signpost,
        .pos = {
            .x = 2304,
            .y = 1792
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_signpost),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_savepoint_interact),
        .reserve_tiles = 0
    }
};
