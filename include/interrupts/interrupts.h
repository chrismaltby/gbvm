#ifndef INTERRUPTS_H_INCLUDE
#define INTERRUPTS_H_INCLUDE

#include "data_manager.h"

extern UINT8 hide_sprites;
extern UBYTE show_actors_on_overlay;
extern UBYTE overlay_cut_scanline;

#define LYC_SYNC_VALUE 150u

void VBL_isr(void);

void add_LCD_ISRs(LCD_isr_e scene_LCD_type) BANKED;
void remove_LCD_ISRs(void) BANKED;

#endif