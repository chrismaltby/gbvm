#include <gb/gb.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "math.h"

#include "framework/test_main.h"

void core_reset_hook(void) {}

UBYTE success;

void test(void) {
    success = isqrt(0) == 0;
    for (UBYTE i = 1; i<255; i++) {
      UWORD square = (UWORD)i * (UWORD)i;
      UBYTE result_before = isqrt(square - 1);
      UBYTE result_at = isqrt(square);
      UBYTE result_after = isqrt(square + 1);
      success = success && (result_before == i - 1) && (result_at == i) && (result_after == i);
    }
}
