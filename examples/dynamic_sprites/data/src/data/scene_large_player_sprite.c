#pragma bank 255

// Scene: Large Player Sprite

#include "gbs_types.h"
#include "data/bg_placeholder.h"
#include "data/scene_large_player_sprite_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_elephant.h"
#include "data/scene_large_player_sprite_actors.h"
#include "data/scene_large_player_sprite_sprites.h"
#include "data/scene_large_player_sprite_init.h"

BANKREF(scene_large_player_sprite)

const struct scene_t scene_large_player_sprite = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_placeholder),
    .collisions = TO_FAR_PTR_T(scene_large_player_sprite_collisions),
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
    .player_sprite = TO_FAR_PTR_T(sprite_elephant),
    .n_actors = 2,
    .n_triggers = 0,
    .n_sprites = 2,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_large_player_sprite_actors),
    .sprites = TO_FAR_PTR_T(scene_large_player_sprite_sprites),
    .script_init = TO_FAR_PTR_T(scene_large_player_sprite_init)
};
