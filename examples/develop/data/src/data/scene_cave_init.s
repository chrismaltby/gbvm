.module scene_cave_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_cave_init = 255
.globl ___bank_scene_cave_init

_scene_cave_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_cave_init$cb03e339_073a_4773_845c_2ab245f13c1f$5e64882f_8ce6_423e_b582_70fdb2142ff6$scene$5e64882f_8ce6_423e_b582_70fdb2142ff6$script = .
.globl GBVM$scene_cave_init$cb03e339_073a_4773_845c_2ab245f13c1f$5e64882f_8ce6_423e_b582_70fdb2142ff6$scene$5e64882f_8ce6_423e_b582_70fdb2142ff6$script
        ; Call Script: Init Menu
        VM_CALL_FAR             ___bank_script_init_menu, _script_init_menu

GBVM$scene_cave_init$autofade$5e64882f_8ce6_423e_b582_70fdb2142ff6$scene$5e64882f_8ce6_423e_b582_70fdb2142ff6$script = .
.globl GBVM$scene_cave_init$autofade$5e64882f_8ce6_423e_b582_70fdb2142ff6$scene$5e64882f_8ce6_423e_b582_70fdb2142ff6$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
