#pragma bank 255

// Scene: space/Deep Space

#include "gbs_types.h"
#include "data/bg_stars.h"
#include "data/scene_deep_space_collisions.h"
#include "data/palette_4.h"
#include "data/palette_9.h"
#include "data/sprite_player.h"
#include "data/scene_deep_space_actors.h"
#include "data/scene_deep_space_triggers.h"
#include "data/scene_deep_space_sprites.h"
#include "data/scene_deep_space_init.h"

BANKREF(scene_deep_space)

const struct scene_t scene_deep_space = {
    .width = 32,
    .height = 32,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_stars),
    .collisions = TO_FAR_PTR_T(scene_deep_space_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 96,
        .bottom = 112
    },
    .palette = TO_FAR_PTR_T(palette_4),
    .sprite_palette = TO_FAR_PTR_T(palette_9),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 3,
    .n_triggers = 1,
    .n_sprites = 3,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_deep_space_actors),
    .triggers = TO_FAR_PTR_T(scene_deep_space_triggers),
    .sprites = TO_FAR_PTR_T(scene_deep_space_sprites),
    .script_init = TO_FAR_PTR_T(scene_deep_space_init)
};
