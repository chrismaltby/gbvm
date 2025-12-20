#pragma bank 255

// Scene: Font tileset

#include "gbs_types.h"
#include "data/bg_00000_ascii.h"
#include "data/scene_font_tileset_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_static.h"
#include "data/scene_font_tileset_init.h"

BANKREF(scene_font_tileset)

const struct scene_t scene_font_tileset = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_00000_ascii),
    .collisions = TO_FAR_PTR_T(scene_font_tileset_collisions),
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
    .player_sprite = TO_FAR_PTR_T(sprite_static),
    .n_actors = 0,
    .n_triggers = 0,
    .n_sprites = 0,
    .n_projectiles = 0,
    .script_init = TO_FAR_PTR_T(scene_font_tileset_init)
};
