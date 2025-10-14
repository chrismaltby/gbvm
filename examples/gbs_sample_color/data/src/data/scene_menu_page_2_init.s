.module scene_menu_page_2_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step, _camera_settings

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_menu_page_2_init = 255
.globl ___bank_scene_menu_page_2_init

_scene_menu_page_2_init::
        VM_LOCK

        VM_RESERVE              4

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_5, 0, 1$, 0
        VM_JUMP                 2$
1$:
        ; Actor Set Animation Frame To
        ; -- Calculate value
        VM_RPN
            .R_INT16    1
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_SET_ANIM_FRAME .LOCAL_ACTOR

2$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_6, 0, 3$, 0
        VM_JUMP                 4$
3$:
        ; Actor Set Animation Frame To
        ; -- Calculate value
        VM_RPN
            .R_INT16    1
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_SET_ANIM_FRAME .LOCAL_ACTOR

4$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_7, 0, 5$, 0
        VM_JUMP                 6$
5$:
        ; Actor Set Animation Frame To
        ; -- Calculate value
        VM_RPN
            .R_INT16    1
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 3
        VM_ACTOR_SET_ANIM_FRAME .LOCAL_ACTOR

6$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_8, 0, 7$, 0
        VM_JUMP                 8$
7$:
        ; Actor Set Animation Frame To
        ; -- Calculate value
        VM_RPN
            .R_INT16    1
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 4
        VM_ACTOR_SET_ANIM_FRAME .LOCAL_ACTOR

8$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_9, 0, 9$, 0
        VM_JUMP                 10$
9$:
        ; Actor Set Animation Frame To
        ; -- Calculate value
        VM_RPN
            .R_INT16    1
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 5
        VM_ACTOR_SET_ANIM_FRAME .LOCAL_ACTOR

10$:

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Wait For Input
        VM_INPUT_WAIT           240

        ; Pop Scene State
        VM_SET_CONST_INT8       _fade_frames_per_step, 3
        VM_FADE_OUT             1
        VM_SET_CONST_INT8       _camera_settings, .CAMERA_LOCK
        VM_SCENE_POP

        ; Stop Script
        VM_STOP
        ; Stop Script
        VM_STOP
