#pragma bank 255

// Scene: path/Parallax Example
// Actors

#include "gbs_types.h"
#include "data/sprite_signpost.h"
#include "data/actor_sign_post_5_interact.h"
#include "data/sprite_elephant.h"

BANKREF(scene_parallax_example_actors)

const struct actor_t scene_parallax_example_actors[] = {
    {
        // Sign Post,
        .pos = {
            .x = 11264,
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
        .script = TO_FAR_PTR_T(actor_sign_post_5_interact),
        .reserve_tiles = 0
    },
    {
        // Elephant,
        .pos = {
            .x = 4352,
            .y = 3328
        },
        .bounds = {
            .left = PX_TO_SUBPX(-21),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(26) - 1,
            .top = PX_TO_SUBPX(-31)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_elephant),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    }
};
