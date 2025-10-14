.module scene_underground_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_underground_init = 255
.globl ___bank_scene_underground_init

_scene_underground_init::
        VM_LOCK

        VM_RESERVE              4

        ; If
        ; -- If Falsy
        VM_IF_CONST             .EQ, SYMBOL_0, 0, 1$, 0
        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 6

        ; Actor Set Collisions
        VM_ACTOR_SET_COLL_ENABLED .LOCAL_ACTOR, 0

        VM_JUMP                 2$
1$:
        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 6
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

2$:

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Call Script: common/ui/Init Menu
        VM_CALL_FAR             ___bank_script_init_menu, _script_init_menu

        ; Music Play
        VM_MUSIC_PLAY           ___bank_song_rulz_undergroundcave_0_Data, _song_rulz_undergroundcave_0_Data, .MUSIC_NO_LOOP

        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, SYMBOL_15, 0, 3$, 0
        VM_JUMP                 4$
3$:
        ; Actor Set Position
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    6144
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    3840
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Position Actor
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_SET_POS        .LOCAL_ACTOR

4$:

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
