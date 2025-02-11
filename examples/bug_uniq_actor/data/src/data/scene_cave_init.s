.module scene_cave_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_cave_init = 255
.globl ___bank_scene_cave_init

_scene_cave_init::
        VM_LOCK

        ; Timer Start
        VM_TIMER_PREPARE        1, ___bank_script_timer, _script_timer
        VM_TIMER_SET            1, 1

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
