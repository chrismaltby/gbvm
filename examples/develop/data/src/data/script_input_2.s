.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

___bank_script_input_2 = 255
.globl ___bank_script_input_2

_script_input_2::
        VM_SET_PRINT_DIR        .UI_PRINT_RIGHTTOLEFT

        ; Text Dialogue
        VM_LOAD_TEXT            0
        .asciz "\002\002\343\342 \361\367\370\357 \371\350 \341\351\355\n\356\340\345\353\346\341 \345\354\364\372\362 \356\366\340 \347\341\370\344"
        VM_OVERLAY_CLEAR        0, 0, 20, 4, .UI_COLOR_WHITE, ^/(.UI_AUTO_SCROLL | .UI_DRAW_FRAME)/
        VM_OVERLAY_MOVE_TO      0, 14, .OVERLAY_TEXT_IN_SPEED
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_TEXT_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

        VM_SET_PRINT_DIR        .UI_PRINT_LEFTTORIGHT

        ; Text Dialogue
        VM_LOAD_TEXT            0
        .asciz "\002\003\321\372\345\370\374 \345\371\270 \375\362\350\365 \354\377\343\352\350\365\n\364\360\340\355\366\363\347\361\352\350\365 \341\363\353\356\352,\n\344\340 \342\373\357\345\351 \367\340\376."
        VM_OVERLAY_CLEAR        0, 0, 20, 5, .UI_COLOR_WHITE, ^/(.UI_AUTO_SCROLL | .UI_DRAW_FRAME)/
        VM_OVERLAY_MOVE_TO      0, 13, .OVERLAY_TEXT_IN_SPEED
        VM_DISPLAY_TEXT
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_A)/
        VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_TEXT_OUT_SPEED
        VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/

                VM_LOAD_PALETTE         0x01, ^/.PALETTE_COMMIT | .PALETTE_BKG/
                    .DMG_PAL    3,2,1,0
        
                VM_PUSH_CONST           10
                VM_PUSH_CONST           ^/(.CAMERA_SHAKE_X | .CAMERA_SHAKE_Y)/
                VM_INVOKE       b_camera_shake_frames, _camera_shake_frames, 2, .ARG1
        
                VM_LOAD_PALETTE         0x01, ^/.PALETTE_COMMIT | .PALETTE_BKG/
                    .DMG_PAL    0,1,2,3
        
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
                    .asciz "\001\005Terminal mode\nLoading text...\nText loaded!\nLet's see how this text scrolls...\rOne more line...\rYes, it does!\rLet's type something else...\rI don't know what...\rHello, world!\rI think that is\r\002\002ENOUGH\002\001."
                VM_DISPLAY_TEXT
                VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT | .UI_WAIT_BTN_ANY)/
        
                VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_TEXT_OUT_SPEED
                VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW)/
        
                VM_POP                  ^/6 + 2/    ; 6 for local vars + 2 results of RPN calc\001\001\002\003DE\nFG\001\003\004\001\377\002\001\001\001\002\003@A\nBC\001\003\004\001\377\002\001

        ; Stop Script
        VM_STOP
