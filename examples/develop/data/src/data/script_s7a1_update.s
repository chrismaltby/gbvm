.module script_s7a1_update

.include "vm.i"
.include "data/game_globals.i"

.globl b_wait_frames, _wait_frames

.area _CODE_255

.LOCAL_ACTOR = -4
.LOCAL_TMP1_WAIT_ARGS = -4
.LOCAL_TMP2_WAIT_ARGS = -6

___bank_script_s7a1_update = 255
.globl ___bank_script_s7a1_update

_script_s7a1_update::
        VM_RESERVE              6

1$:
        ; Variable L0 = VAR_S7A1_LAUNCHANGLE+8
        VM_RPN
            .R_REF      VAR_S7A1_LAUNCHANGLE
            .R_INT16    8
            .R_OPERATOR .ADD
            .R_STOP
        VM_SET                  VAR_S7A1_LAUNCHANGLE, .ARG0
        VM_POP                  1

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 2

        ; Launch Projectile In Angle
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    0
            .R_OPERATOR .ADD
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT16    -128
            .R_OPERATOR .ADD
            .R_REF      VAR_S7A1_LAUNCHANGLE
            .R_STOP
        VM_PUSH_CONST           .PROJECTILE_STRONG
        VM_PROJECTILE_LAUNCH    1, .ARG3
        VM_POP                  4

        ; Wait N Frames
        VM_SET_CONST            .LOCAL_TMP1_WAIT_ARGS, 60
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP1_WAIT_ARGS

        ; Wait N Frames
        VM_SET_CONST            .LOCAL_TMP2_WAIT_ARGS, 1
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP2_WAIT_ARGS

        VM_JUMP                 1$
        ; Stop Script
        VM_STOP
