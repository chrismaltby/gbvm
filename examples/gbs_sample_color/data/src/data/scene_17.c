#pragma bank 255

// Scene: town/Music House

#include "gbs_types.h"
#include "data/bg_house.h"
#include "data/scene_17_collisions.h"
#include "data/palette_0.h"
#include "data/palette_9.h"
#include "data/sprite_player.h"
#include "data/scene_17_actors.h"
#include "data/scene_17_triggers.h"
#include "data/scene_17_sprites.h"
#include "data/scene_17_init.h"

BANKREF(scene_17)

const struct scene_t scene_17 = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_house),
    .collisions = TO_FAR_PTR_T(scene_17_collisions),
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
    .sprite_palette = TO_FAR_PTR_T(palette_9),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 9,
    .n_triggers = 1,
    .n_sprites = 5,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_17_actors),
    .triggers = TO_FAR_PTR_T(scene_17_triggers),
    .sprites = TO_FAR_PTR_T(scene_17_sprites),
    .script_init = TO_FAR_PTR_T(scene_17_init)
};
