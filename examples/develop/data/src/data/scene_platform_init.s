.module scene_platform_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_platform_init = 255
.globl ___bank_scene_platform_init

_scene_platform_init::
        VM_LOCK

        VM_RESERVE              4

GBVM$scene_platform_init$b4ae3fd9_1713_4957_9133_a4eddcdbf9d6$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$startScript = .
.globl GBVM$scene_platform_init$b4ae3fd9_1713_4957_9133_a4eddcdbf9d6$f8f027ef_b818_4038_9eda_0ac477facb41$actor$98159e3a_0bfe_44ec_8312_9dcef04c253f$startScript
        ; Call Script: Turnip Init
        VM_PUSH_CONST           1 ; Actor 0
        VM_PUSH_REFERENCE       VAR_S5A5_DEFEATED ; Variable V1
        VM_CALL_FAR             ___bank_script_turnip_init, _script_turnip_init

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_platform_init$192c2a18_2d20_48b7_9d6f_83e8eb407b82$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$192c2a18_2d20_48b7_9d6f_83e8eb407b82$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; Call Script: Init Menu
        VM_CALL_FAR             ___bank_script_init_menu, _script_init_menu

GBVM$scene_platform_init$8ee11d7f_7d70_47b2_b1a2_9866c27011d2$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$8ee11d7f_7d70_47b2_b1a2_9866c27011d2$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; Variable Set To
        VM_SET_CONST            VAR_TURNIP_COUNTER, 3

GBVM$scene_platform_init$f4aed9cd_2832_499e_896b_ab9e919236bb$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$f4aed9cd_2832_499e_896b_ab9e919236bb$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; If Actor At Position
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_OPERATOR .AND
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 1$, 1

GBVM$scene_platform_init$76b7e86d_5ac4_4efb_aa25_a211f94a792d$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$76b7e86d_5ac4_4efb_aa25_a211f94a792d$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; Variable Decrement By 1
        VM_RPN
            .R_REF      VAR_TURNIP_COUNTER
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  VAR_TURNIP_COUNTER
            .R_STOP

        VM_JUMP                 2$
1$:
2$:

GBVM_END$scene_platform_init$f4aed9cd_2832_499e_896b_ab9e919236bb = .
.globl GBVM_END$scene_platform_init$f4aed9cd_2832_499e_896b_ab9e919236bb
GBVM$scene_platform_init$1c50e8c3_c2a1_4761_ac8d_6846e95e506b$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$1c50e8c3_c2a1_4761_ac8d_6846e95e506b$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; If Actor At Position
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_OPERATOR .AND
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 3$, 1

GBVM$scene_platform_init$4c3ab6a3_9ac9_4ebd_89de_423a9fdaa0a4$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$4c3ab6a3_9ac9_4ebd_89de_423a9fdaa0a4$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; Variable Decrement By 1
        VM_RPN
            .R_REF      VAR_TURNIP_COUNTER
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  VAR_TURNIP_COUNTER
            .R_STOP

        VM_JUMP                 4$
3$:
4$:

GBVM_END$scene_platform_init$1c50e8c3_c2a1_4761_ac8d_6846e95e506b = .
.globl GBVM_END$scene_platform_init$1c50e8c3_c2a1_4761_ac8d_6846e95e506b
GBVM$scene_platform_init$75144b04_358f_4d72_86db_ee446848586f$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$75144b04_358f_4d72_86db_ee446848586f$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; If Actor At Position
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_GET_POS        .LOCAL_ACTOR
        ; -- Calculate coordinate values
        VM_RPN
            .R_REF      ^/(.LOCAL_ACTOR + 1)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_REF      ^/(.LOCAL_ACTOR + 2)/
            .R_INT8     8
            .R_OPERATOR .SHR
            .R_INT16    0
            .R_OPERATOR .EQ
            .R_OPERATOR .AND
            .R_STOP
        VM_IF_CONST             .EQ, .ARG0, 0, 5$, 1

GBVM$scene_platform_init$e5021d48_67a7_4899_851f_1233e8f02947$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$e5021d48_67a7_4899_851f_1233e8f02947$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; Variable Decrement By 1
        VM_RPN
            .R_REF      VAR_TURNIP_COUNTER
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  VAR_TURNIP_COUNTER
            .R_STOP

        VM_JUMP                 6$
5$:
6$:

GBVM_END$scene_platform_init$75144b04_358f_4d72_86db_ee446848586f = .
.globl GBVM_END$scene_platform_init$75144b04_358f_4d72_86db_ee446848586f
GBVM$scene_platform_init$autofade$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script = .
.globl GBVM$scene_platform_init$autofade$f8f027ef_b818_4038_9eda_0ac477facb41$scene$f8f027ef_b818_4038_9eda_0ac477facb41$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
