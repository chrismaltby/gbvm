#pragma bank 255

// Scene: Level 1

#include "gbs_types.h"
#include "data/symbol.h"
#include "data/scene_level_1_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player.h"
#include "data/scene_level_1_actors.h"
#include "data/scene_level_1_sprites.h"
#include "data/scene_level_1_init.h"

BANKREF(scene_level_1)

const struct scene_t scene_level_1 = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(symbol),
    .collisions = TO_FAR_PTR_T(scene_level_1_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .palette = TO_FAR_PTR_T(palette_0),
    .sprite_palette = TO_FAR_PTR_T(palette_1),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 7,
    .n_triggers = 0,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_level_1_actors),
    .sprites = TO_FAR_PTR_T(scene_level_1_sprites),
    .script_init = TO_FAR_PTR_T(scene_level_1_init)
};
