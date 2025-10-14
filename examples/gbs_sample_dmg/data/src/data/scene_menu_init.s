.module scene_menu_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step, _camera_settings

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_menu_init = 255
.globl ___bank_scene_menu_init

_scene_menu_init::
        VM_LOCK

        VM_RESERVE              4

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_3, 0, 1$, 0
        VM_JUMP                 2$
1$:
        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

2$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_4, 0, 7$, 0
        VM_JUMP                 8$
7$:
        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

8$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_5, 0, 13$, 0
        VM_JUMP                 14$
13$:
        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 3
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

14$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_6, 0, 19$, 0
        VM_JUMP                 20$
19$:
        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 4
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

20$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_7, 0, 25$, 0
        VM_JUMP                 26$
25$:
        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 5
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

26$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_8, 0, 31$, 0
        VM_JUMP                 32$
31$:
        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 6
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

32$:

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
