#pragma bank 255

// Scene: town/Sample Town
// Actors

#include "gbs_types.h"
#include "data/sprite_rock.h"
#include "data/actor_rock_interact.h"
#include "data/sprite_duck.h"
#include "data/sprite_npc003.h"
#include "data/actor_pet_owner_update.h"
#include "data/actor_pet_owner_interact.h"
#include "data/sprite_cat.h"
#include "data/actor_cat_interact.h"
#include "data/sprite_npc001.h"
#include "data/actor_angry_guy_interact.h"
#include "data/sprite_npc001.h"
#include "data/actor_oblivious_guy_interact.h"
#include "data/sprite_signpost.h"
#include "data/actor_sign_post_interact.h"
#include "data/sprite_npc004.h"
#include "data/actor_hider_interact.h"
#include "data/sprite_npc007.h"

BANKREF(scene_sample_town_actors)

const struct actor_t scene_sample_town_actors[] = {
    {
        // Rock,
        .pos = {
            .x = 6400,
            .y = 3584
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_rock),
        .move_speed = 16,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_rock_interact),
        .reserve_tiles = 0
    },
    {
        // Duck,
        .pos = {
            .x = 4608,
            .y = 4608
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_duck),
        .move_speed = 32,
        .anim_tick = 63,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    },
    {
        // Pet Owner,
        .pos = {
            .x = 6144,
            .y = 11264
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_npc003),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script_update = TO_FAR_PTR_T(actor_pet_owner_update),
        .script = TO_FAR_PTR_T(actor_pet_owner_interact),
        .reserve_tiles = 0
    },
    {
        // Cat,
        .pos = {
            .x = 1024,
            .y = 1536
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
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_cat_interact),
        .reserve_tiles = 0
    },
    {
        // Angry Guy,
        .pos = {
            .x = 4608,
            .y = 6144
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_UP,
        .sprite = TO_FAR_PTR_T(sprite_npc001),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_angry_guy_interact),
        .reserve_tiles = 0
    },
    {
        // Oblivious Guy,
        .pos = {
            .x = 4608,
            .y = 4096
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_npc001),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_oblivious_guy_interact),
        .reserve_tiles = 0
    },
    {
        // Sign Post,
        .pos = {
            .x = 7168,
            .y = 5888
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
        .script = TO_FAR_PTR_T(actor_sign_post_interact),
        .reserve_tiles = 0
    },
    {
        // Hider,
        .pos = {
            .x = 9216,
            .y = 6144
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_npc004),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .script = TO_FAR_PTR_T(actor_hider_interact),
        .reserve_tiles = 0
    },
    {
        // Florist,
        .pos = {
            .x = 12032,
            .y = 12032
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_npc007),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    }
};
