#pragma bank 255

// Scene: DMGSupport

#include "gbs_types.h"
#include "data/bg_parallax.h"
#include "data/scene_dmg_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player.h"
#include "data/scene_dmg_actors.h"
#include "data/scene_dmg_sprites.h"
#include "data/scene_dmg_init.h"

BANKREF(scene_dmg)

const struct scene_t scene_dmg = {
    .width = 80,
    .height = 18,
    .type = SCENE_TYPE_PLATFORM,
    .background = TO_FAR_PTR_T(bg_parallax),
    .collisions = TO_FAR_PTR_T(scene_dmg_collisions),
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
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 1,
    .n_triggers = 0,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_dmg_actors),
    .sprites = TO_FAR_PTR_T(scene_dmg_sprites),
    .script_init = TO_FAR_PTR_T(scene_dmg_init)
};
