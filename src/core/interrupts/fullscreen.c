#pragma bank 255

#include <gbdk/platform.h>

#include "interrupts/interrupts.h"

#include "scroll.h"
#include "interrupts/parallax.h"

void fullscreen_LCD_isr(void) NONBANKED {
    if (LYC_REG == LYC_SYNC_VALUE) {
        LCDC_REG &= ~LCDCF_BG8000;
        SCX_REG = draw_scroll_x;
        SCY_REG = draw_scroll_y;
        LYC_REG = (9 * 8) - 1;
    } else {
        while (STAT_REG & STATF_BUSY) ;
        LCDC_REG |= LCDCF_BG8000;
        LYC_REG = LYC_SYNC_VALUE;
    }
}
