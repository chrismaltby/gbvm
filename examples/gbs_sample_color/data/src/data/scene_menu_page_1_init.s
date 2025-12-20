.module scene_menu_page_1_init

.include "vm.i"
.include "data/game_globals.i"
.include "macro.i"

.globl _fade_frames_per_step, _camera_settings, ___bank_scene_menu_page_2, _scene_menu_page_2

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_menu_page_1_init = 255
.globl ___bank_scene_menu_page_1_init

_scene_menu_page_1_init::
        VM_LOCK

        VM_RESERVE              4

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL, 0, 1$, 0
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
        VM_IF_CONST             .NE, SYMBOL_0, 0, 3$, 0
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
        VM_IF_CONST             .NE, SYMBOL_1, 0, 5$, 0
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
        VM_IF_CONST             .NE, SYMBOL_2, 0, 7$, 0
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
        VM_IF_CONST             .NE, SYMBOL_3, 0, 9$, 0
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

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_4, 0, 11$, 0
        VM_JUMP                 12$
11$:
        ; Actor Set Animation Frame To
        ; -- Calculate value
        VM_RPN
            .R_INT16    1
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 6
        VM_ACTOR_SET_ANIM_FRAME .LOCAL_ACTOR

12$:

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        ; Music Play
        VM_MUSIC_PLAY           ___bank_song_rulz_pause_underground_0_Data, _song_rulz_pause_underground_0_Data, .MUSIC_NO_LOOP

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Wait For Input
        VM_INPUT_WAIT           240

        ; Load Scene
        VM_SET_CONST_INT8       _fade_frames_per_step, 3
        VM_FADE_OUT             1
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_DOWN
        VM_SET_CONST_INT8       _camera_settings, .CAMERA_LOCK
        VM_RAISE                EXCEPTION_CHANGE_SCENE, 3
            IMPORT_FAR_PTR_DATA _scene_menu_page_2

        ; Stop Script
        VM_STOP
