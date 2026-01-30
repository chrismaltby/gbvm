.module trigger_9_interact

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_trigger_9_interact = 255
.globl ___bank_trigger_9_interact

_trigger_9_interact::
        VM_LOCK

        VM_RESERVE              4

        ; If
        ; -- If Falsy
        VM_IF_CONST             .EQ, SYMBOL_9, 0, 1$, 0
        VM_JUMP                 2$
1$:
        ; If Actor At Position
        VM_SET_CONST            .LOCAL_ACTOR, 8
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    47
            .R_OPERATOR .EQ
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    25
            .R_OPERATOR .EQ
            .R_OPERATOR .AND
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 3$, 1

        VM_JUMP                 4$
3$:
        ; Actor Set Direction To
        VM_SET_CONST            .LOCAL_ACTOR, 8
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_UP

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 8

        ; Actor Emote
        VM_ACTOR_EMOTE          .LOCAL_ACTOR, ___bank_emote_shock, _emote_shock

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    10752
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    7680
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 8
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, 0
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, 0
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, 0

        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    12032
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    6400
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 8
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST

4$:

2$:

        ; Stop Script
        VM_STOP
