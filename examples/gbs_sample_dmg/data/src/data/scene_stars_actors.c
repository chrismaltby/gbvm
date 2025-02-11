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
            .x = 120 * 16,
            .y = 96 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_dog),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .persistent = FALSE,
        .collision_group = COLLISION_GROUP_NONE,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(actor_17_interact),
        .reserve_tiles = 0
    }
};
