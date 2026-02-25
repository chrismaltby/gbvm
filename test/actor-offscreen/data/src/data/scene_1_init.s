.module scene_1_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_1_init = 255
.globl ___bank_scene_1_init

_scene_1_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_1_init$21b5764e_0733_4ad1_b66d_ceb530a4537f$6e8e84f5_e349_4e91_958b_1ae0d5fdde9a$scene$6e8e84f5_e349_4e91_958b_1ae0d5fdde9a$script = .
.globl GBVM$scene_1_init$21b5764e_0733_4ad1_b66d_ceb530a4537f$6e8e84f5_e349_4e91_958b_1ae0d5fdde9a$scene$6e8e84f5_e349_4e91_958b_1ae0d5fdde9a$script
        ; Idle
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

GBVM$scene_1_init$179b5565_453b_483a_9c12_c24a9a152ea3$6e8e84f5_e349_4e91_958b_1ae0d5fdde9a$scene$6e8e84f5_e349_4e91_958b_1ae0d5fdde9a$script = .
.globl GBVM$scene_1_init$179b5565_453b_483a_9c12_c24a9a152ea3$6e8e84f5_e349_4e91_958b_1ae0d5fdde9a$scene$6e8e84f5_e349_4e91_958b_1ae0d5fdde9a$script
        VM_TEST_TERMINATE .TEST_WAIT_VBL

        ; Stop Script
        VM_STOP
