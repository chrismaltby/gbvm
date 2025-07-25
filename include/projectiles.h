#ifndef PROJECTILES_H
#define PROJECTILES_H

#include <gbdk/platform.h>

#include "math.h"
#include "collision.h"
#include "gbs_types.h"

#define MAX_PROJECTILES 5
#define MAX_PROJECTILE_DEFS 5

extern projectile_def_t projectile_defs[MAX_PROJECTILES];

void projectiles_init(void) BANKED;
void projectiles_update(void) NONBANKED;
void projectiles_render(void) NONBANKED;

void projectile_launch(UBYTE index, upoint16_t *pos, UBYTE angle) BANKED;

#endif
