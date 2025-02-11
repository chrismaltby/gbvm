#pragma bank 255

// Tileset: tileset_flowers

#include "gbs_types.h"

BANKREF(tileset_flowers)

const struct tileset_t tileset_flowers = {
    .n_tiles = 4,
    .tiles = {
        0x00, 0x00, 0x00, 0x10, 0x10, 0x28, 0x28, 0x54, 0x10, 0x28, 0x00, 0x10, 0x54, 0x00, 0x38, 0x00,
        0x00, 0x00, 0x00, 0x08, 0x08, 0x14, 0x14, 0x2A, 0x08, 0x14, 0x00, 0x08, 0x54, 0x00, 0x38, 0x00,
        0x00, 0x00, 0x00, 0x10, 0x10, 0x28, 0x28, 0x54, 0x10, 0x28, 0x00, 0x10, 0x54, 0x00, 0x38, 0x00,
        0x00, 0x00, 0x00, 0x20, 0x20, 0x50, 0x50, 0xA8, 0x20, 0x50, 0x00, 0x20, 0x54, 0x00, 0x38, 0x00
    }
};
