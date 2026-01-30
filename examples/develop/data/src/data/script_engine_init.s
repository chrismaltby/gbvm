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
        .db 32
_start_player_anim_tick:: 
        .db 15
_ui_fonts:: 
        IMPORT_FAR_PTR_DATA _font_font_vwf
        IMPORT_FAR_PTR_DATA _font_iec_8859_8
        IMPORT_FAR_PTR_DATA _font_windows_1251_cyrillic_
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
.globl _plat_camera_block
.globl _plat_run_vel
.globl _plat_run_acc
.globl _plat_jump_vel
.globl _plat_jump_hold_vel
.globl _plat_jump_hold_frames
.globl _plat_hold_grav
.globl _plat_run_boost
.globl _plat_coyote_frames
.globl _plat_jump_buffer_frames
.globl _plat_extra_jumps
.globl _plat_jump_reduction
.globl _plat_wall_jump_max
.globl _plat_wall_kick
.globl _plat_wall_slide
.globl _plat_wall_slide_vel
.globl _plat_drop_through_active
.globl _plat_float_active
.globl _plat_float_vel
.globl _plat_climb_vel
.globl _plat_dash_active
.globl _plat_dash_from
.globl _plat_dash_mask
.globl _plat_dash_dist
.globl _plat_dash_frames
.globl _plat_dash_ready_frames
.globl _plat_dash_deadzone
.globl _plat_dash_jump_from
.globl _plat_knockback_vel_x
.globl _plat_knockback_vel_y
.globl _plat_knockback_frames
.globl _plat_blank_grav
.globl _plat_vel_x
.globl _plat_vel_y
.globl _plat_grounded
.globl _plat_is_actor_attached
.globl _plat_run_stage
.globl _plat_jump_type
.globl _plat_extra_jumps_counter
.globl _plat_wall_jump_counter
.globl _plat_next_state
.globl _topdown_grid
.globl _fade_style
.globl _adv_walk_vel
.globl _adv_walk_acc
.globl _adv_dec
.globl _adv_turn_acc
.globl _adv_run_vel
.globl _adv_run_acc
.globl _adv_dash_active
.globl _adv_dash_mask
.globl _adv_dash_dist
.globl _adv_dash_frames
.globl _adv_dash_ready_frames
.globl _adv_dash_deadzone
.globl _adv_push_delay_frames
.globl _adv_knockback_vel_x
.globl _adv_knockback_vel_y
.globl _adv_knockback_frames
.globl _adv_next_state
.globl _adv_vel_x
.globl _adv_vel_y

_script_engine_init::
        VM_RPN
            .R_INT16 6400
            .R_REF_MEM_SET .MEM_I16, _plat_walk_vel
            .R_INT16 152
            .R_REF_MEM_SET .MEM_I16, _plat_walk_acc
            .R_INT16 304
            .R_REF_MEM_SET .MEM_I16, _plat_min_vel
            .R_INT16 712
            .R_REF_MEM_SET .MEM_I16, _plat_turn_acc
            .R_INT16 208
            .R_REF_MEM_SET .MEM_I16, _plat_dec
            .R_INT16 1792
            .R_REF_MEM_SET .MEM_I16, _plat_grav
            .R_INT16 20000
            .R_REF_MEM_SET .MEM_I16, _plat_max_fall_vel
            .R_INT16 208
            .R_REF_MEM_SET .MEM_I16, _plat_air_dec
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_air_control
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_turn_control
            .R_INT8 PLATFORM_CAMERA_LOCK_SCREEN_NONE
            .R_REF_MEM_SET .MEM_I8, _plat_camera_block
            .R_INT16 10496
            .R_REF_MEM_SET .MEM_I16, _plat_run_vel
            .R_INT16 228
            .R_REF_MEM_SET .MEM_I16, _plat_run_acc
            .R_INT16 16384
            .R_REF_MEM_SET .MEM_I16, _plat_jump_vel
            .R_INT16 0
            .R_REF_MEM_SET .MEM_I16, _plat_jump_hold_vel
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_jump_hold_frames
            .R_INT16 512
            .R_REF_MEM_SET .MEM_I16, _plat_hold_grav
            .R_INT16 0
            .R_REF_MEM_SET .MEM_I16, _plat_run_boost
            .R_INT8 2
            .R_REF_MEM_SET .MEM_I8, _plat_coyote_frames
            .R_INT8 2
            .R_REF_MEM_SET .MEM_I8, _plat_jump_buffer_frames
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_extra_jumps
            .R_INT16 0
            .R_REF_MEM_SET .MEM_I16, _plat_jump_reduction
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_wall_jump_max
            .R_INT16 600
            .R_REF_MEM_SET .MEM_I16, _plat_wall_kick
            .R_INT8 0
            .R_REF_MEM_SET .MEM_I8, _plat_wall_slide
            .R_INT16 1792
            .R_REF_MEM_SET .MEM_I16, _plat_wall_slide_vel
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_drop_through_active
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_float_active
            .R_INT16 912
            .R_REF_MEM_SET .MEM_I16, _plat_float_vel
            .R_INT16 4000
            .R_REF_MEM_SET .MEM_I16, _plat_climb_vel
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_dash_active
            .R_INT8 3
            .R_REF_MEM_SET .MEM_I8, _plat_dash_from
            .R_INT8 255
            .R_REF_MEM_SET .MEM_I8, _plat_dash_mask
            .R_INT16 2048
            .R_REF_MEM_SET .MEM_I16, _plat_dash_dist
            .R_INT8 15
            .R_REF_MEM_SET .MEM_I8, _plat_dash_frames
            .R_INT8 10
            .R_REF_MEM_SET .MEM_I8, _plat_dash_ready_frames
            .R_INT8 32
            .R_REF_MEM_SET .MEM_I8, _plat_dash_deadzone
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _plat_dash_jump_from
            .R_INT16 8192
            .R_REF_MEM_SET .MEM_I16, _plat_knockback_vel_x
            .R_INT16 16384
            .R_REF_MEM_SET .MEM_I16, _plat_knockback_vel_y
            .R_INT8 30
            .R_REF_MEM_SET .MEM_I8, _plat_knockback_frames
            .R_INT16 0
            .R_REF_MEM_SET .MEM_I16, _plat_blank_grav
            .R_INT8 8
            .R_REF_MEM_SET .MEM_I8, _topdown_grid
            .R_INT8 0
            .R_REF_MEM_SET .MEM_I8, _fade_style
            .R_INT16 4096
            .R_REF_MEM_SET .MEM_I16, _adv_walk_vel
            .R_INT16 1024
            .R_REF_MEM_SET .MEM_I16, _adv_walk_acc
            .R_INT16 1024
            .R_REF_MEM_SET .MEM_I16, _adv_dec
            .R_INT16 712
            .R_REF_MEM_SET .MEM_I16, _adv_turn_acc
            .R_INT16 6144
            .R_REF_MEM_SET .MEM_I16, _adv_run_vel
            .R_INT16 512
            .R_REF_MEM_SET .MEM_I16, _adv_run_acc
            .R_INT8 1
            .R_REF_MEM_SET .MEM_I8, _adv_dash_active
            .R_INT8 255
            .R_REF_MEM_SET .MEM_I8, _adv_dash_mask
            .R_INT16 2048
            .R_REF_MEM_SET .MEM_I16, _adv_dash_dist
            .R_INT8 15
            .R_REF_MEM_SET .MEM_I8, _adv_dash_frames
            .R_INT8 10
            .R_REF_MEM_SET .MEM_I8, _adv_dash_ready_frames
            .R_INT8 32
            .R_REF_MEM_SET .MEM_I8, _adv_dash_deadzone
            .R_INT8 5
            .R_REF_MEM_SET .MEM_I8, _adv_push_delay_frames
            .R_INT16 6144
            .R_REF_MEM_SET .MEM_I16, _adv_knockback_vel_x
            .R_INT16 6144
            .R_REF_MEM_SET .MEM_I16, _adv_knockback_vel_y
            .R_INT8 10
            .R_REF_MEM_SET .MEM_I8, _adv_knockback_frames
            .R_STOP

        ; return from init routine
        VM_RET_FAR
