#pragma bank 255

// Background: placeholder

#include "gbs_types.h"
#include "data/bg_placeholder_tileset.h"
#include "data/bg_placeholder_tilemap.h"
#include "data/bg_placeholder_tilemap_attr.h"

BANKREF(bg_placeholder)

const struct background_t bg_placeholder = {
    .width = 20,
    .height = 18,
    .tileset = TO_FAR_PTR_T(bg_placeholder_tileset),
    .cgb_tileset = { NULL, NULL },
    .tilemap = TO_FAR_PTR_T(bg_placeholder_tilemap),
    .cgb_tilemap_attr = TO_FAR_PTR_T(bg_placeholder_tilemap_attr)
};
