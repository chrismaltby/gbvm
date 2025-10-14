#pragma bank 255

// Scene: space/Space Battle

#include "gbs_types.h"
#include "data/bg_leaving_earth.h"
#include "data/scene_space_battle_collisions.h"
#include "data/palette_5.h"
#include "data/palette_9.h"
#include "data/sprite_player_ship.h"
#include "data/scene_space_battle_actors.h"
#include "data/scene_space_battle_triggers.h"
#include "data/scene_space_battle_sprites.h"
#include "data/scene_space_battle_projectiles.h"
#include "data/scene_space_battle_init.h"
#include "data/scene_space_battle_p_hit1.h"

BANKREF(scene_space_battle)

const struct scene_t scene_space_battle = {
    .width = 255,
    .height = 18,
    .type = SCENE_TYPE_SHMUP,
    .background = TO_FAR_PTR_T(bg_leaving_earth),
    .collisions = TO_FAR_PTR_T(scene_space_battle_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 1880,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_5),
    .sprite_palette = TO_FAR_PTR_T(palette_9),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player_ship),
    .n_actors = 16,
    .n_triggers = 1,
    .n_sprites = 5,
    .n_projectiles = 2,
    .actors = TO_FAR_PTR_T(scene_space_battle_actors),
    .triggers = TO_FAR_PTR_T(scene_space_battle_triggers),
    .sprites = TO_FAR_PTR_T(scene_space_battle_sprites),
    .projectiles = TO_FAR_PTR_T(scene_space_battle_projectiles),
    .script_init = TO_FAR_PTR_T(scene_space_battle_init),
    .script_p_hit1 = TO_FAR_PTR_T(scene_space_battle_p_hit1)
};
