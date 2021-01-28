.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

___bank_script_s2_timer2 = 255
.globl ___bank_script_s2_timer2
.globl ___bank_tileset_6, _tileset_6

_script_s2_timer2::
        VM_IF_CONST     .EQ     VAR_S2_FLOWER_STATE, 0, 1$, 0

        VM_REPLACE_TILE         0x40, ___bank_tileset_6, _tileset_6, 0, 1
        VM_SET_CONST            VAR_S2_FLOWER_STATE, 0
        VM_STOP

1$:
        VM_REPLACE_TILE         0x40, ___bank_tileset_6, _tileset_6, 1, 1
        VM_SET_CONST            VAR_S2_FLOWER_STATE, 1
        VM_STOP