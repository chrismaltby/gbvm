#pragma bank 255

// Scene: Scene

#include "gbs_types.h"
#include "data/bg_placeholder.h"
#include "data/scene_2_collisions.h"
#include "data/palette_0.h"
#include "data/palette_1.h"
#include "data/sprite_actor_animated.h"
#include "data/scene_2_actors.h"
#include "data/scene_2_sprites.h"
#include "data/scene_2_init.h"
#include "data/scene_2_p_hit1.h"

BANKREF(scene_2)

const struct scene_t scene_2 = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_ADVENTURE,
    .background = TO_FAR_PTR_T(bg_placeholder),
    .collisions = TO_FAR_PTR_T(scene_2_collisions),
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
    .player_sprite = TO_FAR_PTR_T(sprite_actor_animated),
    .n_actors = 1,
    .n_triggers = 0,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_2_actors),
    .sprites = TO_FAR_PTR_T(scene_2_sprites),
    .script_init = TO_FAR_PTR_T(scene_2_init),
    .script_p_hit1 = TO_FAR_PTR_T(scene_2_p_hit1)
};
