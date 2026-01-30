#pragma bank 255

#include "states/platform.h"

#include <string.h>
#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "data/states_defines.h"
#include "data_manager.h"
#include "events.h"
#include "game_time.h"
#include "input.h"
#include "math.h"
#include "scroll.h"
#include "trigger.h"
#include "vm.h"
#include "macro.h"

// Feature Flags --------------------------------------------------------------
// Optional feature flags, set in 'state_defines.h'

// #define FEAT_PLATFORM_BLANK
// #define FEAT_PLATFORM_COYOTE_TIME
// #define FEAT_PLATFORM_DASH
// #define FEAT_PLATFORM_DOUBLE_JUMP
// #define FEAT_PLATFORM_DROP_THROUGH
// #define FEAT_PLATFORM_JUMP
// #define FEAT_PLATFORM_RUN
// #define FEAT_PLATFORM_FLOAT
// #define FEAT_PLATFORM_KNOCKBACK
// #define FEAT_PLATFORM_LADDERS
// #define FEAT_PLATFORM_SLOPES
// #define FEAT_PLATFORM_WALL_JUMP

// End of Feature Flags -------------------------------------------------------

// Constants ------------------------------------------------------------------

#ifndef INPUT_PLATFORM_JUMP
#define INPUT_PLATFORM_JUMP INPUT_A
#endif
#ifndef INPUT_PLATFORM_RUN
#define INPUT_PLATFORM_RUN INPUT_B
#endif
#ifndef INPUT_PLATFORM_INTERACT
#define INPUT_PLATFORM_INTERACT INPUT_A
#endif
#ifndef INPUT_PLATFORM_DROP_THROUGH
#define INPUT_PLATFORM_DROP_THROUGH 0
#endif
#ifndef PLATFORM_CAMERA_DEADZONE_Y
#define PLATFORM_CAMERA_DEADZONE_Y 16
#endif

#define DASH_INPUT_INTERACT 0
#define DASH_INPUT_DOUBLE_TAP 1
#define DASH_INPUT_DOWN_JUMP 2
#define DASH_INPUT_A 3
#define DASH_INPUT_B 4

#define JUMP_TYPE_NONE 0
#define JUMP_TYPE_GROUND 1
#define JUMP_TYPE_DOUBLE 2
#define JUMP_TYPE_WALL 3
#define JUMP_TYPE_FLOATING 4

#define FLOAT_INPUT_HOLD_JUMP 0
#define FLOAT_INPUT_HOLD_UP 1

#define WALL_COL_NONE 0
#define WALL_COL_LEFT -1
#define WALL_COL_RIGHT 1

#define RUN_STYLE_DEFAULT 0
#define RUN_STYLE_SMOOTH 1
#define RUN_STYLE_INSTANT 2

#define RUN_STAGE_TURNING -1
#define RUN_STAGE_NONE 0
#define RUN_STAGE_WALK_ACC 1
#define RUN_STAGE_RUN_ACC 2
#define RUN_STAGE_RUN_MAX 3

#define COL_CHECK_X 0x1
#define COL_CHECK_Y 0x2
#define COL_CHECK_ACTORS 0x4
#define COL_CHECK_TRIGGERS 0x8
#define COL_CHECK_WALLS 0x10

#define CAMERA_LOCK_SCREEN_LEFT 0x1
#define CAMERA_LOCK_SCREEN_RIGHT 0x2

#define DROP_THRU_INPUT_DOWN_HOLD 0x0
#define DROP_THRU_INPUT_DOWN_TAP 0x1
#define DROP_THRU_INPUT_DOWN_JUMP_HOLD 0x2
#define DROP_THRU_INPUT_DOWN_JUMP_TAP 0x3

#define DASH_FROM_GROUND 0x1
#define DASH_FROM_AIR 0x2
#define DASH_FROM_LADDER 0x3

#define DROP_FRAMES_MAX 15

#define MAX_DELTA 127
#define UNLIMITED_JUMPS 255
#define DOUBLE_TAP_WINDOW 15
#define WALL_JUMP_NO_CONTROL_H_FRAMES 15

#define COL_CHECK_ALL COL_CHECK_X | COL_CHECK_Y | COL_CHECK_ACTORS | COL_CHECK_TRIGGERS | COL_CHECK_WALLS

#define COLLISION_SLOPE_LEFT          0x10u
#define COLLISION_SLOPE_45            0x20u
#define COLLISION_SLOPE_225_BOT       0x40u
#define COLLISION_SLOPE_225_TOP       (COLLISION_SLOPE_45 | COLLISION_SLOPE_225_BOT)
#define COLLISION_SLOPE_45_RIGHT      COLLISION_SLOPE_45
#define COLLISION_SLOPE_225_RIGHT_BOT COLLISION_SLOPE_225_BOT
#define COLLISION_SLOPE_225_RIGHT_TOP COLLISION_SLOPE_225_TOP
#define COLLISION_SLOPE_45_LEFT       (COLLISION_SLOPE_LEFT | COLLISION_SLOPE_45)
#define COLLISION_SLOPE_225_LEFT_BOT  (COLLISION_SLOPE_LEFT | COLLISION_SLOPE_225_BOT) 
#define COLLISION_SLOPE_225_LEFT_TOP  (COLLISION_SLOPE_LEFT | COLLISION_SLOPE_225_TOP)
#define COLLISION_SLOPE_ANY           (COLLISION_SLOPE_45 | COLLISION_SLOPE_225_BOT | COLLISION_SLOPE_225_TOP)
#define COLLISION_SLOPE               0x70u


#define PLATFORM_ANIM_OVERRIDES_SET \
    defined(PLATFORM_FALL_ANIM) || \
    (defined(FEAT_PLATFORM_FLOAT) && defined(PLATFORM_FLOAT_ANIM)) || \
    (defined(FEAT_PLATFORM_JUMP) && defined(PLATFORM_JUMP_ANIM)) || \
    (defined(FEAT_PLATFORM_RUN) && defined(PLATFORM_RUN_ANIM)) || \
    (defined(FEAT_PLATFORM_LADDERS) && defined(PLATFORM_LADDERS_ANIM)) || \
    (defined(FEAT_PLATFORM_DASH) && defined(PLATFORM_DASH_ANIM)) || \
    (defined(FEAT_PLATFORM_WALL_JUMP) && defined(FEAT_PLATFORM_JUMP) && defined(PLATFORM_WALL_SLIDE_ANIM)) || \
    (defined(FEAT_PLATFORM_KNOCKBACK) && defined(PLATFORM_KNOCKBACK_ANIM)) || \
    (defined(FEAT_PLATFORM_BLANK) && defined(PLATFORM_BLANK_ANIM))

// End of Constants -----------------------------------------------------------

// Macros ---------------------------------------------------------------------

#define IS_ON_SLOPE(t) ((t) & COLLISION_SLOPE_ANY)
#define IS_SLOPE_LEFT(t) ((t) & COLLISION_SLOPE_LEFT)
#define IS_SLOPE_RIGHT(t) (!((t) & COLLISION_SLOPE_LEFT))
#define IS_LADDER(t) (((t) & COLLISION_SLOPE) == TILE_PROP_LADDER)
#define VEL_TO_SUBPX(v) ((((v) & 0x8000) ? (((v) >> 8) | 0xFF00) : ((v) >> 8)) << 1)

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
#define COUNTER_DECREMENT_IF(x, cond)                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((x) != 0 && (cond))                                                                                        \
            (x)--;                                                                                                     \
    } while (0)

// End of Macros --------------------------------------------------------------

// Type Definitions -----------------------------------------------------------

typedef enum
{
    FALL_STATE = 0,
    GROUND_STATE,
    JUMP_STATE,
    DASH_STATE,
    LADDER_STATE,
    WALL_STATE,
    KNOCKBACK_STATE,
    BLANK_STATE,
    RUN_STATE,
    FLOAT_STATE,
} state_e;

typedef enum
{
    FALL_INIT = 0,
    FALL_END,
    GROUND_INIT,
    GROUND_END,
    JUMP_INIT,
    JUMP_END,
    DASH_INIT,
    DASH_END,
    LADDER_INIT,
    LADDER_END,
    WALL_INIT,
    WALL_END,
    KNOCKBACK_INIT,
    KNOCKBACK_END,
    BLANK_INIT,
    BLANK_END,
    DASH_READY,
    RUN_INIT,
    RUN_END,
    FLOAT_INIT,
    FLOAT_END,
    CALLBACK_SIZE
} callback_e;

// End of Type Definitions ----------------------------------------------------

// Engine Fields --------------------------------------------------------------

WORD plat_walk_vel;            // Maximum velocity while walking
WORD plat_run_vel;             // Maximum velocity while running
WORD plat_climb_vel;           // Maximum velocity while climbing
WORD plat_min_vel;             // Minimum velocity to apply to the player
WORD plat_walk_acc;            // Acceleration while walking
WORD plat_run_acc;             // Acceleration while running
WORD plat_dec;                 // Deceleration rate
WORD plat_jump_vel;            // Jump velocity applied on the first frame of jumping
WORD plat_grav;                // Gravity applied to the player
WORD plat_hold_grav;           // Gravity applied to the player while holding jump
WORD plat_max_fall_vel;        // Maximum fall velocity
UBYTE plat_camera_block;       // Limit the player's movement to the camera's edges
UBYTE plat_drop_through_active;// Drop-through is active
WORD plat_jump_hold_vel;       // Jump velocity applied while holding jump
UBYTE plat_jump_hold_frames;   // Maximum number for frames for additional jump velocity
UBYTE plat_extra_jumps;        // Number of jumps while in the air
WORD plat_jump_reduction;      // Reduce height each double jump
UBYTE plat_coyote_frames;      // Coyote Time maximum frames
UBYTE plat_jump_buffer_frames; // Jump Buffer maximum frames
UBYTE plat_wall_jump_max;      // Number of wall jumps in a row
UBYTE plat_wall_slide;         // Enables/Disables wall sliding
WORD plat_wall_slide_vel;      // Downwards velocity while clinging to the wall
WORD plat_wall_kick;           // Horizontal force for pushing off the wall
UBYTE plat_float_active;       // Float feature is active
WORD plat_float_vel;           // Speed of fall descent while floating
UBYTE plat_air_control;        // Enables/Disables air control
UBYTE plat_turn_control;       // Controls the amount of slippage when the player turns while running.
WORD plat_air_dec;             // air deceleration rate
WORD plat_turn_acc;            // Speed with which a character turns
WORD plat_run_boost;           // Additional jump height based on horizontal speed
UBYTE plat_dash_active;        // Dash feature is active
UBYTE plat_dash_from;          // Ground, air, ladders flags
UBYTE plat_dash_jump_from;     // Allow jumping from dash state
UBYTE plat_dash_mask;          // Choose if the player can dash through actors, triggers, and walls
WORD plat_dash_dist;           // Distance of the dash
UBYTE plat_dash_frames;        // Number of frames for dashing
UBYTE plat_dash_ready_frames;  // Frames before the player can dash again
UBYTE plat_dash_deadzone;      // Override camera x deadzone when in dash state
WORD plat_knockback_vel_x;     // Knockback velocity in the x direction
WORD plat_knockback_vel_y;     // Knockback velocity in the y direction
UBYTE plat_knockback_frames;   // Number of frames for knockback
WORD plat_blank_grav;          // Blank state gravity

// End of Engine Fields -------------------------------------------------------

// Runtime State --------------------------------------------------------------

script_event_t plat_events[CALLBACK_SIZE];

// State machine
state_e plat_state;            // Current platformer state
state_e plat_next_state;       // Next frame's platformer state

// Movement
WORD plat_vel_x;               // Tracks the player's x-velocity between frames
WORD plat_vel_y;               // Tracks the player's y-velocity between frames
WORD plat_delta_x;             // The subpixel offset to apply to the player's x position in move_and_collide
WORD plat_delta_y;             // The subpixel offset to apply to the player's y position in move_and_collide

// Counters
UBYTE plat_coyote_timer;       // Coyote Time Variable
UBYTE plat_jump_buffer_timer;  // Jump Buffer Variable
UBYTE plat_wall_coyote_timer;  // Wall Coyote Time Variable
UBYTE plat_hold_jump_timer;    // Jump input hold variable
UBYTE plat_extra_jumps_counter;// Current extra jump
UBYTE plat_wall_jump_counter;  // Current wall jump
UBYTE plat_knockback_timer;    // Current Knockback frame
UBYTE plat_drop_timer;         // The number of frames remaining to drop through platforms
UBYTE plat_nocontrol_h_timer;  // Turns off horizontal input, currently only for wall jumping

// Wall Jump
BYTE plat_wall_col;            // the wall type that the player is touching this frame
BYTE plat_last_wall_col;       // tracks the last wall the player touched

// Dash
UBYTE plat_dash_pressed;       // Tracks if the dash input was pressed this frame
UBYTE plat_dash_cooldown_timer;// tracks the current amount before the dash is ready
WORD plat_dash_per_frame;      // Takes overall dash distance and holds the amount per-frame
UBYTE plat_dash_currentframe;  // Tracks the current frame of the overall dash
BYTE plat_tap_timer;           // Number of frames since the last time left or right button was tapped

// Solid actors
actor_t *plat_attached_actor;  // The last actor the player hit, and that they were attached to
UBYTE plat_is_actor_attached;  // Keeps track of whether the player is currently on an actor
UWORD plat_attached_prev_x;    // Keeps track of the pos.x of the attached actor from the previous frame
UWORD plat_attached_prev_y;    // Keeps track of the pos.y of the attached actor from the previous frame
UWORD plat_temp_y = 0;         // Temporary y position for the player when moving and colliding with an solid actor

// Jumping
WORD plat_jump_vel_per_frame;  // Holds the jump per frame value for the current jump
WORD plat_jump_reduction_vel;  // Holds the current jump reduction value based on the number of jumps without landing

// Camera
BYTE plat_camera_deadzone_x;   // Default camera deadzone x - used to restore camera after dash

// Ground
UBYTE plat_grounded;           // Tracks whether the player is on the ground or not
UBYTE plat_on_slope;           // Tracks whether the player is on a slope or not
UBYTE plat_slope_y;            // The y position of the slope the player is currently on

// Collision
UBYTE did_interact_actor;      // Tracks whether the player interacted with an actor this frame

// Ladders
UBYTE plat_ladder_block_h;     // Track if player has released horizontal input since joining the ladder
UBYTE plat_ladder_block_v;     // Track if player has released vertical input since leaving the ladder

// Animation
UBYTE plat_anim_dirty;         // Tracks whether the player animation has been modified from the default

// Variables for plugins
BYTE plat_run_stage;           // Tracks the stage of running based on the run type
UBYTE plat_jump_type;          // Tracks the type of jumping, from the ground, in the air, or off the wall

// End of Runtime State -------------------------------------------------------

// Function Definitions -------------------------------------------------------

static void player_set_jump_anim(void);
static void wall_check(void);
static void ladder_check(void);
static void dash_init(void);
static void handle_horizontal_input(void);
static void move_and_collide(UBYTE mask);

void plat_state_script_attach(SCRIPT_CTX *THIS) OLDCALL BANKED;
void plat_state_script_detach(SCRIPT_CTX *THIS) OLDCALL BANKED;
void plat_callback_reset(void);
static void plat_callback_execute(UBYTE i);

#ifdef FEAT_PLATFORM_DROP_THROUGH

inline UBYTE drop_input_pressed(void)
{
  return plat_drop_through_active && (
#if INPUT_PLATFORM_DROP_THROUGH == DROP_THRU_INPUT_DOWN_HOLD
      INPUT_DOWN
#elif INPUT_PLATFORM_DROP_THROUGH == DROP_THRU_INPUT_DOWN_TAP
      INPUT_PRESSED(INPUT_DOWN)
#elif INPUT_PLATFORM_DROP_THROUGH == DROP_THRU_INPUT_DOWN_JUMP_HOLD
      INPUT_DOWN && INPUT_PLATFORM_JUMP
#elif INPUT_PLATFORM_DROP_THROUGH == DROP_THRU_INPUT_DOWN_JUMP_TAP
      (INPUT_PRESSED(INPUT_DOWN) && INPUT_PLATFORM_JUMP) || (INPUT_DOWN && INPUT_PRESSED(INPUT_PLATFORM_JUMP))
#else
      FALSE
#endif
  );
}

#endif

#ifdef FEAT_PLATFORM_FLOAT

inline UBYTE float_input_pressed(void)
{
  return plat_float_active && (
#if INPUT_PLATFORM_FLOAT == FLOAT_INPUT_HOLD_JUMP
      INPUT_PLATFORM_JUMP
#elif INPUT_PLATFORM_FLOAT == FLOAT_INPUT_HOLD_UP
      INPUT_UP
#else
      FALSE
#endif
  );
}

#endif

#ifdef FEAT_PLATFORM_DASH

inline UBYTE dash_input_pressed(void)
{
    if (!plat_dash_active) {
      return FALSE;
    }
#if INPUT_PLATFORM_DASH == DASH_INPUT_INTERACT
    return INPUT_PRESSED(INPUT_PLATFORM_INTERACT);
#elif INPUT_PLATFORM_DASH == DASH_INPUT_A
    return INPUT_PRESSED(INPUT_A);
#elif INPUT_PLATFORM_DASH == DASH_INPUT_B
    return INPUT_PRESSED(INPUT_B);    
#elif INPUT_PLATFORM_DASH == DASH_INPUT_DOUBLE_TAP
    // Double-Tap Dash
    if (INPUT_PRESSED(INPUT_LEFT))
    {
        if (plat_tap_timer < 0)
        {
            return TRUE;
        }
        else
        {
            plat_tap_timer = -DOUBLE_TAP_WINDOW;
        }
    }
    else if (INPUT_PRESSED(INPUT_RIGHT))
    {
        if (plat_tap_timer > 0)
        {
            return TRUE;
        }
        else
        {
            plat_tap_timer = DOUBLE_TAP_WINDOW;
        }
    }
    return FALSE;    
#elif INPUT_PLATFORM_DASH == DASH_INPUT_DOWN_JUMP
    return (INPUT_PRESSED(INPUT_DOWN) && INPUT_PLATFORM_JUMP) || (INPUT_DOWN && INPUT_PRESSED(INPUT_PLATFORM_JUMP));
#else
    return FALSE;
#endif
}

#endif

#if PLATFORM_ANIM_OVERRIDES_SET

inline void plat_set_player_anim_state(UBYTE anim)
{
    load_animations(PLAYER.sprite.ptr, PLAYER.sprite.bank, anim, PLAYER.animations);
    actor_reset_anim(&PLAYER);
    plat_anim_dirty = TRUE;
}

inline void plat_restore_default_anim_state(void)
{
    if (plat_anim_dirty) {
        load_animations(PLAYER.sprite.ptr, PLAYER.sprite.bank, 0, PLAYER.animations);
        actor_reset_anim(&PLAYER);  
        plat_anim_dirty = FALSE;             
    }
}

#endif

static void state_enter_fall(void);      
static void state_exit_fall(void);      
static void state_update_fall(void);
static void state_enter_ground(void);    
static void state_exit_ground(void);    
static void state_update_ground(void);
#ifdef FEAT_PLATFORM_JUMP
static void state_enter_jump(void);      
static void state_exit_jump(void);      
static void state_update_jump(void);
#endif
#ifdef FEAT_PLATFORM_DASH
static void state_enter_dash(void);      
static void state_exit_dash(void);      
static void state_update_dash(void);
#endif
#ifdef FEAT_PLATFORM_LADDERS
static void state_enter_ladder(void);    
static void state_exit_ladder(void);    
static void state_update_ladder(void);
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
static void state_enter_wall(void);      
static void state_exit_wall(void);      
static void state_update_wall(void);
#endif
#ifdef FEAT_PLATFORM_KNOCKBACK
static void state_enter_knockback(void); 
static void state_exit_knockback(void); 
static void state_update_knockback(void);
#endif
#ifdef FEAT_PLATFORM_BLANK
static void state_enter_blank(void);     
static void state_exit_blank(void);     
static void state_update_blank(void);
#endif
#ifdef FEAT_PLATFORM_RUN
static void state_enter_run(void);       
static void state_exit_run(void);       
#endif
#ifdef FEAT_PLATFORM_FLOAT
static void state_enter_float(void);     
static void state_exit_float(void);     
#endif

// End of Function Definitions ------------------------------------------------

void platform_init(void) BANKED
{
    plat_callback_reset();

    // Initialize Camera
    camera_offset_x = 0;
    camera_offset_y = 0;
    plat_camera_deadzone_x = camera_deadzone_x;
    camera_deadzone_y = PLATFORM_CAMERA_DEADZONE_Y;
    if ((camera_settings & CAMERA_LOCK_X_FLAG))
    {
        camera_x = SUBPX_TO_PX(PLAYER.pos.x) + 8;
    }
    else
    {
        camera_x = 0;
    }
    if ((camera_settings & CAMERA_LOCK_Y_FLAG))
    {
        camera_y = SUBPX_TO_PX(PLAYER.pos.y) + 8;
    }
    else
    {
        camera_y = 0;
    }

    // Initialize State
    plat_state = GROUND_STATE;
    plat_next_state = GROUND_STATE;
    plat_is_actor_attached = FALSE;
    plat_run_stage = RUN_STAGE_NONE;
    plat_nocontrol_h_timer = 0;
    did_interact_actor = FALSE;
    plat_anim_dirty = FALSE;

#ifdef FEAT_PLATFORM_DROP_THROUGH
    plat_drop_timer = 0;
#endif

    // Initialize other vars
    game_time = 0;
    plat_vel_x = 0;
    plat_vel_y = 4000;              // Magic number for preventing a small glitch when loading
                                    // into a scene
    plat_last_wall_col = WALL_COL_NONE; // This could be 1 bit
    plat_hold_jump_timer = plat_jump_hold_frames;
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
    plat_extra_jumps_counter = plat_extra_jumps;
#endif
    plat_wall_jump_counter = plat_wall_jump_max;
#ifdef FEAT_PLATFORM_KNOCKBACK
    plat_knockback_timer = 0;
#endif
    plat_jump_type = JUMP_TYPE_NONE;
    plat_delta_x = 0;
    plat_delta_y = 0;

#ifdef FEAT_PLATFORM_LADDERS
    // Test if should start scene attached to ladder
    // Requires player to start scene facing either up/down and start on a ladder tile
    if (IS_DIR_VERTICAL(PLAYER.dir))
    {
        UWORD p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);

        // Grab upwards ladder
        UBYTE tile_x_mid = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left + p_half_width);
        UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top + PX_TO_SUBPX(1));
        if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
        {
            PLAYER.pos.x = TILE_TO_SUBPX(tile_x_mid) + PX_TO_SUBPX(4) - (PLAYER.bounds.left + p_half_width);
            plat_state = plat_next_state = LADDER_STATE;
            actor_set_anim(&PLAYER, ANIM_CLIMB);
            actor_stop_anim(&PLAYER);
        }
    }
#endif

    if (PLAYER.dir == DIR_UP || PLAYER.dir == DIR_DOWN || PLAYER.dir == DIR_NONE)
    {
        PLAYER.dir = DIR_RIGHT;
    }
}

void platform_update(void) BANKED
{
    // State transitions

    if (plat_state != plat_next_state)
    {
        // Exit state

        switch (plat_state)
        {
        case FALL_STATE: {
            state_exit_fall();
            break;
        }
#ifdef FEAT_PLATFORM_FLOAT
        case FLOAT_STATE: {
            state_exit_float();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_JUMP        
        case JUMP_STATE: {
            state_exit_jump();
            break;
        }
#endif
        case GROUND_STATE: {
            state_exit_ground();
            break;
        }
#ifdef FEAT_PLATFORM_RUN
        case RUN_STATE: {
            state_exit_run();
            break;
        }  
#endif      
#ifdef FEAT_PLATFORM_LADDERS
        case LADDER_STATE: {
            state_exit_ladder();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_DASH
        case DASH_STATE: {
            state_exit_dash();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
        case WALL_STATE: {
            state_exit_wall();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_KNOCKBACK
        case KNOCKBACK_STATE: {
            state_exit_knockback();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_BLANK
        case BLANK_STATE: {
            state_exit_blank();
            break;
        }
#endif
        }

        plat_state = plat_next_state;

        // Enter state

        switch (plat_state)
        {
        case FALL_STATE: {
            state_enter_fall();
            break;
        }

#ifdef FEAT_PLATFORM_FLOAT
        case FLOAT_STATE: {
            state_enter_float();
            break;
        }
#endif

#ifdef FEAT_PLATFORM_JUMP        
        case JUMP_STATE: {
            state_enter_jump();
            break;
        }
#endif
        case GROUND_STATE: {
            state_enter_ground();
            break;
        }
#ifdef FEAT_PLATFORM_RUN
        case RUN_STATE: {
            state_enter_run();
            break;
        }  
#endif
#ifdef FEAT_PLATFORM_LADDERS
        case LADDER_STATE: {
            state_enter_ladder();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_DASH
        case DASH_STATE: {
            state_enter_dash();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
        case WALL_STATE: {
            state_enter_wall();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_KNOCKBACK
        case KNOCKBACK_STATE: {
            state_enter_knockback();
            break;
        }
#endif
#ifdef FEAT_PLATFORM_BLANK
        case BLANK_STATE: {
            state_enter_blank();
            break;
        }
#endif
        }
    }

    // INITIALIZE VARS

    plat_wall_col = WALL_COL_NONE;
    did_interact_actor = FALSE;

    // A. INPUT CHECK =========================================================

#ifdef FEAT_PLATFORM_DASH
    // Dash Input Check
    plat_dash_pressed = dash_input_pressed();
#endif

    // B. STATE MACHINE =======================================================

    switch (plat_state)
    {

    case FALL_STATE:
    case FLOAT_STATE: {
        state_update_fall();
        break;
    }

    case GROUND_STATE:
    case RUN_STATE: {
        state_update_ground();
        break;
    }

#ifdef FEAT_PLATFORM_JUMP
    case JUMP_STATE: {
        state_update_jump();
        break;
    }
#endif

#ifdef FEAT_PLATFORM_DASH
    case DASH_STATE: {
        state_update_dash();
        break;
    }
#endif

#ifdef FEAT_PLATFORM_LADDERS
    case LADDER_STATE: {
        state_update_ladder();
        break;
    }
#endif

#ifdef FEAT_PLATFORM_WALL_JUMP
    case WALL_STATE: {
        state_update_wall();
        break;
    }
#endif

#ifdef FEAT_PLATFORM_KNOCKBACK
    case KNOCKBACK_STATE: {
        state_update_knockback();
        break;
    }
#endif

#ifdef FEAT_PLATFORM_BLANK
    case BLANK_STATE: {
        state_update_blank();
        break;
    }
#endif
    }

#ifdef FEAT_PLATFORM_DASH
    // COUNTERS================================================================
    //  Counting down until dashing is ready again
    //  XX Set in dash Init and checked in wall, fall, ground, and jump states
    COUNTER_DECREMENT_CB(plat_dash_cooldown_timer, {
        plat_callback_execute(DASH_READY);
    });
#endif

    // Counting down from the max double-tap time (left is -DOUBLE_TAP_WINDOW, right is +DOUBLE_TAP_WINDOW)
    if (plat_tap_timer != 0) {
        plat_tap_timer += IS_NEG(plat_tap_timer) ? 1 : -1;
    }

    // Hone Camera after the player has dashed
    if ((plat_state != DASH_STATE) && (camera_deadzone_x > plat_camera_deadzone_x))
    {
        camera_deadzone_x--;
    }
}

static void player_set_jump_anim(void)
{
    // This animation is currently shared by jumping, dashing, and falling.
    // Dashing doesn't need this complexity though. Here velocity overrides
    // direction. Whereas on the ground it is the reverse.
    if (plat_turn_control)
    {
        if (INPUT_LEFT)
        {
            PLAYER.dir = DIR_LEFT;
        }
        else if (INPUT_RIGHT)
        {
            PLAYER.dir = DIR_RIGHT;
        }
    }

    if (PLAYER.dir == DIR_LEFT)
    {
        actor_set_anim(&PLAYER, ANIM_JUMP_LEFT);
    }
    else
    {
        actor_set_anim(&PLAYER, ANIM_JUMP_RIGHT);
    }
}

#ifdef FEAT_PLATFORM_WALL_JUMP
static void wall_check(void)
{
    if (plat_wall_col != 0 && plat_wall_slide && plat_next_state != GROUND_STATE)
    {
        plat_next_state = WALL_STATE;
    }
    else if (plat_next_state == WALL_STATE)
    {
        plat_next_state = FALL_STATE;
    }
}
#endif

#ifdef FEAT_PLATFORM_LADDERS
static void ladder_check(void)
{
    if (plat_ladder_block_v) {
        // Need to have released up/down since
        // joining the ladder to allow horizontal movement
        if (!(INPUT_UP | INPUT_DOWN)) {
            plat_ladder_block_v = FALSE;
        } else {
            return;
        }
    }
    if (INPUT_PLATFORM_JUMP && INPUT_DOWN)
    {
        // Allow falling from a ladder
        return;
    }
    if (INPUT_UP)
    {
        // Grab upwards ladder
        UWORD p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
        UBYTE tile_x_mid = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left + p_half_width);
        UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top + PX_TO_SUBPX(1));
        if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
        {
            PLAYER.pos.x = TILE_TO_SUBPX(tile_x_mid) + PX_TO_SUBPX(4) - (PLAYER.bounds.left + p_half_width);
            plat_next_state = LADDER_STATE;
        }
    }
    else if (INPUT_DOWN)
    {
        // Grab downwards ladder
        UWORD p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
        UBYTE tile_x_mid = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left + p_half_width);
        UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1;

        if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
        {
            PLAYER.pos.x = TILE_TO_SUBPX(tile_x_mid) + PX_TO_SUBPX(4) - (PLAYER.bounds.left + p_half_width);
            plat_next_state = LADDER_STATE;
        }
    }
}
#endif

#ifdef FEAT_PLATFORM_DASH
static void dash_init(void)
{
    // If the player is pressing a direction (but not facing a direction, ie on
    // a wall or on a changed frame)
    if (INPUT_RIGHT)
    {
        PLAYER.dir = DIR_RIGHT;
    }
    else if (INPUT_LEFT)
    {
        PLAYER.dir = DIR_LEFT;
    }

    plat_dash_per_frame = plat_dash_dist / plat_dash_frames; // Dash distance per frame in the DASH_STATE

    // Dash through walls - check if destination is clear
    if ((plat_dash_mask & COL_CHECK_WALLS) == 0)
    {
#ifdef FEAT_PLATFORM_DASH_USE_GRAVITY
        plat_next_state = FALL_STATE;
        return;
#else
        // Set new_x be the final destination of the dash (ie. the distance covered
        // by all of the dash frames combined)
        UWORD new_x = PLAYER.pos.x
            + ((PLAYER.dir == DIR_RIGHT) ? plat_dash_per_frame : -plat_dash_per_frame)
            * plat_dash_frames;

        UBYTE tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
        UBYTE tile_end = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
        UBYTE tile_xl = SUBPX_TO_TILE(new_x + PLAYER.bounds.left);
        UBYTE tile_xr = SUBPX_TO_TILE(new_x + PLAYER.bounds.right);
        UBYTE col = tile_col_test_range_x(COLLISION_ALL, tile_start, tile_xl, tile_xr);
        if (!col) {
            col = tile_col_test_range_x(COLLISION_ALL, tile_end, tile_xl, tile_xr);
        }
        if (col) {
            plat_next_state = FALL_STATE;
            return;
        }     
#endif        
    }

    plat_is_actor_attached = FALSE;
    plat_camera_deadzone_x = camera_deadzone_x;
    camera_deadzone_x = plat_dash_deadzone;
    plat_dash_cooldown_timer = plat_dash_ready_frames + plat_dash_frames;
#ifndef FEAT_PLATFORM_DASH_USE_GRAVITY
    plat_vel_y = 0;
#endif
    plat_dash_currentframe = plat_dash_frames;
    plat_tap_timer = 0;
    plat_jump_type = JUMP_TYPE_NONE;
    plat_run_stage = RUN_STAGE_NONE;
    plat_next_state = DASH_STATE;

    plat_dash_mask |= COL_CHECK_X | COL_CHECK_Y;
    player_set_jump_anim();
}
#endif

static void handle_horizontal_input(void)
{
    if (INPUT_LEFT || INPUT_RIGHT)
    {
        BYTE dir;
        WORD input_aligned_vel_x;

        if (INPUT_LEFT)
        {
            dir = -1;
            input_aligned_vel_x = plat_vel_x * -1;
        }
        else
        {
            dir = 1;
            input_aligned_vel_x = plat_vel_x;
        }

        // Currently moving opposite direction to input, add turning friction
        if (input_aligned_vel_x < 0)
        {
            input_aligned_vel_x = MIN(input_aligned_vel_x + plat_turn_acc, 0);
#ifdef FEAT_PLATFORM_RUN
            plat_run_stage = RUN_STAGE_TURNING;
#endif
        }
        else
        {
#ifdef FEAT_PLATFORM_RUN
            const UBYTE running = INPUT_PLATFORM_RUN;
            const WORD max_vel = running ? plat_run_vel : plat_walk_vel;
            const WORD accel = running ? plat_run_acc : plat_walk_acc;
#else
            const WORD max_vel = plat_walk_vel;
            const WORD accel = plat_walk_acc;
#endif

            // Above max speed, decelerate until below max speed
            if (input_aligned_vel_x > max_vel)
            {
                goto finally_decelerate;
            }

#if defined(FEAT_PLATFORM_RUN) && PLATFORM_RUN_STYLE == RUN_STYLE_INSTANT
            if (running)
            {
                // Instant move at run speed
                input_aligned_vel_x = max_vel;
                plat_run_stage = RUN_STAGE_RUN_MAX;
            }
            else
            {
                // Walking
                input_aligned_vel_x = CLAMP(input_aligned_vel_x + accel, plat_min_vel, max_vel);
                plat_run_stage = RUN_STAGE_NONE;
            }
#elif defined(FEAT_PLATFORM_RUN) && PLATFORM_RUN_STYLE == RUN_STYLE_SMOOTH
            if (running)
            {
                // Accelerate to walk speed
                if (input_aligned_vel_x < plat_walk_vel)
                {
                    input_aligned_vel_x = MAX(input_aligned_vel_x + plat_walk_acc, plat_min_vel);
                    plat_run_stage = RUN_STAGE_WALK_ACC;
                }
                // Accelerate to run speed
                else if (input_aligned_vel_x < max_vel)
                {
                    input_aligned_vel_x = MIN(input_aligned_vel_x + plat_run_acc, max_vel);
                    plat_run_stage = RUN_STAGE_RUN_ACC;
                }
                // At max speed
                else
                {
                    input_aligned_vel_x = max_vel;
                    plat_run_stage = RUN_STAGE_RUN_MAX;
                }
            }
            else
            {
                // Walking
                input_aligned_vel_x = CLAMP(input_aligned_vel_x + accel, plat_min_vel, max_vel);
                plat_run_stage = RUN_STAGE_NONE;
            }
#else
            input_aligned_vel_x = CLAMP(input_aligned_vel_x + accel, plat_min_vel, max_vel);
#ifdef FEAT_PLATFORM_RUN
            plat_run_stage = running ? RUN_STAGE_RUN_MAX : RUN_STAGE_NONE;
#endif

#endif
        }
        // Restore velocity to original sign
        plat_vel_x = dir == 1 ? input_aligned_vel_x : input_aligned_vel_x * -1;
        plat_delta_x += VEL_TO_SUBPX(plat_vel_x);
    }
    else // No Horizontal Input
    {
    finally_decelerate:
        // Deceleration
        if (plat_vel_x != 0)
        {
            // Set deceleration value based on state
            WORD dec = (plat_state == GROUND_STATE) ? plat_dec : plat_air_dec;

            if (plat_vel_x < 0)
            {
                // Decelerate while moving left
                plat_vel_x = MIN(plat_vel_x + dec, 0);
            }
            else
            {
                // Decelerate while moving right
                plat_vel_x = MAX(plat_vel_x - dec, 0);
            }
            plat_delta_x += VEL_TO_SUBPX(plat_vel_x);
        }
        plat_run_stage = RUN_STAGE_NONE;
    }
}

static void move_and_collide(UBYTE mask)
{
    UWORD sp_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);

#ifdef FEAT_PLATFORM_SLOPES
    UBYTE prev_on_slope = plat_on_slope;
    plat_on_slope = FALSE;
#endif

#ifdef FEAT_PLATFORM_DROP_THROUGH
    COUNTER_DECREMENT(plat_drop_timer);
#endif

    // Horizontal Movement
    if (mask & COL_CHECK_X)
    {
        plat_delta_x = CLAMP(plat_delta_x, -MAX_DELTA, MAX_DELTA);

        UBYTE tile_y_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
        UBYTE tile_y_end = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
        UWORD new_x = PLAYER.pos.x + plat_delta_x;

        // Edge Locking
        // If the player is past the right screen edge
        if ((plat_camera_block & CAMERA_LOCK_SCREEN_RIGHT) && ((new_x + EXCLUSIVE_OFFSET(PLAYER.bounds.right)) > PX_TO_SUBPX(scroll_x + SCREEN_WIDTH)))
        {
            new_x = PX_TO_SUBPX(scroll_x + SCREEN_WIDTH) - EXCLUSIVE_OFFSET(PLAYER.bounds.right);
            plat_vel_x = 0;
        }
        // If the player is past the left screen edge
        if ((plat_camera_block & CAMERA_LOCK_SCREEN_LEFT) && (new_x + PLAYER.bounds.left < PX_TO_SUBPX(scroll_x)))
        {
            new_x = PX_TO_SUBPX(scroll_x) - PLAYER.bounds.left;
            plat_vel_x = 0;
        }

        if (!(mask & COL_CHECK_WALLS))
        {
            goto finally_update_x;
        }

        // Step-Check for collisions one tile left or right based on movement direction
        UBYTE moving_right, hit_flag;
        BYTE wall;
        WORD bounds_edge;

        if (plat_delta_x > 0)
        {
            // Right movement
            moving_right = TRUE;
            hit_flag = COLLISION_LEFT;
            wall = WALL_COL_RIGHT;
            bounds_edge = EXCLUSIVE_OFFSET(PLAYER.bounds.right);
        }
        else
        {
            // Left movement
            moving_right = FALSE;
            hit_flag = COLLISION_RIGHT;
            wall = WALL_COL_LEFT;
            bounds_edge = PLAYER.bounds.left;
        }

        UBYTE tile_x = SUBPX_TO_TILE(new_x + bounds_edge);
        
        UBYTE tile = tile_col_test_range_y(hit_flag, tile_x, tile_y_start, tile_y_end);

        if (tile)
        {
#ifdef FEAT_PLATFORM_SLOPES
            // Handle case when moving up a slope and top contains a solid collision
            //   e.g.
            //
            //    /EX
            //   /XXX
            //
            //  Tile `E` would block movement up slope without these checks
            if ((tile_hit_y == plat_slope_y) &&
                (IS_ON_SLOPE(prev_on_slope) &&
                (IS_SLOPE_LEFT(prev_on_slope) != moving_right)))
            {
                goto finally_update_x;
            }               
#endif
            if (moving_right)
            {
                new_x = TILE_TO_SUBPX(tile_x) - bounds_edge;
            }
            else
            {
                new_x = TILE_TO_SUBPX(tile_x + 1) - bounds_edge;
            }

            plat_vel_x = 0;
            plat_wall_col = wall;
            plat_last_wall_col = wall;
#ifdef FEAT_PLATFORM_WALL_JUMP
            plat_coyote_timer = plat_coyote_frames + 1;
#endif
        }

    finally_update_x:
        PLAYER.pos.x = new_x;
    }

    // Vertical Movement
    if (mask & COL_CHECK_Y)
    {
        plat_delta_y = CLAMP(plat_delta_y, -MAX_DELTA, MAX_DELTA);

        UWORD new_y = PLAYER.pos.y + plat_delta_y;
        UBYTE prev_grounded = plat_grounded;

        if (!(mask & COL_CHECK_WALLS))
        {
            goto finally_update_y;
        }

#ifdef FEAT_PLATFORM_SLOPES
        // 1 frame leniency of grounded state if we were on a slope last frame
        plat_grounded = prev_on_slope;
#else
        plat_grounded = FALSE;
#endif

        UBYTE tile_x_start = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
        UBYTE tile_x_end = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);

        if (plat_delta_y >= 0)
        {
            // Moving Downward
            UBYTE tile;
            UWORD y_bottom = new_y + PLAYER.bounds.bottom;
            UBYTE new_tile_y = SUBPX_TO_TILE(y_bottom);

#ifdef FEAT_PLATFORM_SLOPES

            UBYTE tile_y_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) - 1;
            UBYTE tile_y_end = new_tile_y;
            UBYTE tile_y_offset = FALSE;

            // If previously grounded and gravity is not enough to pull us down to
            // the next tile, manually check it for the next slope This prevents the
            // "animation glitch" when going down slopes
            if (prev_grounded && tile_y_end == (tile_y_start + 1)) {
                tile_y_end += 1;
                tile_y_offset = TRUE;
            }

            UWORD x_mid_coord = PLAYER.pos.x + PLAYER.bounds.left + sp_half_width + PX_TO_SUBPX(1);
            UBYTE tile_x = SUBPX_TO_TILE(x_mid_coord);

            tile = tile_col_test_range_y(COLLISION_SLOPE_ANY, tile_x, tile_y_start, tile_y_end);
            if (tile)
            {
                const UBYTE slope_type = (tile & COLLISION_SLOPE);
                UBYTE x_offset = SUBPX_TILE_REMAINDER(x_mid_coord);
                WORD offset = 0;

                switch (slope_type) {
                    case COLLISION_SLOPE_45_RIGHT:
                        offset = (PX_TO_SUBPX(8) - x_offset) - PLAYER.bounds.bottom;
                        break;
                    case COLLISION_SLOPE_225_RIGHT_BOT:
                        offset = (PX_TO_SUBPX(8) - DIV_2(x_offset)) - PLAYER.bounds.bottom;
                        break;
                    case COLLISION_SLOPE_225_RIGHT_TOP:
                        offset = (PX_TO_SUBPX(4) - DIV_2(x_offset)) - PLAYER.bounds.bottom;
                        break;
                    case COLLISION_SLOPE_45_LEFT:
                        offset = x_offset - PLAYER.bounds.bottom;
                        break;
                    case COLLISION_SLOPE_225_LEFT_BOT:
                        offset = DIV_2(x_offset) - PLAYER.bounds.bottom + PX_TO_SUBPX(4);
                        break;
                    case COLLISION_SLOPE_225_LEFT_TOP:
                        offset = DIV_2(x_offset) - PLAYER.bounds.bottom;
                        break;
                }

                UWORD slope_y_coord = TILE_TO_SUBPX(tile_hit_y) + offset - 1;

                // If going downwards into a slope, don't snap to it unless
                // we've actually collided
                if (prev_grounded || slope_y_coord <= new_y)
                {
                    // If we are moving up a slope, check for top collision
                    UBYTE slope_top_tile_y = SUBPX_TO_TILE(slope_y_coord + PLAYER.bounds.top);

                    plat_slope_y = tile_hit_y;
                    plat_on_slope = tile;
                    plat_grounded = TRUE;

                    UBYTE top_tile = tile_col_test_range_x(COLLISION_BOTTOM, slope_top_tile_y, tile_x_start, tile_x_end);
                    if (top_tile) {
                        plat_vel_y = 0;
                        plat_vel_x = 0;
                        PLAYER.pos.x -= plat_delta_x;
                        plat_next_state = GROUND_STATE;
                    } else {
                        PLAYER.pos.y = slope_y_coord;
                        plat_vel_y = 0;
#ifdef FEAT_PLATFORM_DROP_THROUGH
                        plat_drop_timer = 0;
#endif
                        if (plat_state != DASH_STATE)
                        {
                            plat_next_state = GROUND_STATE;
                        }
                    }
                    goto finally_check_actor_col;
                }
            }
#endif
            // Tile snap threshold
            // If offset into tile is greater than amount moved down this frame
            // then must have started below top of the tile and should fall through
#ifdef FEAT_PLATFORM_SLOPES
            if (!prev_on_slope && (SUBPX_TILE_REMAINDER(y_bottom) > SUBPX_TILE_REMAINDER(plat_delta_y))) {
#else
            if (SUBPX_TILE_REMAINDER(y_bottom) > SUBPX_TILE_REMAINDER(plat_delta_y)) {
#endif
                goto finally_update_y;
            }

            tile = tile_col_test_range_x(COLLISION_TOP, new_tile_y, tile_x_start, tile_x_end);
            if (tile) {
#ifdef FEAT_PLATFORM_DROP_THROUGH
                // Only drop through platforms without a bottom collision
                if (plat_drop_timer && !(tile & COLLISION_BOTTOM))
                {
                    goto finally_update_y;
                }
#endif
                new_y = TILE_TO_SUBPX(tile_hit_y) - PLAYER.bounds.bottom - 1;
                plat_is_actor_attached = FALSE; // Detach when MP moves through a solid tile.
                plat_vel_y = 0;
#ifdef FEAT_PLATFORM_DROP_THROUGH
                plat_drop_timer = 0;
#endif
                plat_grounded = TRUE;
            }
        finally_update_y:
            if (plat_grounded && (plat_state != DASH_STATE)) {
                plat_next_state = GROUND_STATE;
            }
            PLAYER.pos.y = new_y;
        }
        else if (plat_delta_y < 0)
        {
            // Moving Upward
            UBYTE tile_y = SUBPX_TO_TILE(new_y + PLAYER.bounds.top);
            UBYTE tile = tile_col_test_range_x(COLLISION_BOTTOM, tile_y, tile_x_start, tile_x_end);

            if (tile)
            {
                // Hit the ceiling
                new_y = TILE_TO_SUBPX(tile_hit_y + 1) - PLAYER.bounds.top + 1;
                plat_vel_y = 0;
                // MP Test: Attempting stuff to stop the player from continuing upward
                if (plat_is_actor_attached)
                {
                    plat_temp_y = plat_attached_actor->pos.y;
                    if (plat_attached_actor->bounds.top > 0)
                    {
                        plat_temp_y += plat_attached_actor->bounds.top + plat_attached_actor->bounds.bottom << 5;
                    }
                    new_y = plat_temp_y;
                }
#ifdef FEAT_PLATFORM_COYOTE_TIME
                plat_coyote_timer = 0;
#endif
                plat_next_state = FALL_STATE;
            }
            PLAYER.pos.y = new_y;
        }
    }

finally_check_actor_col:
    plat_delta_x = 0;
    plat_delta_y = 0;

    if (mask & COL_CHECK_ACTORS)
    {
        actor_t *hit_actor;
        hit_actor = actor_overlapping_player();

        // Handle platform actor attachment
        if (hit_actor != NULL) {
            const UBYTE is_platform = hit_actor->collision_group & (COLLISION_GROUP_FLAG_PLATFORM | COLLISION_GROUP_FLAG_SOLID);
            const UBYTE is_solid = is_platform & COLLISION_GROUP_FLAG_SOLID;

            if (is_platform && (!plat_is_actor_attached || hit_actor != plat_attached_actor))
            {
                if (!is_solid && (plat_drop_timer != 0))
                {
                    plat_is_actor_attached = FALSE;
                    plat_next_state = FALL_STATE;
                }
                else if (((plat_temp_y + PLAYER.bounds.bottom - plat_delta_y - PX_TO_SUBPX(2)) < (hit_actor->pos.y + hit_actor->bounds.top)) && (plat_vel_y >= 0)) {
                    // Attach to actor (solid or platform)
                    plat_attached_actor = hit_actor;
                    plat_attached_prev_x = hit_actor->pos.x;
                    plat_attached_prev_y = hit_actor->pos.y;
                    PLAYER.pos.y = hit_actor->pos.y + hit_actor->bounds.top - EXCLUSIVE_OFFSET(PLAYER.bounds.bottom);
                    plat_vel_y = 0;
                    plat_is_actor_attached = TRUE;
                    if (plat_state != DASH_STATE)
                    {
                        plat_next_state = GROUND_STATE;
                    }
                }
                else if (is_solid)
                {
                    // Solid-only behavior (side/bottom collision)
                    if (plat_temp_y + PLAYER.bounds.top >
                        hit_actor->pos.y + hit_actor->bounds.bottom)
                    {
                        plat_delta_y += (hit_actor->pos.y - PLAYER.pos.y) +
                                        (-PLAYER.bounds.top + hit_actor->bounds.bottom) + 32;
                        plat_vel_y = plat_grav;

                        if (plat_next_state == JUMP_STATE || plat_is_actor_attached)
                        {
                            plat_next_state = FALL_STATE;
                        }
                    }
                    else if (PLAYER.pos.x != hit_actor->pos.x)
                    {
                        const UBYTE moving_right = PLAYER.pos.x < hit_actor->pos.x;

                        plat_delta_x = (hit_actor->pos.x - PLAYER.pos.x) + 
                            (moving_right
                                ? (hit_actor->bounds.left - EXCLUSIVE_OFFSET(PLAYER.bounds.right))
                                : (EXCLUSIVE_OFFSET(hit_actor->bounds.right) - PLAYER.bounds.left));
                        PLAYER.pos.x += CLAMP(plat_delta_x, -MAX_DELTA, MAX_DELTA);
                        plat_delta_x = 0;

                        plat_wall_col = moving_right ? WALL_COL_RIGHT : WALL_COL_LEFT;
                        plat_last_wall_col = plat_wall_col;
                        plat_coyote_timer = plat_coyote_frames + 1;

                        plat_vel_x = 0;

#ifdef FEAT_PLATFORM_DASH
                        if (plat_next_state == DASH_STATE)
                        {
                            plat_next_state = FALL_STATE;
                        }
#endif
                    }
                }
            }
        }

        if (hit_actor != NULL && (hit_actor->collision_group & COLLISION_GROUP_MASK))
        {
            // Collision group script handling
            player_register_collision_with(hit_actor);
        }
        else if (INPUT_PRESSED(INPUT_PLATFORM_INTERACT))
        {
            if (!hit_actor)
            {
                hit_actor = actor_with_script_in_front_of_player(8);
            }
            if (hit_actor && !(hit_actor->collision_group & COLLISION_GROUP_MASK) && hit_actor->script.bank)
            {
                script_execute(hit_actor->script.bank, hit_actor->script.ptr, 0, 1, 0);
                did_interact_actor = TRUE;
            }
        }
    }

    if (mask & COL_CHECK_TRIGGERS)
    {
        trigger_activate_at_intersection(&PLAYER.bounds, &PLAYER.pos, INPUT_UP_PRESSED);
    }
}

void plat_callback_attach(SCRIPT_CTX *THIS) OLDCALL BANKED
{
    UWORD *slot = VM_REF_TO_PTR(FN_ARG2);
    UBYTE *bank = VM_REF_TO_PTR(FN_ARG1);
    UBYTE **ptr = VM_REF_TO_PTR(FN_ARG0);
    plat_events[*slot].script_bank = *bank;
    plat_events[*slot].script_addr = *ptr;
}

void plat_callback_detach(SCRIPT_CTX *THIS) OLDCALL BANKED
{
    UWORD *slot = VM_REF_TO_PTR(FN_ARG0);
    plat_events[*slot].script_bank = 0;
    plat_events[*slot].script_addr = NULL;
}

inline void plat_callback_reset(void)
{
    memset(plat_events, 0, sizeof(plat_events));
}

static void plat_callback_execute(UBYTE i)
{
    script_event_t *event = &plat_events[i];
    if (!event->script_addr)
        return;
    if ((event->handle == 0) || ((event->handle & SCRIPT_TERMINATED) != 0))
    {
        script_execute(event->script_bank, event->script_addr, &event->handle, 0, 0);
    }
}

// State Machine Functions ----------------------------------------------------

// FALL_STATE

static void state_enter_fall(void) {
    plat_grounded = FALSE;
    plat_is_actor_attached = FALSE;
#ifdef PLATFORM_FALL_ANIM
    plat_set_player_anim_state(PLATFORM_FALL_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET  
    plat_restore_default_anim_state();
#endif
    plat_callback_execute(FALL_INIT); 
}

static void state_exit_fall(void) {
    plat_callback_execute(FALL_END);
}

static void state_update_fall(void) {
    // Keep this here, rather than in init, so that
    // we can easily track float as a jump type
    plat_jump_type = JUMP_TYPE_NONE;

#ifdef FEAT_PLATFORM_DROP_THROUGH
    if (drop_input_pressed())
    {
        plat_drop_timer = DROP_FRAMES_MAX;
        plat_is_actor_attached = FALSE;
    }
#endif

#ifdef FEAT_PLATFORM_JUMP
    // FALL -> JUMP check
    if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
    {
#ifdef FEAT_PLATFORM_WALL_JUMP
        // Wall Jump
        if (plat_coyote_timer != 0 && plat_wall_jump_counter != 0)
        {
            plat_jump_type = JUMP_TYPE_WALL;
            plat_wall_jump_counter--;
            plat_nocontrol_h_timer = WALL_JUMP_NO_CONTROL_H_FRAMES;
            plat_vel_x += (plat_wall_kick + plat_walk_vel) * -plat_last_wall_col;
            plat_next_state = JUMP_STATE;
            return;
        }
#endif
#ifdef FEAT_PLATFORM_COYOTE_TIME
        if (plat_coyote_timer != 0)
        {
            // Coyote Time Jump
            plat_jump_type = JUMP_TYPE_GROUND;
            plat_next_state = JUMP_STATE;
            return;
        }
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
        if (plat_extra_jumps_counter != 0)
        {
            // Double Jump
            plat_jump_type = JUMP_TYPE_DOUBLE;
            if (plat_extra_jumps_counter != UNLIMITED_JUMPS)
            {
                plat_extra_jumps_counter--;
            }
            plat_vel_y = MIN(-plat_jump_vel, plat_vel_y);
            plat_jump_reduction_vel += plat_jump_reduction;
            plat_next_state = JUMP_STATE;
            return;
        }
#endif

#ifdef FEAT_PLATFORM_COYOTE_TIME
        // Setting the Jump Buffer when jump is pressed while not on ground
        plat_jump_buffer_timer = plat_jump_buffer_frames;
#endif

    }
#endif

    // Vertical Movement ----------------------------------------------

#ifdef FEAT_PLATFORM_FLOAT
    UBYTE float_pressed = float_input_pressed();
    if (plat_state != FLOAT_STATE && float_pressed) {
        plat_next_state = FLOAT_STATE;
        return;
    } else if (plat_state == FLOAT_STATE && !float_pressed) {
        plat_next_state = FALL_STATE;
        return;
    }

    if (plat_state == FLOAT_STATE && plat_vel_y >= 0 && !plat_drop_timer)
    {
        plat_jump_type = JUMP_TYPE_FLOATING;
        plat_vel_y = plat_float_vel;
    }
    else
#endif
    if (INPUT_PLATFORM_JUMP && plat_vel_y < 0)
    {
        // Gravity while holding jump
        plat_vel_y += plat_hold_grav;
        plat_vel_y = MIN(plat_vel_y, plat_max_fall_vel);
    }
    else
    {
        // Normal gravity
        plat_vel_y += plat_grav;
        plat_vel_y = MIN(plat_vel_y, plat_max_fall_vel);
    }

    // Collision ------------------------------------------------------
    // Vertical Collision Checks
    plat_delta_y += VEL_TO_SUBPX(plat_vel_y);
    plat_temp_y = PLAYER.pos.y;

    // Horizontal Movement --------------------------------------------
    if (plat_nocontrol_h_timer != 0 || plat_air_control == 0)
    {
        // No horizontal input
        plat_delta_x += VEL_TO_SUBPX(plat_vel_x);
    }
    else
    {
        handle_horizontal_input();
    }

    move_and_collide(COL_CHECK_ALL);

    // ANIMATION ------------------------------------------------------
    player_set_jump_anim();

    // STATE CHANGE ---------------------------------------------------
    // Above: FALL -> GROUND in basic_y_col()

#ifdef FEAT_PLATFORM_WALL_JUMP
    // FALL -> WALL check
    wall_check();
#endif

#ifdef FEAT_PLATFORM_DASH
    // FALL -> DASH check
    if (plat_dash_pressed && plat_dash_cooldown_timer == 0)
    {
        if (plat_dash_from & DASH_FROM_AIR)
        {
            if (plat_wall_col == WALL_COL_NONE || (plat_wall_col == WALL_COL_RIGHT && !INPUT_RIGHT) ||
                (plat_wall_col == WALL_COL_LEFT && !INPUT_LEFT))
            {
                plat_next_state = DASH_STATE;
                return;
            }
        }
    }
#endif

#ifdef FEAT_PLATFORM_LADDERS
    // FALL -> LADDER Check
    ladder_check();
#endif

    // Counting down No Control frames
    // Set in Wall and Fall states, checked in Fall and Jump states
    COUNTER_DECREMENT(plat_nocontrol_h_timer);

#ifdef FEAT_PLATFORM_COYOTE_TIME
    // Counting down Coyote Time Window
    // Set in ground and checked in fall state
    COUNTER_DECREMENT(plat_coyote_timer);
    //  Counting down Jump Buffer Window
    //  Set in Fall and checked in Ground state
    COUNTER_DECREMENT(plat_jump_buffer_timer);
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
    // Counting down Wall Coyote Time
    //  Set in collisions and checked in fall state
    COUNTER_DECREMENT_IF(plat_coyote_timer, plat_wall_col == WALL_COL_NONE);
#endif
}

// GROUND_STATE

static void state_enter_ground(void) {
    plat_vel_y = 0;
    plat_jump_type = JUMP_TYPE_NONE;
#ifdef FEAT_PLATFORM_WALL_JUMP
    plat_coyote_timer = 0;
    plat_wall_jump_counter = plat_wall_jump_max;
#endif
#ifdef FEAT_PLATFORM_COYOTE_TIME
    plat_coyote_timer = plat_coyote_frames;
#endif
#ifdef FEAT_PLATFORM_DROP_THROUGH
    plat_drop_timer = 0;
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
    plat_extra_jumps_counter = plat_extra_jumps;
#endif
    plat_jump_reduction_vel = 0;
#if PLATFORM_ANIM_OVERRIDES_SET
    plat_restore_default_anim_state();
#endif
    actor_set_dir(&PLAYER, PLAYER.dir, TRUE);
    plat_callback_execute(GROUND_INIT);
}

static void state_exit_ground(void) {
    plat_callback_execute(GROUND_END);
}

static void state_update_ground(void) {
       // Add X & Y motion from moving platforms
        // Transform velocity into positional data, to keep the precision of
        // the platform's movement
        plat_grounded = true;

#ifdef FEAT_PLATFORM_DROP_THROUGH
        if (drop_input_pressed())
        {
            plat_drop_timer = DROP_FRAMES_MAX;
            plat_is_actor_attached = FALSE;
        }
#endif

#ifdef FEAT_PLATFORM_DASH
        // GROUND -> DASH Check
        if (plat_dash_pressed && (plat_dash_from & DASH_FROM_GROUND) && plat_dash_cooldown_timer == 0)
        {
            plat_next_state = DASH_STATE;
            return;
        }
#endif

#ifdef FEAT_PLATFORM_RUN
        const UBYTE running = INPUT_PLATFORM_RUN;
        if (plat_state == GROUND_STATE && running) {
            plat_next_state = RUN_STATE;
            return;
        } else if (plat_state == RUN_STATE && !running) {
            plat_next_state = GROUND_STATE;
            return;
        }
#endif

        if (plat_is_actor_attached)
        {
            // If the platform has been disabled, detach the player
            if (CHK_FLAG(plat_attached_actor->flags, ACTOR_FLAG_DISABLED))
            {
                plat_next_state = FALL_STATE;
                plat_is_actor_attached = FALSE;
            }
            // If the player is off the platform to the right, detach
            // from the platform
            else if (PLAYER.pos.x + PLAYER.bounds.left > plat_attached_actor->pos.x + EXCLUSIVE_OFFSET(plat_attached_actor->bounds.right))
            {
                plat_next_state = FALL_STATE;
                plat_is_actor_attached = FALSE;
            }
            // If the player is off the platform to the left, detach
            else if (PLAYER.pos.x + EXCLUSIVE_OFFSET(PLAYER.bounds.right) < plat_attached_actor->pos.x + plat_attached_actor->bounds.left)
            {
                plat_next_state = FALL_STATE;
                plat_is_actor_attached = FALSE;
            }
            // Otherwise, add any change in movement from platform
            else
            {
                plat_delta_x += (plat_attached_actor->pos.x - plat_attached_prev_x);
                plat_attached_prev_x = plat_attached_actor->pos.x;
            }

            // If we're on a platform, zero out any other motion from
            // gravity or other sources
            plat_vel_y = 0;

            // Add any change from the platform we're standing on
            plat_delta_y += plat_attached_actor->pos.y - plat_attached_prev_y;

            // We're setting these to the platform's position, rather than
            // the actor so that if something causes the player to detach
            // (like hitting the roof), they won't automatically get
            // re-attached in the subsequent actor collision step.
            plat_attached_prev_y = plat_attached_actor->pos.y;
            plat_temp_y = plat_attached_actor->pos.y;
        }
        else
        {
            // Normal gravity
            plat_vel_y += plat_grav;
            plat_temp_y = PLAYER.pos.y;
            // queue falling state which will be set back to ground
            // if collision is detected in move_and_collide
            plat_next_state = FALL_STATE;
        }

        // Add Collision Offset from Moving Platforms
        plat_delta_y += VEL_TO_SUBPX(plat_vel_y);

        handle_horizontal_input();
        move_and_collide(COL_CHECK_ALL);

#ifdef FEAT_PLATFORM_RUN
        if (running && (plat_next_state == GROUND_STATE))
        {
            plat_next_state = RUN_STATE;
        }
#endif

        // ANIMATION ------------------------------------------------------

        if (INPUT_LEFT)
        {
            actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
        }
        else if (INPUT_RIGHT)
        {
            actor_set_dir(&PLAYER, DIR_RIGHT, TRUE);
        }
        else if (plat_vel_x == 0)
        {
            actor_set_anim_idle(&PLAYER);
        }

#ifdef FEAT_PLATFORM_JUMP
        // GROUND -> JUMP Check
        if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || plat_jump_buffer_timer != 0) && !did_interact_actor && !plat_drop_timer)
        {
            // Standard Jump
            plat_jump_type = JUMP_TYPE_GROUND;
            plat_next_state = JUMP_STATE;
            return;
        }
        plat_jump_buffer_timer = 0;
#endif

#ifdef FEAT_PLATFORM_LADDERS
        // GROUND -> LADDER Check
        ladder_check();
#endif

}

// JUMP_STATE

#ifdef FEAT_PLATFORM_JUMP
static void state_enter_jump(void) {
    // Right now this has a limited use for triggered jumps because
    // many of the jump effects depend on testing
    // INPUT_PLATFORM_JUMP But if the player switches to this state
    // without pressing jump, then these won't fire...
    plat_grounded = FALSE;
    plat_hold_jump_timer = plat_jump_hold_frames;
    plat_is_actor_attached = FALSE;
    plat_vel_y = MIN(-plat_jump_vel, plat_vel_y);
#ifdef FEAT_PLATFORM_COYOTE_TIME
    plat_coyote_timer = 0;
    plat_jump_buffer_timer = 0;
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
    plat_coyote_timer = 0;
#endif
    plat_jump_vel_per_frame = plat_jump_hold_vel;
    // Calculate jump boost value based on horizontal velocity
    if (plat_run_boost != 0) {
        UWORD abs_vel_x = MAX(plat_vel_x, -plat_vel_x);
#ifdef FEAT_PLATFORM_RUN                
        UBYTE boost_ratio = abs_vel_x / (plat_run_vel >> 7);
#else
        UBYTE boost_ratio = abs_vel_x / (plat_walk_vel >> 7);
#endif
        plat_jump_vel_per_frame += boost_ratio * (plat_run_boost >> 7);
    }

#ifdef PLATFORM_JUMP_ANIM
    plat_set_player_anim_state(PLATFORM_JUMP_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET
    plat_restore_default_anim_state();
#endif

    plat_callback_execute(JUMP_INIT);
}

static void state_exit_jump(void) {
    plat_callback_execute(JUMP_END);
}

static void state_update_jump(void) {
    // Vertical Movement ----------------------------------------------
    // hold_jump_valump force during each jump frame
    if (plat_hold_jump_timer != 0 && INPUT_PLATFORM_JUMP)
    {
        // Add the boost per frame amount.
        plat_vel_y -= plat_jump_vel_per_frame;

#ifdef FEAT_PLATFORM_DOUBLE_JUMP
        // Reduce subsequent jump amounts (for double jumps)
        WORD reduced_vel_y = plat_vel_y + plat_jump_reduction_vel;
        plat_vel_y = MIN(reduced_vel_y, 0);
#endif

        // Handle jump velocity overflow 
        if (plat_vel_y > 0) {
            plat_vel_y = WORD_MIN;
        }

        plat_hold_jump_timer--;
    }
    else if (INPUT_PLATFORM_JUMP && plat_vel_y < 0)
    {
        // After the jump frames end, use the reduced gravity
        plat_vel_y += plat_hold_grav;
    }
    else if (plat_vel_y >= 0)
    {
        plat_next_state = FALL_STATE;
        plat_vel_y += plat_grav;
    }
    else
    {
        plat_vel_y += plat_grav;
    }

    plat_temp_y = PLAYER.pos.y;
    // Start DeltaX with Actor offsets
    plat_delta_y += VEL_TO_SUBPX(plat_vel_y);

    // Horizontal Movement --------------------------------------------
    if (plat_nocontrol_h_timer != 0 || plat_air_control == 0)
    {
        // If the player doesn't have control of their horizontal
        // movement, skip acceleration phase
        plat_delta_x += VEL_TO_SUBPX(plat_vel_x);
    }
    else
    {
        handle_horizontal_input();
    }

    move_and_collide(COL_CHECK_ALL);

    // ANIMATION ------------------------------------------------------
    player_set_jump_anim();

    // STATE CHANGE ---------------------------------------------------
    // Above: JUMP-> NEUTRAL when a) player starts descending, b) player
    // hits roof, c) player stops pressing, d)jump frames run out.

#ifdef FEAT_PLATFORM_WALL_JUMP
    if (!plat_air_control)
    {
        // If air control is disabled collisions with a wall while jumping
        // will prevent wall_check() from registering in FALL_STATE so instead
        // need to check here and switch to WALL_STATE if hit
        wall_check();
    }
#endif

#ifdef FEAT_PLATFORM_DASH
    // JUMP -> DASH check
    if (plat_dash_pressed && plat_dash_cooldown_timer == 0)
    {
#ifdef FEAT_PLATFORM_COYOTE_TIME
        if ((plat_dash_from & DASH_FROM_AIR) || plat_coyote_timer != 0)
#else
        if ((plat_dash_from & DASH_FROM_AIR))
#endif
        {
            plat_next_state = DASH_STATE;
            return;
        }
    }
#endif

    // JUMP -> JUMP check
    if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
    {
#ifdef FEAT_PLATFORM_WALL_JUMP
        // Wall Jump
        if (plat_coyote_timer != 0 && plat_wall_jump_counter != 0)
        {
            plat_jump_type = JUMP_TYPE_WALL;
            plat_wall_jump_counter--;
            plat_nocontrol_h_timer = WALL_JUMP_NO_CONTROL_H_FRAMES;
            plat_vel_x = (plat_wall_kick + plat_walk_vel) * -plat_last_wall_col;
            plat_next_state = JUMP_STATE;
        }
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
        else
#endif
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
        if (plat_extra_jumps_counter != 0)
        {
            // Double Jump
            plat_jump_type = JUMP_TYPE_DOUBLE;
            if (plat_extra_jumps_counter != UNLIMITED_JUMPS)
            {
                plat_extra_jumps_counter--;
            }
            plat_vel_y = MIN(-plat_jump_vel, plat_vel_y);
            plat_jump_reduction_vel += plat_jump_reduction;
            plat_next_state = JUMP_STATE;
        }
#endif
        return;
    }

#ifdef FEAT_PLATFORM_LADDERS
    // JUMP -> LADDER check
    ladder_check();
#endif

    // Counting down No Control frames
    // Set in Wall and Fall states, checked in Fall and Jump states
    COUNTER_DECREMENT(plat_nocontrol_h_timer);
}
#endif

// DASH_STATE

#ifdef FEAT_PLATFORM_DASH
static void state_enter_dash(void) {
#ifdef FEAT_PLATFORM_COYOTE_TIME
    plat_coyote_timer = plat_coyote_frames;
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
    plat_extra_jumps_counter = plat_extra_jumps;
#endif
    dash_init();
    if (plat_next_state != DASH_STATE) {
        // Break out if dash not allowed
        return;
    }
#ifdef PLATFORM_DASH_ANIM
    plat_set_player_anim_state(PLATFORM_DASH_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET  
    plat_restore_default_anim_state();
#endif
    plat_callback_execute(DASH_INIT);
}

static void state_exit_dash(void) {
    plat_callback_execute(DASH_END);
}

static void state_update_dash(void) {
    BYTE dir = (PLAYER.dir == DIR_LEFT ? -1 : 1);
    WORD remaining_dash_dist = plat_dash_per_frame;

    plat_vel_x = plat_run_vel * dir;
#ifdef FEAT_PLATFORM_DASH_USE_GRAVITY
    plat_delta_y = VEL_TO_SUBPX(plat_grav);
#endif

    while (remaining_dash_dist)
    {
        WORD dist = MIN(remaining_dash_dist, MAX_DELTA);
        plat_delta_x = dist * dir;
        move_and_collide(plat_dash_mask);
        remaining_dash_dist -= dist;
    }

    plat_dash_currentframe--;
    if (plat_dash_currentframe == 0)
    {
        plat_next_state = FALL_STATE;
        plat_vel_x = 0;
    }

#ifdef FEAT_PLATFORM_JUMP
    // DASH -> JUMP Check
    if (
        // Jump pressed or was buffered + Not falling through a platform
        (INPUT_PRESSED(INPUT_PLATFORM_JUMP) || plat_jump_buffer_timer != 0) && !plat_drop_timer
    ) {
        // Check if grounded
        UWORD p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
        UBYTE tile_x_mid = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left + p_half_width);
        UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1;
        plat_grounded = tile_at(tile_x_mid, tile_y) & (COLLISION_TOP | COLLISION_SLOPE);

        if (
            // Can dash from ground and is grounded (or coyote time)
            ((plat_dash_jump_from & DASH_FROM_GROUND) && plat_grounded)
            ||
            // Or can dash from air and is not grounded
            ((plat_dash_jump_from & DASH_FROM_AIR) && !plat_grounded)
        ) {
            // Standard Jump
            plat_jump_type = JUMP_TYPE_GROUND;
            plat_next_state = JUMP_STATE;
            return;
        }
    }
    plat_jump_buffer_timer = 0;
#endif
}
#endif

// LADDERS_STATE

#ifdef FEAT_PLATFORM_LADDERS
static void state_enter_ladder(void) {
    plat_jump_type = JUMP_TYPE_NONE;
    plat_ladder_block_h = TRUE;
#ifdef PLATFORM_LADDERS_ANIM
    plat_set_player_anim_state(PLATFORM_LADDERS_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET
    plat_restore_default_anim_state();
#endif
    plat_callback_execute(LADDER_INIT);
}

static void state_exit_ladder(void) {
    plat_ladder_block_v = TRUE;
    plat_callback_execute(LADDER_END);
}

static void state_update_ladder(void) {
    // For positioning the player in the middle of the ladder
    UWORD p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
    UBYTE tile_x_mid = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left + p_half_width);
    plat_vel_x = 0;
    plat_vel_y = 0;

#if defined(FEAT_PLATFORM_DASH)
    // LADDER -> DASH Check
    if (plat_dash_pressed && (plat_dash_from & DASH_FROM_LADDER) && plat_dash_cooldown_timer == 0)
    {
        plat_next_state = DASH_STATE;

        UBYTE tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
        UBYTE tile_end = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1;
        UBYTE tile_x = tile_x_mid + (PLAYER.dir == DIR_LEFT ? -1 : 1);
        UBYTE tile_edge = (PLAYER.dir == DIR_LEFT ? COLLISION_RIGHT : COLLISION_LEFT);

        while (tile_start != tile_end)
        {
            UBYTE tile = tile_at(tile_x, tile_start);
            if (tile & tile_edge)
            {
                plat_next_state = LADDER_STATE; // If there is a wall, cancel dash.
                return;
            }
            tile_start++;
        }

        return;
    }
#endif

#if defined(FEAT_PLATFORM_JUMP) && defined(FEAT_PLATFORM_LADDERS_DROP)
    // LADDER -> FALL check
    if (INPUT_DOWN && INPUT_PRESSED(INPUT_PLATFORM_JUMP))
    {
        plat_next_state = FALL_STATE;
        return;
    }
#endif

#if defined(FEAT_PLATFORM_JUMP) && defined(FEAT_PLATFORM_LADDERS_JUMP)
    // LADDER -> JUMP check
    if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
    {
        plat_jump_type = JUMP_TYPE_GROUND;
        plat_next_state = JUMP_STATE;
        return;
    }
#endif

    if (INPUT_UP)
    {
        // Climb laddder
        UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top + PX_TO_SUBPX(1));
        // Check if the tile above the player is a ladder tile. If so add ladder velocity
        if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
        {
            plat_vel_y = -plat_climb_vel;
        }
        // If reached the top of ladder and tile just below can be stood on then let go of ladder
        else if (tile_at(tile_x_mid, SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1) &
                    COLLISION_TOP)
        {
            plat_next_state = GROUND_STATE;
            PLAYER.pos.y = TILE_TO_SUBPX(SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1) - PLAYER.bounds.bottom - 1;
            return;
        }
#if defined(FEAT_PLATFORM_LADDERS_HOP) && defined(FEAT_PLATFORM_JUMP)
        else {
            plat_next_state = JUMP_STATE;
        }
#endif
    }
    else if (INPUT_DOWN)
    {
        // Descend ladder
        UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + EXCLUSIVE_OFFSET(PLAYER.bounds.bottom));
        UBYTE tile = tile_at(tile_x_mid, tile_y);
        // If tile below is still a ladder climb down
        if (IS_LADDER(tile))
        {
            plat_vel_y = plat_climb_vel;
        }
        // If reached bottom of ladder then let go
        else if (tile & COLLISION_TOP)
        {
            plat_next_state = GROUND_STATE;
            PLAYER.pos.y = TILE_TO_SUBPX(tile_y) - PLAYER.bounds.bottom - 1;
            return;
        }
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
        else
        {
            plat_next_state = FALL_STATE; // Reached bottom of ladder with no platform below so fall off
        }
#endif
    }

    if (plat_ladder_block_h)
    {
        // Need to have released left/right since
        // joining the ladder to allow horizontal movement
        if (!(INPUT_LEFT | INPUT_RIGHT)) {
            plat_ladder_block_h = FALSE;
        }
    }
    else if (INPUT_LEFT)
    {
        PLAYER.dir = DIR_LEFT;

        // If tile below player can be stood on then let go of ladder
        UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1;
        UBYTE tile = tile_at(tile_x_mid, tile_y);
        if (tile & COLLISION_TOP)
        {
            plat_vel_x = 0;
            plat_next_state = FALL_STATE;
            return;
        }

#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
        plat_next_state = FALL_STATE;
#endif

        UBYTE tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
        UBYTE tile_end = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1;
        while (tile_start != tile_end)
        {
            UBYTE tile = tile_at(tile_x_mid - 1, tile_start);
            if (IS_LADDER(tile))
            {
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
                plat_next_state = LADDER_STATE; // If there is a ladder, stay on the ladder.
#endif
                plat_vel_x = -plat_climb_vel;
                return;
            }
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
            else if (tile & COLLISION_RIGHT)
            {
                plat_next_state = LADDER_STATE; // If there is a wall, stay on the ladder.
                return;
            }
#endif
            tile_start++;
        }
    }
    else if (INPUT_RIGHT)
    {
        PLAYER.dir = DIR_RIGHT;

        // If tile below player can be stood on then let go of ladder
        UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1;
        UBYTE tile = tile_at(tile_x_mid, tile_y);
        if (tile & COLLISION_TOP)
        {
            plat_vel_x = 0;
            plat_next_state = FALL_STATE;
            return;
        }

#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
        plat_next_state = FALL_STATE;
#endif

        // Check if able to leave ladder on right
        UBYTE tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
        UBYTE tile_end = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom) + 1;
        while (tile_start != tile_end)
        {
            UBYTE tile = tile_at(tile_x_mid + 1, tile_start);
            if (IS_LADDER(tile))
            {
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
                plat_next_state = LADDER_STATE; // If there is a ladder, stay on the ladder.
#endif
                plat_vel_x = plat_climb_vel;
                return;
            }
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
            else if (tile & COLLISION_LEFT)
            {
                plat_next_state = LADDER_STATE;
                return;
            }
#endif
            tile_start++;
        }
    }
    PLAYER.pos.x += VEL_TO_SUBPX(plat_vel_x);
    PLAYER.pos.y += VEL_TO_SUBPX(plat_vel_y);

    // Animation---------------------------------------------------------------
    if (plat_vel_x == 0 && plat_vel_y == 0)
    {
#ifdef PLATFORM_LADDERS_ANIM
        actor_set_anim_idle(&PLAYER);
#else
        actor_stop_anim(&PLAYER);
#endif            
    } else {
        actor_set_anim(&PLAYER, ANIM_CLIMB);
    }

    // State Change------------------------------------------------------------
    // Collision logic provides options for exiting to Neutral

    move_and_collide(COL_CHECK_ACTORS | COL_CHECK_TRIGGERS);
}
#endif

// WALL_STATE

#ifdef FEAT_PLATFORM_WALL_JUMP
static void state_enter_wall(void) {
    plat_jump_type = JUMP_TYPE_NONE;
    plat_run_stage = RUN_STAGE_NONE;
#ifdef PLATFORM_WALL_SLIDE_ANIM
    plat_set_player_anim_state(PLATFORM_WALL_SLIDE_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET  
    plat_restore_default_anim_state();
#endif
    plat_callback_execute(WALL_INIT);    
}

static void state_exit_wall(void) {
    plat_callback_execute(WALL_END);
}

static void state_update_wall(void) {
    // Vertical Movement ----------------------------------------------
    // WALL SLIDE
    if (plat_vel_y < 0)
    {
        // If the player is still ascending, don't apply wall-gravity
        plat_vel_y += plat_grav;
    }
    else if (plat_wall_slide)
    {
        // If the toggle is on, use wall gravity
        plat_vel_y = plat_wall_slide_vel;
    }
    else
    {
        // Otherwise use regular gravity
        plat_vel_y += plat_grav;
    }

    // Collision ------------------------------------------------------
    // Vertical Collision Checks
    plat_delta_y += VEL_TO_SUBPX(plat_vel_y);
    plat_temp_y = PLAYER.pos.y;

    handle_horizontal_input();
    move_and_collide(COL_CHECK_ALL);

    // ANIMATION ------------------------------------------------------
    // Face away from walls
    if (plat_wall_col == WALL_COL_RIGHT)
    {
        actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
    }
    else if (plat_wall_col == WALL_COL_LEFT)
    {
        actor_set_dir(&PLAYER, DIR_RIGHT, TRUE);
    }

    // STATE CHANGE ---------------------------------------------------
    // Above, basic_y_col can cause WALL -> GROUNDED.
    // Exit state as baseline
    // WALL CHECK
    wall_check();

#ifdef FEAT_PLATFORM_DASH
    // WALL -> DASH Check
    if (plat_dash_pressed && (plat_dash_from & DASH_FROM_AIR) && plat_dash_cooldown_timer == 0)
    {
        if ((plat_wall_col == WALL_COL_RIGHT && !INPUT_RIGHT) || (plat_wall_col == WALL_COL_LEFT && !INPUT_LEFT))
        {
            plat_next_state = DASH_STATE;
            return;
        }
    }
#endif

#ifdef FEAT_PLATFORM_JUMP
    // WALL -> JUMP Check
    if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || plat_jump_buffer_timer != 0) && plat_wall_jump_counter != 0)
    {
        // Wall Jump
        plat_wall_jump_counter--;
        plat_nocontrol_h_timer = WALL_JUMP_NO_CONTROL_H_FRAMES;
        plat_vel_x = (plat_wall_kick + plat_walk_vel) * -plat_last_wall_col;
        plat_jump_type = JUMP_TYPE_WALL;
        plat_next_state = JUMP_STATE;
        return;
    }
#endif

#ifdef FEAT_PLATFORM_LADDERS
    // WALL -> LADDER Check
    ladder_check();
#endif
}
#endif

// KNOCKBACK_STATE

#ifdef FEAT_PLATFORM_KNOCKBACK
static void state_enter_knockback(void) {
    player_set_jump_anim();
    plat_run_stage = RUN_STAGE_NONE;
    plat_jump_type = JUMP_TYPE_NONE;
    plat_vel_x = PLAYER.dir == DIR_RIGHT ? -plat_knockback_vel_x : plat_knockback_vel_x;
    plat_vel_y = -plat_knockback_vel_y;
    plat_grounded = FALSE;
    plat_knockback_timer = plat_knockback_frames;
    plat_drop_timer = 0;
#ifdef PLATFORM_KNOCKBACK_ANIM
    plat_set_player_anim_state(PLATFORM_KNOCKBACK_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET  
    plat_restore_default_anim_state();
#endif
    plat_callback_execute(KNOCKBACK_INIT);
}

static void state_exit_knockback(void) {
    plat_vel_x = 0;
    plat_callback_execute(KNOCKBACK_END);
}
        
static void state_update_knockback(void) {
    // Horizontal Movement --------------------------------------------

    // Horizontal deceleration
    plat_vel_x = (plat_vel_x < 0)
        ? MIN(plat_vel_x + plat_air_dec, 0)
        : MAX(plat_vel_x - plat_air_dec, 0);
    plat_delta_x += VEL_TO_SUBPX(plat_vel_x);

    // Vertical Movement ----------------------------------------------

    // Normal gravity        
    plat_vel_y += plat_grav;
    plat_vel_y = MIN(plat_vel_y, plat_max_fall_vel);
    plat_delta_y += VEL_TO_SUBPX(plat_vel_y);

    // Collision ------------------------------------------------------

    move_and_collide(COL_CHECK_ALL);

    // Counters -------------------------------------------------------
    
    COUNTER_DECREMENT(plat_knockback_timer);
    if (plat_knockback_timer != 0) {
        plat_next_state = KNOCKBACK_STATE;
    }
}
#endif

// BLANK_STATE

#ifdef FEAT_PLATFORM_BLANK
static void state_enter_blank(void) {
    plat_vel_x = 0;
    plat_vel_y = 0;
    plat_grounded = FALSE;
    plat_run_stage = RUN_STAGE_NONE;
    plat_jump_type = JUMP_TYPE_NONE;
#ifdef PLATFORM_BLANK_ANIM
    plat_set_player_anim_state(PLATFORM_BLANK_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET  
    plat_restore_default_anim_state();
#endif
    plat_callback_execute(BLANK_INIT);  
}

static void state_exit_blank(void) {
    plat_vel_x = 0;
    plat_vel_y = 0;
    plat_callback_execute(BLANK_END);    
}

static void state_update_blank(void) {
    // Vertical Movement ----------------------------------------------

    plat_vel_y += plat_blank_grav;
    plat_vel_y = MIN(plat_vel_y, plat_max_fall_vel);
    plat_delta_y += VEL_TO_SUBPX(plat_vel_y);

    // Collision ------------------------------------------------------

    move_and_collide(COL_CHECK_Y);
}
#endif

// FLOAT_STATE

#ifdef FEAT_PLATFORM_FLOAT
static void state_enter_float(void) {
#ifdef PLATFORM_FLOAT_ANIM
    plat_set_player_anim_state(PLATFORM_FLOAT_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET
    plat_restore_default_anim_state();
#endif
    plat_callback_execute(FLOAT_INIT);
}

static void state_exit_float(void) {
    plat_callback_execute(FLOAT_END);
}
#endif

// RUN_STATE

#ifdef FEAT_PLATFORM_RUN
static void state_enter_run(void) {
#ifdef PLATFORM_RUN_ANIM
    plat_set_player_anim_state(PLATFORM_RUN_ANIM);
#elif PLATFORM_ANIM_OVERRIDES_SET
    plat_restore_default_anim_state();
#endif
    plat_callback_execute(RUN_INIT);
}

static void state_exit_run(void) {
    plat_callback_execute(RUN_END);
}
#endif

// End of State Machine Functions ---------------------------------------------
