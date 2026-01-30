.module actor_scientist_update

.include "vm.i"
.include "data/game_globals.i"

.globl b_wait_frames, _wait_frames

.area _CODE_255

.LOCAL_ACTOR = -4
.LOCAL_TMP1_WAIT_ARGS = -5
.LOCAL_TMP2_WAIT_ARGS = -5
.LOCAL_TMP3_WAIT_ARGS = -5

___bank_actor_scientist_update = 255
.globl ___bank_actor_scientist_update

_actor_scientist_update::
        VM_RESERVE              5

1$:
        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2048
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    3072
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, 0
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, 0
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, 0

        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

        ; Wait 120 frames
        VM_SET_CONST            .LOCAL_TMP1_WAIT_ARGS, 120
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP1_WAIT_ARGS

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1536
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    3072
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST

        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

        ; Wait 120 frames
        VM_SET_CONST            .LOCAL_TMP2_WAIT_ARGS, 120
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP2_WAIT_ARGS

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1024
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    2560
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST

        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

        ; Wait 240 frames
        VM_SET_CONST            .LOCAL_TMP3_WAIT_ARGS, 240
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP3_WAIT_ARGS

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2048
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    3072
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, 0
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, 0
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, 0

        ; Idle
        VM_IDLE

        VM_JUMP                 1$
        ; Stop Script
        VM_STOP
