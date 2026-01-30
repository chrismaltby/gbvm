.module trigger_13_interact

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_trigger_13_interact = 255
.globl ___bank_trigger_13_interact

_trigger_13_interact::
        VM_LOCK

        VM_RESERVE              4

        ; Actor Activate
        VM_SET_CONST            .LOCAL_ACTOR, 9
        VM_ACTOR_ACTIVATE       .LOCAL_ACTOR

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    9
            .R_INT16    0
            .R_INT16    256
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_Y      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 9
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_LEFT

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 9

        ; Actor Emote
        VM_ACTOR_EMOTE          .LOCAL_ACTOR, ___bank_emote_shock, _emote_shock

        ; Text Dialogue
        VM_OVERLAY_CLEAR        0, 0, 20, 5, .UI_COLOR_WHITE, .UI_DRAW_FRAME
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_SPEED_INSTANT
        VM_OVERLAY_MOVE_TO      0, 13, .OVERLAY_IN_SPEED
        VM_OVERLAY_SET_SCROLL   1, 1, 18, 5, .UI_COLOR_WHITE
        VM_LOAD_TEXT            0
        .asciz "HEY!!!\012KEEP OFF MY\012FLOWERS!"
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_INT16    -512
            .R_INT16    0
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_RIGHT

        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 9
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 9

        ; Actor Emote
        VM_ACTOR_EMOTE          .LOCAL_ACTOR, ___bank_emote_anger, _emote_anger

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    9
            .R_INT16    0
            .R_INT16    -256
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_Y      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 9
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        ; Variable Set To
        VM_SET_CONST            SYMBOL_5, 1

        ; Stop Script
        VM_STOP
