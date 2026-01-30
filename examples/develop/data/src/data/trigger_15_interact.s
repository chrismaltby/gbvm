.module trigger_15_interact

.include "vm.i"
.include "data/game_globals.i"
.include "macro.i"

.globl _fade_frames_per_step, _camera_settings, ___bank_scene_parallax, _scene_parallax

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_trigger_15_interact = 255
.globl ___bank_trigger_15_interact

_trigger_15_interact::
        VM_LOCK

        VM_RESERVE              4

GBVM$trigger_15_interact$238eb0b1_2708_426a_9868_1939661132d3$f8f027ef_b818_4038_9eda_0ac477facb41$trigger$00a28fbb_53e3_4f6e_a324_cac17c4181f5$script = .
.globl GBVM$trigger_15_interact$238eb0b1_2708_426a_9868_1939661132d3$f8f027ef_b818_4038_9eda_0ac477facb41$trigger$00a28fbb_53e3_4f6e_a324_cac17c4181f5$script
        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    40704
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    3328
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, .ACTOR_ATTR_H_FIRST

GBVM$trigger_15_interact$6694625e_7adf_463b_9955_7fe76a990359$f8f027ef_b818_4038_9eda_0ac477facb41$trigger$00a28fbb_53e3_4f6e_a324_cac17c4181f5$script = .
.globl GBVM$trigger_15_interact$6694625e_7adf_463b_9955_7fe76a990359$f8f027ef_b818_4038_9eda_0ac477facb41$trigger$00a28fbb_53e3_4f6e_a324_cac17c4181f5$script
        ; Load Scene
        VM_SET_CONST_INT8       _fade_frames_per_step, 15
        VM_FADE_OUT             1
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    512
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    3328
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_RIGHT
        VM_SET_CONST_INT8       _camera_settings, .CAMERA_LOCK
        VM_RAISE                EXCEPTION_CHANGE_SCENE, 3
            IMPORT_FAR_PTR_DATA _scene_parallax

        ; Stop Script
        VM_STOP
