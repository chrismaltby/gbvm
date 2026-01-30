#pragma bank 255

// Scene: space/Deep Space
// Actors

#include "gbs_types.h"
#include "data/sprite_dog.h"
#include "data/actor_space_dog_interact.h"
#include "data/sprite_portal.h"
#include "data/sprite_savepoint.h"
#include "data/actor_save_point_1_interact.h"

BANKREF(scene_deep_space_actors)

const struct actor_t scene_deep_space_actors[] = {
    {
        // Space Dog,
        .pos = {
            .x = 3584,
            .y = 3584
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_dog),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_space_dog_interact),
        .reserve_tiles = 0
    },
    {
        // Portal,
        .pos = {
            .x = 3584,
            .y = 2560
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_portal),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    },
    {
        // Save Point,
        .pos = {
            .x = 4864,
            .y = 3584
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_savepoint),
        .move_speed = 32,
        .anim_tick = 31,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_save_point_1_interact),
        .reserve_tiles = 0
    }
};
