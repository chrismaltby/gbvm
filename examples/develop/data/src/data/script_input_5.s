.module script_input_5

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_script_input_5 = 255
.globl ___bank_script_input_5

_script_input_5::
        VM_RESERVE              4

GBVM$script_input_5$73f350f4_6f18_4ace_a7d4_bbbc8a139403$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$script_input_5$73f350f4_6f18_4ace_a7d4_bbbc8a139403$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 0

        ; Launch Projectile In Source Actor Direction
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT16    0
            .R_STOP
        VM_ACTOR_GET_ANGLE      ^/(.LOCAL_ACTOR - 3)/, .ARG0
        VM_PROJECTILE_LAUNCH    0, .ARG2
        VM_POP                  3

        ; Stop Script
        VM_STOP
