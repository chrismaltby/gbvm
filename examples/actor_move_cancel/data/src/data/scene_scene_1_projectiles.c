#pragma bank 255

// Scene: Scene 1
// Projectiles

#include "gbs_types.h"
#include "data/sprite_actor.h"

BANKREF(scene_scene_1_projectiles)

const struct projectile_def_t scene_scene_1_projectiles[] = {
    {
        // Projectile 0,
        .sprite = TO_FAR_PTR_T(sprite_actor),
        .move_speed = 128,
        .life_time = 60,
        .collision_group = COLLISION_GROUP_3,
        .collision_mask = COLLISION_GROUP_1,
        .strong = false,
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(-8)
        },
        .anim_tick = 15,
        .anim_noloop = false,
        .animations = {
            {
                .start = 0,
                .end = 0
            },
            {
                .start = 1,
                .end = 1
            },
            {
                .start = 2,
                .end = 2
            },
            {
                .start = 3,
                .end = 3
            }
        },
        .initial_offset = 0
    }
};
