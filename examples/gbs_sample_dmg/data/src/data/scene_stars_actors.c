#pragma bank 255

// Scene: Stars
// Actors

#include "gbs_types.h"
#include "data/sprite_dog.h"
#include "data/actor_17_interact.h"

BANKREF(scene_stars_actors)

const struct actor_t scene_stars_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 3840,
            .y = 3072
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
        .script = TO_FAR_PTR_T(actor_17_interact),
        .reserve_tiles = 0
    }
};
