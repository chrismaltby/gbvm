.module scene_dancefloor_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255


___bank_scene_dancefloor_init = 255
.globl ___bank_scene_dancefloor_init

_scene_dancefloor_init::
        VM_LOCK

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_dancefloor_init$83d5edde_9a1c_4147_a731_3966f9773017$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script = .
.globl GBVM$scene_dancefloor_init$83d5edde_9a1c_4147_a731_3966f9773017$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script
        ; Music Routine Attach
        VM_MUSIC_ROUTINE        0, ___bank_script_music, _script_music

GBVM_END$scene_dancefloor_init$83d5edde_9a1c_4147_a731_3966f9773017 = .
.globl GBVM_END$scene_dancefloor_init$83d5edde_9a1c_4147_a731_3966f9773017
GBVM$scene_dancefloor_init$2a5add16_b578_4c68_915e_5a32a94795a6$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script = .
.globl GBVM$scene_dancefloor_init$2a5add16_b578_4c68_915e_5a32a94795a6$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script
        ; Music Routine Attach
        VM_MUSIC_ROUTINE        1, ___bank_script_music, _script_music

GBVM_END$scene_dancefloor_init$2a5add16_b578_4c68_915e_5a32a94795a6 = .
.globl GBVM_END$scene_dancefloor_init$2a5add16_b578_4c68_915e_5a32a94795a6
GBVM$scene_dancefloor_init$7e1b5b5f_9c37_4017_966f_0ff939e6e929$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script = .
.globl GBVM$scene_dancefloor_init$7e1b5b5f_9c37_4017_966f_0ff939e6e929$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script
        ; Music Routine Attach
        VM_MUSIC_ROUTINE        2, ___bank_script_music, _script_music

GBVM_END$scene_dancefloor_init$7e1b5b5f_9c37_4017_966f_0ff939e6e929 = .
.globl GBVM_END$scene_dancefloor_init$7e1b5b5f_9c37_4017_966f_0ff939e6e929
GBVM$scene_dancefloor_init$06417dcc_7d33_425b_b502_63a439344133$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script = .
.globl GBVM$scene_dancefloor_init$06417dcc_7d33_425b_b502_63a439344133$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script
        ; Music Routine Attach
        VM_MUSIC_ROUTINE        3, ___bank_script_music, _script_music

GBVM_END$scene_dancefloor_init$06417dcc_7d33_425b_b502_63a439344133 = .
.globl GBVM_END$scene_dancefloor_init$06417dcc_7d33_425b_b502_63a439344133
GBVM$scene_dancefloor_init$e45f318b_2c19_41e7_b2bc_0a43f533d64b$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script = .
.globl GBVM$scene_dancefloor_init$e45f318b_2c19_41e7_b2bc_0a43f533d64b$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script
        ; Music Play
        VM_MUSIC_PLAY           ___bank_song_zilog_headbang_routine_Data, _song_zilog_headbang_routine_Data, .MUSIC_NO_LOOP

GBVM$scene_dancefloor_init$autofade$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script = .
.globl GBVM$scene_dancefloor_init$autofade$eb295f50_1350_4042_a8d9_ba79f54eab78$scene$eb295f50_1350_4042_a8d9_ba79f54eab78$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
