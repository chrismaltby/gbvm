#pragma bank 255

// Scene: Scene
// Actors

#include "gbs_types.h"
#include "data/sprite_actor_animated.h"
#include "data/actor_0_interact.h"

BANKREF(scene_2_actors)

const struct actor_t scene_2_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 1792,
            .y = 1536
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_actor_animated),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE | COLLISION_GROUP_FLAG_SOLID,
        .script = TO_FAR_PTR_T(actor_0_interact),
        .reserve_tiles = 0
    }
};
