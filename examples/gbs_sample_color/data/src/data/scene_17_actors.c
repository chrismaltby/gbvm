#pragma bank 255

// Scene: town/Music House
// Actors

#include "gbs_types.h"
#include "data/sprite_keyboard.h"
#include "data/actor_18_interact.h"
#include "data/sprite_drumkit.h"
#include "data/actor_19_interact.h"
#include "data/sprite_npc008.h"
#include "data/actor_20_update.h"
#include "data/actor_20_interact.h"
#include "data/sprite_machine.h"
#include "data/actor_21_interact.h"
#include "data/sprite_machine.h"
#include "data/actor_22_interact.h"
#include "data/sprite_machine.h"
#include "data/actor_23_interact.h"
#include "data/sprite_machine.h"
#include "data/actor_24_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_25_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_26_interact.h"

BANKREF(scene_17_actors)

const struct actor_t scene_17_actors[] = {
    {
        // Keyboard,
        .pos = {
            .x = 1280,
            .y = 2560
        },
        .bounds = {
            .left = PX_TO_SUBPX(-8),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(24) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_keyboard),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_18_interact),
        .reserve_tiles = 0
    },
    {
        // Drumkit,
        .pos = {
            .x = 3328,
            .y = 1792
        },
        .bounds = {
            .left = PX_TO_SUBPX(-8),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(24) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_drumkit),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_19_interact),
        .reserve_tiles = 0
    },
    {
        // DJ,
        .pos = {
            .x = 3840,
            .y = 2816
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_npc008),
        .move_speed = 32,
        .anim_tick = 255,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script_update = TO_FAR_PTR_T(actor_20_update),
        .script = TO_FAR_PTR_T(actor_20_interact),
        .reserve_tiles = 0
    },
    {
        // Machine,
        .pos = {
            .x = 768,
            .y = 768
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_machine),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_21_interact),
        .reserve_tiles = 0
    },
    {
        // Machine,
        .pos = {
            .x = 1792,
            .y = 768
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_machine),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_22_interact),
        .reserve_tiles = 0
    },
    {
        // Machine,
        .pos = {
            .x = 2816,
            .y = 768
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_machine),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_23_interact),
        .reserve_tiles = 0
    },
    {
        // Machine,
        .pos = {
            .x = 3840,
            .y = 768
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_machine),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_24_interact),
        .reserve_tiles = 0
    },
    {
        // Sign Post 2,
        .pos = {
            .x = 512,
            .y = 2560
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
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_25_interact),
        .reserve_tiles = 0
    },
    {
        // Sign Post 2,
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
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_26_interact),
        .reserve_tiles = 0
    }
};
