#pragma bank 255

// Scene: Player's House

#include "gbs_types.h"
#include "data/bg_room.h"
#include "data/scene_player_s_house_collisions.h"
#include "data/palette_3.h"
#include "data/palette_9.h"
#include "data/sprite_cursor.h"
#include "data/scene_player_s_house_triggers.h"
#include "data/scene_player_s_house_init.h"

BANKREF(scene_player_s_house)

const struct scene_t scene_player_s_house = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_POINTNCLICK,
    .background = TO_FAR_PTR_T(bg_room),
    .collisions = TO_FAR_PTR_T(scene_player_s_house_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 0,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_3),
    .sprite_palette = TO_FAR_PTR_T(palette_9),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_cursor),
    .n_actors = 0,
    .n_triggers = 11,
    .n_sprites = 0,
    .n_projectiles = 0,
    .triggers = TO_FAR_PTR_T(scene_player_s_house_triggers),
    .script_init = TO_FAR_PTR_T(scene_player_s_house_init)
};
