.include "vm.i"
.include "macro.i"

; define constants in rom bank 0
.area _CODE

_start_scene_x:: 
        .dw 768
_start_scene_y:: 
        .dw 768 
_start_scene_dir:: 
        .db .DIR_DOWN
_start_scene::
        .db 0
_start_player_move_speed:: 
        .db 16
_start_player_anim_tick:: 
        .db 15
_ui_fonts:: 
        .db 0

; define engine init VM routine which will be packed into some bank
.area _CODE_255

___bank_script_engine_init = 255
.globl ___bank_script_engine_init

_script_engine_init::
        ; return from init routine
        VM_RET_FAR
