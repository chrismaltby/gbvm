#pragma bank 255

// Tileset: 21

#include "gbs_types.h"

BANKREF(tileset_21)

const struct tileset_t tileset_21 = {
    .n_tiles = 4,
    .tiles = {
        0xFE, 0xFE, 0xFF, 0x01, 0xFF, 0x01, 0xA7, 0x51, 0x4F, 0xA1, 0x9F, 0x41, 0x37, 0x89, 0x6F, 0x11,
        0xD7, 0x21, 0xA7, 0x49, 0x4F, 0x91, 0x9F, 0x21, 0x37, 0x49, 0x6F, 0x91, 0xFE, 0xFF, 0x00, 0xFE,
        0x7F, 0x7F, 0xFF, 0x80, 0xFF, 0x80, 0xFC, 0x82, 0xD9, 0xA4, 0xB2, 0xC9, 0xE5, 0x92, 0xCA, 0xA5,
        0x94, 0xCA, 0xA9, 0x94, 0xD3, 0xA8, 0xA6, 0xD1, 0xCD, 0xA2, 0x9A, 0xC4, 0x7F, 0xFF, 0x00, 0x7F
    }
};
