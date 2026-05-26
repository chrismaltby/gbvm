#ifndef _CORE_H_INCLUDE
#define _CORE_H_INCLUDE

#include <gbdk/platform.h>

#include "compat.h"

void core_reset(void) BANKED;
void core_run(void) BANKED;
NORETURN void generate_exception(UBYTE code, void const * params_offset, UBYTE params_bank) BANKED;

#endif