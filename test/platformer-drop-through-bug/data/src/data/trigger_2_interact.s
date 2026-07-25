.module trigger_2_interact

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255


___bank_trigger_2_interact = 255
.globl ___bank_trigger_2_interact

_trigger_2_interact::
        VM_LOCK

        ; Draw Text
        VM_SWITCH_TEXT_LAYER    .TEXT_LAYER_BKG
        VM_LOAD_TEXT            0
        .asciz "\003\002\002\001\001FAIL LEFT"
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_NONMODAL, .UI_WAIT_TEXT
        VM_SWITCH_TEXT_LAYER    .TEXT_LAYER_WIN

        VM_TEST_TERMINATE .TEST_WAIT_VBL

        ; Stop Script
        VM_STOP
