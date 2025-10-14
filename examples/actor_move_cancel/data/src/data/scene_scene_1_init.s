.module scene_scene_1_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_scene_1_init = 255
.globl ___bank_scene_scene_1_init

_scene_scene_1_init::
        VM_LOCK

        ; Variable Set To
        VM_SET_CONST            VAR_S0A0_KILLED, 0

        ; Variable Set To
        VM_SET_CONST            VAR_S0A0_KILLED_1, 0

        ; Variable Set To
        VM_SET_CONST            VAR_S0A0_KILLED_2, 0

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Input Script Attach
        VM_CONTEXT_PREPARE      3, ___bank_script_input, _script_input
        VM_INPUT_ATTACH         32, ^/(3 | .OVERRIDE_DEFAULT)/

        ; Input Script Attach
        VM_CONTEXT_PREPARE      1, ___bank_script_input_0, _script_input_0
        VM_INPUT_ATTACH         128, ^/(1 | .OVERRIDE_DEFAULT)/

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
