#pragma bank 255

#include "vm_actor.h"

#include <gbdk/metasprites.h>

#include "actor.h"
#include "game_time.h"
#include "data_manager.h"
#include "scroll.h"
#include "math.h"
#include "macro.h"

BANKREF(VM_ACTOR)

#define EMOTE_TOTAL_FRAMES         60
#define MOVE_INACTIVE              0
#define MOVE_ALLOW_H               1
#define MOVE_ALLOW_V               2
#define MOVE_DIR_H                 4
#define MOVE_DIR_V                 8
#define MOVE_ACTIVE_H              16
#define MOVE_ACTIVE_V              32
#define MOVE_NEEDED_H              64
#define MOVE_NEEDED_V              128
#define MOVE_H                     (MOVE_ALLOW_H | MOVE_NEEDED_H)
#define MOVE_V                     (MOVE_ALLOW_V | MOVE_NEEDED_V)
#define TILE_FRACTION_MASK         0b11111111
#define ONE_TILE_DISTANCE          256


typedef struct act_move_to_t {
    INT16 ID;
    UINT16 X, Y;
    UBYTE ATTR;
} act_move_to_t;

typedef struct act_set_pos_t {
    INT16 ID;
    UINT16 X, Y;
} act_set_pos_t;

typedef struct act_set_bounds_t {
    INT16 ID;
    INT16 LEFT, RIGHT, TOP, BOTTOM;
} act_set_bounds_t;

typedef struct act_set_frame_t {
    INT16 ID;
    INT16 FRAME;
} act_set_frame_t;

typedef struct gbs_farptr_t {
    INT16 BANK;
    const void * DATA;
} gbs_farptr_t;

static UWORD check_collision_horizontal(UWORD start_x, UWORD start_y, rect16_t *bounds, UWORD end_pos) {
    UBYTE tx1, ty1, tx2, ty2, tile_mask;
    ty1 = SUBPX_TO_TILE(start_y + bounds->top);
    ty2 = SUBPX_TO_TILE(start_y + bounds->bottom) + 1;
    if (start_x > end_pos) {
        // Check left
        tile_mask = COLLISION_RIGHT;
        tx1 = SUBPX_TO_TILE(start_x + bounds->left);
        tx2 = SUBPX_TO_TILE(end_pos + bounds->left);
        if (tx2 > tx1) {
            tx2 = 0;
        }
    }
    else {
        // Check right
        tile_mask = COLLISION_LEFT;
        tx1 = SUBPX_TO_TILE(start_x + bounds->right);
        tx2 = SUBPX_TO_TILE(end_pos + bounds->right);
        if (tx2 < tx1) {
            tx2 = image_tile_width;
        }            
    }
    while (ty1 != ty2) {
        if (tile_col_test_range_x(tile_mask, ty1, tx1, tx2)) {
            return (start_x > end_pos) ?
                   TILE_TO_SUBPX(tile_hit_x) - bounds->left + TILE_TO_SUBPX(1) : 
                   TILE_TO_SUBPX(tile_hit_x) - EXCLUSIVE_OFFSET(bounds->right);
        }                
        ty1++;
    }
    return end_pos;
}

static UWORD check_collision_vertical(UWORD start_x, UWORD start_y, rect16_t *bounds, UWORD end_pos) {
    UBYTE tx1, ty1, tx2, ty2, tile_mask;
    tx1 = SUBPX_TO_TILE(start_x + bounds->left);
    tx2 = SUBPX_TO_TILE(start_x + bounds->right) + 1;
    if (start_y > end_pos) {
        // Check up
        tile_mask = COLLISION_BOTTOM;
        ty1 = SUBPX_TO_TILE(start_y + bounds->top);
        ty2 = SUBPX_TO_TILE(end_pos + bounds->top);
        if (ty2 > ty1) {
            ty2 = 0;
        }
    }
    else {
        // Check down
        tile_mask = COLLISION_TOP;
        ty1 = SUBPX_TO_TILE(start_y + bounds->bottom);
        ty2 = SUBPX_TO_TILE(end_pos + bounds->bottom);
        if (ty2 < ty1) {
            ty2 = image_tile_height;
        }
    }
    while (tx1 != tx2) {
        if (tile_col_test_range_y(tile_mask, tx1, ty1, ty2)) {
            return (start_y > end_pos) ? 
                   TILE_TO_SUBPX(tile_hit_y) - bounds->top + TILE_TO_SUBPX(1) : 
                   TILE_TO_SUBPX(tile_hit_y) - EXCLUSIVE_OFFSET(bounds->bottom);
        }
        tx1++;
    }
    return end_pos;
}

void vm_actor_move_to(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;
    static direction_e new_dir = DIR_DOWN;

    // indicate waitable state of context
    THIS->waitable = 1;

    act_move_to_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    if (THIS->flags == 0) {
        CLR_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT);

        // Switch to moving animation frames
        actor_set_anim_moving(actor);

        // Snap to nearest pixel before moving
        actor->pos.x = SUBPX_SNAP_PX(actor->pos.x);
        actor->pos.y = SUBPX_SNAP_PX(actor->pos.y);

        if (CHK_FLAG(params->ATTR, ACTOR_ATTR_DIAGONAL)) {
            SET_FLAG(THIS->flags, MOVE_ALLOW_H | MOVE_ALLOW_V);
        } if (CHK_FLAG(params->ATTR, ACTOR_ATTR_H_FIRST)) {
            SET_FLAG(THIS->flags, MOVE_ALLOW_H);
        } else {
            SET_FLAG(THIS->flags, MOVE_ALLOW_V);
        }

        // If moving relative add current position
        // and prevent overflow
        if (CHK_FLAG(params->ATTR, ACTOR_ATTR_RELATIVE)) {
            params->X = saturating_add_u16(actor->pos.x, (WORD)params->X);
            params->Y = saturating_add_u16(actor->pos.y, (WORD)params->Y);
        }
        // and snap destination to either pixels/tiles
        if (CHK_FLAG(params->ATTR, ACTOR_ATTR_RELATIVE_SNAP_PX)) {
            params->X = SUBPX_SNAP_PX(params->X);
            params->Y = SUBPX_SNAP_PX(params->Y);
        } else if (CHK_FLAG(params->ATTR, ACTOR_ATTR_RELATIVE_SNAP_TILE)) {
            params->X = SUBPX_SNAP_TILE(params->X);
            params->Y = SUBPX_SNAP_TILE(params->Y);
        }

        // Check for collisions in path
        if (CHK_FLAG(params->ATTR, ACTOR_ATTR_CHECK_COLL_WALLS)) {
            if (CHK_FLAG(params->ATTR, ACTOR_ATTR_H_FIRST)) {
                // Check for horizontal collision
                if (actor->pos.x != params->X) {
                    params->X = check_collision_horizontal(actor->pos.x, actor->pos.y, &actor->bounds, params->X);
                }
                // Check for vertical collision
                if (actor->pos.y != params->Y) {
                    params->Y = check_collision_vertical(params->X, actor->pos.y, &actor->bounds, params->Y);
                }
            } else {
                // Check for vertical collision
                if (actor->pos.y != params->Y) {
                    params->Y = check_collision_vertical(actor->pos.x, actor->pos.y, &actor->bounds, params->Y);
                }
                // Check for horizontal collision
                if (actor->pos.x != params->X) {
                    params->X = check_collision_horizontal(actor->pos.x, params->Y, &actor->bounds, params->X);
                }
            }
        }

        // Actor already at destination
        if ((actor->pos.x != params->X)) {
            SET_FLAG(THIS->flags, MOVE_NEEDED_H);
        } else {
            SET_FLAG(THIS->flags, MOVE_ALLOW_V);
        }
        if (actor->pos.y != params->Y) {
            SET_FLAG(THIS->flags, MOVE_NEEDED_V);
        } else {
            SET_FLAG(THIS->flags, MOVE_ALLOW_H);
        }

        // Initialise movement directions
        if (actor->pos.x > params->X) {
            // Move left
            SET_FLAG(THIS->flags, MOVE_DIR_H);
        }
        if (actor->pos.y > params->Y) {
            // Move up
            SET_FLAG(THIS->flags, MOVE_DIR_V);
        }

        THIS->PC -= (INSTRUCTION_SIZE + sizeof(idx));
        return;        
    }

    // Interrupt actor movement
    if (CHK_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT)) {
        // Set new X destination to next tile
        if ((actor->pos.x < params->X) && (actor->pos.x & TILE_FRACTION_MASK)) {   // Bitmask to check for non-grid-aligned position
            params->X = (actor->pos.x & ~TILE_FRACTION_MASK) + ONE_TILE_DISTANCE;  // If moving in positive direction, round up to next tile
        } else {
            params->X = actor->pos.x  & ~TILE_FRACTION_MASK;                       // Otherwise, round down
        }
        // Set new Y destination to next tile
        if ((actor->pos.y < params->Y) && (actor->pos.y & TILE_FRACTION_MASK)) {
            params->Y = (actor->pos.y & ~TILE_FRACTION_MASK) + ONE_TILE_DISTANCE;
        } else {
            params->Y = actor->pos.y  & ~TILE_FRACTION_MASK;
        }
        CLR_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT);
    }

    UBYTE test_actors = CHK_FLAG(params->ATTR, ACTOR_ATTR_CHECK_COLL_ACTORS);

    // Move in X Axis
    if (CHK_FLAG(THIS->flags, MOVE_H) == MOVE_H) {
        // Get hoizontal direction from flags
        new_dir = CHK_FLAG(THIS->flags, MOVE_DIR_H) ? DIR_LEFT : DIR_RIGHT;

        // Move actor horizontally
        actor->pos.x += new_dir == DIR_LEFT ? -actor->move_speed : actor->move_speed;

        // Check for actor collision
        actor_t *hit_actor;
        if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) {
            actor->pos.x = hit_actor->pos.x +
                (new_dir == DIR_LEFT
                    ? hit_actor->bounds.right - actor->bounds.left + 1
                    : hit_actor->bounds.left - actor->bounds.right - 1
                );
            THIS->flags = 0;
            actor_set_anim_idle(actor);
            return;
        }

        // If first frame moving in this direction update actor direction
        if (!CHK_FLAG(THIS->flags, MOVE_ACTIVE_H)) {
            SET_FLAG(THIS->flags, MOVE_ACTIVE_H);
            actor_set_dir(actor, new_dir, TRUE);
        }

        // Check if overshot destination
        if (
            (new_dir == DIR_LEFT && (actor->pos.x <= params->X)) || // Overshot left
            (new_dir == DIR_RIGHT && (actor->pos.x >= params->X))   // Overshot right
        ) {
            // Reached Horizontal Destination
            actor->pos.x = params->X;
            SET_FLAG(THIS->flags, MOVE_ALLOW_V);
            CLR_FLAG(THIS->flags, MOVE_H);
        }
    }

    // Move in Y Axis
    if (CHK_FLAG(THIS->flags, MOVE_V) == MOVE_V) {
        // Get vertical direction from flags
        new_dir = CHK_FLAG(THIS->flags, MOVE_DIR_V) ? DIR_UP : DIR_DOWN;

        // Move actor vertically
        actor->pos.y += new_dir == DIR_UP ? -actor->move_speed : actor->move_speed;

        // Check for actor collision
        actor_t *hit_actor;
        if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) { 
            actor->pos.y = hit_actor->pos.y +
                (new_dir == DIR_UP
                    ? hit_actor->bounds.bottom - actor->bounds.top + 1
                    : hit_actor->bounds.top - actor->bounds.bottom - 1
                );
            THIS->flags = 0;
            actor_set_anim_idle(actor);
            return;
        }

        // If first frame moving in this direction update actor direction
        if (!CHK_FLAG(THIS->flags, MOVE_ACTIVE_V)) {
            SET_FLAG(THIS->flags, MOVE_ACTIVE_V);
            actor_set_dir(actor, new_dir, TRUE);
        }

        // Check if overshot destination
        if (
            (new_dir == DIR_UP && (actor->pos.y <= params->Y)) || // Overshot above
            (new_dir == DIR_DOWN &&  (actor->pos.y >= params->Y)) // Overshot below
         ) {
            actor->pos.y = params->Y;
            SET_FLAG(THIS->flags, MOVE_ALLOW_H);
            CLR_FLAG(THIS->flags, MOVE_V);
        }
    }

    // Actor reached destination
    if (!CHK_FLAG(THIS->flags, MOVE_NEEDED_H | MOVE_NEEDED_V)) {
        THIS->flags = MOVE_INACTIVE;
        actor_set_anim_idle(actor);
        return;
    }

    THIS->PC -= (INSTRUCTION_SIZE + sizeof(idx));
    return;
}

void vm_actor_move_cancel(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor_t * actor = actors + *n_actor;

    SET_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT);
}

void vm_actor_activate(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor_t * actor = actors + *n_actor;
    if (actor == &PLAYER) {
        CLR_FLAG(actor->flags, ACTOR_FLAG_HIDDEN);
    } else {
        CLR_FLAG(actor->flags, ACTOR_FLAG_DISABLED);
        activate_actor(actor);
    }
}

void vm_actor_deactivate(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor_t * actor = actors + *n_actor;
    if (actor == &PLAYER) {
        SET_FLAG(actor->flags, ACTOR_FLAG_HIDDEN);
    } else {
        SET_FLAG(actor->flags, ACTOR_FLAG_DISABLED);
        deactivate_actor(actor);
    }
}

void vm_actor_begin_update(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_set_pos_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    if ((actor->script_update.bank) && (actor->hscript_update & SCRIPT_TERMINATED)) {
        script_execute(actor->script_update.bank, actor->script_update.ptr, &(actor->hscript_update), 0);
    }
}

void vm_actor_terminate_update(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_set_pos_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    if ((actor->hscript_update & SCRIPT_TERMINATED) == 0) {
        script_terminate(actor->hscript_update);
    }
}

void vm_actor_set_dir(SCRIPT_CTX * THIS, INT16 idx, direction_e dir) OLDCALL BANKED {
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor_set_dir(actors + *n_actor, dir, FALSE);
}

void vm_actor_set_anim(SCRIPT_CTX * THIS, INT16 idx, INT16 idx_anim) OLDCALL BANKED {
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    UBYTE * n_anim = VM_REF_TO_PTR(idx_anim);
    actor_set_anim(actors + *n_actor, *n_anim);
}

void vm_actor_set_pos(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_set_pos_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    actor->pos.x = params->X;
    actor->pos.y = params->Y;
}

void vm_actor_get_pos(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_set_pos_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    params->X = actor->pos.x;
    params->Y = actor->pos.y;
}

void vm_actor_get_dir(SCRIPT_CTX * THIS, INT16 idx, INT16 dest) OLDCALL BANKED {
    UWORD * A;
    actor_t *actor;

    act_set_pos_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    if (dest < 0) A = THIS->stack_ptr + dest; else A = script_memory + dest;
    *A = actor->dir;
}

static const UBYTE dir_angle_lookup[4] = { 128, 64, 0, 192 };
void vm_actor_get_angle(SCRIPT_CTX * THIS, INT16 idx, INT16 dest) OLDCALL BANKED {
    UWORD * A;
    actor_t *actor;

    act_set_pos_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    if (dest < 0) A = THIS->stack_ptr + dest; else A = script_memory + dest;
    *A = dir_angle_lookup[actor->dir];
}

void vm_actor_emote(SCRIPT_CTX * THIS, INT16 idx, UBYTE emote_tiles_bank, const unsigned char *emote_tiles) OLDCALL BANKED {

    // on first call load emote sprite
    if (THIS->flags == 0) {
        UBYTE * n_actor = VM_REF_TO_PTR(idx);
        THIS->flags = 1;
        emote_actor = actors + *n_actor;
        emote_timer = 1;
        load_emote(emote_tiles, emote_tiles_bank);
    }

    if (emote_timer == EMOTE_TOTAL_FRAMES) {
        // Reset ctx flags
        THIS->flags = 0;
        emote_actor = NULL;
    } else {
        THIS->waitable = 1;
        emote_timer++;
        THIS->PC -= (INSTRUCTION_SIZE + sizeof(idx) + sizeof(emote_tiles_bank) + sizeof(emote_tiles));
    }
}

void vm_actor_set_bounds(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;
    act_set_bounds_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);
    actor->bounds.left = params->LEFT;
    actor->bounds.right = params->RIGHT;
    actor->bounds.top = params->TOP;
    actor->bounds.bottom = params->BOTTOM;
}

void vm_actor_set_spritesheet(SCRIPT_CTX * THIS, INT16 idx, UBYTE spritesheet_bank, const spritesheet_t *spritesheet) OLDCALL BANKED {
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor_t * actor = actors + *n_actor;
    load_sprite(actor->base_tile, spritesheet, spritesheet_bank);
    actor->sprite.bank = spritesheet_bank;
    actor->sprite.ptr = (void *)spritesheet;
    load_animations(spritesheet, spritesheet_bank, ANIM_SET_DEFAULT, actor->animations);
    load_bounds(spritesheet, spritesheet_bank, &actor->bounds);
    actor_reset_anim(actor);
}

void vm_actor_replace_tile(SCRIPT_CTX * THIS, INT16 idx, UBYTE target_tile, UBYTE tileset_bank, const tileset_t * tileset, UBYTE start_tile, UBYTE length) OLDCALL BANKED {
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor_t * actor = actors + *n_actor;
    SetBankedSpriteData(actor->base_tile + target_tile, length, tileset->tiles + (start_tile << 4), tileset_bank);
}

void vm_actor_set_anim_tick(SCRIPT_CTX * THIS, INT16 idx, UBYTE tick) OLDCALL BANKED {
    actor_t *actor;
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor = actors + *n_actor;
    actor->anim_tick = tick;
}

void vm_actor_set_move_speed(SCRIPT_CTX * THIS, INT16 idx, UBYTE speed) OLDCALL BANKED {
    actor_t *actor;
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor = actors + *n_actor;
    actor->move_speed = speed;
}

void vm_actor_set_anim_frame(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_set_frame_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    actor_set_frame_offset(actor, params->FRAME);
}

void vm_actor_get_anim_frame(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_set_frame_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    params->FRAME = actor_get_frame_offset(actor);
}

void vm_actor_set_anim_set(SCRIPT_CTX * THIS, INT16 idx, UWORD offset) OLDCALL BANKED {
    actor_t *actor;
    UBYTE * n_actor = VM_REF_TO_PTR(idx);
    actor = actors + *n_actor;
    load_animations(actor->sprite.ptr, actor->sprite.bank, offset, actor->animations);
    actor_reset_anim(actor);
}

void vm_actor_set_spritesheet_by_ref(SCRIPT_CTX * THIS, INT16 idxA, INT16 idxB) OLDCALL BANKED {
    actor_t *actor;
    UBYTE * n_actor = VM_REF_TO_PTR(idxA);
    actor = actors + *n_actor;

    gbs_farptr_t * params = VM_REF_TO_PTR(idxB);
    UBYTE spritesheet_bank = (UBYTE)(params->BANK);
    const spritesheet_t *spritesheet = params->DATA;

    load_sprite(actor->base_tile, spritesheet, spritesheet_bank);
    actor->sprite.bank = spritesheet_bank;
    actor->sprite.ptr = (void *)spritesheet;
    load_animations(spritesheet, spritesheet_bank, ANIM_SET_DEFAULT, actor->animations);
    load_bounds(spritesheet, spritesheet_bank, &actor->bounds);
    actor_reset_anim(actor);
}

void vm_actor_set_flags(SCRIPT_CTX * THIS, INT16 idx, UBYTE flags, UBYTE mask) OLDCALL BANKED {
    actor_t * actor = actors + *(UBYTE *)VM_REF_TO_PTR(idx);
    actor->flags |= (mask & flags);
    actor->flags &= ~(mask & ~flags);
}

void vm_actor_move_to_init(SCRIPT_CTX * THIS, INT16 idx, UBYTE attr) OLDCALL BANKED {
    actor_t *actor;

    THIS->waitable = TRUE;

    act_move_to_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    CLR_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT);

    // Switch to moving animation frames

    // Snap to nearest pixel before moving
    actor->pos.x = SUBPX_SNAP_PX(actor->pos.x);
    actor->pos.y = SUBPX_SNAP_PX(actor->pos.y);

    // If moving relative add current position
    // and prevent overflow
    if (CHK_FLAG(attr, ACTOR_ATTR_RELATIVE)) {
        params->X = saturating_add_u16(actor->pos.x, (WORD)params->X);
        params->Y = saturating_add_u16(actor->pos.y, (WORD)params->Y);
    }
    // and snap destination to either pixels/tiles
    if (CHK_FLAG(attr, ACTOR_ATTR_RELATIVE_SNAP_PX)) {
        params->X = SUBPX_SNAP_PX(params->X);
        params->Y = SUBPX_SNAP_PX(params->Y);
    } else if (CHK_FLAG(attr, ACTOR_ATTR_RELATIVE_SNAP_TILE)) {
        params->X = SUBPX_SNAP_TILE(params->X);
        params->Y = SUBPX_SNAP_TILE(params->Y);
    }

    // Check for collisions in path
    if (CHK_FLAG(attr, ACTOR_ATTR_CHECK_COLL_WALLS)) {
        if (CHK_FLAG(attr, ACTOR_ATTR_H_FIRST)) {
            // Check for horizontal collision
            if (actor->pos.x != params->X) {
                params->X = check_collision_horizontal(actor->pos.x, actor->pos.y, &actor->bounds, params->X);
            }
            // Check for vertical collision
            if (actor->pos.y != params->Y) {
                params->Y = check_collision_vertical(params->X, actor->pos.y, &actor->bounds, params->Y);
            }
        } else {
            // Check for vertical collision
            if (actor->pos.y != params->Y) {
                params->Y = check_collision_vertical(actor->pos.x, actor->pos.y, &actor->bounds, params->Y);
            }
            // Check for horizontal collision
            if (actor->pos.x != params->X) {
                params->X = check_collision_horizontal(actor->pos.x, params->Y, &actor->bounds, params->X);
            }
        }
    }
}

void vm_actor_move_to_x(SCRIPT_CTX * THIS, INT16 idx, UBYTE attr) OLDCALL BANKED {
    actor_t *actor;

    // indicate waitable state of context
    THIS->waitable = 1;

    act_move_to_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    // Interrupt actor movement
    if (CHK_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT)) {
        // Set new X destination to next tile
        if ((actor->pos.x < params->X) && (actor->pos.x & TILE_FRACTION_MASK)) {   // Bitmask to check for non-grid-aligned position
            params->X = (actor->pos.x & ~TILE_FRACTION_MASK) + ONE_TILE_DISTANCE;  // If moving in positive direction, round up to next tile
        } else {
            params->X = actor->pos.x  & ~TILE_FRACTION_MASK;                       // Otherwise, round down
        }
        // Set new Y destination to next tile
        if ((actor->pos.y < params->Y) && (actor->pos.y & TILE_FRACTION_MASK)) {
            params->Y = (actor->pos.y & ~TILE_FRACTION_MASK) + ONE_TILE_DISTANCE;
        } else {
            params->Y = actor->pos.y  & ~TILE_FRACTION_MASK;
        }
        CLR_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT);
    }

    UBYTE test_actors = CHK_FLAG(attr, ACTOR_ATTR_CHECK_COLL_ACTORS);

    if (params->X == actor->pos.x) {
        // Already at destination
        actor_set_anim_idle(actor);        
        return;
    } else if (params->X < actor->pos.x) {
        // Moving left
        actor->pos.x -= actor->move_speed;

        // Check for actor collision
        actor_t *hit_actor;
        if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) {
            actor->pos.x += actor->move_speed;
            params->Y = actor->pos.y;
            actor_set_anim_idle(actor);
            return;
        }

        // Check if overshot destination
        if (actor->pos.x <= params->X) {
            // Reached Horizontal Destination
            actor->pos.x = params->X;
            actor_set_anim_idle(actor);
            return;
        }
    } else {
        // Moving right
        actor->pos.x += actor->move_speed;

        // Check for actor collision
        actor_t *hit_actor;
        if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) {
            actor->pos.x -= actor->move_speed;
            params->Y = actor->pos.y;
            actor_set_anim_idle(actor);
            return;
        }

        // Check if overshot destination
        if (actor->pos.x >= params->X) {
            // Reached Horizontal Destination
            actor->pos.x = params->X;
            actor_set_anim_idle(actor);
            return;
        }
    }

    THIS->PC -= (INSTRUCTION_SIZE + sizeof(idx) + sizeof(attr));
    return;
}

void vm_actor_move_to_y(SCRIPT_CTX * THIS, INT16 idx, UBYTE attr) OLDCALL BANKED {
    actor_t *actor;

    // indicate waitable state of context
    THIS->waitable = 1;

    act_move_to_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    // Interrupt actor movement
    if (CHK_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT)) {
        // Set new X destination to next tile
        if ((actor->pos.x < params->X) && (actor->pos.x & TILE_FRACTION_MASK)) {   // Bitmask to check for non-grid-aligned position
            params->X = (actor->pos.x & ~TILE_FRACTION_MASK) + ONE_TILE_DISTANCE;  // If moving in positive direction, round up to next tile
        } else {
            params->X = actor->pos.x  & ~TILE_FRACTION_MASK;                       // Otherwise, round down
        }
        // Set new Y destination to next tile
        if ((actor->pos.y < params->Y) && (actor->pos.y & TILE_FRACTION_MASK)) {
            params->Y = (actor->pos.y & ~TILE_FRACTION_MASK) + ONE_TILE_DISTANCE;
        } else {
            params->Y = actor->pos.y  & ~TILE_FRACTION_MASK;
        }
        CLR_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT);
    }

    UBYTE test_actors = CHK_FLAG(attr, ACTOR_ATTR_CHECK_COLL_ACTORS);

    if (params->Y == actor->pos.y) {
        // Already at destination
        actor_set_anim_idle(actor);        
        return;
    } else if (params->Y < actor->pos.y) {
        // Moving upwards 
        actor->pos.y -= actor->move_speed;

        // Check for actor collision
        actor_t *hit_actor;
        if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) { 
            actor->pos.y += actor->move_speed;
            params->X = actor->pos.x;
            actor_set_anim_idle(actor);
            return;
        }

        // Check if overshot destination
        if (actor->pos.y <= params->Y) {
            actor->pos.y = params->Y;
            actor_set_anim_idle(actor);
            return;
        }
    } else {
        // Moving downwards
        actor->pos.y += actor->move_speed;

        // Check for actor collision
        actor_t *hit_actor;
        if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) { 
            actor->pos.y -= actor->move_speed;
            params->X = actor->pos.x;
            actor_set_anim_idle(actor);
            return;
        }

        // Check if overshot destination
        if (actor->pos.y >= params->Y) {
            actor->pos.y = params->Y;
            actor_set_anim_idle(actor);
            return;
        }
    }

    THIS->PC -= (INSTRUCTION_SIZE + sizeof(idx) + sizeof(attr));
    return;
}

void vm_actor_move_to_xy(SCRIPT_CTX * THIS, INT16 idx, UBYTE attr) OLDCALL BANKED {
    actor_t *actor;

    // indicate waitable state of context
    THIS->waitable = 1;

    act_move_to_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);

    // Interrupt actor movement
    if (CHK_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT)) {
        // Set new X destination to next tile
        if ((actor->pos.x < params->X) && (actor->pos.x & TILE_FRACTION_MASK)) {   // Bitmask to check for non-grid-aligned position
            params->X = (actor->pos.x & ~TILE_FRACTION_MASK) + ONE_TILE_DISTANCE;  // If moving in positive direction, round up to next tile
        } else {
            params->X = actor->pos.x  & ~TILE_FRACTION_MASK;                       // Otherwise, round down
        }
        // Set new Y destination to next tile
        if ((actor->pos.y < params->Y) && (actor->pos.y & TILE_FRACTION_MASK)) {
            params->Y = (actor->pos.y & ~TILE_FRACTION_MASK) + ONE_TILE_DISTANCE;
        } else {
            params->Y = actor->pos.y  & ~TILE_FRACTION_MASK;
        }
        CLR_FLAG(actor->flags, ACTOR_FLAG_INTERRUPT);
    }

    UBYTE test_actors = CHK_FLAG(attr, ACTOR_ATTR_CHECK_COLL_ACTORS);

    UBYTE reached_x = params->X == actor->pos.x;
    UBYTE reached_y = params->Y == actor->pos.y;

    if (!reached_x) {
        if (params->X < actor->pos.x) {
            // Moving left
            actor->pos.x -= actor->move_speed;

            // Check for actor collision
            actor_t *hit_actor;
            if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) {
                actor->pos.x += actor->move_speed;
                params->Y = actor->pos.y;
                reached_x = TRUE;
            }

            // Check if overshot destination
            if (actor->pos.x <= params->X) {
                // Reached Horizontal Destination
                actor->pos.x = params->X;
                reached_x = TRUE;
            }
        } else {
            // Moving right
            actor->pos.x += actor->move_speed;

            // Check for actor collision
            actor_t *hit_actor;
            if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) {
                actor->pos.x -= actor->move_speed;
                params->Y = actor->pos.y;
                reached_x = TRUE;
            }

            // Check if overshot destination
            if (actor->pos.x >= params->X) {
                // Reached Horizontal Destination
                actor->pos.x = params->X;
                reached_x = TRUE;
            }
        }
    }

    if (!reached_y) {
        if (params->Y < actor->pos.y) {
            // Moving upwards 
            actor->pos.y -= actor->move_speed;

            // Check for actor collision
            actor_t *hit_actor;
            if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) { 
                actor->pos.y += actor->move_speed;
                params->X = actor->pos.x;
                reached_y = TRUE;
            }

            // Check if overshot destination
            if (actor->pos.y <= params->Y) {
                actor->pos.y = params->Y;
                reached_y = TRUE;
            }
        } else {
            // Moving downwards
            actor->pos.y += actor->move_speed;

            // Check for actor collision
            actor_t *hit_actor;
            if (test_actors && (hit_actor = actor_overlapping_bb(&actor->bounds, &actor->pos, actor))) { 
                actor->pos.y -= actor->move_speed;
                params->X = actor->pos.x;
                reached_y = TRUE;
            }

            // Check if overshot destination
            if (actor->pos.y >= params->Y) {
                actor->pos.y = params->Y;
                reached_y = TRUE;
            }
        }
    }

    if (reached_x && reached_y) {
        // Already at destination
        actor_set_anim_idle(actor);
        return;
    }

    THIS->PC -= (INSTRUCTION_SIZE + sizeof(idx) + sizeof(attr));
    return;
}

void vm_actor_move_to_set_dir_x(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_move_to_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);
    
    if (params->X != actor->pos.x) {
        actor_set_dir(actor, params->X < actor->pos.x ? DIR_LEFT : DIR_RIGHT, TRUE);
    }
}

void vm_actor_move_to_set_dir_y(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_move_to_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);
    
    if (params->Y != actor->pos.y) {
        actor_set_dir(actor, params->Y < actor->pos.y ? DIR_UP : DIR_DOWN, TRUE);
    }
}

void vm_actor_set_anim_moving(SCRIPT_CTX * THIS, INT16 idx) OLDCALL BANKED {
    actor_t *actor;

    act_move_to_t * params = VM_REF_TO_PTR(idx);
    actor = actors + (UBYTE)(params->ID);
    
    actor_set_anim(actor, actor->dir + N_DIRECTIONS);
}
