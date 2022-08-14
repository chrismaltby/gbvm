#pragma bank 255

// Background: parallax

#include "gbs_types.h"
#include "data/bg_parallax_tileset.h"
#include "data/bg_parallax_tilemap.h"

BANKREF(bg_parallax)

const struct background_t bg_parallax = {
    .width = 80,
    .height = 18,
    .tileset = TO_FAR_PTR_T(bg_parallax_tileset),
    .cgb_tileset = { NULL, NULL },
    .tilemap = TO_FAR_PTR_T(bg_parallax_tilemap),
    .cgb_tilemap_attr = { NULL, NULL }
};
