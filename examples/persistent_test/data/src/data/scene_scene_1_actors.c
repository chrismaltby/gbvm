#pragma bank 255

// Scene: Scene 1
// Actors

#include "gbs_types.h"
#include "data/sprite_box.h"
#include "data/actor_0_update.h"
#include "data/sprite_ice.h"
#include "data/actor_1_update.h"
#include "data/sprite_actor.h"
#include "data/actor_2_update.h"

BANKREF(scene_scene_1_actors)

const struct actor_t scene_scene_1_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 64 * 16,
            .y = 88 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_box),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_NONE,
        .collision_enabled = TRUE,
        .script_update = TO_FAR_PTR_T(actor_0_update),
        .reserve_tiles = 0,
        .persistent = TRUE
    },
    {
        // Actor 2,
        .pos = {
            .x = 104 * 16,
            .y = 88 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_ice),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_NONE,
        .collision_enabled = TRUE,
        .script_update = TO_FAR_PTR_T(actor_1_update),
        .reserve_tiles = 0,
        .persistent = TRUE
    },
    {
        // Actor 3,
        .pos = {
            .x = 8 * 16,
            .y = 16 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_actor),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_NONE,
        .collision_enabled = TRUE,
        .script_update = TO_FAR_PTR_T(actor_2_update),
        .reserve_tiles = 0,
        .persistent = TRUE
    }
};
