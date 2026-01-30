.module actor_2_update

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_actor_2_update = 255
.globl ___bank_actor_2_update

_actor_2_update::
        VM_RESERVE              4

1$:
        ; If
        ; -- If Falsy
        VM_IF_CONST             .EQ, VAR_S0A0_KILLED_2, 0, 2$, 0
        VM_JUMP                 3$
2$:
        ; Variable Set To Random
        VM_RAND                 VAR_S0A2_RAND_X, 0, 19

        ; Variable Set To Random
        VM_RAND                 VAR_S0A2_RAND_Y, 1, 17

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      VAR_S0A2_RAND_X
            .R_INT16    8
            .R_OPERATOR .SHL
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_REF      VAR_S0A2_RAND_Y
            .R_INT16    8
            .R_OPERATOR .SHL
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 3
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/

3$:

        VM_IDLE

        ; Idle
        VM_IDLE

        VM_JUMP                 1$
        ; Stop Script
        VM_STOP
