#pragma bank 255

// Scene: ui/menu/Menu Page 1

#include "gbs_types.h"
#include "data/bg_menu_page1.h"
#include "data/scene_menu_page_1_collisions.h"
#include "data/palette_8.h"
#include "data/palette_9.h"
#include "data/sprite_player.h"
#include "data/scene_menu_page_1_actors.h"
#include "data/scene_menu_page_1_sprites.h"
#include "data/scene_menu_page_1_init.h"

BANKREF(scene_menu_page_1)

const struct scene_t scene_menu_page_1 = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_menu_page1),
    .collisions = TO_FAR_PTR_T(scene_menu_page_1_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 0,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_8),
    .sprite_palette = TO_FAR_PTR_T(palette_9),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 6,
    .n_triggers = 0,
    .n_sprites = 1,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_menu_page_1_actors),
    .sprites = TO_FAR_PTR_T(scene_menu_page_1_sprites),
    .script_init = TO_FAR_PTR_T(scene_menu_page_1_init)
};
