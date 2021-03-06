.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255



___bank_script_s0a5_interact = 255
.globl ___bank_script_s0a5_interact

_script_s0a5_interact::

        VM_LOCK

        VM_RAISE                EXCEPTION_SAVE, 1
            .SAVE_SLOT 0

        VM_PUSH_CONST           0    
        VM_POLL_LOADED          .ARG0
        VM_IF_CONST     .EQ     .ARG0, 1, 1$, 1

        ; Text Dialogue
        VM_LOAD_TEXT            0
        .asciz "Game was saved!\nIt is now safe to\nturn off game boy."
        VM_OVERLAY_CLEAR        0, 0, 20, 5, .UI_COLOR_WHITE, .UI_DRAW_FRAME
        VM_OVERLAY_MOVE_TO      0, 13, .OVERLAY_TEXT_IN_SPEED
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_TEXT_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

1$:
        ; Stop Script
        VM_STOP
