#pragma bank 255

// Scene: ColorOnly
// Actors

#include "gbs_types.h"
#include "data/sprite_elephant_color.h"

BANKREF(scene_color_actors)

const struct actor_t scene_color_actors[] = {
    {
        // Actor 1,
        .pos = {
            .x = 2560,
            .y = 3328
        },
        .bounds = {
            .left = PX_TO_SUBPX(-21),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(26) - 1,
            .top = PX_TO_SUBPX(-31)
        },
        .dir = DIR_DOWN,
        .sprite = TO_FAR_PTR_T(sprite_elephant_color),
        .move_speed = 32,
        .anim_tick = 15,
        .flags = ACTOR_FLAG_COLLISION,
        .collision_group = COLLISION_GROUP_NONE,
        .reserve_tiles = 0
    }
};
