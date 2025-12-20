.module scene_scene_1_init

.include "vm.i"
.include "data/game_globals.i"

.globl _text_ff_joypad, _text_draw_speed, _text_out_speed, _text_in_speed, _fade_frames_per_step

.area _CODE_255


___bank_scene_scene_1_init = 255
.globl ___bank_scene_scene_1_init

_scene_scene_1_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

        ; Text Set Animation Speed
        VM_SET_CONST_INT8       _text_ff_joypad, 1
        VM_SET_CONST_INT8       _text_draw_speed, 0
        VM_SET_CONST_INT8       _text_out_speed, .OVERLAY_SPEED_INSTANT
        VM_SET_CONST_INT8       _text_in_speed, .OVERLAY_SPEED_INSTANT

        ; Input Script Attach
        VM_CONTEXT_PREPARE      3, ___bank_script_input, _script_input
        VM_INPUT_ATTACH         32, ^/(3 | .OVERRIDE_DEFAULT)/

        ; Variable Set To
        VM_SET_CONST            VAR_STRING_0_, 1

        ; Variable Set To
        VM_SET_CONST            VAR_STRING_1_, 1

        ; Variable Set To
        VM_SET_CONST            VAR_STRING_2_, 1

        ; Variable Set To
        VM_SET_CONST            VAR_STRING_3_, 1

        ; Variable Set To
        VM_SET_CONST            VAR_STRING_4_, 1

        ; Call Script: Update Input Fields
        VM_CALL_FAR             ___bank_script_update_input_fields, _script_update_input_fields

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
