.module scene_alt_player_sprite_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_alt_player_sprite_init = 255
.globl ___bank_scene_alt_player_sprite_init

_scene_alt_player_sprite_init::
        VM_LOCK

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
