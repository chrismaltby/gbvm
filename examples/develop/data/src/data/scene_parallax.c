#pragma bank 255

// Scene: Parallax

#include "gbs_types.h"
#include "data/bg_parallax.h"
#include "data/scene_parallax_collisions.h"
#include "data/palette_4.h"
#include "data/palette_6.h"
#include "data/sprite_player_platform.h"
#include "data/scene_parallax_actors.h"
#include "data/scene_parallax_triggers.h"
#include "data/scene_parallax_sprites.h"
#include "data/scene_parallax_init.h"

BANKREF(scene_parallax)

const struct scene_t scene_parallax = {
    .width = 80,
    .height = 18,
    .type = SCENE_TYPE_PLATFORM,
    .background = TO_FAR_PTR_T(bg_parallax),
    .collisions = TO_FAR_PTR_T(scene_parallax_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 10, 6), PARALLAX_STEP(10, 14, 3), PARALLAX_STEP(14, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 480,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_4),
    .sprite_palette = TO_FAR_PTR_T(palette_6),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player_platform),
    .n_actors = 1,
    .n_triggers = 2,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_parallax_actors),
    .triggers = TO_FAR_PTR_T(scene_parallax_triggers),
    .sprites = TO_FAR_PTR_T(scene_parallax_sprites),
    .script_init = TO_FAR_PTR_T(scene_parallax_init)
};
