#pragma bank 255

// Background: placeholder

#include "gbs_types.h"
#include "data/tileset_0.h"
#include "data/tilemap_0.h"

const void __at(255) __bank_background_0;

const struct background_t background_0 = {
    .width = 20,
    .height = 18,
    .tileset = TO_FAR_PTR_T(tileset_0),
    .cgb_tileset = { NULL, NULL },
    .tilemap = TO_FAR_PTR_T(tilemap_0),
    .cgb_tilemap_attr = { NULL, NULL }
};
