.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255



___bank_script_custom_0 = 255
.globl ___bank_script_custom_0

_script_custom_0::
        ; Text Dialogue
        VM_LOAD_TEXT            0
        .asciz "Hello World"
        VM_OVERLAY_CLEAR        0, 0, 20, 3, .UI_COLOR_WHITE, .UI_DRAW_FRAME
        VM_OVERLAY_MOVE_TO      0, 15, .OVERLAY_TEXT_IN_SPEED
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_TEXT_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

        VM_RET_FAR
