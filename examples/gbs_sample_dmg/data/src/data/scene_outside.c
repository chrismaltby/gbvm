#pragma bank 255

// Scene: Outside

#include "gbs_types.h"
#include "data/bg_outside.h"
#include "data/scene_outside_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player.h"
#include "data/scene_outside_actors.h"
#include "data/scene_outside_triggers.h"
#include "data/scene_outside_sprites.h"
#include "data/scene_outside_init.h"

BANKREF(scene_outside)

const struct scene_t scene_outside = {
    .width = 32,
    .height = 32,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_outside),
    .collisions = TO_FAR_PTR_T(scene_outside_collisions),
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
    .n_actors = 7,
    .n_triggers = 3,
    .n_sprites = 6,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_outside_actors),
    .triggers = TO_FAR_PTR_T(scene_outside_triggers),
    .sprites = TO_FAR_PTR_T(scene_outside_sprites),
    .script_init = TO_FAR_PTR_T(scene_outside_init)
};
