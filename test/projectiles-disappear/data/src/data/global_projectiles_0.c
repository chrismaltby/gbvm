#pragma bank 255

// Global Projectiles: global_projectiles_0

#include "gbs_types.h"
#include "data/sprite_actor_animated.h"

BANKREF(global_projectiles_0)

const struct projectile_def_t global_projectiles_0[] = {
    {
        // Projectile 0,
        .sprite = TO_FAR_PTR_T(sprite_actor_animated),
        .move_speed = 0,
        .life_time = 240,
        .collision_group = COLLISION_GROUP_3,
        .collision_mask = COLLISION_GROUP_3,
        .strong = true,
        .bounds = {
            .left = PX_TO_SUBPX(0),
            .bottom = PX_TO_SUBPX(8) - 1,
            .right = PX_TO_SUBPX(16) - 1,
            .top = PX_TO_SUBPX(0)
        },
        .anim_tick = 255,
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
        .initial_offset = 544
    }
};
