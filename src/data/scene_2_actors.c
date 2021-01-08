#pragma bank 255

// Scene: Scene 3
// Actors

#include "gbs_types.h"
#include "data/script_s2a0_interact.h"
#include "data/script_s2a0_update.h"

const void __at(255) __bank_scene_2_actors;

const struct actor_t scene_2_actors[] = {
  {
    // Actor 1,
    .x = 168,
    .y = 104,
    .dir_x = 0,
    .dir_y = 1,
    .sprite_no = 0,
    .sprite = 6,
    .sprite_type = SPRITE_TYPE_ACTOR,
    .palette = 0,
    .n_frames = 2,
    .animate = FALSE,
    .move_speed = 1,
    .anim_tick = 7,
    .frame = 24,
    .frame_start = 24,
    .frame_end = 32,
    .pinned = FALSE,
    .collision_group = COLLISION_GROUP_1,
    .collision_enabled = TRUE,
    .script = TO_FAR_PTR_T(script_s2a0_interact),
    .script_update = TO_FAR_PTR_T(script_s2a0_update)
  }
};
