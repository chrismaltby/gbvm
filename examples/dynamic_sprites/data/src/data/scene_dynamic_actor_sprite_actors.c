#pragma bank 255

// Scene: Dynamic Actor Sprite
// Actors

#include "gbs_types.h"
#include "data/sprite_portal.h"
#include "data/actor_portal_2_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_signpost_2_interact.h"
#include "data/sprite_player.h"
#include "data/actor_setactortoplayer_interact.h"
#include "data/sprite_cat.h"
#include "data/actor_setactortocat_interact.h"
#include "data/sprite_dog.h"
#include "data/actor_setactortodog_interact.h"
#include "data/sprite_box.h"
#include "data/actor_setactortonpc006_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_dynamicactor_interact.h"

BANKREF(scene_dynamic_actor_sprite_actors)

const struct actor_t scene_dynamic_actor_sprite_actors[] = {
    {
        // Portal,
        .pos = {
            .x = 2304,
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
        .script = TO_FAR_PTR_T(actor_portal_2_interact),
        .reserve_tiles = 0
    },
    {
        // Signpost,
        .pos = {
            .x = 1792,
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
        .script = TO_FAR_PTR_T(actor_signpost_2_interact),
        .reserve_tiles = 0
    },
    {
        // SetActorToPlayer,
        .pos = {
            .x = 1024,
            .y = 2304
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_player),
        .move_speed = 32,
        .anim_tick = 3,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_setactortoplayer_interact),
        .reserve_tiles = 0
    },
    {
        // SetActorToCat,
        .pos = {
            .x = 3584,
            .y = 2304
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_cat),
        .move_speed = 32,
        .anim_tick = 3,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_setactortocat_interact),
        .reserve_tiles = 0
    },
    {
        // SetActorToDog,
        .pos = {
            .x = 3584,
            .y = 3584
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
        .anim_tick = 3,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_setactortodog_interact),
        .reserve_tiles = 0
    },
    {
        // SetActorToNPC006,
        .pos = {
            .x = 1024,
            .y = 3584
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_box),
        .move_speed = 32,
        .anim_tick = 3,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_setactortonpc006_interact),
        .reserve_tiles = 0
    },
    {
        // DynamicActor,
        .pos = {
            .x = 2304,
            .y = 1792
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
        .script = TO_FAR_PTR_T(actor_dynamicactor_interact),
        .reserve_tiles = 24
    }
};
