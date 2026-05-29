#pragma bank 255

#include <string.h>
#include <stdlib.h>

#include "system.h"
#include "vm.h"

#include "vm_ui.h"

#include "ui.h"
#include "input.h"
#include "scroll.h"
#include "gbs_types.h"
#include "bankdata.h"
#include "data_manager.h"
#include "data/data_bootstrap.h"

BANKREF(VM_UI)

typedef struct set_submap_params_t {
    UBYTE x;
    UBYTE _pad0;
    UBYTE y;
    UBYTE _pad1;
    UBYTE w;
    UBYTE _pad2;
    UBYTE h;
    UBYTE _pad3;
    UBYTE scene_x;
    UBYTE _pad4;
    UBYTE scene_y;
} set_submap_params_t;


void ui_draw_frame(UBYTE x, UBYTE y, UBYTE width, UBYTE height) BANKED;

extern UBYTE _itoa_fmt_len;
UBYTE itoa_fmt(INT16 v, UBYTE * d) OLDCALL BANKED PRESERVES_REGS(b, c);

inline UBYTE itoa_format(INT16 v, UBYTE * d, UBYTE dlen) {
    _itoa_fmt_len = dlen;
    UBYTE len = itoa_fmt(v, d);
    if (vwf_direction != UI_PRINT_LEFTTORIGHT) reverse(d);
    return len;
}

static const unsigned char * load_text(const unsigned char * s, INT16 * args) NONBANKED {
    unsigned char * d = ui_text_data;
    while (*s) {
        if (*s == '%') {
            switch (*++s) {
                // variable value of fixed width, zero padded
                case 'D':
                    d += itoa_format(*args, d, *++s - '0');
                    break;
                // variable value
                case 'd':
                    d += itoa_format(*args, d, 0);
                    break;
                // char from variable
                case 'c':
                    *d++ = (unsigned char)(*args);
                    break;
                // text tempo from variable
                case 't':
                    *d++ = 0x01u;
                    *d++ = (unsigned char)(*args) + 0x02u;
                    break;
                // font index from variable
                case 'f':
                    *d++ = 0x02u;
                    *d++ = (unsigned char)(*args) + 0x01u;
                    break;
                // excape % symbol
                case '%':
                    s++;
                default:
                    s--;
                    *d++ = *s++;
                    continue;
            }
        } else {
            *d++ = *s++;
            continue;
        }
        s++; args--;
    }
    *d = 0;
    return s + 1;
}

// renders UI text into buffer
void vm_load_text(DUMMY0_t dummy0, DUMMY1_t dummy1, SCRIPT_CTX * THIS, UBYTE nargs) OLDCALL NONBANKED {
    dummy0; dummy1; // suppress warnings
    SWITCH_ROM(THIS->bank);
    const INT16 * sargs = THIS->PC;
    INT16 * dargs = ui_text_data + (sizeof(ui_text_data) - sizeof(INT16));
    while (nargs--) {
        *dargs-- = *((INT16 *)VM_REF_TO_PTR(*sargs));
        ++sargs;
    }
    THIS->PC = load_text((const unsigned char *)sargs, (INT16 *)(ui_text_data + (sizeof(ui_text_data) - sizeof(INT16))));
}

// renders UI text into buffer indirectly
void vm_load_text_ex(DUMMY0_t dummy0, DUMMY1_t dummy1, SCRIPT_CTX * THIS, UBYTE n) OLDCALL NONBANKED {
    dummy0; dummy1; // suppress warnings
    INT16* arg0 = VM_REF_TO_PTR(FN_ARG0);
    SWITCH_ROM(*(UBYTE *)(arg0));
    load_text(*(const unsigned char **)(arg0 - 1), (INT16 *)(arg0 - 2));
    if (n) THIS->stack_ptr -= n;
}

// start displaying text
void vm_display_text(SCRIPT_CTX * THIS, UBYTE options, UBYTE start_tile) OLDCALL BANKED {
    THIS;

    INPUT_RESET;
    text_options = options;
    text_drawn = text_ff = FALSE;

#ifdef CGB
        if (_is_CGB) {
            if (start_tile >= (UBYTE)((0x100 - TEXT_BUFFER_START) + (0x100 - TEXT_BUFFER_START_BANK1))) {
                return;
            } else if (start_tile >= (UBYTE)(0x100 - TEXT_BUFFER_START)) {
                ui_set_start_tile(TEXT_BUFFER_START_BANK1 + (start_tile - (UBYTE)(0x100 - TEXT_BUFFER_START)), 1);
            } else {
                ui_set_start_tile(TEXT_BUFFER_START + start_tile, 0);
            }
        } else {
#endif
            if (start_tile < (UBYTE)(0x100 - TEXT_BUFFER_START)) ui_set_start_tile(TEXT_BUFFER_START + start_tile, 0);
#ifdef CGB
        }
#endif

}

// switch text rendering to window or background
void vm_switch_text_layer(SCRIPT_CTX * THIS, UBYTE target) OLDCALL BANKED {
    THIS;
    if (target) text_render_base_addr = GetWinAddr(); else text_render_base_addr = GetBkgAddr();
}

// set position of overlayed window
void vm_overlay_setpos(SCRIPT_CTX * THIS, UBYTE pos_x, UBYTE pos_y) OLDCALL BANKED {
    THIS;
    ui_set_pos(pos_x << 3, pos_y << 3);
}

// wait until overlay window reaches destination
void vm_overlay_wait(SCRIPT_CTX * THIS, UBYTE is_modal, UBYTE wait_flags) OLDCALL BANKED {
    if (is_modal) {
        ui_run_modal(wait_flags);
        return;
    }

    UBYTE fail = 0;
    if (wait_flags & UI_WAIT_WINDOW)
        if ((win_pos_x != win_dest_pos_x) || (win_pos_y != win_dest_pos_y)) fail = 1;
    if (wait_flags & UI_WAIT_TEXT)
        if (!text_drawn) fail = 1;
    if (wait_flags & UI_WAIT_BTN_A)
        if (!INPUT_A_PRESSED) fail = 1;
    if (wait_flags & UI_WAIT_BTN_B)
        if (!INPUT_B_PRESSED) fail = 1;
    if (wait_flags & UI_WAIT_BTN_ANY)
        if (!INPUT_ANY_PRESSED) fail = 1;

    if (fail) {
        THIS->waitable = 1;
        THIS->PC -= INSTRUCTION_SIZE + sizeof(is_modal) + sizeof(wait_flags);
    }
}

// set position of overlayed window
void vm_overlay_move_to(SCRIPT_CTX * THIS, UBYTE pos_x, UBYTE pos_y, BYTE speed) OLDCALL BANKED {
    THIS;
    if (speed == UI_IN_SPEED) {
        speed = text_in_speed;
    } else if (speed == UI_OUT_SPEED) {
        speed = text_out_speed;
    }
    ui_move_to(pos_x << 3, pos_y << 3, speed);
}

// set autoscroll parameters
void vm_overlay_set_scroll(SCRIPT_CTX * THIS, UBYTE x, UBYTE y, UBYTE w, UBYTE h, UBYTE color) OLDCALL BANKED {
    THIS;
    text_scroll_addr = GetWinAddr() + (y << 5) + x;
    text_scroll_width = w; text_scroll_height = h;
    text_scroll_fill = (color) ? ui_white_tile : ui_black_tile;
}

// clears overlay window
void vm_overlay_clear(SCRIPT_CTX * THIS, UBYTE x, UBYTE y, UBYTE w, UBYTE h, UBYTE color, UBYTE options) OLDCALL BANKED {
    THIS;
    text_bkg_fill = (color) ? TEXT_BKG_FILL_W : TEXT_BKG_FILL_B;
    if (options & UI_DRAW_FRAME) {
        ui_draw_frame(x, y, w, h);
        if (options & UI_AUTOSCROLL) vm_overlay_set_scroll(THIS, x + 1, y + 1, w - 2, h - 2, color);
    } else {
#ifdef CGB
        if (_is_CGB) {
            VBK_REG = VBK_ATTRIBUTES;
            fill_win_rect(x, y, w, h, overlay_priority | (text_palette & 0x07u));
            VBK_REG = VBK_TILES;
        }
#endif
        fill_win_rect(x, y, w, h, ((color) ? ui_white_tile : ui_black_tile));
        if (options & UI_AUTOSCROLL) vm_overlay_set_scroll(THIS, x, y, w, h, color);
    }
}

// shows overlay
void vm_overlay_show(SCRIPT_CTX * THIS, UBYTE pos_x, UBYTE pos_y, UBYTE color, UBYTE options) OLDCALL BANKED {
    THIS;
    if ((pos_x < 20u) && (pos_y < 18u)) vm_overlay_clear(THIS, 0, 0, 20u - pos_x, 18u - pos_y, color, options);
    ui_set_pos(pos_x << 3, pos_y << 3);
}

void vm_choice(SCRIPT_CTX * THIS, INT16 idx, UBYTE options, UBYTE count) OLDCALL BANKED {
    INT16 * v = VM_REF_TO_PTR(idx);
    *v = (count) ? ui_run_menu((menu_item_t *)(THIS->PC), THIS->bank, options, count, MAX(1, MIN(count, *v))) : 0;
    THIS->PC += sizeof(menu_item_t) * count;
}

void vm_set_font(SCRIPT_CTX * THIS, UBYTE font_index) OLDCALL BANKED {
    THIS;
    vwf_current_font_idx = font_index;
    vwf_current_font_bank = ui_fonts[font_index].bank;
    MemcpyBanked(&vwf_current_font_desc, ui_fonts[font_index].ptr, sizeof(font_desc_t), vwf_current_font_bank);
}

void vm_overlay_scroll(SCRIPT_CTX * THIS, UBYTE x, UBYTE y, UBYTE w, UBYTE h, UBYTE color) OLDCALL BANKED {
    THIS;
    UBYTE * base_addr = GetWinAddr() + (y << 5) + x;
#ifdef CGB
    if (_is_CGB) {
        VBK_REG = VBK_ATTRIBUTES;
        scroll_rect(base_addr, w, h, overlay_priority | (text_palette & 0x07u));
        VBK_REG = VBK_TILES;
    }
#endif
    scroll_rect(base_addr, w, h, ((color) ? ui_white_tile : ui_black_tile));
}

void set_xy_win_submap(const UBYTE * source, UBYTE bank, UBYTE image_tile_width, UBYTE x, UBYTE y, UBYTE w, UBYTE h) NONBANKED
{
    UBYTE _save = CURRENT_BANK;
    SWITCH_ROM(bank);
    set_win_submap(x, y, w, h, source, image_tile_width);
    SWITCH_ROM(_save);
}

void set_xy_win_submap_attributes(const UBYTE * source, UBYTE bank, UBYTE image_tile_width, UBYTE x, UBYTE y, UBYTE w, UBYTE h) NONBANKED
{
    UBYTE _save = CURRENT_BANK;
    SWITCH_ROM(bank);
    set_win_submap_attributes(x, y, w, h, source, image_tile_width);
    SWITCH_ROM(_save);
}

void vm_overlay_set_submap(SCRIPT_CTX * THIS, UBYTE x, UBYTE y, UBYTE w, UBYTE h, UBYTE scene_x, UBYTE scene_y) OLDCALL BANKED {
    THIS;
    UWORD offset = (scene_y * image_tile_width) + scene_x;
#ifdef CGB
    if (_is_CGB) {
        set_xy_win_submap_attributes(image_attr_ptr + offset, image_attr_bank, image_tile_width, x, y, w, h);
    }
#endif
    set_xy_win_submap(image_ptr + offset, image_bank, image_tile_width, x, y, w, h);
}

void vm_overlay_set_submap_ex(SCRIPT_CTX * THIS, INT16 params_idx) OLDCALL BANKED {
    set_submap_params_t * params = VM_REF_TO_PTR(params_idx);
    UWORD offset = (params->scene_y * image_tile_width) + params->scene_x;
#ifdef CGB
    if (_is_CGB) {
        set_xy_win_submap_attributes(image_attr_ptr + offset, image_attr_bank, image_tile_width, params->x, params->y, params->w, params->h);
    }
#endif
    set_xy_win_submap(image_ptr + offset, image_bank, image_tile_width, params->x, params->y, params->w, params->h);
}

void vm_overlay_set_map(SCRIPT_CTX * THIS, INT16 idx, INT16 x_idx, INT16 y_idx, UBYTE bank, const background_t * background) OLDCALL BANKED {
    far_ptr_t tilemap;
    UBYTE x = *((x_idx < 0) ? THIS->stack_ptr + x_idx : script_memory + x_idx);
    UBYTE y = *((y_idx < 0) ? THIS->stack_ptr + y_idx : script_memory + y_idx);
    UBYTE w = ReadBankedUBYTE((void *)&(background->width), bank);
    UBYTE h = ReadBankedUBYTE((void *)&(background->height), bank);
#ifdef CGB
    if (_is_CGB) {
        ReadBankedFarPtr(&tilemap, (void *)&(background->cgb_tilemap_attr), bank);
        if (tilemap.bank) {
            VBK_REG = VBK_ATTRIBUTES;
            SetBankedWinTiles(x, y, w, h, tilemap.ptr, tilemap.bank);
            VBK_REG = VBK_TILES;
        }
    }
#endif
    _map_tile_offset = *(INT16 *)(VM_REF_TO_PTR(idx));
    ReadBankedFarPtr(&tilemap, (void *)&(background->tilemap), bank);
    SetBankedWinTiles(x, y, w, h, tilemap.ptr, tilemap.bank);
    _map_tile_offset = 0;
}

void vm_set_text_sound(SCRIPT_CTX * THIS, UBYTE bank, UBYTE * offset, UBYTE channel_mask) OLDCALL BANKED {
    THIS;
    text_sound_bank = bank;
    text_sound_data = offset;
    text_sound_mask = channel_mask;
}
