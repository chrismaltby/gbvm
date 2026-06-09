#pragma bank 255

#include <gbdk/platform.h>

#include "interrupts/interrupts.h"

#include "scroll.h"
#include "ui.h"

void simple_LCD_isr(void) NONBANKED {
    if (LYC_REG == LYC_SYNC_VALUE) {
        SCX_REG = draw_scroll_x;
        SCY_REG = draw_scroll_y;
        if (WY_REG) {
            if (WY_REG < MENU_CLOSED_Y) LYC_REG = WY_REG - 1;
        } else {
            if ((WX_REG == DEVICE_WINDOW_PX_OFFSET_X) && (show_actors_on_overlay == FALSE)) HIDE_SPRITES;
            LYC_REG = overlay_cut_scanline;
        }
    } else {
        if (LYC_REG < overlay_cut_scanline) {
            if ((WX_REG == DEVICE_WINDOW_PX_OFFSET_X) && (show_actors_on_overlay == FALSE)) {
                while (STAT_REG & STATF_BUSY) ;
                HIDE_SPRITES;
            }
            LYC_REG = overlay_cut_scanline;
        } else {
            while (STAT_REG & STATF_BUSY) ;
            WX_REG = 0, HIDE_WIN;
            if (!hide_sprites) SHOW_SPRITES;
            LYC_REG = LYC_SYNC_VALUE;
            return;
        }
    }
}
