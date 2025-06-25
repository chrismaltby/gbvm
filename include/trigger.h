#ifndef TRIGGER_H
#define TRIGGER_H

#include <gbdk/platform.h>

#include "gbs_types.h"
#include "math.h"

#define MAX_TRIGGERS 31
#define MAX_ACTIVE_TRIGGERS 11
#define NO_TRIGGER_COLLISON 0xFF

extern trigger_t triggers[MAX_TRIGGERS];
extern UBYTE triggers_len;

/**
 * Resets trigger collision flags on scene start
 */
void trigger_reset(void) BANKED;

/**
 * Find trigger at tile {tx,ty}
 *
 * @param tx Left tile
 * @param ty Top tile
 * @return tile index or NO_TRIGGER_COLLISON if not found
 */
UBYTE trigger_at_tile(UBYTE tx_a, UBYTE ty_a) BANKED;

/**
 * Run script for trigger specified trigger
 *
 * @param i Trigger index
 */
void trigger_interact(UBYTE i) BANKED;

/**
 * Run script for trigger at tile {tx,ty} if this tile was the
 * most recently activated trigger tile don't reactivate
 * (i.e. player must move to another tile first)
 *
 * @param tx Left tile
 * @param ty Top tile
 * @param force Force trigger to activate without changing tile
 */
UBYTE trigger_activate_at(UBYTE tx, UBYTE ty, UBYTE force) BANKED;

UBYTE trigger_activate_at_intersection(rect16_t *bb, upoint16_t *offset, UBYTE force) BANKED;

inline UBYTE trigger_at_intersection(rect16_t *bb, upoint16_t *offset) {
    UBYTE tile_left   = SUBPX_TO_TILE(offset->x + bb->left);
    UBYTE tile_right  = SUBPX_TO_TILE(offset->x + bb->right);
    UBYTE tile_top    = SUBPX_TO_TILE(offset->y + bb->top);
    UBYTE tile_bottom = SUBPX_TO_TILE(offset->y + bb->bottom);
    UBYTE i;

    for (i = 0; i != triggers_len; i++) {
        if ((tile_left <= triggers[i].right)
            && (tile_right >= triggers[i].left)
            && (tile_top <= triggers[i].bottom)
            && (tile_bottom >= triggers[i].top)) {
                return i;
        }
    }

    return NO_TRIGGER_COLLISON;
}

#endif
