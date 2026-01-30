#pragma bank 255

// Scene: Dynamic Player Sprite
// Actors

#include "gbs_types.h"
#include "data/sprite_portal.h"
#include "data/actor_portal_0_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_signpost_0_interact.h"
#include "data/sprite_player.h"
#include "data/actor_setplayertoplayer_interact.h"
#include "data/sprite_cat.h"
#include "data/actor_setplayertocat_interact.h"
#include "data/sprite_dog.h"
#include "data/actor_setplayertodog_interact.h"
#include "data/sprite_box.h"
#include "data/actor_setplayertonpc006_interact.h"

BANKREF(scene_dynamic_player_sprite_actors)

const struct actor_t scene_dynamic_player_sprite_actors[] = {
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
        .script = TO_FAR_PTR_T(actor_portal_0_interact),
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
        .script = TO_FAR_PTR_T(actor_signpost_0_interact),
        .reserve_tiles = 0
    },
    {
        // SetPlayerToPlayer,
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
        .script = TO_FAR_PTR_T(actor_setplayertoplayer_interact),
        .reserve_tiles = 0
    },
    {
        // SetPlayerToCat,
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
        .script = TO_FAR_PTR_T(actor_setplayertocat_interact),
        .reserve_tiles = 0
    },
    {
        // SetPlayerToDog,
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
        .script = TO_FAR_PTR_T(actor_setplayertodog_interact),
        .reserve_tiles = 0
    },
    {
        // SetPlayerToNPC006,
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
        .script = TO_FAR_PTR_T(actor_setplayertonpc006_interact),
        .reserve_tiles = 0
    }
};
