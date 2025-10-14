#pragma bank 255

// Scene: Dancefloor

#include "gbs_types.h"
#include "data/bg_dancefloor.h"
#include "data/scene_dancefloor_collisions.h"
#include "data/palette_5.h"
#include "data/palette_7.h"
#include "data/sprite_player_platform.h"
#include "data/scene_dancefloor_actors.h"
#include "data/scene_dancefloor_triggers.h"
#include "data/scene_dancefloor_sprites.h"
#include "data/scene_dancefloor_init.h"

BANKREF(scene_dancefloor)

const struct scene_t scene_dancefloor = {
    .width = 20,
    .height = 18,
    .type = SCENE_TYPE_PLATFORM,
    .background = TO_FAR_PTR_T(bg_dancefloor),
    .collisions = TO_FAR_PTR_T(scene_dancefloor_collisions),
    .parallax_rows = {
        PARALLAX_STEP(0, 0, 0)
    },
    .scroll_bounds = {
        .left = 0,
        .top = 0,
        .right = 0,
        .bottom = 0
    },
    .palette = TO_FAR_PTR_T(palette_5),
    .sprite_palette = TO_FAR_PTR_T(palette_7),
    .reserve_tiles = 0,
    .player_sprite = TO_FAR_PTR_T(sprite_player_platform),
    .n_actors = 2,
    .n_triggers = 2,
    .n_sprites = 2,
    .n_projectiles = 0,
    .actors = TO_FAR_PTR_T(scene_dancefloor_actors),
    .triggers = TO_FAR_PTR_T(scene_dancefloor_triggers),
    .sprites = TO_FAR_PTR_T(scene_dancefloor_sprites),
    .script_init = TO_FAR_PTR_T(scene_dancefloor_init)
};
