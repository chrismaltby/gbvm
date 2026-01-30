#pragma bank 255

// Scene: Scene 1
// Actors

#include "gbs_types.h"
#include "data/sprite_radio.h"
#include "data/actor_0_interact.h"

BANKREF(scene_scene_1_actors)

const struct actor_t scene_scene_1_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 2304,
            .y = 2048
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_radio),
        .move_speed = 32,
        .anim_tick = 3,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_0_interact),
        .reserve_tiles = 0
    }
};
