.module scene_parallax_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_parallax_init = 255
.globl ___bank_scene_parallax_init

_scene_parallax_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_parallax_init$autofade$88f214e9_8604_47da_97a3_8400850cde77$scene$88f214e9_8604_47da_97a3_8400850cde77$script = .
.globl GBVM$scene_parallax_init$autofade$88f214e9_8604_47da_97a3_8400850cde77$scene$88f214e9_8604_47da_97a3_8400850cde77$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
