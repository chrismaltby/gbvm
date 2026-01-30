.module trigger_4_interact

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.LOCAL_TMP0_IS_CGB = -4
.LOCAL_ACTOR = -4

___bank_trigger_4_interact = 255
.globl ___bank_trigger_4_interact

_trigger_4_interact::
        VM_LOCK

        VM_RESERVE              4

        ; If Color Supported
        VM_GET_UINT8            .LOCAL_TMP0_IS_CGB, __is_CGB
        VM_IF_CONST             .NE, .LOCAL_TMP0_IS_CGB, 1, 1$, 0

        VM_JUMP                 2$
1$:
        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

2$:

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    0
            .R_INT16    768
            .R_INT16    0
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Activate
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_ACTIVATE       .LOCAL_ACTOR

        ; Stop Script
        VM_STOP
