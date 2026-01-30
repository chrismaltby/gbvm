#pragma bank 255

// Scene: West
// Actors

#include "gbs_types.h"
#include "data/sprite_npc001.h"

BANKREF(scene_west_actors)

const struct actor_t scene_west_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 1280,
            .y = 2304
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_npc001),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    }
};
