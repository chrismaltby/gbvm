#pragma bank 255

// Scene: Scene 1

#include "gbs_types.h"
#include "data/bg_underground.h"
#include "data/test_scene_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player.h"
#include "data/test_scene_actors.h"
#include "data/test_scene_triggers.h"
#include "data/test_scene_sprites.h"
#include "data/test_scene_init.h"

BANKREF(test_scene)

const struct scene_t test_scene = {
    .width = 32,
    .height = 32,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_underground),
    .collisions = TO_FAR_PTR_T(test_scene_collisions),
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
    .n_triggers = 1,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(test_scene_actors),
    .triggers = TO_FAR_PTR_T(test_scene_triggers),
    .sprites = TO_FAR_PTR_T(test_scene_sprites),
    .script_init = TO_FAR_PTR_T(test_scene_init)
};
