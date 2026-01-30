.module scene_transition_init

.include "vm.i"
.include "data/game_globals.i"
.include "macro.i"

.globl _fade_frames_per_step, _camera_settings, ___bank_scene_east, _scene_east, ___bank_scene_west, _scene_west

.area _CODE_255

.LOCAL_ACTOR = -4
.LOCAL_TMP7_ACTOR_POS = -4
.LOCAL_TMP1_ACTOR_DIR = -8
.LOCAL_TMP2_CAMERA_MOVE_ARGS = -8
.LOCAL_TMP3_CAMERA_MOVE_ARGS = -8
.LOCAL_TMP4_ACTOR_POS = -8
.LOCAL_TMP5_CAMERA_MOVE_ARGS = -8
.LOCAL_TMP6_CAMERA_MOVE_ARGS = -8

___bank_scene_transition_init = 255
.globl ___bank_scene_transition_init

_scene_transition_init::
        VM_LOCK

        VM_RESERVE              8

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; If Actor Facing Direction
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_GET_DIR        .LOCAL_ACTOR, .LOCAL_TMP1_ACTOR_DIR
        ; -- Calculate value
        VM_RPN
            .R_INT16    .DIR_RIGHT
            .R_STOP
        VM_IF                   .NE, ^/(.LOCAL_TMP1_ACTOR_DIR - 1)/, .ARG0, 1$, 1

        ; Camera Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2560
            .R_REF_SET  .LOCAL_TMP2_CAMERA_MOVE_ARGS
            .R_INT16    2304
            .R_REF_SET  ^/(.LOCAL_TMP2_CAMERA_MOVE_ARGS + 1)/
            .R_STOP
        ; -- Move Camera
        VM_CAMERA_SET_POS       .LOCAL_TMP2_CAMERA_MOVE_ARGS

        ; Camera Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    7680
            .R_REF_SET  .LOCAL_TMP3_CAMERA_MOVE_ARGS
            .R_INT16    2304
            .R_REF_SET  ^/(.LOCAL_TMP3_CAMERA_MOVE_ARGS + 1)/
            .R_STOP
        ; -- Move Camera
        VM_CAMERA_MOVE_TO       .LOCAL_TMP3_CAMERA_MOVE_ARGS, 32, .CAMERA_UNLOCK

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_INT16    768
            .R_INT16    0
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Load Scene
        ; -- Fetch player actorPosition
        VM_SET_CONST            .LOCAL_TMP4_ACTOR_POS, 0
        VM_ACTOR_GET_POS        .LOCAL_TMP4_ACTOR_POS
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    256
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_REF      ^/(.LOCAL_TMP4_ACTOR_POS + 2)/
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_RIGHT
        VM_SET_CONST_INT8       _camera_settings, .CAMERA_LOCK
        VM_RAISE                EXCEPTION_CHANGE_SCENE, 3
            IMPORT_FAR_PTR_DATA _scene_east

        VM_JUMP                 2$
1$:
        ; Camera Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    7680
            .R_REF_SET  .LOCAL_TMP5_CAMERA_MOVE_ARGS
            .R_INT16    2304
            .R_REF_SET  ^/(.LOCAL_TMP5_CAMERA_MOVE_ARGS + 1)/
            .R_STOP
        ; -- Move Camera
        VM_CAMERA_SET_POS       .LOCAL_TMP5_CAMERA_MOVE_ARGS

        ; Camera Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2560
            .R_REF_SET  .LOCAL_TMP6_CAMERA_MOVE_ARGS
            .R_INT16    2304
            .R_REF_SET  ^/(.LOCAL_TMP6_CAMERA_MOVE_ARGS + 1)/
            .R_STOP
        ; -- Move Camera
        VM_CAMERA_MOVE_TO       .LOCAL_TMP6_CAMERA_MOVE_ARGS, 32, .CAMERA_UNLOCK

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_INT16    -768
            .R_INT16    0
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Load Scene
        ; -- Fetch player actorPosition
        VM_SET_CONST            .LOCAL_TMP7_ACTOR_POS, 0
        VM_ACTOR_GET_POS        .LOCAL_TMP7_ACTOR_POS
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    4352
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_REF      ^/(.LOCAL_TMP7_ACTOR_POS + 2)/
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_LEFT
        VM_SET_CONST_INT8       _camera_settings, .CAMERA_LOCK
        VM_RAISE                EXCEPTION_CHANGE_SCENE, 3
            IMPORT_FAR_PTR_DATA _scene_west

2$:

        ; Stop Script
        VM_STOP
