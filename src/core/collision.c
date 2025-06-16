#pragma bank 255

#include "collision.h"

UBYTE tile_hit_x = 0;
UBYTE tile_hit_y = 0;

UBYTE tile_col_test_range_y(UBYTE tile_mask, UBYTE tx, UBYTE ty_start, UBYTE ty_end) NONBANKED {
    tile_hit_x = tx;
    tile_hit_y = ty_start;

    if (tile_hit_x > image_tile_width || tile_hit_y > image_tile_height) {
      return COLLISION_ALL;
    }

    UBYTE _save = CURRENT_BANK;
    UBYTE inc = UBYTE_LESS_THAN(ty_start, ty_end);
    SWITCH_ROM(collision_bank);
    UBYTE* tile_ptr = collision_ptr + (ty_start * (UINT16)image_tile_width) + tx;
    while (TRUE) {
        UBYTE tile = *tile_ptr;
        if (tile & tile_mask) {
            SWITCH_ROM(_save);
            return tile;
        }
        if (tile_hit_y == ty_end) {
            break;
        }
        if (inc) {
            tile_hit_y++;
            tile_ptr += image_tile_width;
        } else {
            tile_hit_y--;
            tile_ptr -= image_tile_width;
        }
        if (tile_hit_y > image_tile_height) {
          SWITCH_ROM(_save);
          return COLLISION_ALL;
        }
    }
    SWITCH_ROM(_save);
    return 0;
}

UBYTE tile_col_test_range_x(UBYTE tile_mask, UBYTE ty, UBYTE tx_start, UBYTE tx_end) NONBANKED {
    tile_hit_x = tx_start;
    tile_hit_y = ty;

    if (tile_hit_x > image_tile_width || tile_hit_y > image_tile_height) {
      return COLLISION_ALL;
    }

    UBYTE _save = CURRENT_BANK;
    UBYTE inc = UBYTE_LESS_THAN(tx_start, tx_end);
    SWITCH_ROM(collision_bank);
    UBYTE* tile_ptr = collision_ptr + (ty * (UINT16)image_tile_width) + tx_start;
    while (TRUE) {
        UBYTE tile = *tile_ptr;
        if (tile & tile_mask) {
            SWITCH_ROM(_save);
            return tile;
        }
        if (tile_hit_x == tx_end) {
            break;
        }
        if (inc) {
            tile_hit_x++;
            tile_ptr++;
        } else {
            tile_hit_x--;
            tile_ptr--;
        }
        if (tile_hit_x > image_tile_width) {
          SWITCH_ROM(_save);
          return COLLISION_ALL;
        }                
    }
    SWITCH_ROM(_save);
    return 0;
}
