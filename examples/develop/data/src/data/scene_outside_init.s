.module scene_outside_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_outside_init = 255
.globl ___bank_scene_outside_init

_scene_outside_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_outside_init$da5d7bc4_ae28_4992_ab12_dcdcb3e1055e$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$scene_outside_init$da5d7bc4_ae28_4992_ab12_dcdcb3e1055e$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        ; Timer Start
        VM_TIMER_PREPARE        1, ___bank_script_timer_0, _script_timer_0
        VM_TIMER_SET            1, 1

GBVM_END$scene_outside_init$da5d7bc4_ae28_4992_ab12_dcdcb3e1055e = .
.globl GBVM_END$scene_outside_init$da5d7bc4_ae28_4992_ab12_dcdcb3e1055e
GBVM$scene_outside_init$3b08bd04_281b_4503_ab76_20e52f029427$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$scene_outside_init$3b08bd04_281b_4503_ab76_20e52f029427$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        ; Input Script Attach
        VM_CONTEXT_PREPARE      1, ___bank_script_input_4, _script_input_4
        VM_INPUT_ATTACH         128, ^/(1 | .OVERRIDE_DEFAULT)/

GBVM_END$scene_outside_init$3b08bd04_281b_4503_ab76_20e52f029427 = .
.globl GBVM_END$scene_outside_init$3b08bd04_281b_4503_ab76_20e52f029427
GBVM$scene_outside_init$cb0440ac_447b_47e3_a8c7_ca61f54c9738$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$scene_outside_init$cb0440ac_447b_47e3_a8c7_ca61f54c9738$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        ; Input Script Attach
        VM_CONTEXT_PREPARE      3, ___bank_script_input_5, _script_input_5
        VM_INPUT_ATTACH         32, ^/(3 | .OVERRIDE_DEFAULT)/

GBVM_END$scene_outside_init$cb0440ac_447b_47e3_a8c7_ca61f54c9738 = .
.globl GBVM_END$scene_outside_init$cb0440ac_447b_47e3_a8c7_ca61f54c9738
GBVM$scene_outside_init$autofade$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$scene_outside_init$autofade$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
