#pragma bank 255

#include <gbdk/platform.h>
#include "vm.h"
#include "actor.h"

// function inverse the DMG palette the number of times passed on the VM stack
void my_native_function(SCRIPT_CTX * THIS) OLDCALL BANKED {
    // inverse DMG palette several times:
    for (uint8_t i = *(int16_t*)VM_REF_TO_PTR(FN_ARG0); i != 0; i--) {
        BGP_REG = ~BGP_REG;
        if (i) wait_vbl_done();
    }
}

// function inverse the DMG palette the number of times passed on the VM stack
void my_native_nonbloking_function(SCRIPT_CTX * THIS) OLDCALL BANKED {
    // the count argument is on the VM stack
    int16_t* arg = VM_REF_TO_PTR(FN_ARG0);
    if (*arg) {
        // function payload: inverse the DMG background palette
        BGP_REG = ~BGP_REG;
        // decrease the count
        if (--(*arg)) {
            // if count is not zero, make VM_CALL_NATIVE instruction re-run the next iteration
            THIS->PC -= (INSTRUCTION_SIZE + sizeof(uint8_t) + sizeof(void*));
            // don't execute this thread until the next frame
            THIS->waitable = TRUE;
            // exit the function
            return;
        }
    }
}

void check_update_running(SCRIPT_CTX * THIS) OLDCALL BANKED {
    int16_t * arg = VM_REF_TO_PTR(FN_ARG0);
    actor_t * actor = actors + (uint8_t)*arg;
    *arg = ((actor->hscript_update == 0) || (actor->hscript_update & SCRIPT_TERMINATED)) ? 0 : 1;
}

void test_inline_asm(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
}