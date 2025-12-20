#pragma bank 255

// Scene: Platform

#include "gbs_types.h"
#include "data/bg_platform_path.h"
#include "data/scene_platform_collisions.h"
#include "data/palette_2.h"
#include "data/palette_6.h"
#include "data/sprite_player_platform.h"
#include "data/scene_platform_actors.h"
#include "data/scene_platform_triggers.h"
#include "data/scene_platform_sprites.h"
#include "data/scene_platform_init.h"

BANKREF(scene_platform)

const struct scene_t scene_platform = {
    .width = 161,
    .height = 18,
    .type = SCENE_TYPE_PLATFORM,
    .background = TO_FAR_PTR_T(bg_platform_path),
    .collisions = TO_FAR_PTR_T(scene_platform_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 1128,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_2),
    .sprite_palette = TO_FAR_PTR_T(palette_6),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player_platform),
    .n_actors = 3,
    .n_triggers = 5,
    .n_sprites = 2,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_platform_actors),
    .triggers = TO_FAR_PTR_T(scene_platform_triggers),
    .sprites = TO_FAR_PTR_T(scene_platform_sprites),
    .script_init = TO_FAR_PTR_T(scene_platform_init)
};
