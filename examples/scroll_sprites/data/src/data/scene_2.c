#pragma bank 255

// Scene: Scene 2

#include "gbs_types.h"
#include "data/bg_town.h"
#include "data/scene_2_collisions.h"
#include "data/palette_1.h"
#include "data/palette_3.h"
#include "data/sprite_panacea.h"
#include "data/scene_2_actors.h"
#include "data/scene_2_sprites.h"
#include "data/scene_2_init.h"

BANKREF(scene_2)

const struct scene_t scene_2 = {
    .width = 61,
    .height = 18,
    .type = SCENE_TYPE_PLATFORM,
    .background = TO_FAR_PTR_T(bg_town),
    .collisions = TO_FAR_PTR_T(scene_2_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 2, 2), PARALLAX_STEP(2, 6, 1), PARALLAX_STEP(6, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 328,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_1),
    .sprite_palette = TO_FAR_PTR_T(palette_3),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_panacea),
    .n_actors = 4,
    .n_triggers = 0,
    .n_sprites = 3,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_2_actors),
    .sprites = TO_FAR_PTR_T(scene_2_sprites),
    .script_init = TO_FAR_PTR_T(scene_2_init)
};
