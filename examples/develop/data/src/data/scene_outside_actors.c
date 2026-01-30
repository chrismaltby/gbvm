#pragma bank 255

// Scene: Outside
// Actors

#include "gbs_types.h"
#include "data/sprite_npc003.h"
#include "data/actor_2_update.h"
#include "data/actor_2_interact.h"
#include "data/sprite_torch.h"
#include "data/actor_3_update.h"

BANKREF(scene_outside_actors)

const struct actor_t scene_outside_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 5376,
            .y = 2560
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_npc003),
        .move_speed = 24,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_1 | COLLISION_GROUP_FLAG_SOLID,
        .script_update = TO_FAR_PTR_T(actor_2_update),
        .script = TO_FAR_PTR_T(actor_2_interact),
        .reserve_tiles = 0
    },
    {
        // Actor 2,
        .pos = {
            .x = 768,
            .y = 2048
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_torch),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE | COLLISION_GROUP_FLAG_SOLID,
        .script_update = TO_FAR_PTR_T(actor_3_update),
        .reserve_tiles = 0
    }
};
