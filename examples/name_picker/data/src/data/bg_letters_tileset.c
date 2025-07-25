#pragma bank 255

// Tileset: bg_letters_tileset

#include "gbs_types.h"

BANKREF(bg_letters_tileset)

const struct tileset_t bg_letters_tileset = {
    .n_tiles = 59,
    .tiles = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x3C, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00,
        0x00, 0x00, 0x7C, 0x7C, 0x42, 0x42, 0x7C, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x7C, 0x00, 0x00,
        0x00, 0x00, 0x3C, 0x3C, 0x42, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 0x42, 0x3C, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x7C, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x7C, 0x00, 0x00,
        0x00, 0x00, 0x7E, 0x7E, 0x40, 0x40, 0x7C, 0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x7E, 0x00, 0x00,
        0x00, 0x00, 0x7E, 0x7E, 0x40, 0x40, 0x40, 0x40, 0x7C, 0x7C, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,
        0x00, 0x00, 0x3C, 0x3C, 0x42, 0x42, 0x40, 0x40, 0x4E, 0x4E, 0x42, 0x42, 0x3E, 0x3E, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x44, 0x44, 0x44, 0x44, 0x4C, 0x4C, 0x34, 0x34, 0x00, 0x00,
        0x00, 0x00, 0x40, 0x40, 0x78, 0x78, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x78, 0x78, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x3C, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x04, 0x04, 0x3C, 0x3C, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x3C, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x44, 0x44, 0x7C, 0x7C, 0x40, 0x40, 0x3C, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x38, 0x38, 0x40, 0x40, 0x40, 0x40, 0x78, 0x78, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x44, 0x44, 0x44, 0x44, 0x3C, 0x3C, 0x04, 0x04, 0x78, 0x78,
        0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00,
        0x00, 0x00, 0x7C, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x7C, 0x00, 0x00,
        0x00, 0x00, 0x7C, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x60, 0x60, 0x00, 0x00,
        0x00, 0x00, 0x44, 0x44, 0x48, 0x48, 0x50, 0x50, 0x70, 0x70, 0x48, 0x48, 0x44, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x7E, 0x00, 0x00,
        0x00, 0x00, 0x42, 0x42, 0x66, 0x66, 0x5A, 0x5A, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00,
        0x00, 0x00, 0x42, 0x42, 0x62, 0x62, 0x52, 0x52, 0x4A, 0x4A, 0x46, 0x46, 0x42, 0x42, 0x00, 0x00,
        0x00, 0x00, 0x40, 0x40, 0x78, 0x78, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x30, 0x30,
        0x00, 0x00, 0x40, 0x40, 0x44, 0x44, 0x48, 0x48, 0x70, 0x70, 0x48, 0x48, 0x44, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x6C, 0x6C, 0x54, 0x54, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x58, 0x58, 0x64, 0x64, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x3C, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x7C, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x7C, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,
        0x00, 0x00, 0x3C, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x4A, 0x4A, 0x44, 0x44, 0x3A, 0x3A, 0x00, 0x00,
        0x00, 0x00, 0x7C, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x7C, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00,
        0x00, 0x00, 0x3E, 0x3E, 0x40, 0x40, 0x3C, 0x3C, 0x02, 0x02, 0x42, 0x42, 0x3C, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x7C, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x3C, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 0x38, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x78, 0x78, 0x40, 0x40,
        0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x3C, 0x3C, 0x04, 0x04,
        0x00, 0x00, 0x00, 0x00, 0x58, 0x58, 0x64, 0x64, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3C, 0x3C, 0x40, 0x40, 0x38, 0x38, 0x04, 0x04, 0x78, 0x78, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x78, 0x78, 0x40, 0x40, 0x40, 0x40, 0x38, 0x38, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x4C, 0x4C, 0x34, 0x34, 0x00, 0x00,
        0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x28, 0x28, 0x28, 0x28, 0x10, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x5A, 0x5A, 0x66, 0x66, 0x42, 0x42, 0x00, 0x00,
        0x00, 0x00, 0x42, 0x42, 0x24, 0x24, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x42, 0x42, 0x00, 0x00,
        0x00, 0x00, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x7C, 0x7C, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x7C, 0x7C, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x28, 0x28, 0x28, 0x28, 0x10, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x54, 0x54, 0x6C, 0x6C, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x28, 0x28, 0x44, 0x44, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10, 0x60, 0x60,
        0x00, 0x00, 0x00, 0x00, 0x7C, 0x7C, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x7C, 0x7C, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08
    }
};
