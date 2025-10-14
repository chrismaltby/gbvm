.module scene_deeper_underground_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_deeper_underground_init = 255
.globl ___bank_scene_deeper_underground_init

_scene_deeper_underground_init::
        VM_LOCK

        VM_RESERVE              4

GBVM$scene_deeper_underground_init$7ef18fac_6a8e_4ec8_a4a0_c452e46047e4$a15eed10_615c_488a_b972_b4b37ccfc14e$actor$114806de_0098_4bac_a152_7f61497f7c99$startScript = .
.globl GBVM$scene_deeper_underground_init$7ef18fac_6a8e_4ec8_a4a0_c452e46047e4$a15eed10_615c_488a_b972_b4b37ccfc14e$actor$114806de_0098_4bac_a152_7f61497f7c99$startScript
        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, VAR_QUEST10, 0, 1$, 0
        VM_JUMP                 2$
1$:
GBVM$scene_deeper_underground_init$1a8bd618_474f_4e90_9df0_1984fa00c656$a15eed10_615c_488a_b972_b4b37ccfc14e$actor$114806de_0098_4bac_a152_7f61497f7c99$startScript = .
.globl GBVM$scene_deeper_underground_init$1a8bd618_474f_4e90_9df0_1984fa00c656$a15eed10_615c_488a_b972_b4b37ccfc14e$actor$114806de_0098_4bac_a152_7f61497f7c99$startScript
        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 1

        ; Actor Set Animation State
        VM_ACTOR_SET_ANIM_SET   .LOCAL_ACTOR, STATE_OPEN
        VM_ACTOR_SET_FLAGS      .LOCAL_ACTOR, 0, .ACTOR_FLAG_ANIM_NOLOOP

2$:

GBVM_END$scene_deeper_underground_init$7ef18fac_6a8e_4ec8_a4a0_c452e46047e4 = .
.globl GBVM_END$scene_deeper_underground_init$7ef18fac_6a8e_4ec8_a4a0_c452e46047e4
        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_deeper_underground_init$23de90eb_bd01_4caf_954a_17b4fef4ec62$a15eed10_615c_488a_b972_b4b37ccfc14e$scene$a15eed10_615c_488a_b972_b4b37ccfc14e$script = .
.globl GBVM$scene_deeper_underground_init$23de90eb_bd01_4caf_954a_17b4fef4ec62$a15eed10_615c_488a_b972_b4b37ccfc14e$scene$a15eed10_615c_488a_b972_b4b37ccfc14e$script
        ; Call Script: Init Menu
        VM_CALL_FAR             ___bank_script_init_menu, _script_init_menu

GBVM$scene_deeper_underground_init$autofade$a15eed10_615c_488a_b972_b4b37ccfc14e$scene$a15eed10_615c_488a_b972_b4b37ccfc14e$script = .
.globl GBVM$scene_deeper_underground_init$autofade$a15eed10_615c_488a_b972_b4b37ccfc14e$scene$a15eed10_615c_488a_b972_b4b37ccfc14e$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
