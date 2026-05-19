.module scene_1_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_1_init = 255
.globl ___bank_scene_1_init

_scene_1_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_1_init$854f43ba_dd50_4e14_8706_386e9c998a6f$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script = .
.globl GBVM$scene_1_init$854f43ba_dd50_4e14_8706_386e9c998a6f$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script
        ; Input Script Attach
        VM_CONTEXT_PREPARE      3, ___bank_script_input, _script_input
        VM_INPUT_ATTACH         32, ^/(3 | .OVERRIDE_DEFAULT)/

GBVM_END$scene_1_init$854f43ba_dd50_4e14_8706_386e9c998a6f = .
.globl GBVM_END$scene_1_init$854f43ba_dd50_4e14_8706_386e9c998a6f
GBVM$scene_1_init$autofade$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script = .
.globl GBVM$scene_1_init$autofade$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script
        ; Idle
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
