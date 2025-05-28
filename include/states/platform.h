#ifndef STATE_PLATFORM_H
#define STATE_PLATFORM_H

#include <gb/gb.h>

void platform_init(void) BANKED;
void platform_update(void) BANKED;

extern WORD plat_vel_x;
extern WORD plat_vel_y;
extern WORD plat_min_vel;
extern WORD plat_walk_vel;
extern WORD plat_run_vel;
extern WORD plat_climb_vel;
extern WORD plat_walk_acc;
extern WORD plat_run_acc;
extern WORD plat_dec;
extern WORD plat_jump_vel;
extern WORD plat_grav;
extern WORD plat_hold_grav;
extern WORD plat_max_fall_vel;

extern BYTE plat_camera_deadzone_x;
extern UBYTE plat_camera_block;
extern UBYTE plat_drop_through;
extern WORD plat_jump_min;
extern UBYTE plat_hold_jump_max;
extern UBYTE plat_extra_jumps;
extern WORD plat_jump_reduction;
extern UBYTE plat_coyote_max;
extern UBYTE plat_buffer_max;
extern UBYTE plat_wall_jump_max;
extern UBYTE plat_wall_slide;
extern WORD plat_wall_grav;
extern WORD plat_wall_kick;
extern UBYTE plat_float_input;
extern WORD plat_float_grav;
extern UBYTE plat_air_control;
extern UBYTE plat_turn_control;
extern WORD plat_air_dec;
extern WORD plat_turn_acc;
extern UBYTE plat_run_boost;
extern UBYTE plat_dash;
extern WORD plat_dash_dist;
extern UBYTE plat_dash_frames;
extern UBYTE plat_dash_ready_max;

#endif
