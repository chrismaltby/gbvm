#pragma bank 255

// Tileset: sprite_button_b_tileset

#include "gbs_types.h"

BANKREF(sprite_button_b_tileset)

const struct tileset_t sprite_button_b_tileset = {
    .n_tiles = 4,
    .tiles = {
        0x00, 0x00, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0x1C, 0x9E, 0x7E, 0xDE, 0xBE, 0x1E, 0xFE,
        0x9E, 0x6E, 0xCE, 0xBE, 0x0E, 0xFE, 0x1C, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0x00, 0x00,
        0x00, 0x00, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F, 0x3F, 0x38, 0x7D, 0x7A, 0x7D, 0x7B, 0x7C, 0x7B,
        0x7D, 0x7A, 0x7D, 0x7B, 0x7C, 0x7B, 0x3C, 0x3B, 0x1F, 0x1F, 0x0F, 0x0F, 0x07, 0x07, 0x00, 0x00
    }
};
