#pragma bank 255

// Scene: Scene 1
// Actors

#include "gbs_types.h"
#include "data/sprite_box.h"
#include "data/actor_0_update.h"
#include "data/sprite_ice.h"
#include "data/actor_1_update.h"
#include "data/sprite_actor.h"
#include "data/actor_2_update.h"

BANKREF(scene_scene_1_actors)

const struct actor_t scene_scene_1_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 2048,
            .y = 2816
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_box),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION | ACTOR_FLAG_PERSISTENT,
        .collision_group = COLLISION_GROUP_NONE,
        .script_update = TO_FAR_PTR_T(actor_0_update),
        .reserve_tiles = 0
    },
    {
        // Actor 2,
        .pos = {
            .x = 3328,
            .y = 2816
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_ice),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION | ACTOR_FLAG_PERSISTENT,
        .collision_group = COLLISION_GROUP_NONE,
        .script_update = TO_FAR_PTR_T(actor_1_update),
        .reserve_tiles = 0
    },
    {
        // Actor 3,
        .pos = {
            .x = 256,
            .y = 512
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_actor),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION | ACTOR_FLAG_PERSISTENT,
        .collision_group = COLLISION_GROUP_NONE,
        .script_update = TO_FAR_PTR_T(actor_2_update),
        .reserve_tiles = 0
    }
};
