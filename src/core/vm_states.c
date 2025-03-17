#pragma bank 255

#include "vm_states.h"

void vm_state_script_attach(SCRIPT_CTX* THIS) OLDCALL BANKED {
  UWORD* slot = VM_REF_TO_PTR(FN_ARG2);
  UBYTE* bank = VM_REF_TO_PTR(FN_ARG1);
  UBYTE** ptr = VM_REF_TO_PTR(FN_ARG0);
  state_events[*slot].script_bank = *bank;
  state_events[*slot].script_addr = *ptr;
}

void vm_state_script_detach(SCRIPT_CTX* THIS) OLDCALL BANKED {
  UWORD* slot = VM_REF_TO_PTR(FN_ARG0);
  state_events[*slot].script_bank = NULL;
  state_events[*slot].script_addr = NULL;
}
