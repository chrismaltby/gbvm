#ifndef INTERRUPTS_H_INCLUDE
#define INTERRUPTS_H_INCLUDE

// Used in LCD interrupt handlers to wait until writing PPU registers is safe
#ifdef NINTENDO
#define HBLANK_WAIT while(STAT_REG & STATF_BUSY)
#else
#define HBLANK_WAIT
#endif

extern UINT8 hide_sprites;
extern UBYTE show_actors_on_overlay;

void simple_LCD_isr(void);
void fullscreen_LCD_isr(void);

void VBL_isr(void);

void remove_LCD_ISRs(void) BANKED;

#endif