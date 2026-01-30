#pragma bank 255

// Scene: Platform
// Actors

#include "gbs_types.h"
#include "data/sprite_turnip.h"
#include "data/actor_turnip_1_update.h"
#include "data/actor_turnip_1_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_sign_post_0_interact.h"
#include "data/sprite_savepoint.h"
#include "data/actor_save_point_0_interact.h"

BANKREF(scene_platform_actors)

const struct actor_t scene_platform_actors[] = {
    {
        // Turnip 1,
        .pos = {
            .x = 18432,
            .y = 3328
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_turnip),
        .move_speed = 16,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_1,
        .script_update = TO_FAR_PTR_T(actor_turnip_1_update),
        .script = TO_FAR_PTR_T(actor_turnip_1_interact),
        .reserve_tiles = 4
    },
    {
        // Sign Post,
        .pos = {
            .x = 34304,
            .y = 3328
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
        .script = TO_FAR_PTR_T(actor_sign_post_0_interact),
        .reserve_tiles = 0
    },
    {
        // Save Point,
        .pos = {
            .x = 29952,
            .y = 3328
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
        .script = TO_FAR_PTR_T(actor_save_point_0_interact),
        .reserve_tiles = 0
    }
};
