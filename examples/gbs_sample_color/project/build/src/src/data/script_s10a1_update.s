.include "vm.i"
.include "data/game_globals.i"

.globl b_wait_frames, _wait_frames

.area _CODE_255



___bank_script_s10a1_update = 255
.globl ___bank_script_s10a1_update

_script_s10a1_update::
1$:
        ; Call Script: Turnip Movement
        VM_PUSH_CONST           0 ; Actor .ARG2
        VM_CALL_FAR             ___bank_script_custom_10, _script_custom_10
        VM_POP                  1

        ; Wait 1 Frame
        VM_PUSH_CONST           1
        VM_INVOKE               b_wait_frames, _wait_frames, 1, .ARG0

        VM_JUMP                 1$
        ; Stop Script
        VM_STOP
