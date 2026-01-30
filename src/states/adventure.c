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

// #define FEAT_ADVENTURE_BLANK
// #define FEAT_ADVENTURE_DASH
// #define FEAT_ADVENTURE_RUN
// #define FEAT_ADVENTURE_KNOCKBACK
// #define FEAT_ADVENTURE_PUSH

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
    (defined(FEAT_ADVENTURE_BLANK) && defined(ADVENTURE_BLANK_ANIM)) || \
    (defined(FEAT_ADVENTURE_PUSH) && defined(ADVENTURE_PUSH_ANIM))

#define MOVE_TYPE_4_WAY 0
#define MOVE_TYPE_8_WAY 1

#define DIRECTION_TYPE_4_WAY 0
#define DIRECTION_TYPE_HORIZONTAL 1

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
#ifndef INPUT_ADVENTURE_DIRECTION_TYPE
#define INPUT_ADVENTURE_DIRECTION_TYPE DIRECTION_TYPE_4_WAY
#endif
#define DASH_INPUT_INTERACT 0
#define DASH_INPUT_DOUBLE_TAP 1
#define DASH_INPUT_A 3
#define DASH_INPUT_B 4

#define DOUBLE_TAP_WINDOW 15
#define MAX_DELTA 127

// End of Constants -----------------------------------------------------------

// Macros ---------------------------------------------------------------------

#define VEL_TO_SUBPX(v) ((((v) & 0x8000) ? (((v) >> 8) | 0xFF00) : ((v) >> 8)) << 1)
#define DELTA_TO_VEL(v) ((v) << 8)

#define COUNTER_DECREMENT(x)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((x) != 0)                                                                                                  \
            (x)--;                                                                                                     \
    } while (0)
#define COUNTER_DECREMENT_CB(x, cond)                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((x) != 0) {                                                                                                \
            (x)--;                                                                                                     \
            if ((x) == 0) cond                                                                                         \
        }                                                                                                              \
    } while (0)

// End of Macros --------------------------------------------------------------

// Type Definitions -----------------------------------------------------------

typedef enum
{
    GROUND_STATE = 0,
    DASH_STATE,
    KNOCKBACK_STATE,
    BLANK_STATE,
    RUN_STATE,
    PUSH_STATE,
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
    PUSH_INIT,
    PUSH_END,
    CALLBACK_SIZE
} callback_e;

// End of Type Definitions ----------------------------------------------------

// Engine Fields --------------------------------------------------------------

WORD adv_walk_vel;            // Maximum velocity while walking
WORD adv_run_vel;             // Maximum velocity while running
WORD adv_dec;                 // Deceleration value
WORD adv_turn_acc;            // Acceleration when changing direction
WORD adv_walk_acc;            // Acceleration when walking
WORD adv_run_acc;             // Acceleration when running
WORD adv_knockback_vel_x;     // Knockback velocity in the x direction
WORD adv_knockback_vel_y;     // Knockback velocity in the y direction
UBYTE adv_knockback_frames;   // Number of frames for knockback
UBYTE adv_dash_active;        // Dash feature is active
UBYTE adv_dash_mask;          // Choose if the player can dash through actors, triggers, and walls
WORD adv_dash_dist;           // Distance of the dash
UBYTE adv_dash_frames;        // Number of frames for dashing
UBYTE adv_dash_ready_frames;  // Frames before the player can dash again
UBYTE adv_dash_deadzone;      // Override camera deadzone when in dash state
UBYTE adv_push_delay_frames;  // Frames before entering push state

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

// Dash
UBYTE adv_dash_cooldown_timer;// tracks the current amount before the dash is ready
WORD adv_dash_per_frame;      // Takes overall dash distance and holds the amount per-frame
UBYTE adv_dash_currentframe;  // Tracks the current frame of the overall dash
UBYTE adv_tap_timer;          // Number of frames since the last time dpad button was tapped
UBYTE adv_dash_dir;

// Camera
BYTE adv_camera_deadzone_x;   // Default camera deadzone X - used to restore camera after dash
BYTE adv_camera_deadzone_y;   // Default camera deadzone Y - used to restore camera after dash
UBYTE adv_camera_transitioning; // Flag to track if we're animating back from dash deadzone

// Push
UBYTE adv_push_timer;         // Number of frames pushing against a wall

// End of Runtime State -------------------------------------------------------

// Function Definitions -------------------------------------------------------

static void move_and_collide(UBYTE mask);
static void handle_dir_input(void);
static void adv_deceleration(void);
static void dash_init(void);

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

#ifdef FEAT_ADVENTURE_DASH

inline UBYTE dash_input_pressed(void)
{
    if (!adv_dash_active) {
      return FALSE;
    }
#if INPUT_ADVENTURE_DASH == DASH_INPUT_INTERACT
    return INPUT_PRESSED(INPUT_ADVENTURE_INTERACT);
#elif INPUT_ADVENTURE_DASH == DASH_INPUT_A
    return INPUT_PRESSED(INPUT_A);
#elif INPUT_ADVENTURE_DASH == DASH_INPUT_B
    return INPUT_PRESSED(INPUT_B);
#elif INPUT_ADVENTURE_DASH == DASH_INPUT_DOUBLE_TAP
    // Double-Tap Dash
    if (INPUT_PRESSED(INPUT_DPAD)) {
        UBYTE dir = joy & INPUT_DPAD;
        if (adv_tap_timer > 0 && dir == adv_dash_dir) {
            adv_tap_timer = 0;
            return TRUE;
        } else {
            adv_tap_timer = DOUBLE_TAP_WINDOW;
            adv_dash_dir = dir;
        }
    }
    return FALSE;
#endif
}

#endif

static void state_enter_ground(void);
static void state_exit_ground(void);
static void state_update_ground(void);
#ifdef FEAT_ADVENTURE_DASH
static void state_enter_dash(void);
static void state_exit_dash(void);
static void state_update_dash(void);
#endif
#ifdef FEAT_ADVENTURE_KNOCKBACK
static void state_enter_knockback(void);
static void state_exit_knockback(void);
static void state_update_knockback(void);
#endif
#ifdef FEAT_ADVENTURE_BLANK
static void state_enter_blank(void);
static void state_exit_blank(void);
#endif
#ifdef FEAT_ADVENTURE_RUN
static void state_enter_run(void);
static void state_exit_run(void);
#endif
#ifdef FEAT_ADVENTURE_PUSH
static void state_enter_push(void);
static void state_exit_push(void);
static void state_update_push(void);
#endif

// End of Function Definitions ------------------------------------------------

void adventure_init(void) BANKED {

    adv_callback_reset();

    // Set camera to follow player
    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = ADVENTURE_CAMERA_DEADZONE;
    camera_deadzone_y = ADVENTURE_CAMERA_DEADZONE;

    // Initialize facing direction
    facing_dir = PLAYER.dir;
    delta.x  = 0;
    delta.y  = 0;
    movement_delta.x = 0;
    movement_delta.y = 0;
    adv_vel_x = 0;
    adv_vel_y = 0;

    collision_dir = DIR_NONE;

    adv_state = GROUND_STATE;
    adv_next_state = GROUND_STATE;
    adv_camera_deadzone_x = camera_deadzone_x;
    adv_camera_deadzone_y = camera_deadzone_y;
    adv_camera_transitioning = FALSE;
    adv_dash_cooldown_timer = 0;
    adv_knockback_timer = 0;
    adv_push_timer = 0;
}

void adventure_update(void) BANKED {
    // State transitions

    if (adv_state != adv_next_state)
    {
        // Exit state
        switch (adv_state)
        {
            case GROUND_STATE: {
                state_exit_ground();
                break;
            }
#ifdef FEAT_ADVENTURE_RUN
            case RUN_STATE: {
                state_exit_run();
                break;
            }
#endif              
#ifdef FEAT_ADVENTURE_DASH
            case DASH_STATE: {
                state_exit_dash();
                break;
            }
#endif
#ifdef FEAT_ADVENTURE_KNOCKBACK
            case KNOCKBACK_STATE: {
                state_exit_knockback();
                break;
            }
#endif
#ifdef FEAT_ADVENTURE_BLANK
            case BLANK_STATE: {
                state_exit_blank();
                break;
            }
#endif
#ifdef FEAT_ADVENTURE_PUSH
            case PUSH_STATE: {
                state_exit_push();
                break;
            }
#endif
        }

        adv_state = adv_next_state;

        // Enter state
        switch (adv_state)
        {
            case GROUND_STATE: {
                state_enter_ground();
                break;
            }
#ifdef FEAT_ADVENTURE_RUN
            case RUN_STATE: {
                state_enter_run();
                break;
            }
#endif            
#ifdef FEAT_ADVENTURE_DASH
            case DASH_STATE: {
                state_enter_dash();
                break;
            }
#endif
#ifdef FEAT_ADVENTURE_KNOCKBACK
            case KNOCKBACK_STATE: {
                state_enter_knockback();
                break;
            }
#endif
#ifdef FEAT_ADVENTURE_BLANK
            case BLANK_STATE: {
                state_enter_blank();
                break;
            }
#endif
#ifdef FEAT_ADVENTURE_PUSH
            case PUSH_STATE: {
                state_enter_push();
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
            state_update_ground();
            break;
        }

#ifdef FEAT_ADVENTURE_DASH
        case DASH_STATE: {
            state_update_dash();
            break;
        }
#endif

#ifdef FEAT_ADVENTURE_KNOCKBACK
        case KNOCKBACK_STATE: {
            state_update_knockback();
            break;
        }
#endif

#ifdef FEAT_ADVENTURE_PUSH
        case PUSH_STATE: {
            state_update_push();
            break;
        }
#endif

    }

    // Timers

#ifdef FEAT_ADVENTURE_DASH
    COUNTER_DECREMENT(adv_tap_timer);

    // COUNTERS================================================================
    //  Counting down until dashing is ready again
    //  XX Set in dash Init and checked in wall, fall, ground, and jump states
    COUNTER_DECREMENT_CB(adv_dash_cooldown_timer, {
        adv_callback_execute(DASH_READY);
    });
#endif

    // Restore camera deadzone after dash
    if (adv_camera_transitioning) {
        if (camera_deadzone_x > adv_camera_deadzone_x) {
            camera_deadzone_x--;
        } else if (camera_deadzone_x < adv_camera_deadzone_x) {
            camera_deadzone_x++;
        }
        
        if (camera_deadzone_y > adv_camera_deadzone_y) {
            camera_deadzone_y--;
        } else if (camera_deadzone_y < adv_camera_deadzone_y) {
            camera_deadzone_y++;
        }
        if (camera_deadzone_x == adv_camera_deadzone_x &&
            camera_deadzone_y == adv_camera_deadzone_y) {
            adv_camera_transitioning = FALSE;
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

    if (target_x && target_y) {
        // Approximate diagonal movement normalization
        target_x = (target_x >> 1) + (target_x >> 2);  
        target_y = (target_y >> 1) + (target_y >> 2);  
    }
#if INPUT_ADVENTURE_DIRECTION_TYPE == DIRECTION_TYPE_4_WAY
    // Update facing priority axis
    if ((left | right) && !(up | down)) {
        facing_priority_axis = DIR_PRIORITY_HORIZONTAL;
    } else if ((up | down) && !(left | right)) {
        facing_priority_axis = DIR_PRIORITY_VERTICAL;
    } else if (!(left | right | up | down)) {
        facing_priority_axis = DIR_PRIORITY_NONE;
    }
#endif
    // Determine facing based on which axis was pressed first
    if ((left | right) && (up | down)) {
#if INPUT_ADVENTURE_DIRECTION_TYPE == DIRECTION_TYPE_4_WAY
        // Both axes pressed, respect whichever axis was pressed first
        if (facing_priority_axis == DIR_PRIORITY_HORIZONTAL) {
            facing_dir = left ? DIR_LEFT : DIR_RIGHT;
        } else {
            facing_dir = up ? DIR_UP : DIR_DOWN;
        }	
#else
	    facing_dir = left ? DIR_LEFT : DIR_RIGHT;
#endif
    } else if (left) {
        facing_dir = DIR_LEFT;
    } else if (right) {
        facing_dir = DIR_RIGHT;
    } 
#if INPUT_ADVENTURE_DIRECTION_TYPE != DIRECTION_TYPE_HORIZONTAL
	else if (up) {
        facing_dir = DIR_UP;
    } else if (down) {
        facing_dir = DIR_DOWN;
    }
#endif
#else
    // ---------------------- 4-WAY ----------------------
#if INPUT_ADVENTURE_DIRECTION_TYPE != DIRECTION_TYPE_HORIZONTAL
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
    }
#else
	if (INPUT_RECENT_LEFT) {
        target_x = -max_vel;
        facing_dir = DIR_LEFT;
    } else if (INPUT_RECENT_RIGHT) {
        target_x =  max_vel;
        facing_dir = DIR_RIGHT;
    } else if (INPUT_RECENT_UP) {
        target_y = -max_vel;
    } else if (INPUT_RECENT_DOWN) {
        target_y =  max_vel;
    }
#endif
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

    adv_vel_x = CLAMP(adv_vel_x, -max_vel, max_vel);
    adv_vel_y = CLAMP(adv_vel_y, -max_vel, max_vel);
}

static void move_and_collide(UBYTE mask)
{
    temp_x = PLAYER.pos.x;
    temp_y = PLAYER.pos.y;

    // Horizontal Movement
    if (mask & COL_CHECK_X)
    {
        UWORD new_x = PLAYER.pos.x + delta.x;

        if (!(mask & COL_CHECK_WALLS))
        {
            goto finally_update_x;
        }

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
            new_x = MIN(image_width_subpx - EXCLUSIVE_OFFSET(PLAYER.bounds.right), new_x);
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
        }

    finally_update_x:
        PLAYER.pos.x = new_x;
    }

    // Vertical Movement
    if (mask & COL_CHECK_Y)
    {
        UWORD new_y = PLAYER.pos.y + delta.y;

        if (!(mask & COL_CHECK_WALLS))
        {
            goto finally_update_y;
        }

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
        }

    finally_update_y:
        PLAYER.pos.y = new_y;
    }

    delta.x  = 0;
    delta.y  = 0;

    if (mask & COL_CHECK_ACTORS)
    {
        actor_t *hit_actor;
        actor_t *initial_hit_actor;
        initial_hit_actor = hit_actor = actor_overlapping_player();
        adv_attached_actor = NULL;

        while (hit_actor != NULL) {
            const UBYTE is_solid = hit_actor->collision_group & COLLISION_GROUP_FLAG_SOLID;
            if (is_solid)
            {
                adv_attached_actor = hit_actor;
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
            hit_actor = actor_overlapping_player_from(hit_actor);
        }

        if (adv_attached_actor != NULL) {
            hit_actor = adv_attached_actor;
            adv_attached_prev_x = hit_actor->pos.x;
            adv_attached_prev_y = hit_actor->pos.y; 
        } else {
            hit_actor = initial_hit_actor;
            adv_attached_actor = NULL;
            collision_dir = DIR_NONE;
            adv_attached_prev_x = 0;
            adv_attached_prev_y = 0;
        }

        if (hit_actor != NULL && (hit_actor->collision_group & COLLISION_GROUP_MASK))
        {
            // Collision group script handling
            player_register_collision_with(hit_actor);
        }
        else if (INPUT_PRESSED(INPUT_ADVENTURE_INTERACT)) {
            hit_actor = actor_with_script_in_front_of_player(8);
            if (hit_actor && !(hit_actor->collision_group & COLLISION_GROUP_MASK) && hit_actor->script.bank) {
                actor_set_dir(hit_actor, FLIPPED_DIR(PLAYER.dir), FALSE);
                script_execute(hit_actor->script.bank, hit_actor->script.ptr, 0, 1, 0);
            }
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
    adv_events[*slot].script_bank = 0;
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

#ifdef FEAT_ADVENTURE_DASH
static void dash_init(void)
{
    adv_dash_per_frame = adv_dash_dist / adv_dash_frames; // Dash distance per frame in the DASH_STATE

    // Dash through walls - check if destination is clear
    if ((adv_dash_mask & COL_CHECK_WALLS) == 0)
    {
        // Compute destination position based on dash direction
        WORD dash_dx = 0;
        WORD dash_dy = 0;

        switch (PLAYER.dir) {
            case DIR_LEFT:
                dash_dx = -adv_dash_per_frame * adv_dash_frames;
                break;
            case DIR_RIGHT:
                dash_dx =  adv_dash_per_frame * adv_dash_frames;
                break;
            case DIR_UP:
                dash_dy = -adv_dash_per_frame * adv_dash_frames;
                break;
            case DIR_DOWN:
                dash_dy =  adv_dash_per_frame * adv_dash_frames;
                break;
        }

        UWORD new_x = PLAYER.pos.x + dash_dx;
        UWORD new_y = PLAYER.pos.y + dash_dy;

        UBYTE tile_top    = SUBPX_TO_TILE(new_y + PLAYER.bounds.top);
        UBYTE tile_bottom = SUBPX_TO_TILE(new_y + PLAYER.bounds.bottom);
        UBYTE tile_left   = SUBPX_TO_TILE(new_x + PLAYER.bounds.left);
        UBYTE tile_right  = SUBPX_TO_TILE(new_x + PLAYER.bounds.right);

        UBYTE col = 0;

        if (PLAYER.dir == DIR_LEFT || PLAYER.dir == DIR_RIGHT) {
            col = tile_col_test_range_y(COLLISION_ALL, tile_left, tile_top, tile_bottom);
            if (!col) {
                col = tile_col_test_range_y(COLLISION_ALL, tile_right, tile_top, tile_bottom);
            }
        }
        else {
            col = tile_col_test_range_x(COLLISION_ALL, tile_top, tile_left, tile_right);
            if (!col) {
                col = tile_col_test_range_x(COLLISION_ALL, tile_bottom, tile_left, tile_right);
            }
        }

        if (col) {
            adv_dash_per_frame = 0;
            adv_next_state = GROUND_STATE;
            return;
        }
    }

    adv_is_actor_attached = FALSE;
    adv_camera_deadzone_x = camera_deadzone_x;
    adv_camera_deadzone_y = camera_deadzone_y;
    camera_deadzone_x = adv_dash_deadzone;
    camera_deadzone_y = adv_dash_deadzone;
    adv_camera_transitioning = TRUE;
    adv_dash_cooldown_timer = adv_dash_ready_frames + adv_dash_frames;
    adv_dash_currentframe = adv_dash_frames;
    adv_tap_timer = 0;
    adv_next_state = DASH_STATE;

    adv_dash_mask |= COL_CHECK_X | COL_CHECK_Y;
}
#endif

// State Machine Functions ----------------------------------------------------

// GROUND_STATE

static void state_enter_ground(void)
{
#if ADVENTURE_ANIM_OVERRIDES_SET
    adv_restore_default_anim_state();
#endif
    adv_callback_execute(GROUND_INIT);
}

static void state_exit_ground(void)
{
    adv_callback_execute(GROUND_END);
}

static void state_update_ground(void)
{
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

#ifdef FEAT_ADVENTURE_PUSH
    UWORD prev_x = PLAYER.pos.x;
    UWORD prev_y = PLAYER.pos.y;
#endif

    move_and_collide(COL_CHECK_ALL);

#ifdef FEAT_ADVENTURE_PUSH
    // Check if player is pushing against an obstacle
    if (joy & INPUT_DPAD && prev_x == PLAYER.pos.x && prev_y == PLAYER.pos.y) {
        if (adv_push_timer == adv_push_delay_frames) {
            adv_next_state = PUSH_STATE;
            return;
        }                
        adv_push_timer++;
    } else {
        adv_push_timer = 0;
    }
#endif

#ifdef FEAT_ADVENTURE_DASH
    if (adv_dash_cooldown_timer == 0 && dash_input_pressed()) {
        adv_next_state = DASH_STATE;
        return;
    }
#endif

#ifdef FEAT_ADVENTURE_RUN
    const UBYTE running = INPUT_ADVENTURE_RUN;
    if (adv_state == GROUND_STATE && running) {
        adv_next_state = RUN_STATE;
        return;
    } else if (adv_state == RUN_STATE && !running) {
        adv_next_state = GROUND_STATE;
        return;
    }
#endif

    // Facing and animation update
    if (joy & INPUT_DPAD) {
        actor_set_dir(&PLAYER, facing_dir, TRUE);
    } else {
        actor_set_anim_idle(&PLAYER);
    }
    
}

// DASH_STATE

#ifdef FEAT_ADVENTURE_DASH
static void state_enter_dash(void)
{
    dash_init();
    if (adv_next_state != DASH_STATE) {
        // Break out if dash not allowed
        return;
    }
#ifdef ADVENTURE_DASH_ANIM
    adv_set_player_anim_state(ADVENTURE_DASH_ANIM);
#elif ADVENTURE_ANIM_OVERRIDES_SET  
    adv_restore_default_anim_state();
#endif
    adv_callback_execute(DASH_INIT);
}

static void state_exit_dash(void)
{
    adv_callback_execute(DASH_END);
}

static void state_update_dash(void)
{
    WORD remaining_dash_dist = adv_dash_per_frame;

    BYTE x_dir = 0;
    BYTE y_dir = 0;

    if (PLAYER.dir == DIR_RIGHT) {
        x_dir = 1;
    } else if (PLAYER.dir == DIR_LEFT) {
        x_dir = -1;
    } else if (PLAYER.dir == DIR_DOWN) {
        y_dir = 1;
    } else if (PLAYER.dir == DIR_UP) {
        y_dir = -1;
    }

    while (remaining_dash_dist)
    {
        WORD dist = MIN(remaining_dash_dist, MAX_DELTA);
        delta.x = dist * x_dir;
        delta.y = dist * y_dir;
        move_and_collide(adv_dash_mask);
        remaining_dash_dist -= dist;
    }

    COUNTER_DECREMENT_CB(adv_dash_currentframe, {
        adv_next_state = GROUND_STATE;
        adv_vel_x = 0;
        adv_vel_y = 0;
    });
}
#endif

// KNOCKBACK_STATE

#ifdef FEAT_ADVENTURE_KNOCKBACK
static void state_enter_knockback(void)
{
    // Knockback in opposite direction to current movement
    if (adv_vel_x != 0) {
        adv_vel_x = adv_vel_x > 0 ? -adv_knockback_vel_x : adv_knockback_vel_x;
    } else if (IS_DIR_HORIZONTAL(PLAYER.dir)) {
        adv_vel_x = PLAYER.dir == DIR_RIGHT ? -adv_knockback_vel_x : adv_knockback_vel_x;
    }

    if (adv_vel_y != 0) {
        adv_vel_y = adv_vel_y > 0 ? -adv_knockback_vel_y : adv_knockback_vel_y;
    } else if (IS_DIR_VERTICAL(PLAYER.dir)) {
        adv_vel_y = PLAYER.dir == DIR_DOWN ? -adv_knockback_vel_y : adv_knockback_vel_y;
    }

    adv_knockback_timer = adv_knockback_frames;
#ifdef ADVENTURE_KNOCKBACK_ANIM
    adv_set_player_anim_state(ADVENTURE_KNOCKBACK_ANIM);
#elif ADVENTURE_ANIM_OVERRIDES_SET
    adv_restore_default_anim_state();
#endif
    adv_callback_execute(KNOCKBACK_INIT);
}

static void state_exit_knockback(void)
{
    adv_vel_x = 0;
    adv_vel_y = 0;
    adv_callback_execute(KNOCKBACK_END);
}

static void state_update_knockback(void)
{
    delta.x = VEL_TO_SUBPX(adv_vel_x);
    delta.y = VEL_TO_SUBPX(adv_vel_y);

    move_and_collide(COL_CHECK_ALL);

    COUNTER_DECREMENT_CB(adv_knockback_timer, {
        adv_next_state = GROUND_STATE;
    });
}
#endif

// BLANK_STATE

#ifdef FEAT_ADVENTURE_BLANK
static void state_enter_blank(void)
{
    adv_vel_x = 0;
    adv_vel_y = 0;
#ifdef ADVENTURE_BLANK_ANIM
    adv_set_player_anim_state(ADVENTURE_BLANK_ANIM);
#elif ADVENTURE_ANIM_OVERRIDES_SET
    adv_restore_default_anim_state();
#endif
    adv_callback_execute(BLANK_INIT);
}

static void state_exit_blank(void)
{
    adv_vel_x = 0;
    adv_vel_y = 0;
    adv_callback_execute(BLANK_END);
}
#endif

// RUN_STATE

#ifdef FEAT_ADVENTURE_RUN
static void state_enter_run(void)
{
#ifdef ADVENTURE_RUN_ANIM
    adv_set_player_anim_state(ADVENTURE_RUN_ANIM);
#elif ADVENTURE_ANIM_OVERRIDES_SET
    adv_restore_default_anim_state();
#endif
    adv_callback_execute(RUN_INIT);
}

static void state_exit_run(void)
{
    adv_callback_execute(RUN_END);
}
#endif

// PUSH_STATE

#ifdef FEAT_ADVENTURE_PUSH
static void state_enter_push(void)
{
#ifdef ADVENTURE_PUSH_ANIM
    adv_set_player_anim_state(ADVENTURE_PUSH_ANIM);
#elif ADVENTURE_ANIM_OVERRIDES_SET
    adv_restore_default_anim_state();
#endif
    actor_set_dir(&PLAYER, facing_dir, TRUE);
    adv_callback_execute(PUSH_INIT);
}

static void state_exit_push(void)
{
    adv_callback_execute(PUSH_END);
}

static void state_update_push(void)
{
    handle_dir_input();
  
    delta.x = VEL_TO_SUBPX(adv_vel_x);
    delta.y = VEL_TO_SUBPX(adv_vel_y);

    UWORD prev_x = PLAYER.pos.x;
    UWORD prev_y = PLAYER.pos.y;

    move_and_collide(COL_CHECK_ALL);

    // Check if player is still pushing against an obstacle
    if (!(joy & INPUT_DPAD) || prev_x != PLAYER.pos.x || prev_y != PLAYER.pos.y) {
        adv_next_state = GROUND_STATE;
        return;
    }

    // Facing and animation update
    if (joy & INPUT_DPAD) {
        actor_set_dir(&PLAYER, facing_dir, TRUE);
    } else {
        actor_set_anim_idle(&PLAYER);
    }
}
#endif

// End of State Machine Functions ---------------------------------------------
