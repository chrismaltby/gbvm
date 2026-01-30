#pragma bank 255

// Scene: Scene 1

#include "gbs_types.h"
#include "data/bg_placeholder.h"
#include "data/scene_scene_1_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_actor.h"
#include "data/scene_scene_1_actors.h"
#include "data/scene_scene_1_sprites.h"
#include "data/scene_scene_1_init.h"

BANKREF(scene_scene_1)

const struct scene_t scene_scene_1 = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_placeholder),
    .collisions = TO_FAR_PTR_T(scene_scene_1_collisions),
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
    .player_sprite = TO_FAR_PTR_T(sprite_actor),
    .n_actors = 5,
    .n_triggers = 0,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_scene_1_actors),
    .sprites = TO_FAR_PTR_T(scene_scene_1_sprites),
    .script_init = TO_FAR_PTR_T(scene_scene_1_init)
};
