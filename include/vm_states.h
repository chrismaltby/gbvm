#ifndef _VM_STATES_H_INCLUDE
#define _VM_STATES_H_INCLUDE

#include <gbdk/platform.h>

#include "gbs_types.h"
#include "events.h"
#include "vm.h"

void vm_state_script_attach(SCRIPT_CTX* THIS) OLDCALL BANKED;
void vm_states_script_detach(SCRIPT_CTX* THIS) OLDCALL BANKED;

#endif
