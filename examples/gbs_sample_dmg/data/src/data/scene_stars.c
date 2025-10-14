#pragma bank 255

// Scene: Stars

#include "gbs_types.h"
#include "data/bg_stars.h"
#include "data/scene_stars_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player.h"
#include "data/scene_stars_actors.h"
#include "data/scene_stars_sprites.h"
#include "data/scene_stars_init.h"

BANKREF(scene_stars)

const struct scene_t scene_stars = {
    .width = 32,
    .height = 32,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_stars),
    .collisions = TO_FAR_PTR_T(scene_stars_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 96,
        .bottom = 112
    },
    .palette = TO_FAR_PTR_T(palette_0),
    .sprite_palette = TO_FAR_PTR_T(palette_1),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 1,
    .n_triggers = 0,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_stars_actors),
    .sprites = TO_FAR_PTR_T(scene_stars_sprites),
    .script_init = TO_FAR_PTR_T(scene_stars_init)
};
