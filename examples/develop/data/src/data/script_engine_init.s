.include "vm.i"
.include "macro.i"
.include "data/game_globals.i"

; define constants in rom bank 0
.area _CODE

_start_scene_x:: 
        .dw 0
_start_scene_y:: 
        .dw 0 
_start_scene_dir:: 
        .db .DIR_RIGHT
_start_scene::
        IMPORT_FAR_PTR_DATA _scene_logo
_start_player_move_speed:: 
        .db 16
_start_player_anim_tick:: 
        .db 15
_ui_fonts:: 
        IMPORT_FAR_PTR_DATA _font_font_vwf
        IMPORT_FAR_PTR_DATA _font_font_he
        IMPORT_FAR_PTR_DATA _font_font_ru
        IMPORT_FAR_PTR_DATA _avatar_font_0

; define engine init VM routine which will be packed into some bank
.area _CODE_255

___bank_script_engine_init = 255
.globl ___bank_script_engine_init

.globl _plat_walk_vel
.globl _plat_walk_acc
.globl _plat_min_vel
.globl _plat_turn_acc
.globl _plat_dec
.globl _plat_grav
.globl _plat_max_fall_vel
.globl _plat_air_dec
.globl _plat_air_control
.globl _plat_turn_control
.globl _plat_camera_deadzone_x
.globl _plat_camera_block
.globl _plat_run_vel
.globl _plat_run_acc
.globl _plat_jump_vel
.globl _plat_hold_jump_max
.globl _plat_hold_grav
.globl _plat_jump_min
.globl _plat_buffer_max
.globl _plat_run_boost
.globl _plat_extra_jumps
.globl _plat_jump_reduction
.globl _plat_coyote_max
.globl _plat_wall_jump_max
.globl _plat_wall_kick
.globl _plat_wall_slide
.globl _plat_wall_grav
.globl _plat_drop_through
.globl _plat_float_input
.globl _plat_float_grav
.globl _plat_climb_vel
.globl _plat_dash
.globl _plat_dash_from
.globl _plat_dash_mask
.globl _plat_dash_dist
.globl _plat_dash_frames
.globl _plat_dash_ready_max
.globl _plat_dash_deadzone
.globl _plat_dash_use_grav
.globl _plat_actor_attached
.globl _plat_run_stage
.globl _plat_jump_type
.globl _plat_ct_val
.globl _plat_dj_val
.globl _plat_wj_val
.globl _plat_wc_val
.globl _plat_next_state
.globl _shooter_scroll_speed
.globl _topdown_grid
.globl _fade_style

_script_engine_init::
        VM_SET_CONST_INT16      _plat_walk_vel, 6400
        VM_SET_CONST_INT16      _plat_walk_acc, 152
        VM_SET_CONST_INT16      _plat_min_vel, 304
        VM_SET_CONST_INT16      _plat_turn_acc, 712
        VM_SET_CONST_INT16      _plat_dec, 208
        VM_SET_CONST_INT16      _plat_grav, 1792
        VM_SET_CONST_INT16      _plat_max_fall_vel, 20000
        VM_SET_CONST_INT16      _plat_air_dec, 208
        VM_SET_CONST_INT8      _plat_air_control, 1
        VM_SET_CONST_INT8      _plat_turn_control, 1
        VM_SET_CONST_INT8      _plat_camera_deadzone_x, 4
        VM_SET_CONST_INT8      _plat_camera_block, 0
        VM_SET_CONST_INT16      _plat_run_vel, 10496
        VM_SET_CONST_INT16      _plat_run_acc, 228
        VM_SET_CONST_INT16      _plat_jump_vel, 16384
        VM_SET_CONST_INT8      _plat_hold_jump_max, 1
        VM_SET_CONST_INT16      _plat_hold_grav, 512
        VM_SET_CONST_INT16      _plat_jump_min, 0
        VM_SET_CONST_INT8      _plat_buffer_max, 0
        VM_SET_CONST_INT8      _plat_run_boost, 0
        VM_SET_CONST_INT8      _plat_extra_jumps, 1
        VM_SET_CONST_INT16      _plat_jump_reduction, 0
        VM_SET_CONST_INT8      _plat_coyote_max, 2
        VM_SET_CONST_INT8      _plat_wall_jump_max, 1
        VM_SET_CONST_INT16      _plat_wall_kick, 600
        VM_SET_CONST_INT8      _plat_wall_slide, 0
        VM_SET_CONST_INT16      _plat_wall_grav, 1792
        VM_SET_CONST_INT8      _plat_drop_through, 4
        VM_SET_CONST_INT8      _plat_float_input, 1
        VM_SET_CONST_INT16      _plat_float_grav, 912
        VM_SET_CONST_INT16      _plat_climb_vel, 4000
        VM_SET_CONST_INT8      _plat_dash, 2
        VM_SET_CONST_INT8      _plat_dash_from, 3
        VM_SET_CONST_INT8      _plat_dash_mask, 0
        VM_SET_CONST_INT16      _plat_dash_dist, 800
        VM_SET_CONST_INT8      _plat_dash_frames, 5
        VM_SET_CONST_INT8      _plat_dash_ready_max, 10
        VM_SET_CONST_INT8      _plat_dash_deadzone, 4
        VM_SET_CONST_INT8      _plat_dash_use_grav, 0


        VM_SET_CONST_INT8      _shooter_scroll_speed, 16
        VM_SET_CONST_INT8      _topdown_grid, 8
        VM_SET_CONST_INT8      _fade_style, 0

        ; return from init routine
        VM_RET_FAR
