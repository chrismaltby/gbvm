#include "core.h"
#include "test_main.h"
#include <string.h>

void core_reset_hook() { core_reset(); }

void test() {
  strcpy(result, "PASSED");
  core_run();
}
