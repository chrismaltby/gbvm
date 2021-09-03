#pragma bank 255

// Tileset: 21

#include "gbs_types.h"

BANKREF(tileset_21)

const struct tileset_t tileset_21 = {
    .n_tiles = 4,
    .tiles = {
        0x00, 0x00, 0x00, 0x00, 0xFC, 0xFC, 0x02, 0xFE, 0xFA, 0x06, 0xFA, 0xD6, 0xFA, 0xB6, 0xFA, 0x56,
        0xFA, 0x06, 0x02, 0xFE, 0xFC, 0xFC, 0x40, 0xC0, 0xC0, 0x40, 0xC0, 0x40, 0xC0, 0x40, 0xC0, 0xC0,
        0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x40, 0x7F, 0x5F, 0x60, 0x5F, 0x6E, 0x5F, 0x6A, 0x5F, 0x6D,
        0x5F, 0x60, 0x40, 0x7F, 0x3F, 0x3F, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03
    }
};
