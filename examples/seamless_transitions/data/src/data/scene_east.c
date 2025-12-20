#pragma bank 255

// Scene: East

#include "gbs_types.h"
#include "data/bg_east_tileset_town.h"
#include "data/scene_east_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_player.h"
#include "data/scene_east_actors.h"
#include "data/scene_east_triggers.h"
#include "data/scene_east_sprites.h"
#include "data/scene_east_init.h"

BANKREF(scene_east)

const struct scene_t scene_east = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_east_tileset_town),
    .collisions = TO_FAR_PTR_T(scene_east_collisions),
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
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 1,
    .n_triggers = 1,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_east_actors),
    .triggers = TO_FAR_PTR_T(scene_east_triggers),
    .sprites = TO_FAR_PTR_T(scene_east_sprites),
    .script_init = TO_FAR_PTR_T(scene_east_init)
};
