#pragma bank 255

// Spritesheet Tileset: 1

#include "gbs_types.h"

const void __at(255) __bank_spritesheet_1_tiles;

const struct tileset_t spritesheet_1_tiles = {
  .n_tiles = 4,
  .tiles = {
    127,127,255,128,255,128,252,130,217,164,178,201,229,146,202,165,148,202,169,148,211,168,166,209,205,162,154,196,127,255,0,127,
    254,254,255,1,255,1,167,81,79,161,159,65,55,137,111,17,215,33,167,73,79,145,159,33,55,73,111,145,254,255,0,254
  }
};
