#pragma bank 255

// Scene: Large Player Sprite
// Actors

#include "gbs_types.h"
#include "data/sprite_portal.h"
#include "data/actor_portal_1_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_signpost_1_interact.h"

BANKREF(scene_large_player_sprite_actors)

const struct actor_t scene_large_player_sprite_actors[] = {
    {
        // Portal,
        .pos = {
            .x = 2048,
            .y = 512
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_portal),
        .move_speed = 32,
        .anim_tick = 7,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_1,
        .script = TO_FAR_PTR_T(actor_portal_1_interact),
        .reserve_tiles = 0
    },
    {
        // Signpost,
        .pos = {
            .x = 1536,
            .y = 512
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
        .anim_tick = 3,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_signpost_1_interact),
        .reserve_tiles = 0
    }
};
