#pragma bank 255

// Scene: Underground
// Actors

#include "gbs_types.h"
#include "data/sprite_signpost.h"
#include "data/actor_18_interact.h"
#include "data/sprite_ice.h"
#include "data/actor_ice_block_interact.h"
#include "data/sprite_rock.h"
#include "data/actor_rock_3_interact.h"
#include "data/sprite_rock.h"
#include "data/actor_rock_2_interact.h"
#include "data/sprite_rock.h"
#include "data/actor_rock_1_interact.h"

BANKREF(scene_underground_actors)

const struct actor_t scene_underground_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 1792,
            .y = 6400
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
        .script = TO_FAR_PTR_T(actor_18_interact),
        .reserve_tiles = 0
    },
    {
        // Ice Block,
        .pos = {
            .x = 6144,
            .y = 4608
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_ice),
        .move_speed = 64,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_ice_block_interact),
        .reserve_tiles = 0
    },
    {
        // Rock 3,
        .pos = {
            .x = 5888,
            .y = 6912
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_rock),
        .move_speed = 16,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_rock_3_interact),
        .reserve_tiles = 0
    },
    {
        // Rock 2,
        .pos = {
            .x = 5376,
            .y = 6912
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_rock),
        .move_speed = 16,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_rock_2_interact),
        .reserve_tiles = 0
    },
    {
        // Rock 1,
        .pos = {
            .x = 4864,
            .y = 6912
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_rock),
        .move_speed = 16,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_rock_1_interact),
        .reserve_tiles = 0
    }
};
