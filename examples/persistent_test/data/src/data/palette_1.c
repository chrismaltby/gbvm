#pragma bank 255

// Palette: 1

#include "gbs_types.h"

BANKREF(palette_1)

const struct palette_t palette_1 = {
    .mask = 0xFF,
    .palette = {
        DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK),
        DMG_PALETTE(DMG_WHITE, DMG_WHITE, DMG_DARK_GRAY, DMG_BLACK)
    },
    .cgb_palette = {
        CGB_PALETTE(RGB(31, 30, 28), RGB(31, 30, 28), RGB(27, 16, 15), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 30, 28), RGB(31, 30, 28), RGB(27, 16, 15), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 30, 28), RGB(31, 30, 28), RGB(27, 16, 15), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 30, 28), RGB(31, 30, 28), RGB(27, 16, 15), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 30, 28), RGB(31, 30, 28), RGB(27, 16, 15), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 30, 28), RGB(31, 30, 28), RGB(27, 16, 15), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 30, 28), RGB(31, 30, 28), RGB(27, 16, 15), RGB(0, 0, 1)),
        CGB_PALETTE(RGB(31, 30, 28), RGB(31, 30, 28), RGB(27, 16, 15), RGB(0, 0, 1)) 
    }
};
