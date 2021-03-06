#pragma bank 255

// Scene: Title Screen

#include "gbs_types.h"
#include "data/background_9.h"
#include "data/scene_2_collisions.h"
#include "data/palette_0.h"
#include "data/palette_6.h"
#include "data/spritesheet_1.h"
#include "data/script_s2_init.h"

const void __at(255) __bank_scene_2;

const struct scene_t scene_2 = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(background_9),
    .collisions = TO_FAR_PTR_T(scene_2_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0,0,0)
    },
    .palette = TO_FAR_PTR_T(palette_0),
    .sprite_palette = TO_FAR_PTR_T(palette_6),
    .player_sprite = TO_FAR_PTR_T(spritesheet_1),
    .n_actors = 0,
    .n_triggers = 0,
    .n_sprites = 0,
    .script_init = TO_FAR_PTR_T(script_s2_init)
};
