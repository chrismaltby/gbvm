.module actor_1_update

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255


___bank_actor_1_update = 255
.globl ___bank_actor_1_update

_actor_1_update::
1$:
        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2
            .R_INT16    0
            .R_INT16    -1536
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_Y      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2
            .R_INT16    0
            .R_INT16    1536
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_Y      .ARG2, ^/(.ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Idle
        VM_IDLE

        VM_JUMP                 1$
        ; Stop Script
        VM_STOP
