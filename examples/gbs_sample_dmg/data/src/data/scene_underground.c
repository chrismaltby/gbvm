#pragma bank 255

// Scene: Underground

#include "gbs_types.h"
#include "data/bg_underground.h"
#include "data/scene_underground_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player.h"
#include "data/scene_underground_actors.h"
#include "data/scene_underground_triggers.h"
#include "data/scene_underground_sprites.h"
#include "data/scene_underground_init.h"

BANKREF(scene_underground)

const struct scene_t scene_underground = {
    .width = 32,
    .height = 32,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_underground),
    .collisions = TO_FAR_PTR_T(scene_underground_collisions),
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
    .n_actors = 5,
    .n_triggers = 1,
    .n_sprites = 3,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_underground_actors),
    .triggers = TO_FAR_PTR_T(scene_underground_triggers),
    .sprites = TO_FAR_PTR_T(scene_underground_sprites),
    .script_init = TO_FAR_PTR_T(scene_underground_init)
};
