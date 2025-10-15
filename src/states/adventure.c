#pragma bank 255

#include "data/states_defines.h"
#include "states/adventure.h"

#include <string.h>
#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "game_time.h"
#include "input.h"
#include "scroll.h"
#include "trigger.h"
#include "data_manager.h"
#include "events.h"
#include "rand.h"
#include "vm.h"
#include "math.h"

// Feature Flags --------------------------------------------------------------
// Optional feature flags, set in 'state_defines.h'

#define FEAT_ADVENTURE_BLANK
#define FEAT_ADVENTURE_DASH
// #define FEAT_ADVENTURE_RUN
#define FEAT_ADVENTURE_KNOCKBACK

// End of Feature Flags -------------------------------------------------------

// Constants ------------------------------------------------------------------

#ifndef ADVENTURE_CAMERA_DEADZONE
#define ADVENTURE_CAMERA_DEADZONE 8
#endif

#define MAX_CORNER_PUSH_DISTANCE PX_TO_SUBPX(9)

#define COLLISION_SLOPE 0x10

#define COL_CHECK_X 0x1
#define COL_CHECK_Y 0x2
#define COL_CHECK_ACTORS 0x4
#define COL_CHECK_TRIGGERS 0x8
#define COL_CHECK_WALLS 0x10
#define COL_CHECK_ALL COL_CHECK_X | COL_CHECK_Y | COL_CHECK_ACTORS | COL_CHECK_TRIGGERS | COL_CHECK_WALLS

#define ADVENTURE_ANIM_OVERRIDES_SET \
    (defined(FEAT_ADVENTURE_RUN) && defined(ADVENTURE_RUN_ANIM)) || \
    (defined(FEAT_ADVENTURE_DASH) && defined(ADVENTURE_DASH_ANIM)) || \
    (defined(FEAT_ADVENTURE_KNOCKBACK) && defined(ADVENTURE_KNOCKBACK_ANIM)) || \
    (defined(FEAT_ADVENTURE_BLANK) && defined(ADVENTURE_BLANK_ANIM))

#define MOVE_TYPE_4_WAY 0
#define MOVE_TYPE_8_WAY 1

#define DIR_PRIORITY_NONE 0
#define DIR_PRIORITY_HORIZONTAL 1
#define DIR_PRIORITY_VERTICAL 2

#ifndef INPUT_ADVENTURE_INTERACT
#define INPUT_ADVENTURE_INTERACT INPUT_A
#endif

#ifndef INPUT_ADVENTURE_RUN
#define INPUT_ADVENTURE_RUN INPUT_B
#endif

#ifndef INPUT_ADVENTURE_MOVE_TYPE
#define INPUT_ADVENTURE_MOVE_TYPE MOVE_TYPE_8_WAY
#endif

// End of Constants -----------------------------------------------------------

// Macros ---------------------------------------------------------------------

#define VEL_TO_SUBPX(v) ((((v) & 0x8000) ? (((v) >> 8) | 0xFF00) : ((v) >> 8)) << 1)
#define DELTA_TO_VEL(v) ((v) << 8)

// End of Macros --------------------------------------------------------------

// Type Definitions -----------------------------------------------------------
typedef enum
{
    GROUND_STATE = 0,
    DASH_STATE,
    KNOCKBACK_STATE,
    BLANK_STATE,
    RUN_STATE,
} state_e;

typedef enum
{
    GROUND_INIT = 0,
    GROUND_END,
    DASH_INIT,
    DASH_END,
    KNOCKBACK_INIT,
    KNOCKBACK_END,
    BLANK_INIT,
    BLANK_END,
    DASH_READY,
    RUN_INIT,
    RUN_END,
    CALLBACK_SIZE
} callback_e;

// End of Type Definitions ----------------------------------------------------

// Engine Fields --------------------------------------------------------------

WORD adv_walk_vel;            // Maximum velocity while walking
WORD adv_run_vel;             // Maximum velocity while running
WORD adv_dec;
WORD adv_turn_acc;
WORD adv_walk_acc;
WORD adv_run_acc;
WORD adv_knockback_vel_x;     // Knockback velocity in the x direction
WORD adv_knockback_vel_y;     // Knockback velocity in the y direction
UBYTE adv_knockback_frames;   // Number of frames for knockback

// End of Engine Fields -------------------------------------------------------

// Runtime State --------------------------------------------------------------

script_event_t adv_events[CALLBACK_SIZE];

// State machine
state_e adv_state;            // Current adventure state
state_e adv_next_state;       // Next frame's adventure state

WORD adv_vel_x;               // Tracks the player's x-velocity between frames
WORD adv_vel_y;               // Tracks the player's y-velocity between frames

// Track last cardinal direction for facing
static direction_e facing_dir = DIR_DOWN;
static point16_t delta;
static point16_t movement_delta;

// Counters
UBYTE adv_knockback_timer;    // Current Knockback frame

// Animation
UBYTE adv_anim_dirty;         // Tracks whether the player animation has been modified from the default

// Solid actors
actor_t *adv_attached_actor;  // The last actor the player hit, and that they were attached to
UBYTE adv_is_actor_attached;  // Keeps track of whether the player is currently on an actor
UWORD adv_attached_prev_x;    // Keeps track of the pos.x of the attached actor from the previous frame
UWORD adv_attached_prev_y;    // Keeps track of the pos.y of the attached actor from the previous frame
UWORD adv_temp_y = 0;         // Temporary y position for the player when moving and colliding with an solid actor
static direction_e collision_dir;
static UWORD temp_y;    // Player's position on the last frame
static UWORD temp_x;    // Player's position on the last frame
UWORD adv_pos_x; // Used for debugging position @TODO remove this
UWORD adv_pos_y; // Used for debugging position @TODO remove this

// End of Runtime State -------------------------------------------------------

// Function Definitions -------------------------------------------------------

static void move_and_collide(UBYTE mask);
static void handle_dir_input(void);
static void adv_deceleration(void);

void adv_state_script_attach(SCRIPT_CTX *THIS) OLDCALL BANKED;
void adv_state_script_detach(SCRIPT_CTX *THIS) OLDCALL BANKED;
void adv_callback_reset(void);
static void adv_callback_execute(UBYTE i);

#if ADVENTURE_ANIM_OVERRIDES_SET

inline void adv_set_player_anim_state(UBYTE anim)
{
    load_animations(PLAYER.sprite.ptr, PLAYER.sprite.bank, anim, PLAYER.animations);
    actor_reset_anim(&PLAYER);
    adv_anim_dirty = TRUE;
}

inline void adv_restore_default_anim_state(void)
{
    if (adv_anim_dirty) {
        load_animations(PLAYER.sprite.ptr, PLAYER.sprite.bank, 0, PLAYER.animations);
        actor_reset_anim(&PLAYER);  
        adv_anim_dirty = FALSE;             
    }
}

#endif

// End of Function Definitions ------------------------------------------------

void adventure_init(void) BANKED {
    // Set camera to follow player
    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = ADVENTURE_CAMERA_DEADZONE;
    camera_deadzone_y = ADVENTURE_CAMERA_DEADZONE;

    // Initialize facing direction
    facing_dir = DIR_DOWN;
    delta.x  = 0;
    delta.y  = 0;
    movement_delta.x = 0;
    movement_delta.y = 0;
    adv_vel_x = 0;
    adv_vel_y = 0;

    collision_dir = DIR_NONE;
    // @TODO - should be set in engine.json

    adv_state = GROUND_STATE;
}

void adventure_update(void) BANKED {
  // State transitions

    if (adv_state != adv_next_state)
    {
        // Exit state
        switch (adv_state)
        {
            case GROUND_STATE: {
                adv_callback_execute(GROUND_END);
                break;
            }
#ifdef FEAT_ADVENTURE_RUN
            case RUN_STATE: {
                adv_callback_execute(RUN_END);
                break;
            }
#endif              
#ifdef FEAT_ADVENTURE_KNOCKBACK
            case KNOCKBACK_STATE: {
                adv_vel_x = 0;
                adv_callback_execute(KNOCKBACK_END);
                break;
            }
#endif
#ifdef FEAT_ADVENTURE_BLANK
            case BLANK_STATE: {
                adv_vel_x = 0;
                adv_vel_y = 0;
                adv_callback_execute(BLANK_END);
                break;
            }
#endif
        }

        adv_state = adv_next_state;

        // Enter state
        switch (adv_state)
        {
            case GROUND_STATE: {
#if ADVENTURE_ANIM_OVERRIDES_SET
                adv_restore_default_anim_state();
#endif
                adv_callback_execute(GROUND_INIT);
                break;
            }
#ifdef FEAT_ADVENTURE_RUN
            case RUN_STATE: {
#ifdef ADVENTURE_RUN_ANIM
                adv_set_player_anim_state(ADVENTURE_RUN_ANIM);
#elif ADVENTURE_ANIM_OVERRIDES_SET
                adv_restore_default_anim_state();
#endif
                adv_callback_execute(RUN_INIT);
                break;
            }
#endif            
#ifdef FEAT_ADVENTURE_KNOCKBACK
            case KNOCKBACK_STATE: {
                adv_vel_x = PLAYER.dir == DIR_RIGHT ? -adv_knockback_vel_x : adv_knockback_vel_x;
                adv_vel_y = -adv_knockback_vel_y;
                adv_knockback_timer = adv_knockback_frames;
#ifdef ADVENTURE_KNOCKBACK_ANIM
                adv_set_player_anim_state(ADVENTURE_KNOCKBACK_ANIM);
#elif ADVENTURE_ANIM_OVERRIDES_SET
                adv_restore_default_anim_state();
#endif
                adv_callback_execute(KNOCKBACK_INIT);
                break;
            }
#endif
#ifdef FEAT_ADVENTURE_BLANK
            case BLANK_STATE: {
                adv_vel_x = 0;
                adv_vel_y = 0;
#ifdef ADVENTURE_BLANK_ANIM
                adv_set_player_anim_state(ADVENTURE_BLANK_ANIM);
#elif ADVENTURE_ANIM_OVERRIDES_SET
                adv_restore_default_anim_state();
#endif
                adv_callback_execute(BLANK_INIT);
                break;
            }
#endif      
        }  
    }


    // STATE MACHINE =======================================================

    switch (adv_state)
    {
        case GROUND_STATE:
        case RUN_STATE: {

            handle_dir_input();
            adv_deceleration();

            if (collision_dir != DIR_NONE) {
                // Push away from attached solid actor
                WORD delta_mp_x = adv_attached_actor->pos.x - adv_attached_prev_x;
                WORD delta_mp_y = adv_attached_actor->pos.y - adv_attached_prev_y;
                adv_attached_prev_x = adv_attached_actor->pos.x;
                adv_attached_prev_y = adv_attached_actor->pos.y;
                
                if (collision_dir == DIR_DOWN && delta_mp_y > adv_vel_y) {
                    adv_vel_y = MAX(0, DELTA_TO_VEL(delta_mp_y));
                } else if (collision_dir == DIR_UP && delta_mp_y < adv_vel_y) {
                    adv_vel_y = MIN(0, DELTA_TO_VEL(delta_mp_y));
                } else if (collision_dir == DIR_LEFT && delta_mp_x < adv_vel_x) {
                    adv_vel_x = MIN(0, DELTA_TO_VEL(delta_mp_x));
                } else if (collision_dir == DIR_RIGHT && delta_mp_x > adv_vel_x) {
                    adv_vel_x = MAX(0, DELTA_TO_VEL(delta_mp_x));
                }
            }

            delta.x = VEL_TO_SUBPX(adv_vel_x);
            delta.y = VEL_TO_SUBPX(adv_vel_y);

            move_and_collide(COL_CHECK_ALL);

            if (INPUT_PRESSED(INPUT_ADVENTURE_INTERACT)) {
                actor_t *hit_actor = adv_attached_actor;
                if (!hit_actor) {
                    hit_actor = actor_in_front_of_player(8, TRUE);
                }
                if (hit_actor && !(hit_actor->collision_group & COLLISION_GROUP_MASK) && hit_actor->script.bank) {
                    actor_set_dir(hit_actor, FLIPPED_DIR(PLAYER.dir), FALSE);
                    script_execute(hit_actor->script.bank, hit_actor->script.ptr, 0, 1, 0);
                }
            }

#ifdef FEAT_ADVENTURE_RUN
            const UBYTE running = INPUT_ADVENTURE_RUN;
            if (adv_state == GROUND_STATE && running) {
                adv_next_state = RUN_STATE;
                break;
            } else if (adv_state == RUN_STATE && !running) {
                adv_next_state = GROUND_STATE;
                break;
            }
#endif

            // Facing and animation update
            if (joy & INPUT_DPAD) {
                actor_set_dir(&PLAYER, facing_dir, TRUE);
            } else {
                actor_set_anim_idle(&PLAYER);
            }
            
            break;
        }

    }
}

static void handle_dir_input(void) {
    WORD target_x = 0;
    WORD target_y = 0;
    static UBYTE facing_priority_axis = DIR_PRIORITY_NONE;

#ifdef FEAT_ADVENTURE_RUN
    const WORD max_vel = (adv_state == RUN_STATE) ? adv_run_vel : adv_walk_vel;
    const WORD base_acc = (adv_state == RUN_STATE) ? adv_run_acc : adv_walk_acc;
#else
    const WORD max_vel = adv_walk_vel;
    const WORD base_acc = adv_walk_acc;    
#endif

#if INPUT_ADVENTURE_MOVE_TYPE == MOVE_TYPE_8_WAY
    // ---------------------- 8-WAY ----------------------
    const UBYTE left  = INPUT_LEFT;
    const UBYTE right = INPUT_RIGHT;
    const UBYTE up    = INPUT_UP;
    const UBYTE down  = INPUT_DOWN;

    // Determine velocity intent
    if (left)  target_x = -max_vel;
    if (right) target_x =  max_vel;
    if (up)    target_y = -max_vel;
    if (down)  target_y =  max_vel;

    // Update facing priority axis
    if ((left | right) && !(up | down)) {
        facing_priority_axis = DIR_PRIORITY_HORIZONTAL;
    } else if ((up | down) && !(left | right)) {
        facing_priority_axis = DIR_PRIORITY_VERTICAL;
    } else if (!(left | right | up | down)) {
        facing_priority_axis = DIR_PRIORITY_NONE;
    }

    // Determine facing based on which axis was pressed first
    if ((left | right) && (up | down)) {
        // Both axes pressed, respect whichever axis was pressed first
        if (facing_priority_axis == DIR_PRIORITY_HORIZONTAL) {
            facing_dir = left ? DIR_LEFT : DIR_RIGHT;
        } else if (facing_priority_axis == DIR_PRIORITY_VERTICAL) {
            facing_dir = up ? DIR_UP : DIR_DOWN;
        }
    } else if (left) {
        facing_dir = DIR_LEFT;
    } else if (right) {
        facing_dir = DIR_RIGHT;
    } else if (up) {
        facing_dir = DIR_UP;
    } else if (down) {
        facing_dir = DIR_DOWN;
    } else {
        facing_dir = DIR_NONE;
    }
#else
    // ---------------------- 4-WAY ----------------------
    if (INPUT_RECENT_LEFT) {
        target_x = -max_vel;
        facing_dir = DIR_LEFT;
    } else if (INPUT_RECENT_RIGHT) {
        target_x =  max_vel;
        facing_dir = DIR_RIGHT;
    } else if (INPUT_RECENT_UP) {
        target_y = -max_vel;
        facing_dir = DIR_UP;
    } else if (INPUT_RECENT_DOWN) {
        target_y =  max_vel;
        facing_dir = DIR_DOWN;
    } else {
        facing_dir = DIR_NONE;
    }
#endif

    // ---------------------- Apply Acceleration ----------------------
    if (target_x != 0) {
        WORD acc_x = ((target_x > 0 && adv_vel_x < 0) || (target_x < 0 && adv_vel_x > 0))
            ? adv_turn_acc : base_acc;

        if (target_x > adv_vel_x) {
            adv_vel_x += acc_x;
            if (adv_vel_x >  max_vel) adv_vel_x =  max_vel;
        } else if (target_x < adv_vel_x) {
            adv_vel_x -= acc_x;
            if (adv_vel_x < -max_vel) adv_vel_x = -max_vel;
        }
    }

    if (target_y != 0) {
        WORD acc_y = ((target_y > 0 && adv_vel_y < 0) || (target_y < 0 && adv_vel_y > 0))
            ? adv_turn_acc : base_acc;

        if (target_y > adv_vel_y) {
            adv_vel_y += acc_y;
            if (adv_vel_y >  max_vel) adv_vel_y =  max_vel;
        } else if (target_y < adv_vel_y) {
            adv_vel_y -= acc_y;
            if (adv_vel_y < -max_vel) adv_vel_y = -max_vel;
        }
    }
}

static void move_and_collide(UBYTE mask)
{
    temp_x = PLAYER.pos.x;
    temp_y = PLAYER.pos.y;

    adv_pos_x = PLAYER.pos.x;
    adv_pos_y = PLAYER.pos.y;

    // Horizontal Movement
    if (mask & COL_CHECK_X)
    {
        UWORD new_x = PLAYER.pos.x + delta.x;
        // Step X
        UBYTE tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
        UBYTE tile_end   = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
        if (delta.x > 0) {
            UBYTE tile_x = SUBPX_TO_TILE(new_x + PLAYER.bounds.right);
            UBYTE tile = tile_col_test_range_y(COLLISION_LEFT, tile_x, tile_start, tile_end);
            if (tile) {
                new_x = TILE_TO_SUBPX(tile_x) - EXCLUSIVE_OFFSET(PLAYER.bounds.right);
                adv_vel_x = 0;
                if (tile & COLLISION_SLOPE && delta.y == 0) {
                    if (tile & COLLISION_TOP) {
                        UWORD target_y = TILE_TO_SUBPX(tile_hit_y) - EXCLUSIVE_OFFSET(PLAYER.bounds.bottom);
                        if (PLAYER.pos.y < target_y + MAX_CORNER_PUSH_DISTANCE) {
                            adv_attached_actor = NULL;
                            PLAYER.pos.y -= VEL_TO_SUBPX(adv_walk_vel);
                            if (PLAYER.pos.y < target_y) {
                                PLAYER.pos.y = target_y;
                            }
                        }
                    } else if (tile & COLLISION_BOTTOM) {
                        UWORD target_y = TILE_TO_SUBPX(tile_hit_y + 1) + 1 - EXCLUSIVE_OFFSET(PLAYER.bounds.top);
                        if (PLAYER.pos.y > target_y - MAX_CORNER_PUSH_DISTANCE) {
                            adv_attached_actor = NULL;
                            PLAYER.pos.y += VEL_TO_SUBPX(adv_walk_vel);
                            if (PLAYER.pos.y > target_y) {
                                PLAYER.pos.y = target_y;
                            }
                        }
                    }
                } 
            }
            PLAYER.pos.x = MIN(image_width_subpx - EXCLUSIVE_OFFSET(PLAYER.bounds.right), new_x);
        } else if (delta.x < 0) {
            UBYTE tile_x = SUBPX_TO_TILE(new_x + PLAYER.bounds.left);
            UBYTE tile = tile_col_test_range_y(COLLISION_RIGHT, tile_x, tile_start, tile_end);
            if (tile) {
                new_x = TILE_TO_SUBPX(tile_x + 1) - PLAYER.bounds.left;
                adv_vel_x = 0;
                if (tile & COLLISION_SLOPE && delta.y == 0) {
                    if (tile & COLLISION_TOP) {
                        UWORD target_y = TILE_TO_SUBPX(tile_hit_y) - EXCLUSIVE_OFFSET(PLAYER.bounds.bottom);
                        if (PLAYER.pos.y < target_y + MAX_CORNER_PUSH_DISTANCE) {
                            adv_attached_actor = NULL;
                            PLAYER.pos.y -= VEL_TO_SUBPX(adv_walk_vel);
                            if (PLAYER.pos.y < target_y) {
                                PLAYER.pos.y = target_y;
                            }
                        }
                    } else if (tile & COLLISION_BOTTOM) {
                        UWORD target_y = TILE_TO_SUBPX(tile_hit_y + 1) + 1 - EXCLUSIVE_OFFSET(PLAYER.bounds.top);
                        if (PLAYER.pos.y > target_y - MAX_CORNER_PUSH_DISTANCE) {
                            adv_attached_actor = NULL;
                            PLAYER.pos.y += VEL_TO_SUBPX(adv_walk_vel);
                            if (PLAYER.pos.y > target_y) {
                                PLAYER.pos.y = target_y;
                            }
                        }
                    }
                }
            }
            PLAYER.pos.x = new_x;
        }
    }

    // Vertical Movement
    if (mask & COL_CHECK_Y)
    {
        UWORD new_y = PLAYER.pos.y + delta.y;

        // Step Y
        UBYTE tile_start = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
        UBYTE tile_end   = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);
        if (delta.y > 0) {
            UBYTE tile_y = SUBPX_TO_TILE(new_y + PLAYER.bounds.bottom);
            UBYTE tile = tile_col_test_range_x(COLLISION_TOP, tile_y, tile_start, tile_end);
            if (tile) {
                new_y = TILE_TO_SUBPX(tile_y) - EXCLUSIVE_OFFSET(PLAYER.bounds.bottom);
                adv_vel_y = 0;
                if (tile & COLLISION_SLOPE && delta.x == 0) {
                    if (tile & COLLISION_LEFT) {
                        UWORD target_x = TILE_TO_SUBPX(tile_hit_x) - EXCLUSIVE_OFFSET(PLAYER.bounds.right);
                        if (PLAYER.pos.x < target_x + MAX_CORNER_PUSH_DISTANCE) {
                            adv_attached_actor = NULL;
                            PLAYER.pos.x -= VEL_TO_SUBPX(adv_walk_vel);
                            if (PLAYER.pos.x < target_x) {
                                PLAYER.pos.x = target_x;   
                            }
                        }                            
                    } else if (tile & COLLISION_RIGHT) {
                        UWORD target_x = TILE_TO_SUBPX(tile_hit_x + 1) + 1 - EXCLUSIVE_OFFSET(PLAYER.bounds.left);
                        if (PLAYER.pos.x > target_x - MAX_CORNER_PUSH_DISTANCE) {
                            adv_attached_actor = NULL;
                            PLAYER.pos.x += VEL_TO_SUBPX(adv_walk_vel);
                            if (PLAYER.pos.x > target_x) {
                                PLAYER.pos.x = target_x;   
                            }
                        }
                    }                        
                }
            }
            PLAYER.pos.y = new_y;
        } else if (delta.y < 0) {
            UBYTE tile_y = SUBPX_TO_TILE(new_y + PLAYER.bounds.top);
            UBYTE tile = tile_col_test_range_x(COLLISION_BOTTOM, tile_y, tile_start, tile_end);
            if (tile) {            
                new_y = TILE_TO_SUBPX(tile_y + 1) - PLAYER.bounds.top;
                adv_vel_y = 0;
                if (tile & COLLISION_SLOPE && delta.x == 0) {
                    if (tile & COLLISION_LEFT) {
                        UWORD target_x = TILE_TO_SUBPX(tile_hit_x) - EXCLUSIVE_OFFSET(PLAYER.bounds.right);
                        if (PLAYER.pos.x < target_x + MAX_CORNER_PUSH_DISTANCE) {
                            adv_attached_actor = NULL;
                            PLAYER.pos.x -= VEL_TO_SUBPX(adv_walk_vel);
                            if (PLAYER.pos.x < target_x) {
                                PLAYER.pos.x = target_x;   
                            }  
                        }                          
                    } else if (tile & COLLISION_RIGHT) {
                        UWORD target_x = TILE_TO_SUBPX(tile_hit_x + 1) + 1 - EXCLUSIVE_OFFSET(PLAYER.bounds.left);
                        if (PLAYER.pos.x > target_x - MAX_CORNER_PUSH_DISTANCE) {
                            adv_attached_actor = NULL;
                            PLAYER.pos.x += VEL_TO_SUBPX(adv_walk_vel);
                            if (PLAYER.pos.x > target_x) {
                                PLAYER.pos.x = target_x;   
                            }
                        }
                    }
                }
            }
            PLAYER.pos.y = new_y;
        }
    }

    delta.x  = 0;
    delta.y  = 0;

    if (mask & COL_CHECK_ACTORS)
    {
        actor_t *hit_actor;
        hit_actor = actor_overlapping_player(FALSE);
        if (hit_actor != NULL) {
            const UBYTE is_solid = hit_actor->collision_group & COLLISION_GROUP_FLAG_SOLID;
             if (is_solid && hit_actor != adv_attached_actor)
            {
                adv_attached_prev_x = hit_actor->pos.x;
                adv_attached_prev_y = hit_actor->pos.y;

                if (hit_actor != adv_attached_actor) {
                    adv_attached_actor = hit_actor;
                    adv_attached_prev_x = hit_actor->pos.x;
                    adv_attached_prev_y = hit_actor->pos.y;
                    if ((temp_y + PLAYER.bounds.bottom) < (hit_actor->pos.y + hit_actor->bounds.top)) {
                        PLAYER.pos.y += (hit_actor->pos.y + hit_actor->bounds.top) - (PLAYER.pos.y + EXCLUSIVE_OFFSET(PLAYER.bounds.bottom));
                        collision_dir = DIR_UP;
                    } else if ((temp_y  + PLAYER.bounds.top) > (hit_actor->pos.y + hit_actor->bounds.bottom)) {
                        PLAYER.pos.y += (hit_actor->pos.y + EXCLUSIVE_OFFSET(hit_actor->bounds.bottom)) - (PLAYER.pos.y + PLAYER.bounds.top);
                        collision_dir = DIR_DOWN;
                    } else if ((temp_x + PLAYER.bounds.right) < (hit_actor->pos.x + hit_actor->bounds.left)) {
                        PLAYER.pos.x += (hit_actor->pos.x + hit_actor->bounds.left) - (PLAYER.pos.x + EXCLUSIVE_OFFSET(PLAYER.bounds.right));
                        collision_dir = DIR_LEFT;
                    } else if ((temp_x + PLAYER.bounds.left) > hit_actor->pos.x + hit_actor->bounds.right) {
                        PLAYER.pos.x += (hit_actor->pos.x + EXCLUSIVE_OFFSET(hit_actor->bounds.right)) - (PLAYER.pos.x + PLAYER.bounds.left);
                        collision_dir = DIR_RIGHT;
                    } else {
                        collision_dir = hit_actor->dir;
                    }
                }
            }
        } else {
            adv_attached_actor = NULL;
            collision_dir = DIR_NONE;
            adv_attached_prev_x = 0;
            adv_attached_prev_y = 0;
        }
    }

    if (mask & COL_CHECK_TRIGGERS)
    {
        trigger_activate_at_intersection(&PLAYER.bounds, &PLAYER.pos, FALSE);
    }    
}


void adv_callback_attach(SCRIPT_CTX *THIS) OLDCALL BANKED
{
    UWORD *slot = VM_REF_TO_PTR(FN_ARG2);
    UBYTE *bank = VM_REF_TO_PTR(FN_ARG1);
    UBYTE **ptr = VM_REF_TO_PTR(FN_ARG0);
    adv_events[*slot].script_bank = *bank;
    adv_events[*slot].script_addr = *ptr;
}

void adv_callback_detach(SCRIPT_CTX *THIS) OLDCALL BANKED
{
    UWORD *slot = VM_REF_TO_PTR(FN_ARG0);
    adv_events[*slot].script_bank = NULL;
    adv_events[*slot].script_addr = NULL;
}

inline void adv_callback_reset(void)
{
    memset(adv_events, 0, sizeof(adv_events));
}

static void adv_callback_execute(UBYTE i)
{
    script_event_t *event = &adv_events[i];
    if (!event->script_addr)
        return;
    if ((event->handle == 0) || ((event->handle & SCRIPT_TERMINATED) != 0))
    {
        script_execute(event->script_bank, event->script_addr, &event->handle, 0, 0);
    }
}

static void adv_deceleration(void) {
#if INPUT_ADVENTURE_MOVE_TYPE == MOVE_TYPE_8_WAY
    if (!(INPUT_LEFT | INPUT_RIGHT)) {
        if (adv_vel_x > adv_dec) {
            adv_vel_x -= adv_dec;
        } else if (adv_vel_x < -adv_dec) {
            adv_vel_x += adv_dec;
        } else {
            adv_vel_x = 0;
        }
    }

    if (!(INPUT_UP | INPUT_DOWN)) {
        if (adv_vel_y > adv_dec) {
            adv_vel_y -= adv_dec;
        } else if (adv_vel_y < -adv_dec) {
            adv_vel_y += adv_dec;
        } else {
            adv_vel_y = 0;
        }
    }
#else
    if (!(INPUT_RECENT_LEFT | INPUT_RECENT_RIGHT)) {
        if (adv_vel_x > adv_dec) {
            adv_vel_x -= adv_dec;
        } else if (adv_vel_x < -adv_dec) {
            adv_vel_x += adv_dec;
        } else {
            adv_vel_x = 0;
        }
    }

    if (!(INPUT_RECENT_UP | INPUT_RECENT_DOWN)) {
        if (adv_vel_y > adv_dec) {
            adv_vel_y -= adv_dec;
        } else if (adv_vel_y < -adv_dec) {
            adv_vel_y += adv_dec;
        } else {
            adv_vel_y = 0;
        }
    }
#endif
}
