.module scene_player_s_house_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_player_s_house_init = 255
.globl ___bank_scene_player_s_house_init

_scene_player_s_house_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_player_s_house_init$7b6132c6_bb47_4c09_bc3d_0a33f53c43e7$c22cad6f_1191_4623_911d_1ec9a7b52fe6$scene$c22cad6f_1191_4623_911d_1ec9a7b52fe6$script = .
.globl GBVM$scene_player_s_house_init$7b6132c6_bb47_4c09_bc3d_0a33f53c43e7$c22cad6f_1191_4623_911d_1ec9a7b52fe6$scene$c22cad6f_1191_4623_911d_1ec9a7b52fe6$script
        ; Call Script: Init Menu
        VM_CALL_FAR             ___bank_script_init_menu, _script_init_menu

GBVM$scene_player_s_house_init$autofade$c22cad6f_1191_4623_911d_1ec9a7b52fe6$scene$c22cad6f_1191_4623_911d_1ec9a7b52fe6$script = .
.globl GBVM$scene_player_s_house_init$autofade$c22cad6f_1191_4623_911d_1ec9a7b52fe6$scene$c22cad6f_1191_4623_911d_1ec9a7b52fe6$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
