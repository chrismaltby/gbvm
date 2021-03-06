#pragma bank 255

// Scene: Space Battle
// Actors

#include "gbs_types.h"
#include "data/spritesheet_24.h"
#include "data/spritesheet_25.h"
#include "data/script_s7a1_interact.h"
#include "data/script_s7a1_update.h"
#include "data/script_s7a1_hit1.h"
#include "data/script_s7a1_hit3.h"
#include "data/spritesheet_25.h"
#include "data/script_s7a2_interact.h"
#include "data/script_s7a2_update.h"
#include "data/script_s7a2_hit1.h"
#include "data/script_s7a2_hit3.h"
#include "data/spritesheet_25.h"
#include "data/script_s7a3_interact.h"
#include "data/script_s7a3_update.h"
#include "data/script_s7a3_hit1.h"
#include "data/script_s7a3_hit3.h"
#include "data/spritesheet_25.h"
#include "data/script_s7a4_interact.h"
#include "data/script_s7a4_update.h"
#include "data/script_s7a4_hit1.h"
#include "data/script_s7a4_hit3.h"
#include "data/spritesheet_25.h"
#include "data/script_s7a5_interact.h"
#include "data/script_s7a5_update.h"
#include "data/script_s7a5_hit1.h"
#include "data/script_s7a5_hit3.h"
#include "data/spritesheet_25.h"
#include "data/script_s7a6_interact.h"
#include "data/script_s7a6_update.h"
#include "data/script_s7a6_hit1.h"
#include "data/script_s7a6_hit3.h"
#include "data/spritesheet_25.h"
#include "data/script_s7a7_interact.h"
#include "data/script_s7a7_update.h"
#include "data/script_s7a7_hit1.h"
#include "data/script_s7a7_hit3.h"
#include "data/spritesheet_26.h"
#include "data/script_s7a8_interact.h"
#include "data/script_s7a8_update.h"
#include "data/script_s7a8_hit1.h"
#include "data/spritesheet_26.h"
#include "data/script_s7a9_interact.h"
#include "data/script_s7a9_update.h"
#include "data/script_s7a9_hit1.h"
#include "data/spritesheet_26.h"
#include "data/script_s7a10_interact.h"
#include "data/script_s7a10_update.h"
#include "data/script_s7a10_hit1.h"
#include "data/spritesheet_26.h"
#include "data/script_s7a11_interact.h"
#include "data/script_s7a11_update.h"
#include "data/script_s7a11_hit1.h"
#include "data/spritesheet_26.h"
#include "data/script_s7a12_interact.h"
#include "data/script_s7a12_update.h"
#include "data/script_s7a12_hit1.h"
#include "data/spritesheet_26.h"
#include "data/script_s7a13_interact.h"
#include "data/script_s7a13_update.h"
#include "data/script_s7a13_hit1.h"
#include "data/spritesheet_26.h"
#include "data/script_s7a14_interact.h"
#include "data/script_s7a14_update.h"
#include "data/script_s7a14_hit1.h"
#include "data/spritesheet_26.h"
#include "data/script_s7a15_interact.h"
#include "data/script_s7a15_update.h"
#include "data/script_s7a15_hit1.h"

const void __at(255) __bank_scene_7_actors;

const struct actor_t scene_7_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 0 * 16,
            .y = 8 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_24),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = TRUE,
        .collision_group = COLLISION_GROUP_NONE,
        .collision_enabled = FALSE
    },
    {
        // Actor 2,
        .pos = {
            .x = 288 * 16,
            .y = 72 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_25),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a1_interact),
        .script_update = TO_FAR_PTR_T(script_s7a1_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a1_hit1),
        .script_hit3 = TO_FAR_PTR_T(script_s7a1_hit3)
    },
    {
        // Actor 3,
        .pos = {
            .x = 536 * 16,
            .y = 112 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_25),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a2_interact),
        .script_update = TO_FAR_PTR_T(script_s7a2_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a2_hit1),
        .script_hit3 = TO_FAR_PTR_T(script_s7a2_hit3)
    },
    {
        // Actor 4,
        .pos = {
            .x = 608 * 16,
            .y = 32 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_25),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a3_interact),
        .script_update = TO_FAR_PTR_T(script_s7a3_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a3_hit1),
        .script_hit3 = TO_FAR_PTR_T(script_s7a3_hit3)
    },
    {
        // Actor 5,
        .pos = {
            .x = 688 * 16,
            .y = 112 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_25),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a4_interact),
        .script_update = TO_FAR_PTR_T(script_s7a4_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a4_hit1),
        .script_hit3 = TO_FAR_PTR_T(script_s7a4_hit3)
    },
    {
        // Actor 6,
        .pos = {
            .x = 1824 * 16,
            .y = 24 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_25),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a5_interact),
        .script_update = TO_FAR_PTR_T(script_s7a5_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a5_hit1),
        .script_hit3 = TO_FAR_PTR_T(script_s7a5_hit3)
    },
    {
        // Actor 7,
        .pos = {
            .x = 1744 * 16,
            .y = 72 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_25),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a6_interact),
        .script_update = TO_FAR_PTR_T(script_s7a6_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a6_hit1),
        .script_hit3 = TO_FAR_PTR_T(script_s7a6_hit3)
    },
    {
        // Actor 8,
        .pos = {
            .x = 1832 * 16,
            .y = 120 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_25),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a7_interact),
        .script_update = TO_FAR_PTR_T(script_s7a7_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a7_hit1),
        .script_hit3 = TO_FAR_PTR_T(script_s7a7_hit3)
    },
    {
        // Actor 9,
        .pos = {
            .x = 888 * 16,
            .y = 72 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_26),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a8_interact),
        .script_update = TO_FAR_PTR_T(script_s7a8_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a8_hit1)
    },
    {
        // Actor 10,
        .pos = {
            .x = 1040 * 16,
            .y = 24 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_26),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a9_interact),
        .script_update = TO_FAR_PTR_T(script_s7a9_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a9_hit1)
    },
    {
        // Actor 11,
        .pos = {
            .x = 1320 * 16,
            .y = 120 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_26),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a10_interact),
        .script_update = TO_FAR_PTR_T(script_s7a10_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a10_hit1)
    },
    {
        // Actor 12,
        .pos = {
            .x = 1120 * 16,
            .y = 24 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_26),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a11_interact),
        .script_update = TO_FAR_PTR_T(script_s7a11_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a11_hit1)
    },
    {
        // Actor 13,
        .pos = {
            .x = 1200 * 16,
            .y = 24 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_26),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a12_interact),
        .script_update = TO_FAR_PTR_T(script_s7a12_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a12_hit1)
    },
    {
        // Actor 14,
        .pos = {
            .x = 1400 * 16,
            .y = 120 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_26),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a13_interact),
        .script_update = TO_FAR_PTR_T(script_s7a13_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a13_hit1)
    },
    {
        // Actor 15,
        .pos = {
            .x = 1480 * 16,
            .y = 120 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_26),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a14_interact),
        .script_update = TO_FAR_PTR_T(script_s7a14_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a14_hit1)
    },
    {
        // Actor 16,
        .pos = {
            .x = 1648 * 16,
            .y = 72 * 16
        },
        .bounds = {
            .left = 0,
            .bottom = 7,
            .right = 15,
            .top = -8
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(spritesheet_26),
        .move_speed = 16,
        .anim_tick = 15,
        .pinned = FALSE,
        .collision_group = COLLISION_GROUP_1,
        .collision_enabled = TRUE,
        .script = TO_FAR_PTR_T(script_s7a15_interact),
        .script_update = TO_FAR_PTR_T(script_s7a15_update),
        .script_hit1 = TO_FAR_PTR_T(script_s7a15_hit1)
    }
};
