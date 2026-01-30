#pragma bank 255

// Scene: Outside
// Actors

#include "gbs_types.h"
#include "data/spritesheet_1.h"
#include "data/script_s0a0_interact.h"
#include "data/spritesheet_2.h"
#include "data/script_s0a1_update.h"
#include "data/spritesheet_3.h"

BANKREF(scene_0_actors)

const struct actor_t scene_0_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 152 * 16,
            .y = 120 * 16
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(7),
            .right = PX_TO_SUBPX(15),
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_1),
        .move_speed = 16,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(script_s0a0_interact),
        .reserve_tiles = 0
    },
    {
        // Actor 2,
        .pos = {
            .x = 176 * 16,
            .y = 144 * 16
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(7),
            .right = PX_TO_SUBPX(15),
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_2),
        .move_speed = 16,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script_update = TO_FAR_PTR_T(script_s0a1_update),
        .reserve_tiles = 0
    },
    {
        // Actor 3,
        .pos = {
            .x = 176 * 16,
            .y = 72 * 16
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(7),
            .right = PX_TO_SUBPX(15),
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_3),
        .move_speed = 16,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    }
};
