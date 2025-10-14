.module scene_logo_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_logo_init = 255
.globl ___bank_scene_logo_init

_scene_logo_init::
        VM_LOCK

        VM_RESERVE              4

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_logo_init$8343c54c_07a1_4d30_892c_91db234b8d9b$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script = .
.globl GBVM$scene_logo_init$8343c54c_07a1_4d30_892c_91db234b8d9b$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script
        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

GBVM$scene_logo_init$405bf31a_8aa7_4fa2_adbd_d2499176fee7$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script = .
.globl GBVM$scene_logo_init$405bf31a_8aa7_4fa2_adbd_d2499176fee7$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script
        ; Music Play
        VM_MUSIC_PLAY           ___bank_song_dizzy_Data, _song_dizzy_Data, .MUSIC_NO_LOOP

GBVM$scene_logo_init$d00e4e57_f9f3_4b64_ac9a_dc6bf12d84b1$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script = .
.globl GBVM$scene_logo_init$d00e4e57_f9f3_4b64_ac9a_dc6bf12d84b1$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script
        ; Timer Start
        VM_TIMER_PREPARE        1, ___bank_script_timer, _script_timer
        VM_TIMER_SET            1, 1

GBVM_END$scene_logo_init$d00e4e57_f9f3_4b64_ac9a_dc6bf12d84b1 = .
.globl GBVM_END$scene_logo_init$d00e4e57_f9f3_4b64_ac9a_dc6bf12d84b1
GBVM$scene_logo_init$312318bd_3d5c_49bb_b91e_dd923ea1575b$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script = .
.globl GBVM$scene_logo_init$312318bd_3d5c_49bb_b91e_dd923ea1575b$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script
        ; Input Script Attach
        VM_CONTEXT_PREPARE      1, ___bank_script_input_0, _script_input_0
        VM_INPUT_ATTACH         240, ^/(1 | .OVERRIDE_DEFAULT)/

GBVM_END$scene_logo_init$312318bd_3d5c_49bb_b91e_dd923ea1575b = .
.globl GBVM_END$scene_logo_init$312318bd_3d5c_49bb_b91e_dd923ea1575b
GBVM$scene_logo_init$autofade$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script = .
.globl GBVM$scene_logo_init$autofade$382961a1_e615_4b92_92a7_f1a791b50b7a$scene$382961a1_e615_4b92_92a7_f1a791b50b7a$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
