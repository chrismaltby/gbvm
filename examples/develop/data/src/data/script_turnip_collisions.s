.module script_turnip_collisions

.include "vm.i"
.include "data/game_globals.i"

.globl _plat_vel_y, b_wait_frames, _wait_frames, b_camera_shake_frames, _camera_shake_frames

.area _CODE_255

.SCRIPT_ARG_INDIRECT_0_VARIABLE = -10
.SCRIPT_ARG_INDIRECT_1_VARIABLE = -11
.SCRIPT_ARG_2_ACTOR = -12
.LOCAL_ACTOR = -4
.LOCAL_TMP4_CAMERA_SHAKE_ARGS = -4
.LOCAL_TMP1_OTHER_ACTOR = -7
.LOCAL_TMP2_VALUE_TMP = -7
.LOCAL_TMP3_WAIT_ARGS = -7

___bank_script_turnip_collisions = 255
.globl ___bank_script_turnip_collisions

_script_turnip_collisions::
        VM_RESERVE              7

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 0

        ; If Actor up Relative To Actor
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        VM_SET                  .LOCAL_TMP1_OTHER_ACTOR, .SCRIPT_ARG_2_ACTOR
        VM_ACTOR_GET_POS        .LOCAL_TMP1_OTHER_ACTOR
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_REF      ^/(.LOCAL_TMP1_OTHER_ACTOR + 2)/
            .R_OPERATOR .LT
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 1$, 1

        ; Variable Set To
        VM_SET_CONST            .LOCAL_TMP2_VALUE_TMP, 1
        VM_SET_INDIRECT         .SCRIPT_ARG_INDIRECT_0_VARIABLE, .LOCAL_TMP2_VALUE_TMP

        ; Variable Decrement By 1
        VM_RPN
            .R_REF_IND  .SCRIPT_ARG_INDIRECT_1_VARIABLE
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET_IND .SCRIPT_ARG_INDIRECT_1_VARIABLE
            .R_STOP

        ; Actor Set Active
        VM_SET                  .LOCAL_ACTOR, .SCRIPT_ARG_2_ACTOR

        ; Actor Set Collisions
        VM_ACTOR_SET_COLL_ENABLED .LOCAL_ACTOR, 0

        ; Actor Set Active
        VM_SET                  .LOCAL_ACTOR, .SCRIPT_ARG_2_ACTOR

        ; Actor Stop Update Script
        VM_ACTOR_TERMINATE_UPDATE .LOCAL_ACTOR

        ; Actor Set Active
        VM_SET                  .LOCAL_ACTOR, .SCRIPT_ARG_2_ACTOR

        ; Actor Set Spritesheet
        VM_ACTOR_SET_SPRITESHEET .LOCAL_ACTOR, ___bank_sprite_turnip_squash, _sprite_turnip_squash

        ; Player Bounce
        VM_SET_CONST_INT16      _plat_vel_y, -8192

        ; Wait 30 frames
        VM_SET_CONST            .LOCAL_TMP3_WAIT_ARGS, 30
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP3_WAIT_ARGS

        ; Actor Deactivate
        VM_SET                  .LOCAL_ACTOR, .SCRIPT_ARG_2_ACTOR
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        VM_JUMP                 2$
1$:
        ; Actor Set Position
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    6656
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    1664
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Position Actor
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR

        ; Camera Shake
        VM_SET_CONST            .LOCAL_TMP4_CAMERA_SHAKE_ARGS, 30
        VM_SET_CONST            ^/(.LOCAL_TMP4_CAMERA_SHAKE_ARGS + 1)/, .CAMERA_SHAKE_X
        VM_RPN
            .R_INT16    5
            .R_REF_SET  ^/(.LOCAL_TMP4_CAMERA_SHAKE_ARGS + 2)/
            .R_STOP
        VM_INVOKE               b_camera_shake_frames, _camera_shake_frames, 0, .LOCAL_TMP4_CAMERA_SHAKE_ARGS

2$:

        VM_RESERVE              -7
        VM_RET_FAR_N            3
