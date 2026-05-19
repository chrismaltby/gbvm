.module script_input

.include "vm.i"
.include "data/game_globals.i"

.globl b_wait_frames, _wait_frames

.area _CODE_255

.LOCAL_ACTOR = -4
.LOCAL_TMP1_WAIT_ARGS = -4

___bank_script_input = 255
.globl ___bank_script_input

_script_input::
        VM_RESERVE              4

GBVM$script_input$6a30cb29_4cd4_47e3_984e_a7371cbdd736$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script = .
.globl GBVM$script_input$6a30cb29_4cd4_47e3_984e_a7371cbdd736$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script
        ; Load Projectile Into Slot
        VM_PROJECTILE_LOAD_TYPE 0, 0, ___bank_global_projectiles_0, _global_projectiles_0

GBVM$script_input$33de16ef_29b9_4413_a15a_fe8b2cde028a$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script = .
.globl GBVM$script_input$33de16ef_29b9_4413_a15a_fe8b2cde028a$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script
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

GBVM$script_input$3f41d6a5_79cb_4fee_8a55_c4017a725066$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script = .
.globl GBVM$script_input$3f41d6a5_79cb_4fee_8a55_c4017a725066$8e4f1f9d_d4ea_4e79_89c6_25a388370165$scene$8e4f1f9d_d4ea_4e79_89c6_25a388370165$script
        ; Wait 30 frames
        VM_SET_CONST            .LOCAL_TMP1_WAIT_ARGS, 30
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP1_WAIT_ARGS

        ; Stop Script
        VM_STOP
