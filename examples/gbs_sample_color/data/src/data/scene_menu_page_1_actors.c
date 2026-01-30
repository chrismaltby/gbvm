#pragma bank 255

// Scene: ui/menu/Menu Page 1
// Actors

#include "gbs_types.h"
#include "data/sprite_checkbox.h"
#include "data/sprite_checkbox.h"
#include "data/sprite_checkbox.h"
#include "data/sprite_checkbox.h"
#include "data/sprite_checkbox.h"
#include "data/sprite_checkbox.h"

BANKREF(scene_menu_page_1_actors)

const struct actor_t scene_menu_page_1_actors[] = {
    {
        // Quest1,
        .pos = {
            .x = 512,
            .y = 1024
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_checkbox),
        .move_speed = 32,
        .anim_tick = 255,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    },
    {
        // Quest2,
        .pos = {
            .x = 512,
            .y = 1536
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_checkbox),
        .move_speed = 32,
        .anim_tick = 255,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    },
    {
        // Quest3,
        .pos = {
            .x = 512,
            .y = 2048
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_checkbox),
        .move_speed = 32,
        .anim_tick = 255,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    },
    {
        // Quest4,
        .pos = {
            .x = 512,
            .y = 2816
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_checkbox),
        .move_speed = 32,
        .anim_tick = 255,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    },
    {
        // Quest5,
        .pos = {
            .x = 512,
            .y = 3328
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_checkbox),
        .move_speed = 32,
        .anim_tick = 255,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    },
    {
        // Quest6,
        .pos = {
            .x = 512,
            .y = 3840
        },
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_checkbox),
        .move_speed = 32,
        .anim_tick = 255,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    }
};
