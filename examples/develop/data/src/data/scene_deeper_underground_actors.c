#pragma bank 255

// Scene: Deeper Underground
// Actors

#include "gbs_types.h"
#include "data/sprite_chest.h"
#include "data/actor_chest_interact.h"

BANKREF(scene_deeper_underground_actors)

const struct actor_t scene_deeper_underground_actors[] = {
    {
        // Chest,
        .pos = {
            .x = 6912,
            .y = 3840
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_chest),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_chest_interact),
        .reserve_tiles = 0
    }
};
