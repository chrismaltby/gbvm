#pragma bank 255

// Scene: ColorOnly

#include "gbs_types.h"
#include "data/bg_parallax_color.h"
#include "data/scene_color_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player_color.h"
#include "data/scene_color_actors.h"
#include "data/scene_color_sprites.h"
#include "data/scene_color_init.h"

BANKREF(scene_color)

const struct scene_t scene_color = {
    .width = 80,
    .height = 18,
    .type = SCENE_TYPE_PLATFORM,
    .background = TO_FAR_PTR_T(bg_parallax_color),
    .collisions = TO_FAR_PTR_T(scene_color_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 10, 2), PARALLAX_STEP(10, 14, 1), PARALLAX_STEP(14, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 480,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_0),
    .sprite_palette = TO_FAR_PTR_T(palette_1),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player_color),
    .n_actors = 1,
    .n_triggers = 0,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_color_actors),
    .sprites = TO_FAR_PTR_T(scene_color_sprites),
    .script_init = TO_FAR_PTR_T(scene_color_init)
};
