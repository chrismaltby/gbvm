#pragma bank 255

// Scene: Title

#include "gbs_types.h"
#include "data/bg_title.h"
#include "data/scene_title_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player_1.h"
#include "data/scene_title_actors.h"
#include "data/scene_title_sprites.h"
#include "data/scene_title_init.h"

BANKREF(scene_title)

const struct scene_t scene_title = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_title),
    .collisions = TO_FAR_PTR_T(scene_title_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 0,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_0),
    .sprite_palette = TO_FAR_PTR_T(palette_1),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player_1),
    .n_actors = 5,
    .n_triggers = 0,
    .n_sprites = 5,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_title_actors),
    .sprites = TO_FAR_PTR_T(scene_title_sprites),
    .script_init = TO_FAR_PTR_T(scene_title_init)
};
