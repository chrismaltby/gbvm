.module actor_2_update

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_actor_2_update = 255
.globl ___bank_actor_2_update

_actor_2_update::
        VM_RESERVE              4

1$:
GBVM$actor_2_update$20012a02_de4b_4373_8e0e_6ea938d8b352$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$actor$421f79f2_8b1c_457a_a3d7_9f3b8f8c1076$updateScript = .
.globl GBVM$actor_2_update$20012a02_de4b_4373_8e0e_6ea938d8b352$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$actor$421f79f2_8b1c_457a_a3d7_9f3b8f8c1076$updateScript
        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2048
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    2560
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/

GBVM$actor_2_update$e50471f2_11f7_4034_bfa9_91dac1688209$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$actor$421f79f2_8b1c_457a_a3d7_9f3b8f8c1076$updateScript = .
.globl GBVM$actor_2_update$e50471f2_11f7_4034_bfa9_91dac1688209$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$actor$421f79f2_8b1c_457a_a3d7_9f3b8f8c1076$updateScript
        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    2048
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    4352
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/

GBVM$actor_2_update$bb085584_80fc_4591_8c1d_5c2b391e5650$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$actor$421f79f2_8b1c_457a_a3d7_9f3b8f8c1076$updateScript = .
.globl GBVM$actor_2_update$bb085584_80fc_4591_8c1d_5c2b391e5650$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$actor$421f79f2_8b1c_457a_a3d7_9f3b8f8c1076$updateScript
        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    512
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    4352
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/

GBVM$actor_2_update$10fa0512_ea4a_488b_bcfa_37b2bf8b361a$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$actor$421f79f2_8b1c_457a_a3d7_9f3b8f8c1076$updateScript = .
.globl GBVM$actor_2_update$10fa0512_ea4a_488b_bcfa_37b2bf8b361a$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$actor$421f79f2_8b1c_457a_a3d7_9f3b8f8c1076$updateScript
        ; Actor Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    512
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    2560
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Move Actor
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_MOVE_TO_INIT   .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_X .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_X      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/
        VM_ACTOR_MOVE_TO_SET_DIR_Y .LOCAL_ACTOR
        VM_ACTOR_MOVE_TO_Y      .LOCAL_ACTOR, ^/(.ACTOR_ATTR_CHECK_COLL_WALLS | .ACTOR_ATTR_CHECK_COLL_ACTORS | .ACTOR_ATTR_H_FIRST)/

        ; Idle
        VM_IDLE

        VM_JUMP                 1$
        ; Stop Script
        VM_STOP
