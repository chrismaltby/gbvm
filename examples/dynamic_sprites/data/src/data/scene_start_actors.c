#pragma bank 255

// Scene: Start
// Actors

#include "gbs_types.h"
#include "data/sprite_portal.h"
#include "data/actor_portalleft_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_signpostleft_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_signposttop_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_signpostright_interact.h"
#include "data/sprite_portal.h"
#include "data/actor_portalright_interact.h"
#include "data/sprite_portal.h"
#include "data/actor_portaltop_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_signpostbottom_interact.h"
#include "data/sprite_portal.h"
#include "data/actor_portalbottom_interact.h"

BANKREF(scene_start_actors)

const struct actor_t scene_start_actors[] = {
    {
        // PortalLeft,
        .pos = {
            .x = 1024,
            .y = 1792
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
        .script = TO_FAR_PTR_T(actor_portalleft_interact),
        .reserve_tiles = 0
    },
    {
        // SignpostLeft,
        .pos = {
            .x = 512,
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
        .script = TO_FAR_PTR_T(actor_signpostleft_interact),
        .reserve_tiles = 0
    },
    {
        // SignpostTop,
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
        .script = TO_FAR_PTR_T(actor_signposttop_interact),
        .reserve_tiles = 0
    },
    {
        // SignpostRight,
        .pos = {
            .x = 4096,
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
        .script = TO_FAR_PTR_T(actor_signpostright_interact),
        .reserve_tiles = 0
    },
    {
        // PortalRight,
        .pos = {
            .x = 3584,
            .y = 1792
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
        .script = TO_FAR_PTR_T(actor_portalright_interact),
        .reserve_tiles = 0
    },
    {
        // PortalTop,
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
        .script = TO_FAR_PTR_T(actor_portaltop_interact),
        .reserve_tiles = 0
    },
    {
        // SignpostBottom,
        .pos = {
            .x = 1792,
            .y = 3840
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
        .script = TO_FAR_PTR_T(actor_signpostbottom_interact),
        .reserve_tiles = 0
    },
    {
        // PortalBottom,
        .pos = {
            .x = 2304,
            .y = 3840
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
        .script = TO_FAR_PTR_T(actor_portalbottom_interact),
        .reserve_tiles = 0
    }
};
