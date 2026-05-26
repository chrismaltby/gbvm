#pragma bank 255

#include "vm.h"
#include "vm_exceptions.h"

#include "vm_scene.h"

#include "actor.h"
#include "bankdata.h"
#include "core.h"
#include "data_manager.h"

BANKREF(VM_SCENE)

void vm_scene_push(void) OLDCALL BANKED {
    scene_stack_ptr->scene = current_scene;
    scene_stack_ptr->pos = PLAYER.pos;
    scene_stack_ptr->dir = PLAYER.dir;
    scene_stack_ptr++;
}

static void raise_change_scene_exception(void) {
    PLAYER.pos = scene_stack_ptr->pos;
    PLAYER.dir = scene_stack_ptr->dir;
	generate_exception(EXCEPTION_CHANGE_SCENE, &scene_stack_ptr->scene, 0);
}

void vm_scene_pop(void) OLDCALL BANKED {
    scene_stack_ptr--;
    raise_change_scene_exception();
}

void vm_scene_pop_all(void) OLDCALL BANKED {
    scene_stack_ptr = scene_stack;
    raise_change_scene_exception();
}

void vm_scene_stack_reset(void) OLDCALL BANKED {
    scene_stack_ptr = scene_stack;
}
