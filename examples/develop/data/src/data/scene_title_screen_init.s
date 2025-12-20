.module scene_title_screen_init

.include "vm.i"
.include "data/game_globals.i"
.include "macro.i"

.globl _fade_frames_per_step, _camera_settings, ___bank_scene_outside, _scene_outside

.area _CODE_255

.LOCAL_ACTOR = -4
.LOCAL_TMP1_SAVE_PEEK = -5

___bank_scene_title_screen_init = 255
.globl ___bank_scene_title_screen_init

_scene_title_screen_init::
        VM_LOCK

        VM_RESERVE              5

        ; Set Sprite Mode: 8x16
        VM_SET_SPRITE_MODE      .MODE_8X16

GBVM$scene_title_screen_init$ff79b819_b435_4ef8_af20_07302038959f$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$ff79b819_b435_4ef8_af20_07302038959f$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

GBVM$scene_title_screen_init$autofade$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$autofade$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

GBVM$scene_title_screen_init$41b284dc_047f_4bb1_ad5c_f8ade30d034e$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$41b284dc_047f_4bb1_ad5c_f8ade30d034e$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; Wait For Input
        VM_INPUT_WAIT           240

GBVM$scene_title_screen_init$19a94599_0006_4e3f_9049_c5087d230ed8$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$19a94599_0006_4e3f_9049_c5087d230ed8$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
2$:
GBVM$scene_title_screen_init$44762258_56af_44bd_abea_f0b9358bc514$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$44762258_56af_44bd_abea_f0b9358bc514$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; Text Multiple Choice
        VM_OVERLAY_CLEAR        0, 0, 20, 4, .UI_COLOR_WHITE, ^/(.UI_AUTO_SCROLL | .UI_DRAW_FRAME)/
        VM_OVERLAY_MOVE_TO      0, 14, .OVERLAY_IN_SPEED
        VM_LOAD_TEXT            0
        .asciz "\001\001\003\003\002New Game\012\003\003\003Continue"
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/
        VM_CHOICE               VAR_S2_MENU_CHOICE, ^/(.UI_MENU_LAST_0 | .UI_MENU_CANCEL_B)/, 2
            .MENUITEM           1, 1, 0, 0, 0, 2
            .MENUITEM           1, 2, 0, 0, 1, 0
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

GBVM$scene_title_screen_init$9e757f17_62ae_4fb5_990f_a9d337d7f07d$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$9e757f17_62ae_4fb5_990f_a9d337d7f07d$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; If
        ; -- If Truthy
        VM_IF_CONST             .NE, VAR_S2_MENU_CHOICE, 0, 3$, 0
GBVM$scene_title_screen_init$d2cd5812_f043_4aa5_b827_475dc79091e7$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$d2cd5812_f043_4aa5_b827_475dc79091e7$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; If Variable True
        VM_SAVE_PEEK            .LOCAL_TMP1_SAVE_PEEK, 0, 0, 0, 0
        VM_IF_CONST             .EQ, .LOCAL_TMP1_SAVE_PEEK, 1, 5$, 0

GBVM$scene_title_screen_init$06b8f464_996e_4c51_8918_50d62bb0c02d$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$06b8f464_996e_4c51_8918_50d62bb0c02d$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; Text Dialogue
        VM_OVERLAY_CLEAR        0, 0, 20, 4, .UI_COLOR_WHITE, .UI_DRAW_FRAME
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_SPEED_INSTANT
        VM_OVERLAY_MOVE_TO      0, 14, .OVERLAY_IN_SPEED
        VM_OVERLAY_SET_SCROLL   1, 1, 18, 5, .UI_COLOR_WHITE
        VM_LOAD_TEXT            0
        .asciz "No Save Data\012Found..."
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

        VM_JUMP                 6$
5$:
GBVM$scene_title_screen_init$4a922761_48a9_410d_b603_00e7a7dd91ea$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$4a922761_48a9_410d_b603_00e7a7dd91ea$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; Load Data from Slot 0
        VM_RAISE                EXCEPTION_LOAD, 1
            .SAVE_SLOT 0

6$:

GBVM_END$scene_title_screen_init$d2cd5812_f043_4aa5_b827_475dc79091e7 = .
.globl GBVM_END$scene_title_screen_init$d2cd5812_f043_4aa5_b827_475dc79091e7
        VM_JUMP                 4$
3$:
GBVM$scene_title_screen_init$a5dddc76_e5fe_424a_9b2b_1ad1834acefb$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script = .
.globl GBVM$scene_title_screen_init$a5dddc76_e5fe_424a_9b2b_1ad1834acefb$4912bee2_387a_472f_ae4f_6679b6149517$scene$4912bee2_387a_472f_ae4f_6679b6149517$script
        ; Load Scene
        VM_SET_CONST_INT8       _fade_frames_per_step, 15
        VM_FADE_OUT             1
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    4096
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    3328
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_RIGHT
        VM_SET_CONST_INT8       _camera_settings, .CAMERA_LOCK
        VM_RAISE                EXCEPTION_CHANGE_SCENE, 3
            IMPORT_FAR_PTR_DATA _scene_outside

4$:

GBVM_END$scene_title_screen_init$9e757f17_62ae_4fb5_990f_a9d337d7f07d = .
.globl GBVM_END$scene_title_screen_init$9e757f17_62ae_4fb5_990f_a9d337d7f07d
        VM_JUMP                 2$
GBVM_END$scene_title_screen_init$19a94599_0006_4e3f_9049_c5087d230ed8 = .
.globl GBVM_END$scene_title_screen_init$19a94599_0006_4e3f_9049_c5087d230ed8
        ; Stop Script
        VM_STOP
