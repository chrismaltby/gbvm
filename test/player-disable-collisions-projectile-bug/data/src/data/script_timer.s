.module script_timer

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255


___bank_script_timer = 255
.globl ___bank_script_timer

_script_timer::
        ; Draw Text
        VM_SWITCH_TEXT_LAYER    .TEXT_LAYER_BKG
        VM_LOAD_TEXT            0
        .asciz "\003\002\002\001\001SUCCESS"
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_NONMODAL, .UI_WAIT_TEXT
        VM_SWITCH_TEXT_LAYER    .TEXT_LAYER_WIN

        VM_TEST_TERMINATE .TEST_WAIT_VBL

        ; Stop Script
        VM_STOP
