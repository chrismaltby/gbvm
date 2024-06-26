.module script_s0a1_update

.include "vm.i"
.include "data/game_globals.i"

.globl b_wait_frames, _wait_frames

.area _CODE_255

ACTOR = -4

___bank_script_s0a1_update = 255
.globl ___bank_script_s0a1_update

_script_s0a1_update::
        ; Local Actor
        VM_PUSH_CONST           0
        VM_PUSH_CONST           0
        VM_PUSH_CONST           0
        VM_PUSH_CONST           0

2$:
        ; Actor Set Active
        VM_SET_CONST            ACTOR, 2

        ; Actor Move Relative
        VM_ACTOR_GET_POS        ACTOR
        VM_RPN
            .R_REF      ^/(ACTOR + 1)/
            .R_INT16    256
            .R_OPERATOR .ADD
            .R_REF      ^/(ACTOR + 2)/
            .R_INT16    384
            .R_OPERATOR .ADD
            .R_STOP
        VM_SET                  ^/(ACTOR + 1 - 2)/, .ARG1
        VM_SET                  ^/(ACTOR + 2 - 2)/, .ARG0
        VM_POP                  2
        VM_SET_CONST            ^/(ACTOR + 3)/, 0
        VM_ACTOR_MOVE_TO        ACTOR

        ; Actor Set Active
        VM_SET_CONST            ACTOR, 2

        ; Actor Move Relative
        VM_ACTOR_GET_POS        ACTOR
        VM_RPN
            .R_REF      ^/(ACTOR + 1)/
            .R_INT16    -256
            .R_OPERATOR .ADD
            .R_REF      ^/(ACTOR + 2)/
            .R_INT16    -384
            .R_OPERATOR .ADD
            .R_STOP
        VM_SET                  ^/(ACTOR + 1 - 2)/, .ARG1
        VM_SET                  ^/(ACTOR + 2 - 2)/, .ARG0
        VM_POP                  2
        VM_SET_CONST            ^/(ACTOR + 3)/, 0
        VM_ACTOR_MOVE_TO        ACTOR

        ; Wait 1 Frame
        VM_PUSH_CONST           1
        VM_INVOKE               b_wait_frames, _wait_frames, 1, .ARG0

        VM_JUMP                 2$
        ; Stop Script
        VM_STOP
