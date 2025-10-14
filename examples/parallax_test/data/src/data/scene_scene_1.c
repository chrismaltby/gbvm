#pragma bank 255

// Scene: Scene 1

#include "gbs_types.h"
#include "data/bg_parallax_test.h"
#include "data/scene_scene_1_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_actor_animated.h"
#include "data/scene_scene_1_init.h"

BANKREF(scene_scene_1)

const struct scene_t scene_scene_1 = {
    .width = 40,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_parallax_test),
    .collisions = TO_FAR_PTR_T(scene_scene_1_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 3, 0), PARALLAX_STEP(3, 9, 8), PARALLAX_STEP(9, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 160,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_0),
    .sprite_palette = TO_FAR_PTR_T(palette_1),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_actor_animated),
    .n_actors = 0,
    .n_triggers = 0,
    .n_sprites = 0,
    .n_projectiles = 0,
    .script_init = TO_FAR_PTR_T(scene_scene_1_init)
};
