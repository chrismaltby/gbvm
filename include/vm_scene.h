#ifndef _VM_SCENE_H_INCLUDE
#define _VM_SCENE_H_INCLUDE

#include <gb/gb.h>

#include "vm.h"

void vm_scene_push() __banked;
void vm_scene_pop() __banked;
void vm_scene_pop_all() __banked;
void vm_scene_stack_reset() __banked;

#endif