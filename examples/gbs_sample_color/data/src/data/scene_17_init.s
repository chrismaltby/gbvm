.module scene_17_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_17_init = 255
.globl ___bank_scene_17_init

_scene_17_init::
        VM_LOCK

        ; Music Stop
        VM_MUSIC_STOP

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
