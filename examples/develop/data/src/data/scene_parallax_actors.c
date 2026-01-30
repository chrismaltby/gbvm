#pragma bank 255

// Scene: Parallax
// Actors

#include "gbs_types.h"
#include "data/sprite_elephant.h"

BANKREF(scene_parallax_actors)

const struct actor_t scene_parallax_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 3584,
            .y = 3328
        },
        .bounds = {
            .left = PX_TO_SUBPX(-22),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(34) - 1,
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
