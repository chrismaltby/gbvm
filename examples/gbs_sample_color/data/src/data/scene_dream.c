#pragma bank 255

// Scene: Dream

#include "gbs_types.h"
#include "data/bg_black.h"
#include "data/scene_dream_collisions.h"
#include "data/palette_0.h"
#include "data/palette_9.h"
#include "data/sprite_player.h"
#include "data/scene_dream_init.h"

BANKREF(scene_dream)

const struct scene_t scene_dream = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_black),
    .collisions = TO_FAR_PTR_T(scene_dream_collisions),
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
    .n_actors = 0,
    .n_triggers = 0,
    .n_sprites = 0,
    .n_projectiles = 0,
    .script_init = TO_FAR_PTR_T(scene_dream_init)
};
