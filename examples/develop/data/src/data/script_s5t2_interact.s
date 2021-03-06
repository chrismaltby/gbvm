.include "vm.i"
.include "data/game_globals.i"
.include "macro.i"

.globl ___bank_scene_4, _scene_4

.area _CODE_255

ACTOR = -4

___bank_script_s5t2_interact = 255
.globl ___bank_script_s5t2_interact

_script_s5t2_interact::
        VM_LOCK

        ; Local Actor
        VM_PUSH_CONST           0
        VM_PUSH_CONST           0
        VM_PUSH_CONST           0
        VM_PUSH_CONST           0

        ; Load Scene
        VM_FADE_OUT             2
        VM_SET_CONST            ACTOR, 0
        VM_SET_CONST            ^/(ACTOR + 1)/, 1152
        VM_SET_CONST            ^/(ACTOR + 2)/, 768
        VM_ACTOR_SET_POS        ACTOR
        VM_ACTOR_SET_DIR        ACTOR, .DIR_UP
        VM_RAISE                EXCEPTION_CHANGE_SCENE, 3
            IMPORT_FAR_PTR_DATA _scene_4

        ; Stop Script
        VM_STOP
