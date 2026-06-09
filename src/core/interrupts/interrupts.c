#pragma bank 255

#include <gbdk/platform.h>

#include "interrupts/interrupts.h"

#include "interrupts/parallax.h"
#include "interrupts/fullscreen.h"
#include "interrupts/simple.h"

#include "scroll.h"

#include "ui.h"

UBYTE hide_sprites;                                // default initialized to FALSE
UBYTE show_actors_on_overlay;                      // default initialized to FALSE
UBYTE overlay_cut_scanline = LYC_SYNC_VALUE;

void add_LCD_ISRs(LCD_isr_e scene_LCD_type) BANKED {
    CRITICAL {
        switch (scene_LCD_type) {
            case LCD_parallax:
                add_LCD(parallax_LCD_isr);
                break;
            case LCD_fullscreen:
                add_LCD(fullscreen_LCD_isr);
                break;
            default:
                add_LCD(simple_LCD_isr);
                break;
        }
        LYC_REG = 0u;
    }
}

void remove_LCD_ISRs(void) BANKED {
    CRITICAL {
        remove_LCD(parallax_LCD_isr);
        remove_LCD(simple_LCD_isr);
        remove_LCD(fullscreen_LCD_isr);
        LCDC_REG &= ~LCDCF_BG8000;
    }
}

void VBL_isr(void) NONBANKED {
    if ((WY_REG = win_pos_y) < MENU_CLOSED_Y) WX_REG = (win_pos_x + DEVICE_WINDOW_PX_OFFSET_X), SHOW_WIN; else WX_REG = 0, HIDE_WIN;
    if (hide_sprites) HIDE_SPRITES; else SHOW_SPRITES;
    scroll_shadow_update();
}
