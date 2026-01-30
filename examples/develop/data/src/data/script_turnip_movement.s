.module script_turnip_movement

.include "vm.i"
.include "data/game_globals.i"

.globl b_wait_frames, _wait_frames

.area _CODE_255

.SCRIPT_ARG_0_ACTOR = -10
.LOCAL_ACTOR = -4
.LOCAL_TMP2_WAIT_ARGS = -4
.LOCAL_TMP1_OTHER_ACTOR = -7

___bank_script_turnip_movement = 255
.globl ___bank_script_turnip_movement

_script_turnip_movement::
        VM_RESERVE              7

GBVM$script_turnip_movement$15904eb6_30ec_4787_a7e9_013046f9d182$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$updateScript = .
.globl GBVM$script_turnip_movement$15904eb6_30ec_4787_a7e9_013046f9d182$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$updateScript
        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 0

        ; If Actor left Relative To Actor
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        VM_SET                  .LOCAL_TMP1_OTHER_ACTOR, .SCRIPT_ARG_0_ACTOR
        VM_ACTOR_GET_POS        .LOCAL_TMP1_OTHER_ACTOR
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_REF      ^/(.LOCAL_TMP1_OTHER_ACTOR + 1)/
            .R_OPERATOR .LT
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 1$, 1

GBVM$script_turnip_movement$753e2e8a_a98d_4a66_b326_b1c61a019237$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$updateScript = .
.globl GBVM$script_turnip_movement$753e2e8a_a98d_4a66_b326_b1c61a019237$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$updateScript
        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      .SCRIPT_ARG_0_ACTOR
            .R_INT16    -1024
            .R_INT16    0
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

        VM_JUMP                 2$
1$:
GBVM$script_turnip_movement$d565478e_995d_48f4_bbbe_7848a86b71a5$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$updateScript = .
.globl GBVM$script_turnip_movement$d565478e_995d_48f4_bbbe_7848a86b71a5$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$updateScript
        ; Actor Move Relative
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      .SCRIPT_ARG_0_ACTOR
            .R_INT16    1024
            .R_INT16    0
            .R_STOP
        ; -- Move Actor
        VM_ACTOR_MOVE_TO_INIT   .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .ARG2
        VM_ACTOR_MOVE_TO_X      .ARG2, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST | .ACTOR_ATTR_RELATIVE_SNAP_TILE)/
        VM_POP                  3

2$:

GBVM_END$script_turnip_movement$15904eb6_30ec_4787_a7e9_013046f9d182 = .
.globl GBVM_END$script_turnip_movement$15904eb6_30ec_4787_a7e9_013046f9d182
GBVM$script_turnip_movement$19eacd42_ec0b_4def_ac07_68c79e1b675f$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$updateScript = .
.globl GBVM$script_turnip_movement$19eacd42_ec0b_4def_ac07_68c79e1b675f$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$updateScript
        ; Wait 60 frames
        VM_SET_CONST            .LOCAL_TMP2_WAIT_ARGS, 60
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP2_WAIT_ARGS

        VM_RESERVE              -7
        VM_RET_FAR_N            1
