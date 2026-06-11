// must be in the same bank with ui_a.s
#pragma bank 1

#include <string.h>

#include "system.h"
#include "ui.h"
#include "game_time.h"
#include "data/data_bootstrap.h"
#include "data/frame_image.h"
#include "data/cursor_image.h"
#include "bankdata.h"
#include "camera.h"
#include "scroll.h"
#include "input.h"
#include "math.h"
#include "actor.h"
#include "projectiles.h"
#include "shadow.h"
#include "music_manager.h"

#define ui_frame_tl_tiles 0xC0u
#define ui_frame_bl_tiles 0xC6u
#define ui_frame_tr_tiles 0xC2u
#define ui_frame_br_tiles 0xC8u
#define ui_frame_t_tiles  0xC1u
#define ui_frame_b_tiles  0xC7u
#define ui_frame_l_tiles  0xC3u
#define ui_frame_r_tiles  0xC5u
#define ui_frame_bg_tiles 0xC4u

UBYTE win_pos_x, win_dest_pos_x;
UBYTE win_pos_y, win_dest_pos_y;
UBYTE win_speed;

UBYTE text_drawn;
UBYTE current_text_speed;

UBYTE text_options;
UBYTE text_in_speed;
UBYTE text_out_speed;
UBYTE text_draw_speed;
UBYTE text_ff_joypad;
UBYTE text_ff;
UBYTE text_bkg_fill;

unsigned char ui_text_data[TEXT_MAX_LENGTH + 1];

// char printer internals
static UBYTE * ui_text_ptr;
static UBYTE ui_dest_x;
static UBYTE ui_dest_y;
static UBYTE ui_base_x;
static UBYTE ui_base_y;
static UBYTE ui_current_tile;
static UBYTE ui_current_tile_bank;
static UBYTE ui_prev_tile;
static UBYTE ui_prev_tile_bank;
static UBYTE vwf_current_offset;
//UBYTE vwf_tile_data[16 * 2]; // moved into absolute.c to free 64 bytes of WRAM (move after shadow_OAM[] which is 256-boundary aligned)
UBYTE vwf_current_mask;
UBYTE vwf_current_rotate;
UBYTE vwf_inverse_map;
UBYTE vwf_direction;

font_desc_t vwf_current_font_desc;
UBYTE vwf_current_font_bank;
UBYTE vwf_current_font_idx;

UBYTE text_render_layer;

UBYTE text_scroll_layer;
UBYTE text_scroll_x;
UBYTE text_scroll_y;
UBYTE text_scroll_width, text_scroll_height;
UBYTE text_scroll_fill;

UBYTE text_sound_mask;
UBYTE text_sound_bank;
const UBYTE * text_sound_data;

UBYTE overlay_priority;
UBYTE text_palette;

static void goto_base_xy(void)
{
    ui_dest_x = ui_base_x;
    ui_dest_y = ui_base_y;
}

static void goto_xy(UBYTE x, UBYTE y)
{
    ui_base_x = x;
    ui_base_y = y;
    ui_dest_x = x;
    ui_dest_y = y;
}

void ui_init(void) BANKED {
    vwf_direction               = UI_PRINT_LEFTTORIGHT;
    vwf_current_font_idx        = 0;
    vwf_current_font_bank       = ui_fonts[0].bank;
    MemcpyBanked(&vwf_current_font_desc, ui_fonts[0].ptr, sizeof(font_desc_t), vwf_current_font_bank);

    text_options                = TEXT_OPT_DEFAULT;
    text_in_speed               = 0;
    text_out_speed              = 0;
    text_ff_joypad              = TRUE;
    text_bkg_fill               = TEXT_BKG_FILL_W;

    ui_text_ptr                 = 0;

    vwf_current_offset          = 0;

    ui_current_tile             = TEXT_BUFFER_START;
    ui_current_tile_bank        = 0;
    ui_prev_tile                = TEXT_BUFFER_START;
    ui_prev_tile_bank           = 0;

    ui_set_pos(0, MENU_CLOSED_Y);

    win_speed                   = 1;
    text_drawn                  = TRUE;
    text_draw_speed             = 1;
    current_text_speed          = 0;

    text_render_layer = UI_TEXT_LAYER_WIN;
    goto_xy(1, 1);

    text_scroll_layer = UI_TEXT_LAYER_WIN;
    text_scroll_width           = DEVICE_SCREEN_WIDTH;
    text_scroll_height          = 8;
    text_scroll_fill            = ui_white_tile;

    text_sound_bank             = SFX_STOP_BANK;

    ui_load_tiles();

#ifdef CGB
    overlay_priority            = S_PRIORITY;
    text_palette                = UI_DEFAULT_PALETTE;
#endif
}

void ui_load_tiles(void) BANKED {
    // load frame
    SetBankedBkgData(ui_frame_tl_tiles, 9, frame_image, BANK(frame_image));
    // load cursor
    SetBankedBkgData(ui_cursor_tile, 1, cursor_image, BANK(cursor_image));

    memset(vwf_tile_data, TEXT_BKG_FILL_W, 16);
    set_bkg_data(ui_white_tile, 1, vwf_tile_data);
    memset(vwf_tile_data, TEXT_BKG_FILL_B, 16);
    set_bkg_data(ui_black_tile, 1, vwf_tile_data);
}

void ui_draw_frame_row(void * dest, UBYTE tile, UBYTE width) OLDCALL;

#ifdef CGB
void ui_draw_frame_row_cgb(void * dest, UBYTE tile, UBYTE width, UBYTE attr) OLDCALL;
#endif

void ui_draw_frame(UBYTE x, UBYTE y, UBYTE width, UBYTE height) BANKED {
    if (height == 0) return;
#ifdef CGB
    if (_is_CGB) {
        UBYTE attr = overlay_priority | (text_palette & 0x07u);
        ui_draw_frame_row_cgb(get_win_xy_addr(x, y), ui_frame_tl_tiles, width, attr);
        if (--height == 0) return;
        if (height > 1)
            for (UBYTE i = height - 1; i != 0; i--) {
                ui_draw_frame_row_cgb(get_win_xy_addr(x, y + i), ui_frame_l_tiles, width, attr);
            }
        ui_draw_frame_row_cgb(get_win_xy_addr(x, y + height), ui_frame_bl_tiles, width, attr);
        return;
    }
#endif
    ui_draw_frame_row(get_win_xy_addr(x, y), ui_frame_tl_tiles, width);
    if (--height == 0) return;
    if (height > 1)
        for (UBYTE i = height - 1; i != 0; i--) {
            ui_draw_frame_row(get_win_xy_addr(x, y + i), ui_frame_l_tiles, width);
        }
    ui_draw_frame_row(get_win_xy_addr(x, y + height), ui_frame_bl_tiles, width);
}

inline void ui_load_tile(const UBYTE * tiledata, UBYTE bank) {
#ifdef CGB
    VBK_REG = (ui_current_tile_bank != 0) ? VBK_BANK_1 : VBK_BANK_0;
#endif
    SetBankedBkgData(ui_current_tile, 1, tiledata, bank);
#ifdef CGB
    VBK_REG = VBK_BANK_0;
#endif
}
inline void ui_load_wram_tile(const UBYTE * tiledata) {
#ifdef CGB
    VBK_REG = (ui_current_tile_bank != 0) ? VBK_BANK_1 : VBK_BANK_0;
#endif
    set_bkg_data(ui_current_tile, 1, tiledata);
#ifdef CGB
    VBK_REG = VBK_BANK_0;
#endif
}

inline void ui_next_tile(void) {
    ui_prev_tile_bank = ui_current_tile_bank;
    ui_prev_tile = ui_current_tile++;
    if (ui_current_tile) return;
#ifdef CGB
    if (_is_CGB) {
        ui_current_tile_bank++;
        ui_current_tile_bank &= 1;
        ui_current_tile = (ui_current_tile_bank) ? TEXT_BUFFER_START_BANK1 : TEXT_BUFFER_START;
    } else {
        ui_current_tile = TEXT_BUFFER_START;
    }
#else
    ui_current_tile = TEXT_BUFFER_START;
#endif
}

void ui_print_reset(void) {
    if (vwf_current_offset) ui_next_tile();
    vwf_current_offset = 0;
    memset(vwf_tile_data, text_bkg_fill, sizeof(vwf_tile_data));
}

void ui_set_start_tile(UBYTE start_tile, UBYTE start_tile_bank) BANKED {
    ui_prev_tile = ui_current_tile = start_tile;
    ui_prev_tile_bank = ui_current_tile_bank = start_tile_bank;
    vwf_current_offset = 0;
    memset(vwf_tile_data, text_bkg_fill, sizeof(vwf_tile_data));
}

void ui_print_shift_char(void * dest, const void * src, UBYTE bank) OLDCALL;
UWORD ui_print_make_mask_lr(UBYTE width, UBYTE ofs) OLDCALL;
UWORD ui_print_make_mask_rl(UBYTE width, UBYTE ofs) OLDCALL;
void ui_swap_tiles(void);

UBYTE ui_print_render(const unsigned char ch) {
    UBYTE letter = (vwf_current_font_desc.attr & FONT_RECODE) ? ReadBankedUBYTE(vwf_current_font_desc.recode_table + (ch & vwf_current_font_desc.mask), vwf_current_font_bank) : ch;
    const UBYTE * bitmap = vwf_current_font_desc.bitmaps + letter * 16u;
    if (vwf_current_font_desc.attr & FONT_VWF) {
        vwf_inverse_map = (vwf_current_font_desc.attr & FONT_VWF_1BIT) ? text_bkg_fill : 0u;
        UBYTE width = ReadBankedUBYTE(vwf_current_font_desc.widths + letter, vwf_current_font_bank);
        if (vwf_direction == UI_PRINT_LEFTTORIGHT) {
            vwf_current_rotate = vwf_current_offset;
            UWORD masks = ui_print_make_mask_lr(width, vwf_current_offset);
            vwf_current_mask = (UBYTE)masks;
            ui_print_shift_char(vwf_tile_data, bitmap, vwf_current_font_bank);

            if ((UBYTE)(vwf_current_offset + width) > 8u) {
                vwf_current_rotate = (8u - vwf_current_offset) | 0x80u;
                vwf_current_mask = (UBYTE)(masks >> 8u);
                ui_print_shift_char(vwf_tile_data + 16u, bitmap, vwf_current_font_bank);
            }
        } else {
            UBYTE dx = (8u - vwf_current_offset);
            vwf_current_rotate =  (width < dx) ? (dx - width) : (width - dx) | 0x80u;
            UWORD masks = ui_print_make_mask_rl(width, vwf_current_offset);
            vwf_current_mask = (UBYTE)masks;
            ui_print_shift_char(vwf_tile_data, bitmap, vwf_current_font_bank);

            if ((UBYTE)(vwf_current_offset + width) > 8u) {
                vwf_current_rotate = 16u - (UBYTE)(vwf_current_offset + width);
                vwf_current_mask = (UBYTE)(masks >> 8u);
                ui_print_shift_char(vwf_tile_data + 16u, bitmap, vwf_current_font_bank);
            }
        }
        vwf_current_offset += width;

        ui_load_wram_tile(vwf_tile_data);
        if (vwf_current_offset > 7u) {
            ui_swap_tiles();
            vwf_current_offset -= 8u;
            ui_next_tile();
            if (vwf_current_offset) ui_load_wram_tile(vwf_tile_data);
            return TRUE;
        }
        return FALSE;
    } else {
        if (vwf_current_offset) ui_next_tile();
        ui_load_tile(bitmap, vwf_current_font_bank);
        ui_next_tile();
        vwf_current_offset = 0u;
        return TRUE;
    }
}

inline void ui_set_tile(UBYTE layer, UBYTE x, UBYTE y, UBYTE tile, UBYTE bank) {
#ifdef CGB
    if (_is_CGB) {
        UBYTE bank_bitmask = bank ? 0x08u : 0x00;
        UBYTE attribute = overlay_priority | bank_bitmask | (text_palette & 0x07u);
        if(layer == UI_TEXT_LAYER_WIN)
            set_win_attribute_xy(x, y, attribute);
        else
            set_bkg_attribute_xy(x, y, attribute);
    }
#else
    bank;
#endif
    if(layer == UI_TEXT_LAYER_WIN)
        set_win_tile_xy(x, y, tile);
    else
        set_bkg_tile_xy(x, y, tile);
}

UBYTE ui_draw_text_buffer_char(void) BANKED {
    static UBYTE current_font_idx, current_text_bkg_fill, current_vwf_direction, current_text_ff_joypad, current_text_draw_speed;

    if (ui_text_ptr == 0) {
        // set the delay mask
        current_text_speed = ui_time_masks[text_draw_speed];
        // save font and color global properties
        current_font_idx        = vwf_current_font_idx;
        current_text_bkg_fill   = text_bkg_fill;
        current_vwf_direction   = vwf_direction;
        current_text_ff_joypad  = text_ff_joypad;
        current_text_draw_speed = text_draw_speed;
        // reset to first line
        // current char pointer
        ui_text_ptr = ui_text_data;
        // VRAM destination
        if ((text_options & TEXT_OPT_PRESERVE_POS) == 0) {
            goto_xy(1,1);
            if (vwf_direction == UI_PRINT_RIGHTTOLEFT)
            {
                // right_to_left initial pos correction
                ui_base_x += (DEVICE_SCREEN_WIDTH-3);
            }
            // initialize current pointer with corrected base value
            ui_dest_x = ui_base_x;
            // tileno destination
            ui_print_reset();
        }
    }

    // normally runs once, but if control code encountered, then process them until printable symbol or terminator
    while (TRUE) {
        switch (*ui_text_ptr) {
            case 0x00: {
                ui_text_ptr = 0;
                text_drawn = TRUE;
                if (vwf_current_font_idx != current_font_idx) {
                    const far_ptr_t * font = ui_fonts + vwf_current_font_idx;
                    MemcpyBanked(&vwf_current_font_desc, font->ptr, sizeof(font_desc_t), vwf_current_font_bank = font->bank);
                }
                text_bkg_fill = current_text_bkg_fill;
                vwf_direction = current_vwf_direction;
                text_ff_joypad = current_text_ff_joypad;
                text_draw_speed = current_text_draw_speed;
                return FALSE;
            }
            case 0x01:
                // set text speed
                text_draw_speed = (*(++ui_text_ptr) - 1u) & 0x07u;
                current_text_speed = ui_time_masks[text_draw_speed];
                break;
            case 0x02: {
                // set current font
                current_font_idx = *(++ui_text_ptr) - 1u;
                const far_ptr_t * font = ui_fonts + current_font_idx;
                UBYTE old_flags = vwf_current_font_desc.attr;
                MemcpyBanked(&vwf_current_font_desc, font->ptr, sizeof(font_desc_t), vwf_current_font_bank = font->bank);
                if ((vwf_current_offset) && ((old_flags & FONT_VWF) != 0) && ((vwf_current_font_desc.attr & FONT_VWF) == 0)) {
                    ui_dest_x++;
                }
                break;
            }
            case 0x03:
                // goto (x,y) location
                UBYTE x = (*++ui_text_ptr - 1u);
                UBYTE y = (*++ui_text_ptr - 1u);
                goto_xy(x, y);
                if (vwf_current_offset) ui_print_reset();
                break;
            case 0x04: {
                // relative gotoxy
                BYTE dx = (BYTE)(*++ui_text_ptr);
                if (dx > 0) dx--;
                BYTE dy = (BYTE)(*++ui_text_ptr);
                if (dy > 0) dy--;
                goto_xy(ui_dest_x + dx, ui_dest_y + dy);
                if (vwf_current_offset) ui_print_reset();
                break;
            }
            case 0x06:
                // wait for input cancels fast forward
                if (text_ff) {
                    text_ff = FALSE;
                    INPUT_RESET;
                }
                text_ff_joypad = FALSE;
                // point to the button mask
                ui_text_ptr++;
                // if high speed then skip waiting
                if (text_draw_speed) {
                    // wait for key press (parameter is a mask)
                    if (INPUT_PRESSED(*ui_text_ptr)) {
                        // mask matches
                        text_ff_joypad = current_text_ff_joypad;
                        INPUT_RESET;
                    } else {
                        // go back to 0x06 control code
                        ui_text_ptr--;
                        current_text_speed = 0;
                        return FALSE;
                    }
                }
                current_text_speed = ui_time_masks[text_draw_speed];
                break;
            case 0x07:
                // set text color
                text_bkg_fill = (*++ui_text_ptr & 1u) ? TEXT_BKG_FILL_W : TEXT_BKG_FILL_B;
                break;
            case 0x08:
                // text direction (left-to-right or right-to-left)
                vwf_direction = (*++ui_text_ptr & 1u) ? UI_PRINT_LEFTTORIGHT : UI_PRINT_RIGHTTOLEFT;
                break;
            case 0x09:
                break;
            case '\n':  // 0x0a
                // new line
                goto_xy(ui_base_x, ui_base_y+1);
                if (vwf_current_offset) ui_print_reset();
                break;
            case 0x0b:
                text_palette = (((*++ui_text_ptr) - 1u) & 0x07u);
                break;
            case '\r':  // 0x0d
                // new line and scroll the text area
                if((ui_dest_y + 1) > (text_scroll_y + text_scroll_height)) {
                    uint8_t* text_scroll_addr = (text_scroll_layer == UI_TEXT_LAYER_WIN) ? get_win_xy_addr(text_scroll_x, text_scroll_y) : get_bkg_xy_addr(text_scroll_x, text_scroll_y);
                    scroll_rect(text_scroll_addr, text_scroll_width, text_scroll_height, text_scroll_fill);
#ifdef CGB
                    if (_is_CGB) {
                        VBK_REG = VBK_ATTRIBUTES;
                        scroll_rect(text_scroll_addr, text_scroll_width, text_scroll_height, overlay_priority | (text_palette & 0x07u));
                        VBK_REG = VBK_TILES;
                    }
#endif
                    goto_base_xy();
                } else {
                    goto_base_xy();
                    ui_dest_y++;
                }
                if (vwf_current_offset) ui_print_reset();
                break;
            case 0x05:
                // escape symbol
                ui_text_ptr++;
                // fall down to default
            default:
                if (ui_print_render(*ui_text_ptr)) {
                    ui_set_tile(text_render_layer, ui_dest_x, ui_dest_y, ui_prev_tile, ui_prev_tile_bank);
                    if (vwf_direction == UI_PRINT_LEFTTORIGHT)  ui_dest_x++; else ui_dest_x--;
                }
                if (vwf_current_offset) ui_set_tile(text_render_layer, ui_dest_x, ui_dest_y, ui_current_tile, ui_current_tile_bank);
                ui_text_ptr++;
                return TRUE;
        }
        ui_text_ptr++;
    }
}

void ui_update(void) BANKED {
    UBYTE flag = FALSE;

    // y should always move first
    if (win_pos_y != win_dest_pos_y) {
        if ((game_time & ui_time_masks[win_speed]) == 0) {
            UBYTE interval = (win_speed == 0) ? 2u : 1u;
            // move window up/down
            if (win_pos_y < win_dest_pos_y) win_pos_y += interval; else win_pos_y -= interval;
        }
        flag = TRUE;
    }
    if (win_pos_x != win_dest_pos_x) {
        if ((game_time & ui_time_masks[win_speed]) == 0) {
            UBYTE interval = (win_speed == 0) ? 2u : 1u;
            // move window left/right
            if (win_pos_x < win_dest_pos_x) win_pos_x += interval; else win_pos_x -= interval;
        }
        flag = TRUE;
    }

    // don't draw text while moving
    if (flag) return;
    // all drawn - nothing to do
    if (text_drawn) return;
    // too fast - wait
    if ((text_ff_joypad) && (INPUT_A_OR_B_PRESSED)) {
        text_ff = TRUE;
    } else {
        if (game_time & current_text_speed) return;
    }
    // render next char
    do {
        flag = ui_draw_text_buffer_char();
    } while (((text_ff) || (text_draw_speed == 0)) && (!text_drawn));
    // play sound
    if ((flag) && (text_sound_bank != SFX_STOP_BANK)) music_play_sfx(text_sound_bank, text_sound_data, text_sound_mask, MUSIC_SFX_PRIORITY_NORMAL);
}

UBYTE ui_run_menu(menu_item_t * start_item, UBYTE bank, UBYTE options, UBYTE count, UBYTE start_index) BANKED {
    menu_item_t current_menu_item;
    UBYTE current_index = ((options & MENU_SET_START) ? start_index : 1u), next_index = 0u;
    // copy first menu item
    MemcpyBanked(&current_menu_item, start_item + (current_index - 1u), sizeof(menu_item_t), bank);

    // draw menu cursor
#ifdef CGB
    if (_is_CGB) {
        set_win_attribute_xy(current_menu_item.X, current_menu_item.Y, overlay_priority | (text_palette & 0x07u));
    }
#endif
    set_win_tile_xy(current_menu_item.X, current_menu_item.Y, ui_cursor_tile);

    // menu loop
    while (TRUE) {
        input_update();
        ui_update();

        toggle_shadow_OAM();
        camera_update();
        scroll_update();
        actors_update();
        actors_render();
        projectiles_render();
        activate_shadow_OAM();

        game_time++;
        wait_vbl_done();

        if (INPUT_UP_PRESSED) {
            next_index = current_menu_item.iU;
        } else if (INPUT_DOWN_PRESSED) {
            next_index = current_menu_item.iD;
        } else if (INPUT_LEFT_PRESSED) {
            next_index = current_menu_item.iL;
        } else if (INPUT_RIGHT_PRESSED) {
            next_index = current_menu_item.iR;
        } else if (INPUT_A_PRESSED) {
            return ((current_index == count) && (options & MENU_CANCEL_LAST)) ? 0u : current_index;
        } else if ((INPUT_B_PRESSED) && (options & MENU_CANCEL_B))  {
            return 0u;
        } else {
            continue;
        }

        if (!next_index) continue;

        // update current index
        current_index = next_index;
        // erase old cursor
#ifdef CGB
        if (_is_CGB) {
            set_win_attribute_xy(current_menu_item.X, current_menu_item.Y, overlay_priority | (text_palette & 0x07u));
        }
#endif
        set_win_tile_xy(current_menu_item.X, current_menu_item.Y, ui_bg_tile);
        // read menu data
        MemcpyBanked(&current_menu_item, start_item + current_index - 1u, sizeof(menu_item_t), bank);
        // put new cursor
#ifdef CGB
        if (_is_CGB) {
            set_win_attribute_xy(current_menu_item.X, current_menu_item.Y, overlay_priority | (text_palette & 0x07u));
        }
#endif
        set_win_tile_xy(current_menu_item.X, current_menu_item.Y, ui_cursor_tile);
        // reset next index
        next_index = 0;
    };
}

void ui_run_modal(UBYTE wait_flags) BANKED {
    UBYTE fail;
    input_update();
    do {
        fail = FALSE;

        if (wait_flags & UI_WAIT_WINDOW)
            if ((win_pos_x != win_dest_pos_x) || (win_pos_y != win_dest_pos_y)) fail = TRUE;
        if (wait_flags & UI_WAIT_TEXT)
            if (!text_drawn) fail = TRUE;
        if (wait_flags & UI_WAIT_BTN_A)
            if (!INPUT_A_PRESSED) fail = TRUE;
        if (wait_flags & UI_WAIT_BTN_B)
            if (!INPUT_B_PRESSED) fail = TRUE;
        if (wait_flags & UI_WAIT_BTN_ANY)
            if (!INPUT_ANY_PRESSED) fail = TRUE;

        if (!fail) return;

        ui_update();

        toggle_shadow_OAM();
        camera_update();
        scroll_update();
        actors_update();
        actors_render();
        projectiles_render();
        activate_shadow_OAM();

        game_time++;
        wait_vbl_done();
        input_update();
    } while (fail);
}
