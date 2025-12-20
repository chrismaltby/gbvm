.module scene_digits_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_digits_init = 255
.globl ___bank_scene_digits_init

_scene_digits_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_digits_init$autofade$04fc3521_5d48_4c5b_8d2b_3ac18309bc01$scene$04fc3521_5d48_4c5b_8d2b_3ac18309bc01$script = .
.globl GBVM$scene_digits_init$autofade$04fc3521_5d48_4c5b_8d2b_3ac18309bc01$scene$04fc3521_5d48_4c5b_8d2b_3ac18309bc01$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
