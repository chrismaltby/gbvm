#pragma bank 255

// Scene: town/Top House
// Actors

#include "gbs_types.h"
#include "data/sprite_npc002.h"
#include "data/actor_radio_guy_interact.h"
#include "data/sprite_radio.h"
#include "data/actor_radio_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_sign_post_3_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_sign_post_2_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_sign_post_1_interact.h"

BANKREF(scene_top_house_actors)

const struct actor_t scene_top_house_actors[] = {
    {
        // Radio Guy,
        .pos = {
            .x = 3072,
            .y = 1280
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_npc002),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_radio_guy_interact),
        .reserve_tiles = 0
    },
    {
        // Radio,
        .pos = {
            .x = 3840,
            .y = 1280
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_radio),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_radio_interact),
        .reserve_tiles = 0
    },
    {
        // Sign Post 3,
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
        .sprite = TO_FAR_PTR_T(sprite_signpost),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_sign_post_3_interact),
        .reserve_tiles = 0
    },
    {
        // Sign Post 2,
        .pos = {
            .x = 768,
            .y = 2816
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
        .script = TO_FAR_PTR_T(actor_sign_post_2_interact),
        .reserve_tiles = 0
    },
    {
        // Sign Post 1,
        .pos = {
            .x = 768,
            .y = 1280
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
        .script = TO_FAR_PTR_T(actor_sign_post_1_interact),
        .reserve_tiles = 0
    }
};
