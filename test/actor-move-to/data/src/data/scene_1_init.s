.module scene_1_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_1_init = 255
.globl ___bank_scene_1_init

_scene_1_init::
        VM_LOCK

        VM_RESERVE              4

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1024
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    256
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1024
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    1280
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2048
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    1280
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1024
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    768
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 3
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    1280
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 4
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_DIAGONAL)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_XY     .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_DIAGONAL)/

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    4
            .R_INT16    2048
            .R_INT16    -2048
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_XY     .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    5
            .R_INT16    -1280
            .R_INT16    0
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    6
            .R_INT16    -1280
            .R_INT16    -7680
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_Y      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    7
            .R_INT16    1280
            .R_INT16    -1280
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_Y      .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    2048
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 8
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_H_FIRST)/

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    8
            .R_INT16    0
            .R_INT16    512
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_Y      .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    8
            .R_INT16    1280
            .R_INT16    -1280
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_XY     .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    9
            .R_INT16    256
            .R_INT16    0
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        VM_TEST_TERMINATE .TEST_WAIT_VBL

        ; Stop Script
        VM_STOP
