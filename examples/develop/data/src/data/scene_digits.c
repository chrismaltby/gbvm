#pragma bank 255

// Scene: Digits

#include "gbs_types.h"
#include "data/bg_digits.h"
#include "data/scene_digits_collisions.h"
#include "data/palette_0.h"
#include "data/palette_6.h"
#include "data/sprite_player.h"
#include "data/scene_digits_init.h"

BANKREF(scene_digits)

const struct scene_t scene_digits = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_digits),
    .collisions = TO_FAR_PTR_T(scene_digits_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .palette = TO_FAR_PTR_T(palette_0),
    .sprite_palette = TO_FAR_PTR_T(palette_6),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 0,
    .n_triggers = 0,
    .n_sprites = 0,
    .n_projectiles = 0,
    .script_init = TO_FAR_PTR_T(scene_digits_init)
};
