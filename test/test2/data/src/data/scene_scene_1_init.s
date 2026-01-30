.module scene_scene_1_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_scene_1_init = 255
.globl ___bank_scene_scene_1_init

_scene_scene_1_init::
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
            .R_INT16    512
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    1536
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/

        ; Stop Script
        VM_STOP
