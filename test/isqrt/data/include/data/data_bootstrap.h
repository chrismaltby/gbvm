#ifndef DATA_PTRS_H
#define DATA_PTRS_H

#include "bankdata.h"
#include "gbs_types.h"

extern const INT16 start_scene_x;
extern const INT16 start_scene_y;
extern const direction_e start_scene_dir;
extern const far_ptr_t start_scene;
extern const UBYTE start_player_move_speed;
extern const UBYTE start_player_anim_tick;

extern const far_ptr_t ui_fonts[];

void bootstrap_init() BANKED;

#endif
