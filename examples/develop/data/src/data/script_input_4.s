.module script_input_4

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255


___bank_script_input_4 = 255
.globl ___bank_script_input_4

_script_input_4::
GBVM$script_input_4$088b0d8b_52f3_4460_a48f_15b654b420f8$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$script_input_4$088b0d8b_52f3_4460_a48f_15b654b420f8$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        VM_RANDOMIZE

        ; -- overlay cut scanline example --------------------

        VM_SET_CONST_UINT8      _overlay_cut_scanline, 127

        ; --- VM_SFX_PLAY complex effect example -------------
        VM_SFX_PLAY             ___bank_sound_effect1, _sound_effect1, ___mute_mask_sound_effect1, .SFX_PRIORITY_NORMAL

        ; --- VM_LOAD_TILESET/VM_OVERLAY_SET_MAP example -----
        VM_PUSH_CONST           0       ; Y coord
        VM_PUSH_CONST           0       ; X coord
        VM_PUSH_CONST           128
        VM_LOAD_TILESET         .ARG0, ___bank_bg_cave, _bg_cave
        VM_OVERLAY_SET_MAP      .ARG0, .ARG1, .ARG2, ___bank_bg_cave, _bg_cave
        VM_POP                  3

        VM_OVERLAY_MOVE_TO      0, 0, .OVERLAY_IN_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_BTN_A)/

        ; Print
        VM_PUSH_CONST           0
        VM_PRINTER_DETECT       .ARG0, 10
        VM_IF_CONST     .NE     .ARG0, 0, 103$, 0
        VM_PRINT_OVERLAY        .ARG0, 0, 18, 3
        103$:
        VM_POP                  1

        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW)/

        VM_ASM
                push de
                ld e, #b_test_inline_asm
                ld hl, #_test_inline_asm
                call ___sdcc_bcall_ehl
                pop de
        VM_ENDASM

        ; --- VM_SFX_PLAY waveform example
        VM_SFX_PLAY             ___bank_wave_icq_message, _wave_icq_message, ___mute_mask_wave_icq_message, .SFX_PRIORITY_NORMAL

        ; --- VM_SWITCH example ------------------------------
        VM_PUSH_CONST           10
        VM_SWITCH               .ARG0, 3, 0
                .dw 0,  11$
                .dw 1,  12$
                .dw 10, 13$

        VM_LOAD_TEXT            1
                .dw .ARG0
                .asciz "Default; value: %d"
        VM_JUMP                 10$
        11$:
        VM_LOAD_TEXT            1
                .dw .ARG0
                .asciz "Zero; value: %d"
        VM_JUMP                 10$
        12$:
        VM_LOAD_TEXT            1
                .dw .ARG0
                .asciz "One; value: %d"
        VM_JUMP                 10$
        13$:
        VM_LOAD_TEXT            1
                .dw .ARG0
                .asciz "Ten; value: %d"
        VM_JUMP                 10$
        10$:
        VM_POP                  1

        VM_OVERLAY_CLEAR        0, 0, 20, 8, .UI_COLOR_WHITE, ^/(.UI_AUTO_SCROLL | .UI_DRAW_FRAME)/
        VM_OVERLAY_MOVE_TO      2, 10, .OVERLAY_IN_SPEED
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

        ; --- VM_DISPLAY_TEXT_EX example -------------------------
        VM_OVERLAY_CLEAR        0, 0, 20, 8, .UI_COLOR_WHITE, ^/(.UI_AUTO_SCROLL | .UI_DRAW_FRAME)/
        VM_OVERLAY_MOVE_TO      2, 10, .OVERLAY_IN_SPEED
        VM_LOAD_TEXT            0
                .asciz "Hello"
        VM_DISPLAY_TEXT_EX      .DISPLAY_DEFAULT, .TEXT_TILE_CONTINUE
        VM_OVERLAY_WAIT         .UI_MODAL, .UI_WAIT_TEXT
        ; <- Wait code goes here
        VM_LOAD_TEXT            0
                .asciz "World"
        VM_DISPLAY_TEXT_EX      .DISPLAY_PRESERVE_POS, .TEXT_TILE_CONTINUE
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/

        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

        ; --- VM_CALL_NATIVE example -------------------------
        VM_PUSH_CONST           0                       ; actor 0 is the player
        VM_CALL_NATIVE          b_check_update_running, _check_update_running
        VM_IF_CONST     .EQ     .ARG0, 0, 1000$, 1      ; check result in .ARG0 for zero, and pop the value
        ; update script is running
        VM_JUMP                1001$
1000$:
        ; update script is not running
1001$:

        VM_PUSH_CONST           10
        VM_CALL_NATIVE          b_my_native_nonbloking_function, _my_native_nonbloking_function
        VM_POP                  1
        VM_JUMP                 101$
        102$:
        ; sound effect test
        .db 0x71, 0b11111000, 0x4c,0x81,0x43,0x73,0x86  ; play for 2 frames
        .db 0x01, 0b00101000, 0x00,0xc0                 ; shut ch1
        .db 0x01, 0b00000111                            ; stop
        101$:

GBVM$script_input_4$6251bef4_aea4_4d84_8fe4_e7c0be7b1947$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$script_input_4$6251bef4_aea4_4d84_8fe4_e7c0be7b1947$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        VM_SET_PRINT_DIR        .UI_PRINT_RIGHTTOLEFT

GBVM$script_input_4$3d2e9696_fda5_4441_bb38_ec87604ea8e7$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$script_input_4$3d2e9696_fda5_4441_bb38_ec87604ea8e7$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        ; Text Dialogue
        VM_PUSH_CONST           12345
        VM_LOAD_TEXT            1
            .dw .ARG0
            .asciz "\002\002\343\342 \361\367\370\357 \371\350 \341\351\355\n%d \356\340\345\353\346\341 \345\354\364\372\362 \356\366\340 \347\341\370\344"
        VM_POP                  1
        VM_OVERLAY_CLEAR        0, 0, 20, 4, .UI_COLOR_WHITE, ^/(.UI_AUTO_SCROLL | .UI_DRAW_FRAME)/
        VM_OVERLAY_MOVE_TO      0, 12, .OVERLAY_IN_SPEED
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

GBVM$script_input_4$ab938946_d2a7_470a_87d8_38f05f00236e$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$script_input_4$ab938946_d2a7_470a_87d8_38f05f00236e$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        VM_SET_PRINT_DIR        .UI_PRINT_LEFTTORIGHT

GBVM$script_input_4$5bae42a6_8f4a_4993_868b_8298bed6ed2c$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$script_input_4$5bae42a6_8f4a_4993_868b_8298bed6ed2c$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        ; Text Dialogue
        VM_OVERLAY_CLEAR        0, 0, 20, 5, .UI_COLOR_WHITE, .UI_DRAW_FRAME
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_SPEED_INSTANT
        VM_OVERLAY_MOVE_TO      0, 13, .OVERLAY_IN_SPEED
        VM_OVERLAY_SET_SCROLL   1, 1, 18, 5, .UI_COLOR_WHITE
        VM_LOAD_TEXT            0
        .asciz "\002\003\321\372\345\370\374 \345\371\270 \375\362\350\365 \354\377\343\352\350\365\012\364\360\340\355\366\363\347\361\352\350\365 \341\363\353\356\352,\012\344\340 \342\373\357\345\351 \367\340\376."
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

GBVM$script_input_4$9a4e73eb_fb72_4725_a058_bf47cb369f5b$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script = .
.globl GBVM$script_input_4$9a4e73eb_fb72_4725_a058_bf47cb369f5b$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$scene$2017e4bb_16d3_47bc_a86c_9c47e1860e0c$script
        VM_PUSH_CONST           10                                      ; duration
        VM_PUSH_CONST           ^/(.CAMERA_SHAKE_X | .CAMERA_SHAKE_Y)/  ; axis
        VM_PUSH_CONST           8                                       ; dispersion
        VM_INVOKE       b_camera_shake_frames, _camera_shake_frames, 2, .ARG2

        VM_RESERVE              6

        VM_GET_INT8             .ARG0, __is_SGB
        VM_IF_CONST     .EQ     .ARG0, 0, 1$, 0
        VM_SGB_TRANSFER
            .db ((0x04 << 3) | 1), 1, 0x07, ((0x01 << 4) | (0x02 << 2) | 0x03), 5,5, 10,10,  0, 0, 0, 0, 0, 0, 0, 0 ; ATTR_BLK packet
        1$:

        VM_RTC_START            .RTC_START
        VM_RTC_LATCH
        VM_RTC_GET              .ARG3, .RTC_SECONDS
        VM_RTC_GET              .ARG2, .RTC_MINUTES
        VM_RTC_GET              .ARG1, .RTC_HOURS
        VM_RTC_GET              .ARG0, .RTC_DAYS

        VM_LOAD_TEXT            4
            .dw .ARG0, .ARG1, .ARG2, .ARG3
            .asciz "\002\001DAY:%D8 TIME: %D2:%D2:%D2"
        VM_OVERLAY_CLEAR        0, 0, 20, 4, .UI_COLOR_BLACK, 0
        VM_OVERLAY_MOVE_TO      0, 9, .OVERLAY_TEXT_IN_SPEED
        VM_DISPLAY_TEXT
        VM_OVERLAY_SHOW         0, 9, .UI_COLOR_BLACK, 0

        VM_OVERLAY_SET_SUBMAP   2, 2, 6, 5, 8, 4

        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_ANY)/

        VM_SET_CONST            .ARG5, 0
        VM_ACTOR_GET_POS        .ARG5

        VM_SET_CONST            .ARG2, 1
        VM_ACTOR_GET_POS        .ARG2

        VM_RPN
            ; chebyshev distance
            .R_REF      .ARG4
            .R_REF      .ARG1
            .R_OPERATOR .SUB
            .R_OPERATOR .ABS
            .R_REF      .ARG3
            .R_REF      .ARG0
            .R_OPERATOR .SUB
            .R_OPERATOR .ABS
            .R_OPERATOR .MAX
            ; manhattan distance
            .R_REF      .ARG4
            .R_REF      .ARG1
            .R_OPERATOR .SUB
            .R_OPERATOR .ABS
            .R_REF      .ARG3
            .R_REF      .ARG0
            .R_OPERATOR .SUB
            .R_OPERATOR .ABS
            .R_OPERATOR .ADD

            .R_STOP

        VM_LOAD_TEXT            6
            .dw .ARG6, .ARG5, .ARG3, .ARG2, .ARG1, .ARG0
            .asciz "\001\001\002\004@A\nBC\001\003\004\001\377\002\001x1=%d y1=%d\nx2=%d y2=%d\n\004\376\001Chebyshev:\002\002%d\n\002\001Manhattan:\002\002%d\n\002\001\007\002This\007\001 is \002\002BOLD\002\001\nOk!"
        VM_OVERLAY_CLEAR        0, 0, 20, 9, .UI_COLOR_WHITE, .UI_DRAW_FRAME
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_ANY)/

        VM_LOAD_TEXT            0
            .asciz "\001\001\002\004@A\nBC\001\003\004\001\377\002\001Hi, it's KOT speaking!\nWhere's SLON?\006\377\003\022\005\001\001\002\004DE\nFG\003\006\005\001\003\002\001Sorry, i have no idea\nwhat're you mean!"
        VM_OVERLAY_MOVE_TO      0, 11, .OVERLAY_TEXT_OUT_SPEED
        VM_OVERLAY_CLEAR        0, 0, 20, 7, .UI_COLOR_WHITE, .UI_DRAW_FRAME
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_ANY)/

        VM_OVERLAY_CLEAR        0, 0, 20, 7, .UI_COLOR_WHITE, ^/(.UI_DRAW_FRAME | .UI_AUTO_SCROLL)/
        VM_LOAD_TEXT            0
            .asciz "\001\005Terminal mode\rLoading text...\rText loaded!\rLet's see how this text\rscrolls...\rOne more line...\rYes, it does!\rLet's type something\relse...\rI don't know what...\rHello, world!\rI think that is\r\002\002ENOUGH\002\001."
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_ANY)/

        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_TEXT_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW)/

        VM_POP                  ^/6 + 2/    ; 6 for local vars + 2 results of RPN calc\001\001\002\003DE\nFG\001\003\004\001\377\002\001\001\001\002\003@A\nBC\001\003\004\001\377\002\001

        ; Stop Script
        VM_STOP
