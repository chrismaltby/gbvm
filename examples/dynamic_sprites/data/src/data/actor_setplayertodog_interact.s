.module actor_setplayertodog_interact

.include "vm.i"
.include "data/game_globals.i"

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_actor_setplayertodog_interact = 255
.globl ___bank_actor_setplayertodog_interact

_actor_setplayertodog_interact::
        VM_LOCK

        VM_RESERVE              4

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 0

        ; Actor Set Spritesheet
        VM_ACTOR_SET_SPRITESHEET .LOCAL_ACTOR, ___bank_sprite_dog, _sprite_dog

        ; Stop Script
        VM_STOP
