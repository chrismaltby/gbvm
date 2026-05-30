#pragma bank 255

// Palette: 0

#include "gbs_types.h"

BANKREF(palette_0)

const struct palette_t palette_0 = {
    .mask = 0xFF,
    .palette = {
        DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK)
    }
};
