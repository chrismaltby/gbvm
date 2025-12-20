#pragma bank 255

// Scene: Cave

#include "gbs_types.h"
#include "data/bg_cave.h"
#include "data/scene_cave_collisions.h"
#include "data/palette_0.h"
#include "data/palette_6.h"
#include "data/sprite_player.h"
#include "data/scene_cave_actors.h"
#include "data/scene_cave_triggers.h"
#include "data/scene_cave_sprites.h"
#include "data/scene_cave_init.h"

BANKREF(scene_cave)

const struct scene_t scene_cave = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_cave),
    .collisions = TO_FAR_PTR_T(scene_cave_collisions),
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
    .sprite_palette = TO_FAR_PTR_T(palette_6),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 6,
    .n_triggers = 1,
    .n_sprites = 4,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_cave_actors),
    .triggers = TO_FAR_PTR_T(scene_cave_triggers),
    .sprites = TO_FAR_PTR_T(scene_cave_sprites),
    .script_init = TO_FAR_PTR_T(scene_cave_init)
};
