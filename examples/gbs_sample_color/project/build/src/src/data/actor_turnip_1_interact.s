.module actor_turnip_1_interact

.include "vm.i"
.include "data/game_globals.i"

.globl _plat_vel_y, b_wait_frames, _wait_frames, b_camera_shake_frames, _camera_shake_frames

.area _CODE_255

.LOCAL_TMP0_PARAM0_VALUE = -4
.LOCAL_ACTOR = -4
.LOCAL_TMP4_CAMERA_SHAKE_ARGS = -4
.LOCAL_TMP2_OTHER_ACTOR = -7
.LOCAL_TMP3_WAIT_ARGS = -7

___bank_actor_turnip_1_interact = 255
.globl ___bank_actor_turnip_1_interact

_actor_turnip_1_interact::
        VM_RESERVE              7

        ; If Parameter 0 Equals 0
        VM_GET_TLOCAL           .LOCAL_TMP0_PARAM0_VALUE, 0
        VM_IF_CONST             .EQ, .LOCAL_TMP0_PARAM0_VALUE, 0, 1$, 0
        VM_JUMP                 2$
1$:
        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 0

        ; If Actor up Relative To Actor
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        VM_SET_CONST            .LOCAL_TMP2_OTHER_ACTOR, 1
        VM_ACTOR_GET_POS        .LOCAL_TMP2_OTHER_ACTOR
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_REF      ^/(.LOCAL_TMP2_OTHER_ACTOR + 2)/
            .R_OPERATOR .LT
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 3$, 1

        ; Variable Set To
        VM_SET_CONST            VAR_S5A5_DEFEATED, 1

        ; Variable Decrement By 1
        VM_RPN
            .R_REF      SYMBOL_11
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  SYMBOL_11
            .R_STOP

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 1

        ; Actor Set Collisions
        VM_ACTOR_SET_COLL_ENABLED .LOCAL_ACTOR, 0

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 1

        ; Actor Stop Update Script
        VM_ACTOR_TERMINATE_UPDATE .LOCAL_ACTOR

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 1

        ; Actor Set Animation State
        VM_ACTOR_SET_ANIM_SET   .LOCAL_ACTOR, STATE_EXPLODE
        VM_ACTOR_SET_FLAGS      .LOCAL_ACTOR, 0, .ACTOR_FLAG_ANIM_NOLOOP

        ; Player Bounce
        VM_SET_CONST_INT16      _plat_vel_y, -8192

        ; Wait 30 frames
        VM_SET_CONST            .LOCAL_TMP3_WAIT_ARGS, 30
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP3_WAIT_ARGS

        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        VM_JUMP                 4$
3$:
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

4$:

        ; Stop Script
        VM_STOP
2$:

        ; Stop Script
        VM_STOP
