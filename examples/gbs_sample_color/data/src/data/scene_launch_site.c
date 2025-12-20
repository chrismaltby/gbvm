#pragma bank 255

// Scene: town/Launch Site

#include "gbs_types.h"
#include "data/bg_launch_site.h"
#include "data/scene_launch_site_collisions.h"
#include "data/palette_6.h"
#include "data/palette_9.h"
#include "data/sprite_player.h"
#include "data/scene_launch_site_actors.h"
#include "data/scene_launch_site_triggers.h"
#include "data/scene_launch_site_sprites.h"
#include "data/scene_launch_site_init.h"

BANKREF(scene_launch_site)

const struct scene_t scene_launch_site = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_TOPDOWN,
    .background = TO_FAR_PTR_T(bg_launch_site),
    .collisions = TO_FAR_PTR_T(scene_launch_site_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 0,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_6),
    .sprite_palette = TO_FAR_PTR_T(palette_9),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player),
    .n_actors = 6,
    .n_triggers = 2,
    .n_sprites = 3,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_launch_site_actors),
    .triggers = TO_FAR_PTR_T(scene_launch_site_triggers),
    .sprites = TO_FAR_PTR_T(scene_launch_site_sprites),
    .script_init = TO_FAR_PTR_T(scene_launch_site_init)
};
