#pragma bank 255

#include "actor.h"

#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#include <string.h>

#include "system.h"
#include "interrupts.h"
#include "game_time.h"
#include "scroll.h"
#include "linked_list.h"
#include "math.h"
#include "collision.h"
#include "ui.h"
#include "vm.h"

#ifdef STRICT
    #include <gb/bgb_emu.h>
    #include <gb/crash_handler.h>
#endif

#define EMOTE_BOUNCE_FRAMES        15
#define ANIM_PAUSED                255

#define TILE16_OFFSET              64u
#define SCREEN_TILE16_W            10u
#define SCREEN_TILE16_H            9u
#define ACTOR_BOUNDS_TILE16        6u
#define ACTOR_BOUNDS_TILE16_HALF   3u

BANKREF(ACTOR)

const BYTE emote_offsets[] = {2, 1, 0, -1, -2, -3, -4, -5, -6, -5, -4, -3, -2, -1, 0};

const metasprite_t emote_metasprite_8_16[]  = {
    {0, 0, 0, 7}, {0, 8, 2, 7}, 
    {metasprite_end}
};

const metasprite_t emote_metasprite_8_8[]  = {
    {0, 0, 0, 7}, {0, 8, 2, 7},
    {8, -8, 1, 7}, {0, 8, 3, 7},
    {metasprite_end}
};

actor_t actors[MAX_ACTORS];
actor_t * actors_active_head;
actor_t * actors_active_tail;
actor_t * actors_inactive_head;

UBYTE screen_x, screen_y;
actor_t * invalid;
UBYTE player_moving;
UBYTE player_iframes;
UBYTE player_is_offscreen;
actor_t * player_collision_actor;
actor_t * emote_actor;
UBYTE emote_timer;

UBYTE allocated_sprite_tiles;
UBYTE allocated_hardware_sprites;

static void deactivate_actor_impl(actor_t *actor);

void actors_init(void) BANKED {
    actors_active_tail = actors_active_head = actors_inactive_head = NULL;
    player_moving           = FALSE;
    player_iframes          = 0;
    player_collision_actor  = NULL;
    emote_actor             = NULL;

    memset(actors, 0, sizeof(actors));
}

void player_init(void) BANKED {
    actor_set_anim_idle(&PLAYER);
    PLAYER.hidden = FALSE;
    PLAYER.disabled = FALSE;
    PLAYER.anim_noloop = FALSE;
    PLAYER.pinned = FALSE;
    PLAYER.collision_enabled = TRUE;
}

void actors_update(void) BANKED {
    static actor_t *actor;
    static uint8_t screen_tile16_x, screen_tile16_y, screen_tile16_x_end, screen_tile16_y_end;
    static uint8_t actor_tile16_x, actor_tile16_y;
    static uint8_t tmp_iterator; 

    // Convert scroll pos to 16px tile coordinates
    // allowing full range of scene to be represented in 7 bits
    // offset by 64 to allow signed comparisons on
    // unsigned int values (is faster)
    screen_tile16_x = PX_TO_TILE16(draw_scroll_x) + TILE16_OFFSET;
    screen_tile16_x_end = screen_tile16_x + ACTOR_BOUNDS_TILE16 + SCREEN_TILE16_W;
    screen_tile16_y = PX_TO_TILE16(draw_scroll_y) + TILE16_OFFSET;
    screen_tile16_y_end = screen_tile16_y + ACTOR_BOUNDS_TILE16 + SCREEN_TILE16_H;

    tmp_iterator = game_time;

    actor = actors_active_tail;
    while (actor) {

        // Check reached animation tick frame
        if ((actor->anim_tick != ANIM_PAUSED) && (game_time & actor->anim_tick) == 0) {
            actor->frame++;
            // Check reached end of animation
            if (actor->frame == actor->frame_end) {
                if (actor->anim_noloop) {
                    actor->frame--;
                    // TODO: execute onAnimationEnd here + set to ANIM_PAUSED?
                } else {
                    actor->frame = actor->frame_start;
                }
            }
        }

       if (actor->pinned) {
            actor = actor->prev;
            continue;
        }

        if ((tmp_iterator++ & 0x3) == 0) {
            // Bottom right coordinate of actor in 16px tile coordinates
            // Subtract bounding box estimate width/height
            // and offset by 64 to allow signed comparisons with screen tiles
            actor_tile16_x = SUBPX_TO_TILE16(actor->pos.x) + ACTOR_BOUNDS_TILE16_HALF + TILE16_OFFSET;
            actor_tile16_y = SUBPX_TO_TILE16(actor->pos.y) + ACTOR_BOUNDS_TILE16_HALF + TILE16_OFFSET;

            if (
                // Actor right edge < screen left edge
                (actor_tile16_x < screen_tile16_x) ||
                // Actor left edge > screen right edge
                (actor_tile16_x > screen_tile16_x_end) ||
                // Actor bottom edge < screen top edge
                (actor_tile16_y < screen_tile16_y) ||
                // Actor top edge > screen bottom edge
                (actor_tile16_y > screen_tile16_y_end)
            ) {
                // Deactivate if offscreen
                actor_t * prev = actor->prev;
                if (!VM_ISLOCKED()) {
                    if (actor == &PLAYER) {
                        player_is_offscreen = TRUE;
                    } else if (actor->persistent) {
                        actor->disabled = TRUE;
                    } else {
                        deactivate_actor_impl(actor);
                    }
                }
                actor = prev;
                continue;
            }

            if (actor == &PLAYER) {
                player_is_offscreen = FALSE;
            } else if (actor->persistent) {
                actor->disabled = FALSE;
            }
        }

        actor = actor->prev;
    }
}

void actors_render(void) NONBANKED {
    UBYTE _save = CURRENT_BANK;
    static actor_t *actor;

    if (emote_actor) {
        SWITCH_ROM(emote_actor->sprite.bank);
        spritesheet_t *sprite = emote_actor->sprite.ptr;
        screen_x = SUBPX_TO_PX(emote_actor->pos.x) - scroll_x + 8 + sprite->emote_origin.x;
        screen_y = SUBPX_TO_PX(emote_actor->pos.y) - scroll_y + 8 + sprite->emote_origin.y;

        SWITCH_ROM(BANK(ACTOR));  // bank of emote_offsets[] and emote_metasprite[]
        if (emote_timer < EMOTE_BOUNCE_FRAMES) {
            screen_y += emote_offsets[emote_timer];
        }

        const metasprite_t * emote_metasprite = ((LCDC_REG & LCDCF_OBJ16) ? emote_metasprite_8_16 : emote_metasprite_8_8);
        allocated_hardware_sprites += move_metasprite(
            emote_metasprite,
            allocated_sprite_tiles,
            allocated_hardware_sprites,
            screen_x,
            screen_y
        );
    }

    static bool window_hide_actors;
#ifdef CGB
    window_hide_actors = (!_is_CGB) && ((overlay_priority & S_PRIORITY) == 0) && (!show_actors_on_overlay) && (WX_REG > DEVICE_WINDOW_PX_OFFSET_X);
#else
    window_hide_actors = (!show_actors_on_overlay) && (WX_REG > DEVICE_WINDOW_PX_OFFSET_X);
#endif
    
    actor = PLAYER.active ? (player_is_offscreen ? PLAYER.prev ? &PLAYER) : actors_active_tail;
    // Render all actors
    for (; actor; actor = actor->prev){
        if (actor->hidden || actor->disabled) {
           continue;
        }
        
        if (actor->pinned) {
            screen_x = SUBPX_TO_PX(actor->pos.x) + 8, screen_y = SUBPX_TO_PX(actor->pos.y) + 8;
        } else {
            screen_x = (SUBPX_TO_PX(actor->pos.x) + 8) - draw_scroll_x, screen_y = (SUBPX_TO_PX(actor->pos.y) + 8) - draw_scroll_y;
        }

        if (((window_hide_actors) && (((screen_x + 8) > WX_REG) && ((screen_y - 8) > WY_REG)))) {
            continue;
        }
        SWITCH_ROM(actor->sprite.bank);
        spritesheet_t *sprite = actor->sprite.ptr;

        allocated_hardware_sprites += move_metasprite(
            *(sprite->metasprites + actor->frame),
            actor->base_tile,
            allocated_hardware_sprites,
            screen_x,
            screen_y
        );
    }

    SWITCH_ROM(_save);
}

static void deactivate_actor_impl(actor_t *actor) {
#ifdef STRICT
    // Check exists in inactive list
    UBYTE found = 0;
    actor_t *current = actors_active_head;
    DL_CONTAINS(current, actor, found);
    if (!found)
    {
        BGB_MESSAGE("Deactivated non active actor\n");
        __HandleCrash();
        return;
    }
#endif
    if (!actor->active) return;
    if (actor == &PLAYER) return;
    actor->active = FALSE;
    DL_REMOVE_ITEM(actors_active_head, actor);
    DL_PUSH_HEAD(actors_inactive_head, actor);
    if ((actor->hscript_update & SCRIPT_TERMINATED) == 0) {
        script_terminate(actor->hscript_update);
    }
    if ((actor->hscript_hit & SCRIPT_TERMINATED) == 0) {
        script_detach_hthread(actor->hscript_hit);
    }
}

void deactivate_actor(actor_t *actor) BANKED {
    deactivate_actor_impl(actor);
}

static void activate_actor_impl(actor_t *actor) {
#ifdef STRICT
    // Check exists in inactive list
    UBYTE found = 0;
    actor_t *current = actors_inactive_head;
    DL_CONTAINS(current, actor, found);
    if (!found)
    {
        BGB_MESSAGE("Activated non inactive actor\n");
        __HandleCrash();
        return;
    }
#endif
    if (actor->active || actor->disabled) return;

    // Check if on screen before activating to avoid flash of offscreen actors
    if (actor != &PLAYER && !actor->pinned && !actor->persistent) {
        UBYTE actor_tile16_x = SUBPX_TO_TILE16(actor->pos.x) + ACTOR_BOUNDS_TILE16_HALF + TILE16_OFFSET;
        UBYTE actor_tile16_y = SUBPX_TO_TILE16(actor->pos.y) + ACTOR_BOUNDS_TILE16_HALF + TILE16_OFFSET;
        UBYTE screen_tile16_x = PX_TO_TILE16(draw_scroll_x) + TILE16_OFFSET;
        UBYTE screen_tile16_x_end = screen_tile16_x + ACTOR_BOUNDS_TILE16 + SCREEN_TILE16_W;
        UBYTE screen_tile16_y = PX_TO_TILE16(draw_scroll_y) + TILE16_OFFSET;
        UBYTE screen_tile16_y_end = screen_tile16_y + ACTOR_BOUNDS_TILE16 + SCREEN_TILE16_H;
        if (
            // Actor right edge < screen left edge
            (actor_tile16_x < screen_tile16_x) ||
            // Actor left edge > screen right edge
            (actor_tile16_x > screen_tile16_x_end) ||
            // Actor bottom edge < screen top edge
            (actor_tile16_y < screen_tile16_y) ||
            // Actor top edge > screen bottom edge
            (actor_tile16_y > screen_tile16_y_end)
        ) {
            return;
        }
    }

    actor->active = TRUE;
    actor_set_anim_idle(actor);
    DL_REMOVE_ITEM(actors_inactive_head, actor);
    DL_PUSH_HEAD(actors_active_head, actor);
    actor->hscript_update = SCRIPT_TERMINATED;
    if (actor->script_update.bank) {
        script_execute(actor->script_update.bank, actor->script_update.ptr, &(actor->hscript_update), 0);
    }
    actor->hscript_hit = SCRIPT_TERMINATED;
}

void activate_actor(actor_t *actor) BANKED {
    activate_actor_impl(actor);
}

void activate_actors_in_row(UBYTE x, UBYTE y) BANKED {
    actor_t *actor = actors_inactive_head;
    UBYTE x_end = x + SCREEN_TILE_REFRES_W;

    while (actor) {
        UBYTE ty = SUBPX_TO_TILE(actor->pos.y);
        if (ty == y) {
            UBYTE tx = SUBPX_TO_TILE(actor->pos.x);
            if ((tx >= x) && (tx < x_end)) {
                actor_t * next = actor->next;
                activate_actor_impl(actor);
                actor = next;
                continue;
            }
        }
        actor = actor->next;
    }
}

void activate_actors_in_col(UBYTE x, UBYTE y) BANKED {
    actor_t *actor = actors_inactive_head;
    UBYTE y_end = y + SCREEN_TILE_REFRES_H;

    while (actor) {
        UBYTE tx = SUBPX_TO_TILE(actor->pos.x);
        if (tx == x) {
            UBYTE ty = SUBPX_TO_TILE(actor->pos.y);
            if ((ty >= y) && (ty < y_end)) {
                actor_t * next = actor->next;
                activate_actor_impl(actor);
                actor = next;
                continue;
            }
        }
        actor = actor->next;
    }
}

void actor_set_frames(actor_t *actor, UBYTE frame_start, UBYTE frame_end) NONBANKED {
    if ((actor->frame_start != frame_start) || (actor->frame_end != frame_end)) {
        actor->frame = frame_start;
        actor->frame_start = frame_start;
        actor->frame_end = frame_end;
    }
}

void actor_set_frame_offset(actor_t *actor, UBYTE frame_offset) BANKED {
    actor->frame = actor->frame_start + (frame_offset % (actor->frame_end - actor->frame_start));
}

UBYTE actor_get_frame_offset(actor_t *actor) BANKED {
    return actor->frame - actor->frame_start;
}

void actor_set_anim_idle(actor_t *actor) BANKED {
    actor_set_anim(actor, actor->dir);
}

void actor_set_anim_moving(actor_t *actor) BANKED {
    actor_set_anim(actor, actor->dir + N_DIRECTIONS);
}

void actor_set_dir(actor_t *actor, direction_e dir, UBYTE moving) BANKED {
    actor->dir = dir;
    if (moving) {
        actor_set_anim(actor, dir + N_DIRECTIONS);
    } else {
        actor_set_anim(actor, dir);
    }
}

actor_t *actor_at_tile(UBYTE tx, UBYTE ty, UBYTE inc_noclip) BANKED {
    for (actor_t *actor = actors_active_head; (actor); actor = actor->next) {
        if ((!inc_noclip && !actor->collision_enabled))
            continue;

        UBYTE a_tx = SUBPX_TO_TILE(actor->pos.x), a_ty = SUBPX_TO_TILE(actor->pos.y);
        if ((ty == a_ty || ty == a_ty + 1) && (tx == a_tx || tx == a_tx + 1 || tx == a_tx - 1)) return actor;
    }
    return NULL;
}

actor_t *actor_in_front_of_player(UBYTE grid_size, UBYTE inc_noclip) BANKED {
    upoint16_t offset;
    offset.x = PLAYER.pos.x;
    offset.y = PLAYER.pos.y;
    point_translate_dir_word(&offset, PLAYER.dir, PX_TO_SUBPX(grid_size));
    if(inc_noclip)
    {
        return actor_overlapping_bb_inc_noclip(&PLAYER.bounds, &offset, &PLAYER);
    }
    else
    {
        return actor_overlapping_bb(&PLAYER.bounds, &offset, &PLAYER);
    }
}

actor_t *actor_with_script_in_front_of_player(UBYTE grid_size) BANKED {
    upoint16_t offset;
    offset.x = PLAYER.pos.x;
    offset.y = PLAYER.pos.y;
    point_translate_dir_word(&offset, PLAYER.dir, PX_TO_SUBPX(grid_size));
    actor_t *actor = &PLAYER;

    const UWORD a_left   = offset.x + PLAYER.bounds.left;
    const UWORD a_right  = offset.x + PLAYER.bounds.right;
    const UWORD a_top    = offset.y + PLAYER.bounds.top;
    const UWORD a_bottom = offset.y + PLAYER.bounds.bottom;

    while (actor) {
        if (!actor->script.bank) {
            actor = actor->prev;
            continue;
        }
        if ((actor->pos.x + actor->bounds.left)   > a_right)  { actor = actor->prev; continue; }
        if ((actor->pos.x + actor->bounds.right)  < a_left)   { actor = actor->prev; continue; }
        if ((actor->pos.y + actor->bounds.top)    > a_bottom) { actor = actor->prev; continue; }
        if ((actor->pos.y + actor->bounds.bottom) < a_top)    { actor = actor->prev; continue; }
        return actor;
    }

    return NULL;
}

actor_t *actor_overlapping_player(void) BANKED {
    return actor_overlapping_player_from(NULL);
}

actor_t *actor_overlapping_player_from(actor_t *start_actor) BANKED {
    actor_t *actor = start_actor ? start_actor->prev : PLAYER.prev;

    const UWORD a_left   = PLAYER.pos.x + PLAYER.bounds.left;
    const UWORD a_right  = PLAYER.pos.x + PLAYER.bounds.right;
    const UWORD a_top    = PLAYER.pos.y + PLAYER.bounds.top;
    const UWORD a_bottom = PLAYER.pos.y + PLAYER.bounds.bottom;

    while (actor) {
        if (!actor->collision_enabled) {
            actor = actor->prev;
            continue;
        }

        if ((actor->pos.x + actor->bounds.left)   > a_right)  { actor = actor->prev; continue; }
        if ((actor->pos.x + actor->bounds.right)  < a_left)   { actor = actor->prev; continue; }
        if ((actor->pos.y + actor->bounds.top)    > a_bottom) { actor = actor->prev; continue; }
        if ((actor->pos.y + actor->bounds.bottom) < a_top)    { actor = actor->prev; continue; }

        return actor;
    }

    return NULL;
}

actor_t *actor_overlapping_bb(rect16_t *bb, upoint16_t *offset, actor_t *ignore) BANKED {
    actor_t *actor = &PLAYER;

    const UWORD a_left   = offset->x + bb->left;
    const UWORD a_right  = offset->x + bb->right;
    const UWORD a_top    = offset->y + bb->top;
    const UWORD a_bottom = offset->y + bb->bottom;

    while (actor) {
        if (actor == ignore || !actor->collision_enabled) {
            actor = actor->prev;
            continue;
        }

        if ((actor->pos.x + actor->bounds.left)   > a_right)  { actor = actor->prev; continue; }
        if ((actor->pos.x + actor->bounds.right)  < a_left)   { actor = actor->prev; continue; }
        if ((actor->pos.y + actor->bounds.top)    > a_bottom) { actor = actor->prev; continue; }
        if ((actor->pos.y + actor->bounds.bottom) < a_top)    { actor = actor->prev; continue; }

        return actor;
    }

    return NULL;
}

actor_t *actor_overlapping_bb_inc_noclip(rect16_t *bb, upoint16_t *offset, actor_t *ignore) BANKED {
    actor_t *actor = &PLAYER;

    const UWORD a_left   = offset->x + bb->left;
    const UWORD a_right  = offset->x + bb->right;
    const UWORD a_top    = offset->y + bb->top;
    const UWORD a_bottom = offset->y + bb->bottom;

    while (actor) {
        if (actor == ignore) {
            actor = actor->prev;
            continue;
        }

        if ((actor->pos.x + actor->bounds.left)   > a_right)  { actor = actor->prev; continue; }
        if ((actor->pos.x + actor->bounds.right)  < a_left)   { actor = actor->prev; continue; }
        if ((actor->pos.y + actor->bounds.top)    > a_bottom) { actor = actor->prev; continue; }
        if ((actor->pos.y + actor->bounds.bottom) < a_top)    { actor = actor->prev; continue; }

        return actor;
    }

    return NULL;
}

void actors_handle_player_collision(void) BANKED {
    if (player_iframes == 0 && player_collision_actor != NULL) {
        if (player_collision_actor->collision_group & COLLISION_GROUP_MASK) {
            // Execute scene player hit scripts based on actor's collision group
            if (PLAYER.script.bank) {
                script_execute(
                    PLAYER.script.bank,
                    PLAYER.script.ptr, 0, 1,
                    (UWORD)(player_collision_actor->collision_group & COLLISION_GROUP_MASK)
                );
            }
            // Execute actor's onHit player script
            if (player_collision_actor->script.bank) {
                script_execute(player_collision_actor->script.bank,
                               player_collision_actor->script.ptr, 0, 1, 0);
            }

            // Set player to be invicible for N frames
            player_iframes = PLAYER_HURT_IFRAMES;
        }
    } else if (player_iframes != 0) {
        player_iframes--;
    }
    player_collision_actor = NULL;
}
