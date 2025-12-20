.module scene_underground_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_underground_init = 255
.globl ___bank_scene_underground_init

_scene_underground_init::
        VM_LOCK

        VM_RESERVE              4

GBVM$scene_underground_init$b1d1a0dd_3c32_4881_ad85_a1cb42386bf4$3509d273_bf7e_4946_89ce_a489df5a449d$actor$a65cba5e_5d01_4f02_b32c_ed99c9276ad3$startScript = .
.globl GBVM$scene_underground_init$b1d1a0dd_3c32_4881_ad85_a1cb42386bf4$3509d273_bf7e_4946_89ce_a489df5a449d$actor$a65cba5e_5d01_4f02_b32c_ed99c9276ad3$startScript
        ; If
        ; -- If Falsy
        VM_IF_CONST             .EQ, VAR_QUEST2, 0, 1$, 0
GBVM$scene_underground_init$a07c58fa_1126_4da4_adef_cc15a74d2a3a$3509d273_bf7e_4946_89ce_a489df5a449d$actor$a65cba5e_5d01_4f02_b32c_ed99c9276ad3$startScript = .
.globl GBVM$scene_underground_init$a07c58fa_1126_4da4_adef_cc15a74d2a3a$3509d273_bf7e_4946_89ce_a489df5a449d$actor$a65cba5e_5d01_4f02_b32c_ed99c9276ad3$startScript
        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 6

        ; Actor Set Collisions
        VM_ACTOR_SET_COLL_ENABLED .LOCAL_ACTOR, 0

        VM_JUMP                 2$
1$:
GBVM$scene_underground_init$0a586506_2101_49ce_b244_cbe2df8b39a0$3509d273_bf7e_4946_89ce_a489df5a449d$actor$a65cba5e_5d01_4f02_b32c_ed99c9276ad3$startScript = .
.globl GBVM$scene_underground_init$0a586506_2101_49ce_b244_cbe2df8b39a0$3509d273_bf7e_4946_89ce_a489df5a449d$actor$a65cba5e_5d01_4f02_b32c_ed99c9276ad3$startScript
        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 6
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

2$:

GBVM_END$scene_underground_init$b1d1a0dd_3c32_4881_ad85_a1cb42386bf4 = .
.globl GBVM_END$scene_underground_init$b1d1a0dd_3c32_4881_ad85_a1cb42386bf4
        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_underground_init$02ae19dc_29ba_438b_9437_712f79c5c758$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script = .
.globl GBVM$scene_underground_init$02ae19dc_29ba_438b_9437_712f79c5c758$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script
        ; Call Script: Init Menu
        VM_CALL_FAR             ___bank_script_init_menu, _script_init_menu

GBVM$scene_underground_init$4434a78c_23e6_464a_9b03_916b537343e9$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script = .
.globl GBVM$scene_underground_init$4434a78c_23e6_464a_9b03_916b537343e9$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script
GBVM$scene_underground_init$648db27d_c819_42ea_9acb_45e2e4a54857$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script = .
.globl GBVM$scene_underground_init$648db27d_c819_42ea_9acb_45e2e4a54857$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script
        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, VAR_PUSHED_ICE_BLOCK, 0, 3$, 0
        VM_JUMP                 4$
3$:
GBVM$scene_underground_init$1b7fb9ee_e8d1_450e_99e3_265dfbb2b1dd$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script = .
.globl GBVM$scene_underground_init$1b7fb9ee_e8d1_450e_99e3_265dfbb2b1dd$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script
        ; Actor Set Position
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    6144
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    3840
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Position Actor
        VM_SET_CONST            .LOCAL_ACTOR, 2
        VM_ACTOR_SET_POS        .LOCAL_ACTOR

4$:

GBVM_END$scene_underground_init$648db27d_c819_42ea_9acb_45e2e4a54857 = .
.globl GBVM_END$scene_underground_init$648db27d_c819_42ea_9acb_45e2e4a54857
GBVM_END$scene_underground_init$4434a78c_23e6_464a_9b03_916b537343e9 = .
.globl GBVM_END$scene_underground_init$4434a78c_23e6_464a_9b03_916b537343e9
GBVM$scene_underground_init$autofade$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script = .
.globl GBVM$scene_underground_init$autofade$3509d273_bf7e_4946_89ce_a489df5a449d$scene$3509d273_bf7e_4946_89ce_a489df5a449d$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
