.module scene_path_to_sample_town_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_path_to_sample_town_init = 255
.globl ___bank_scene_path_to_sample_town_init

_scene_path_to_sample_town_init::
        VM_LOCK

        VM_RESERVE              4

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, VAR_S5A5_DEFEATED, 0, 1$, 0
        VM_JUMP                 2$
1$:
        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        ; Actor Set Position
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Position Actor
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_SET_POS        .LOCAL_ACTOR

2$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, VAR_S5A5_DEFEATED_1, 0, 3$, 0
        VM_JUMP                 4$
3$:
        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 3
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        ; Actor Set Position
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Position Actor
        VM_SET_CONST            .LOCAL_ACTOR, 3
        VM_ACTOR_SET_POS        .LOCAL_ACTOR

4$:

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, VAR_S5A5_DEFEATED_2, 0, 5$, 0
        VM_JUMP                 6$
5$:
        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 4
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        ; Actor Set Position
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    0
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Position Actor
        VM_SET_CONST            .LOCAL_ACTOR, 4
        VM_ACTOR_SET_POS        .LOCAL_ACTOR

6$:

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Call Script: common/ui/Init Menu
        VM_CALL_FAR             ___bank_script_init_menu, _script_init_menu

        ; Music Play
        VM_MUSIC_PLAY           ___bank_song_rulz_outside_0_Data, _song_rulz_outside_0_Data, .MUSIC_NO_LOOP

        ; Variable Set To
        VM_SET_CONST            SYMBOL_11, 3

        ; If Actor At Position
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_OPERATOR .AND
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 7$, 1

        ; Variable Decrement By 1
        VM_RPN
            .R_REF      SYMBOL_11
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  SYMBOL_11
            .R_STOP

        VM_JUMP                 8$
7$:
8$:

        ; If Actor At Position
        VM_SET_CONST            .LOCAL_ACTOR, 3
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_OPERATOR .AND
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 9$, 1

        ; Variable Decrement By 1
        VM_RPN
            .R_REF      SYMBOL_11
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  SYMBOL_11
            .R_STOP

        VM_JUMP                 10$
9$:
10$:

        ; If Actor At Position
        VM_SET_CONST            .LOCAL_ACTOR, 4
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_OPERATOR .AND
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 11$, 1

        ; Variable Decrement By 1
        VM_RPN
            .R_REF      SYMBOL_11
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  SYMBOL_11
            .R_STOP

        VM_JUMP                 12$
11$:
12$:

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
