#pragma bank 255

// Scene: Scene 2
// Actors

#include "gbs_types.h"
#include "data/sprite_slon_metaspritesheet.h"
#include "data/actor_0_interact.h"
#include "data/sprite_6_colors.h"
#include "data/actor_1_update.h"
#include "data/sprite_static.h"
#include "data/sprite_6_colors.h"

BANKREF(scene_2_actors)

const struct actor_t scene_2_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 5632,
            .y = 3328
        },
        .bounds = {
            .left = PX_TO_SUBPX(-16),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(32) - 1,
            .top = PX_TO_SUBPX(-32)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_slon_metaspritesheet),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_0_interact),
        .reserve_tiles = 0
    },
    {
        // Actor 2,
        .pos = {
            .x = 0,
            .y = 0
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(0) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_6_colors),
        .move_speed = 32,
        .anim_tick = 3,
        .flags = ACTOR_FLAG_PINNED,
        .collision_group = COLLISION_GROUP_NONE,
        .script_update = TO_FAR_PTR_T(actor_1_update),
        .reserve_tiles = 0
    },
    {
        // Actor 3,
        .pos = {
            .x = 11520,
            .y = 3328
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_static),
        .move_speed = 32,
        .anim_tick = 1,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    },
    {
        // Actor 4,
        .pos = {
            .x = 13056,
            .y = 3584
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(0) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_6_colors),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    }
};
