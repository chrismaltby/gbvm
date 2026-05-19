.include "vm.i"
.include "macro.i"
.include "data/game_globals.i"

; define constants in rom bank 0
.area _CODE

_start_scene_x:: 
        .dw 1792
_start_scene_y:: 
        .dw 3072 
_start_scene_dir:: 
        .db .DIR_UP
_start_scene::
        IMPORT_FAR_PTR_DATA _scene_2
_start_player_move_speed:: 
        .db 32
_start_player_anim_tick:: 
        .db 15
_ui_fonts:: 
        IMPORT_FAR_PTR_DATA _font_gbs_mono


; define engine init VM routine which will be packed into some bank
.area _CODE_255

___bank_script_engine_init = 255
.globl ___bank_script_engine_init

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
