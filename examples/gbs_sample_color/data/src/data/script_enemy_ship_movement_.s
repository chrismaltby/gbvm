.module script_enemy_ship_movement_

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.SCRIPT_ARG_0_ACTOR = -7
.LOCAL_ACTOR = -4

___bank_script_enemy_ship_movement_ = 255
.globl ___bank_script_enemy_ship_movement_

_script_enemy_ship_movement_::
        VM_RESERVE              4

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      .SCRIPT_ARG_0_ACTOR
            .R_INT16    -1024
            .R_INT16    -1024
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_XY     .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      .SCRIPT_ARG_0_ACTOR
            .R_INT16    1024
            .R_INT16    1024
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_XY     .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Set Active
        VM_SET                  .LOCAL_ACTOR, .SCRIPT_ARG_0_ACTOR

        ; Launch Projectile In Direction
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT16    192
            .R_STOP
        VM_PROJECTILE_LAUNCH    1, .ARG2
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      .SCRIPT_ARG_0_ACTOR
            .R_INT16    -1024
            .R_INT16    1024
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_XY     .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      .SCRIPT_ARG_0_ACTOR
            .R_INT16    1024
            .R_INT16    -1024
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .ARG2
        VM_ACTOR_MOVE_TO_XY     .ARG2, ^/(.ACTOR_ATTR_DIAGONAL | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        VM_RESERVE              -4
        VM_RET_FAR_N            1
