#pragma bank 255

#include "states/platform.h"

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
#ifndef PLATFORM_CAMERA_DEADZONE_Y
#define PLATFORM_CAMERA_DEADZONE_Y 16
#endif

#define DASH_INPUT_INTERACT 1
#define DASH_INPUT_DOUBLE_TAP 2
#define DASH_INPUT_DOWN_JUMP 3

#define DASH_THRU_NONE 0
#define DASH_THRU_ACTORS 1
#define DASH_THRU_ACTORS_TRIGGERS 2
#define DASH_THRU_ACTORS_TRIGGERS_WALLS 3

#define JUMP_TYPE_NONE 0
#define JUMP_TYPE_GROUND 1
#define JUMP_TYPE_DOUBLE 2
#define JUMP_TYPE_WALL 3
#define JUMP_TYPE_FLOATING 4

#define FLOAT_INPUT_NONE 0
#define FLOAT_INPUT_HOLD_JUMP 1
#define FLOAT_INPUT_HOLD_UP 2

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

#define DROP_THRU_INPUT_DOWN_HOLD 0x1
#define DROP_THRU_INPUT_DOWN_TAP 0x2
#define DROP_THRU_INPUT_DOWN_JUMP_HOLD 0x3
#define DROP_THRU_INPUT_DOWN_JUMP_TAP 0x4

#define DASH_FROM_GROUND 0x1
#define DASH_FROM_AIR 0x2
#define DASH_FROM_LADDER 0x3

#define DROP_FRAMES_MAX 15

#define MAX_DELTA 127
#define UNLIMITED_JUMPS 255
#define DOUBLE_TAP_WINDOW 15
#define WALL_JUMP_NO_CONTROL_H_FRAMES 15

#define COL_CHECK_ALL COL_CHECK_X | COL_CHECK_Y | COL_CHECK_ACTORS | COL_CHECK_TRIGGERS | COL_CHECK_WALLS

#ifndef COLLISION_LADDER
#define COLLISION_LADDER 0x10
#endif
#ifndef COLLISION_SLOPE_45_RIGHT
#define COLLISION_SLOPE_45_RIGHT 0x20
#endif
#ifndef COLLISION_SLOPE_225_RIGHT_BOT
#define COLLISION_SLOPE_225_RIGHT_BOT 0x40
#endif
#ifndef COLLISION_SLOPE_225_RIGHT_TOP
#define COLLISION_SLOPE_225_RIGHT_TOP 0x60
#endif
#ifndef COLLISION_SLOPE_45_LEFT
#define COLLISION_SLOPE_45_LEFT 0x30
#endif
#ifndef COLLISION_SLOPE_225_LEFT_BOT
#define COLLISION_SLOPE_225_LEFT_BOT 0x50
#endif
#ifndef COLLISION_SLOPE_225_LEFT_TOP
#define COLLISION_SLOPE_225_LEFT_TOP 0x70
#endif
#ifndef COLLISION_SLOPE
#define COLLISION_SLOPE 0xF0
#endif

// End of Constants -----------------------------------------------------------

// Macros ---------------------------------------------------------------------

#define IS_ON_SLOPE(t) ((t) & 0x60)
#define IS_SLOPE_LEFT(t) ((t) & 0x10)
#define IS_SLOPE_RIGHT(t) (((t) & 0x10) == 0)
#define IS_LADDER(t) (((t) & 0xF0) == 0x10)
#define VEL_TO_SUBPX(v) ((v) >> 8)
#define IS_FLOAT_INPUT_PRESSED                                                                                         \
    ((plat_float_input == FLOAT_INPUT_HOLD_JUMP && INPUT_PLATFORM_JUMP) ||                                             \
     (plat_float_input == FLOAT_INPUT_HOLD_UP && INPUT_UP))

#define COUNTER_DECREMENT(x)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((x) != 0)                                                                                                  \
            (x)--;                                                                                                     \
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
    BLANK_STATE
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
    CALLBACK_SIZE
} callback_e;

// End of Type Definitions ----------------------------------------------------

// Engine Fields --------------------------------------------------------------

WORD plat_min_vel;
WORD plat_walk_vel;
WORD plat_run_vel;
WORD plat_climb_vel;
WORD plat_walk_acc;
WORD plat_run_acc;
WORD plat_dec;
WORD plat_jump_vel;
WORD plat_grav;
WORD plat_hold_grav;
WORD plat_max_fall_vel;

BYTE plat_camera_deadzone_x; // Camera deadzone x
UBYTE plat_camera_block;     // Limit the player's movement to the camera's edges
UBYTE plat_drop_through;     // Drop-through control input option
WORD plat_jump_min;          // Jump amount applied on the first frame of jumping
UBYTE plat_hold_jump_max;    // Maximum number for frames for continuous input
UBYTE plat_extra_jumps;      // Number of jumps while in the air
WORD plat_jump_reduction;    // Reduce height each double jump
UBYTE plat_coyote_max;       // Coyote Time maximum frames
UBYTE plat_buffer_max;       // Jump Buffer maximum frames
UBYTE plat_wall_jump_max;    // Number of wall jumps in a row
UBYTE plat_wall_slide;       // Enables/Disables wall sliding
WORD plat_wall_grav;         // Gravity while clinging to the wall
WORD plat_wall_kick;         // Horizontal force for pushing off the wall
UBYTE plat_float_input;      // Input type for float (hold up or hold jump)
WORD plat_float_grav;        // Speed of fall descent while floating
UBYTE plat_air_control;      // Enables/Disables air control
UBYTE plat_turn_control;     // Controls the amount of slippage when the player
                             // turns while running.
WORD plat_air_dec;           // air deceleration rate
WORD plat_turn_acc;          // Speed with which a character turns
UBYTE plat_run_boost;        // Additional jump height based on horizontal speed
UBYTE plat_dash;             // Choice of input for dashing:
                             // double-tap, interact, or down and interact
UBYTE plat_dash_from;        // Ground, air, ladders flags
UBYTE plat_dash_use_grav;    // Applies gravity during a dash
UBYTE plat_dash_mask;        // Choose if the player can dash through actors,
                             // triggers, and walls
WORD plat_dash_dist;         // Distance of the dash
UBYTE plat_dash_frames;      // Number of frames for dashing
UBYTE plat_dash_ready_max;   // Time before the player can dash again
UBYTE plat_dash_deadzone;    // Override camera x deadzone when in dash state

// End of Engine Fields -------------------------------------------------------

// Runtime State --------------------------------------------------------------

script_event_t plat_events[CALLBACK_SIZE];

state_e plat_state;      // Current platformer state
state_e plat_next_state; // Next frame's platformer state
UBYTE plat_nocontrol_h;  // Turns off horizontal input, currently only for wall jumping
UBYTE plat_drop_frames;  // The number of frames remaining to drop through platforms
WORD plat_delta_x;
WORD plat_delta_y;

// COUNTER variables
UBYTE plat_ct_val;        // Coyote Time Variable
UBYTE plat_jb_val;        // Jump Buffer Variable
UBYTE plat_wc_val;        // Wall Coyote Time Variable
UBYTE plat_hold_jump_val; // Jump input hold variable
UBYTE plat_dj_val;        // Current double jump
UBYTE plat_wj_val;        // Current wall jump

// WALL variables
BYTE plat_last_wall; // tracks the last wall the player touched
BYTE plat_col;

// DASH VARIABLES
UBYTE plat_dash_ready_val;    // tracks the current amount before the dash is ready
WORD plat_dash_per_frame;     // Takes overall dash distance and holds the amount per-frame
UBYTE plat_dash_currentframe; // Tracks the current frame of the overall dash
BYTE plat_tap_val;            // Number of frames since the last time left or right button was
                              // tapped
UBYTE plat_dash_end_clear;    // Used to store the result of whether the end-position
                              // of a dash is empty

// COLLISION VARS
actor_t *plat_last_actor;  // The last actor the player hit, and that they were
                           // attached to
UBYTE plat_actor_attached; // Keeps track of whether the player is currently on an
                           // actor and inheriting its movement
WORD plat_mp_last_x;       // Keeps track of the pos.x of the attached actor from the
                           // previous frame
WORD plat_mp_last_y;       // Keeps track of the pos.y of the attached actor from the
                           // previous frame

// JUMPING VARIABLES
WORD plat_jump_reduction_val; // Holds a temporary jump velocity reduction
WORD plat_jump_per_frame;     // Holds a jump amount that has been normalized over the
                              // number of jump frames
WORD plat_jump_reduction;     // Holds the reduction amount that has been normalized
                              // over the number of jump frames
WORD plat_boost_val;

// WALKING AND RUNNING VARIABLES
WORD plat_vel_x; // Tracks the player's x-velocity between frames
WORD plat_vel_y; // Tracks the player's y-velocity between frames

// VARIABLES FOR CAMERAS
WORD *plat_edge_left;
WORD *plat_edge_right;
WORD plat_stage_left;

// VARIABLES FOR EVENT PLUGINS
BYTE plat_run_stage;  // Tracks the stage of running based on the run type
UBYTE plat_jump_type; // Tracks the type of jumping, from the ground, in the air, or
                      // off the wall
UBYTE plat_grounded;
UBYTE plat_on_slope;
UBYTE plat_slope_y;
WORD plat_temp_y = 0;

// End of Runtime State -------------------------------------------------------

// Function Definitions -------------------------------------------------------

void player_set_jump_anim(void) BANKED;
void wall_check(void) BANKED;
void ladder_check(void) BANKED;
void dash_init(void) BANKED;
UBYTE drop_press(void) BANKED;
void handle_horizontal_input(void) BANKED;
void move_and_collide(UBYTE mask) BANKED;
void plat_state_script_attach(SCRIPT_CTX *THIS) OLDCALL BANKED;
void plat_state_script_detach(SCRIPT_CTX *THIS) OLDCALL BANKED;
void plat_callback_execute(UBYTE i) BANKED;

// End of Function Definitions ------------------------------------------------

void platform_init(void) BANKED
{
    // Initialize Camera
    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = plat_camera_deadzone_x;
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

    // Initialize Camera Bounds
    plat_stage_left = 0;

    if (plat_camera_block & CAMERA_LOCK_SCREEN_LEFT)
    {
        plat_edge_left = &scroll_x;
    }
    else
    {
        plat_edge_left = &plat_stage_left;
    }
    if (plat_camera_block & CAMERA_LOCK_SCREEN_RIGHT)
    {
        plat_edge_right = &scroll_x;
    }
    else
    {
        plat_edge_right = &image_width;
    }

    // Make sure jumping doesn't overflow variables
    // First, check for jumping based on Frames and Initial Jump Min
    while (32000 - (plat_jump_vel / MIN(15, plat_hold_jump_max)) - plat_jump_min < 0)
    {
        plat_hold_jump_max += 1;
    }

    // This ensures that, by itself, the plat run boost active on any single
    // frame cannot overflow a WORD. It is complemented by another check in the
    // jump itself that works with the actual velocity.
    if (plat_run_boost != 0)
    {
        while ((32000 / plat_run_boost) < (VEL_TO_SUBPX(plat_run_vel) / plat_hold_jump_max))
        {
            plat_run_boost--;
        }
    }

    // Normalize variables by number of frames
    plat_jump_per_frame = plat_jump_vel / MIN(15, plat_hold_jump_max); // jump force applied per
                                                                       // frame in the JUMP_STATE
    plat_jump_reduction = plat_jump_reduction / plat_hold_jump_max;    // Amount to reduce subequent jumps
                                                                       // per frame in JUMP_STATE
#ifdef FEAT_PLATFORM_DASH
    plat_dash_per_frame = plat_dash_dist / plat_dash_frames; // Dash distance per frame in the DASH_STATE
#endif

    plat_boost_val = plat_run_boost / plat_hold_jump_max; // Vertical boost from horizontal
                                                          // speed per frame in JUMP STATE

    // Initialize State
    plat_state = GROUND_STATE;
    plat_next_state = GROUND_STATE;
    plat_actor_attached = FALSE;
    plat_run_stage = RUN_STAGE_NONE;
    plat_nocontrol_h = 0;

#ifdef FEAT_PLATFORM_DROP_THROUGH
    plat_drop_frames = 0;
#endif

    // Initialize other vars
    game_time = 0;
    plat_vel_x = 0;
    plat_vel_y = 4000;              // Magic number for preventing a small glitch when loading
                                    // into a scene
    plat_last_wall = WALL_COL_NONE; // This could be 1 bit
    plat_hold_jump_val = plat_hold_jump_max;
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
    plat_dj_val = 0;
#endif
    plat_wj_val = plat_wall_jump_max;
    plat_dash_end_clear = FALSE; // could also be mixed into the collision bitmask
    plat_jump_type = JUMP_TYPE_NONE;
    plat_delta_x = 0;
    plat_delta_y = 0;

#ifdef FEAT_PLATFORM_LADDERS
    // Test if should start scene attached to ladder
    // Requires player to start scene facing either up/down and start on a ladder tile
    if (IS_DIR_VERTICAL(PLAYER.dir))
    {
        UBYTE p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);

        // Grab upwards ladder
        UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.x) + PLAYER.bounds.left + p_half_width);
        UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top + 1);
        if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
        {
            PLAYER.pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x_mid) + 4 - (PLAYER.bounds.left + p_half_width));
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
            plat_callback_execute(FALL_END);
            break;
        }
        case JUMP_STATE: {
            plat_callback_execute(JUMP_END);
            break;
        }
        case GROUND_STATE: {
            plat_callback_execute(GROUND_END);
            break;
        }
#ifdef FEAT_PLATFORM_LADDERS
        case LADDER_STATE: {
            plat_callback_execute(LADDER_END);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_DASH
        case DASH_STATE: {
            plat_callback_execute(DASH_END);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
        case WALL_STATE: {
            plat_callback_execute(WALL_END);
            break;
        }
#endif
        }

        plat_state = plat_next_state;

        // Enter state

        switch (plat_state)
        {
        case FALL_STATE: {
            plat_actor_attached = FALSE;
            plat_callback_execute(FALL_INIT);
            break;
        }
        case JUMP_STATE: {
            // Right now this has a limited use for triggered jumps because
            // many of the jump effects depend on testing
            // INPUT_PLATFORM_JUMP But if the player switches to this state
            // without pressing jump, then these won't fire...
            plat_hold_jump_val = plat_hold_jump_max;
            plat_actor_attached = FALSE;
            plat_vel_y = MIN(-plat_jump_min, plat_vel_y);
            plat_jb_val = 0;
#ifdef FEAT_PLATFORM_COYOTE_TIME
            plat_ct_val = 0;
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
            plat_wc_val = 0;
#endif
            plat_callback_execute(JUMP_INIT);
            break;
        }
        case GROUND_STATE: {
            plat_vel_y = 0;
            plat_jump_type = JUMP_TYPE_NONE;
#ifdef FEAT_PLATFORM_WALL_JUMP
            plat_wc_val = 0;
            plat_wj_val = plat_wall_jump_max;
#endif
#ifdef FEAT_PLATFORM_COYOTE_TIME
            plat_ct_val = plat_coyote_max;
#endif
#ifdef FEAT_PLATFORM_DROP_THROUGH
            plat_drop_frames = 0;
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
            plat_dj_val = plat_extra_jumps;
#endif
            plat_jump_reduction_val = 0;
            plat_callback_execute(GROUND_INIT);
            break;
        }
#ifdef FEAT_PLATFORM_LADDERS
        case LADDER_STATE: {
            plat_jump_type = JUMP_TYPE_NONE;
            plat_callback_execute(LADDER_INIT);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_DASH
        case DASH_STATE: {
#ifdef FEAT_PLATFORM_COYOTE_TIME
            plat_ct_val = plat_coyote_max;
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
            plat_dj_val = plat_extra_jumps;
#endif
            dash_init();
            plat_callback_execute(DASH_INIT);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
        case WALL_STATE: {
            plat_jump_type = JUMP_TYPE_NONE;
            plat_run_stage = RUN_STAGE_NONE;
            plat_callback_execute(WALL_INIT);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_KNOCKBACK
        case KNOCKBACK_STATE: {
            plat_run_stage = RUN_STAGE_NONE;
            plat_jump_type = JUMP_TYPE_NONE;
            plat_callback_execute(KNOCKBACK_INIT);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_BLANK
        case BLANK_STATE: {
            plat_vel_x = 0;
            plat_vel_y = 0;
            plat_run_stage = RUN_STAGE_NONE;
            plat_jump_type = JUMP_TYPE_NONE;
            plat_callback_execute(BLANK_INIT);
            break;
        }
#endif
        }
    }

    // INITIALIZE VARS

    plat_col = WALL_COL_NONE; // tracks if there is a block left or right

    // A. INPUT CHECK =========================================================

#ifdef FEAT_PLATFORM_DASH

    // Dash Input Check
    UBYTE dash_press = FALSE;
    switch (plat_dash)
    {
    case DASH_INPUT_INTERACT:
        // Interact Dash
        if (INPUT_PRESSED(INPUT_PLATFORM_INTERACT))
        {
            dash_press = TRUE;
        }
        break;
    case DASH_INPUT_DOUBLE_TAP:
        // Double-Tap Dash
        if (INPUT_PRESSED(INPUT_LEFT))
        {
            if (plat_tap_val < 0)
            {
                dash_press = TRUE;
            }
            else
            {
                plat_tap_val = -DOUBLE_TAP_WINDOW;
            }
        }
        else if (INPUT_PRESSED(INPUT_RIGHT))
        {
            if (plat_tap_val > 0)
            {
                dash_press = TRUE;
            }
            else
            {
                plat_tap_val = DOUBLE_TAP_WINDOW;
            }
        }
        break;
    case DASH_INPUT_DOWN_JUMP:
        // Down and Interact (need to check both orders)
        if ((INPUT_PRESSED(INPUT_DOWN) && INPUT_PLATFORM_JUMP) || (INPUT_DOWN && INPUT_PRESSED(INPUT_PLATFORM_JUMP)))
        {
            dash_press = TRUE;
        }
        break;
    }
#endif

    // B. STATE MACHINE =======================================================

    switch (plat_state)
    {

    case FALL_STATE: {
        // Keep this here, rather than in init, so that
        // we can easily track float as a jump type
        plat_jump_type = JUMP_TYPE_NONE;

#ifdef FEAT_PLATFORM_DROP_THROUGH
        if (drop_press())
        {
            plat_drop_frames = DROP_FRAMES_MAX;
            plat_actor_attached = FALSE;
        }
#endif

        // Vertical Movement ----------------------------------------------

#ifdef FEAT_PLATFORM_FLOAT
        if (IS_FLOAT_INPUT_PRESSED && plat_vel_y >= 0 && !plat_drop_frames)
        {
            plat_jump_type = JUMP_TYPE_FLOATING;
            plat_vel_y = plat_float_grav;
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
        if (plat_nocontrol_h != 0 || plat_air_control == 0)
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
        if (dash_press && plat_dash_ready_val == 0)
        {
            if (plat_dash_from & DASH_FROM_AIR)
            {
                if (plat_col == WALL_COL_NONE || (plat_col == WALL_COL_RIGHT && !INPUT_RIGHT) ||
                    (plat_col == WALL_COL_LEFT && !INPUT_LEFT))
                {
                    plat_next_state = DASH_STATE;
                    break;
                }
            }
        }
#endif

#ifdef FEAT_PLATFORM_JUMP
        // FALL -> JUMP check
        if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
        {
#ifdef FEAT_PLATFORM_WALL_JUMP
            // Wall Jump
            if (plat_wc_val != 0 && plat_wj_val != 0)
            {
                plat_jump_type = JUMP_TYPE_WALL;
                plat_wj_val -= 1;
                plat_nocontrol_h = WALL_JUMP_NO_CONTROL_H_FRAMES;
                plat_vel_x += (plat_wall_kick + plat_walk_vel) * -plat_last_wall;
                plat_next_state = JUMP_STATE;
                break;
            }
#endif
#ifdef FEAT_PLATFORM_COYOTE_TIME
            if (plat_ct_val != 0)
            {
                // Coyote Time Jump
                plat_jump_type = JUMP_TYPE_GROUND;
                plat_next_state = JUMP_STATE;
                break;
            }
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
            if (plat_dj_val != 0)
            {
                // Double Jump
                plat_jump_type = JUMP_TYPE_DOUBLE;
                if (plat_dj_val != UNLIMITED_JUMPS)
                {
                    plat_dj_val -= 1;
                }
                plat_jump_reduction_val += plat_jump_reduction;
                plat_next_state = JUMP_STATE;
                break;
            }
#endif

            // Setting the Jump Buffer when jump is pressed while not on
            // the ground
            plat_jb_val = plat_buffer_max;
        }
        // NEUTRAL -> LADDER check
#endif

#ifdef FEAT_PLATFORM_LADDERS
        ladder_check();
#endif

        // COUNTERS
        //  Counting down Jump Buffer Window
        //  Set in Fall and checked in Ground state
        COUNTER_DECREMENT(plat_jb_val);

        // Counting down No Control frames
        // Set in Wall and Fall states, checked in Fall and Jump states
        COUNTER_DECREMENT(plat_nocontrol_h);

#ifdef FEAT_PLATFORM_COYOTE_TIME
        // Counting down Coyote Time Window
        // Set in ground and checked in fall state
        COUNTER_DECREMENT(plat_ct_val);
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
        // Counting down Wall Coyote Time
        //  Set in collisions and checked in fall state
        COUNTER_DECREMENT_IF(plat_wc_val, plat_col == WALL_COL_NONE);
#endif

        break;
    }

    case GROUND_STATE: {
        // Add X & Y motion from moving platforms
        // Transform velocity into positional data, to keep the precision of
        // the platform's movement
        plat_grounded = true;

#ifdef FEAT_PLATFORM_DROP_THROUGH
        if (drop_press())
        {
            plat_drop_frames = DROP_FRAMES_MAX;
            plat_actor_attached = FALSE;
        }
#endif

        if (plat_actor_attached)
        {
            // If the platform has been disabled, detach the player
            if (plat_last_actor->disabled == TRUE)
            {
                plat_next_state = FALL_STATE;
                plat_actor_attached = FALSE;
            }
            // If the player is off the platform to the right, detach
            // from the platform
            else if (PLAYER.pos.x + PX_TO_SUBPX(PLAYER.bounds.left) >
                     plat_last_actor->pos.x + 16 + PX_TO_SUBPX(plat_last_actor->bounds.right))
            {
                plat_next_state = FALL_STATE;
                plat_actor_attached = FALSE;
            }
            // If the player is off the platform to the left, detach
            else if (PLAYER.pos.x + 16 + PX_TO_SUBPX(PLAYER.bounds.right) <
                     plat_last_actor->pos.x + PX_TO_SUBPX(plat_last_actor->bounds.left))
            {
                plat_next_state = FALL_STATE;
                plat_actor_attached = FALSE;
            }
            // Otherwise, add any change in movement from platform
            else
            {
                plat_delta_x += (plat_last_actor->pos.x - plat_mp_last_x);
                plat_mp_last_x = plat_last_actor->pos.x;
            }

            // If we're on a platform, zero out any other motion from
            // gravity or other sources
            plat_vel_y = 0;

            // Add any change from the platform we're standing on
            plat_delta_y += plat_last_actor->pos.y - plat_mp_last_y;

            // We're setting these to the platform's position, rather than
            // the actor so that if something causes the player to detach
            // (like hitting the roof), they won't automatically get
            // re-attached in the subsequent actor collision step.
            plat_mp_last_y = plat_last_actor->pos.y;
            plat_temp_y = plat_last_actor->pos.y;
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

        // ANIMATION ------------------------------------------------------
        // Button direction overrides velocity, for slippery run reasons
        if (INPUT_LEFT)
        {
            actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
        }
        else if (INPUT_RIGHT)
        {
            actor_set_dir(&PLAYER, DIR_RIGHT, TRUE);
        }
        else if (plat_vel_x < 0)
        {
            actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
        }
        else if (plat_vel_x > 0)
        {
            actor_set_dir(&PLAYER, DIR_RIGHT, TRUE);
        }
        else
        {
            actor_set_anim_idle(&PLAYER);
        }

#ifdef FEAT_PLATFORM_DASH
        // STATE CHANGE: Above, basic_y_col can shift to
        // FALL_STATE.--------------------------------------------------
        // GROUND -> DASH Check
        if (dash_press && (plat_dash_from & DASH_FROM_GROUND) && plat_dash_ready_val == 0)
        {
            plat_next_state = DASH_STATE;
            break;
        }
#endif

#ifdef FEAT_PLATFORM_JUMP
        // GROUND -> JUMP Check
        if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || plat_jb_val != 0) && !plat_drop_frames)
        {
            // Standard Jump
            plat_jump_type = JUMP_TYPE_GROUND;
            plat_next_state = JUMP_STATE;
            break;
        }
        plat_jb_val = 0;
#endif

#ifdef FEAT_PLATFORM_LADDERS
        // GROUND -> LADDER Check
        ladder_check();
#endif

        break;
    }

#ifdef FEAT_PLATFORM_JUMP
    case JUMP_STATE: {
        // Vertical Movement ----------------------------------------------
        // hold_jump_valump force during each jump frame
        if (plat_hold_jump_val != 0 && INPUT_PLATFORM_JUMP)
        {
            // Add the boost per frame amount.
            plat_vel_y -= plat_jump_per_frame;
            // Reduce subsequent jump amounts (for double jumps)
            if (plat_jump_vel >= plat_jump_reduction_val)
            {
                plat_vel_y += plat_jump_reduction_val;
            }
            else
            {
                // When reducing that value, zero out if it's negative
                plat_vel_y = 0;
            }
            // Add jump boost from horizontal movement
            WORD tempBoost = VEL_TO_SUBPX(plat_vel_x) * plat_boost_val;
            // Take the positive value of x-vel
            tempBoost = MAX(tempBoost, -tempBoost);
            // This is a test to see if the results will overflow plat_vel_y.
            // Note, plat_vel_y is negative here.
            if (tempBoost > 32767 + plat_vel_y)
            {
                plat_vel_y = -32767;
            }
            else
            {
                plat_vel_y += -tempBoost;
            }
            plat_hold_jump_val -= 1;
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
        if (plat_nocontrol_h != 0 || plat_air_control == 0)
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
        if (dash_press && plat_dash_ready_val == 0)
        {
#ifdef FEAT_PLATFORM_COYOTE_TIME
            if ((plat_dash_from & DASH_FROM_AIR) || plat_ct_val != 0)
#else
            if ((plat_dash_from & DASH_FROM_AIR))
#endif
            {
                plat_next_state = DASH_STATE;
                break;
            }
        }
#endif

        // JUMP -> JUMP check
        if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
        {
#ifdef FEAT_PLATFORM_WALL_JUMP
            // Wall Jump
            if (plat_wc_val != 0 && plat_wj_val != 0)
            {
                plat_jump_type = JUMP_TYPE_WALL;
                plat_wj_val -= 1;
                plat_nocontrol_h = WALL_JUMP_NO_CONTROL_H_FRAMES;
                plat_vel_x = (plat_wall_kick + plat_walk_vel) * -plat_last_wall;
                plat_next_state = JUMP_STATE;
            }
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
            else
#endif
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
                if (plat_dj_val != 0)
            {
                // Double Jump
                plat_jump_type = JUMP_TYPE_DOUBLE;
                if (plat_dj_val != UNLIMITED_JUMPS)
                {
                    plat_dj_val -= 1;
                }
                plat_jump_reduction_val += plat_jump_reduction;
                plat_next_state = JUMP_STATE;
            }
#endif
            break;
        }

#ifdef FEAT_PLATFORM_LADDERS
        // JUMP -> LADDER check
        ladder_check();
#endif

        // Counting down No Control frames
        // Set in Wall and Fall states, checked in Fall and Jump states
        COUNTER_DECREMENT(plat_nocontrol_h);

        break;
    }
#endif

#ifdef FEAT_PLATFORM_DASH
    case DASH_STATE: {

        if (!plat_dash_end_clear)
        {
            plat_next_state = FALL_STATE;
            break;
        }

        BYTE dir = (PLAYER.dir == DIR_LEFT ? -1 : 1);
        WORD remaining_dash_dist = plat_dash_per_frame;

        plat_vel_x = plat_run_vel * dir;
        plat_delta_y = plat_dash_use_grav ? VEL_TO_SUBPX(plat_grav) : -1;

        while (remaining_dash_dist)
        {
            WORD dist = MIN(remaining_dash_dist, MAX_DELTA);
            plat_delta_x = dist * dir;
            move_and_collide(plat_dash_mask);
            remaining_dash_dist -= dist;
        }

        plat_dash_currentframe -= 1;
        if (plat_dash_currentframe == 0)
        {
            plat_next_state = FALL_STATE;
            plat_vel_x = 0;
        }

#ifdef FEAT_PLATFORM_JUMP
        // DASH -> JUMP Check
        if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || plat_jb_val != 0) &&
            (plat_grounded || plat_dj_val != 0 || plat_ct_val != 0) && !plat_drop_frames)
        {
            // Standard Jump
            plat_jump_type = JUMP_TYPE_GROUND;
            plat_next_state = JUMP_STATE;
            break;
        }
        plat_jb_val = 0;
#endif
        break;
    }
#endif

#ifdef FEAT_PLATFORM_LADDERS
    case LADDER_STATE: {
        // For positioning the player in the middle of the ladder
        UBYTE p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
        UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.x) + PLAYER.bounds.left + p_half_width);
        plat_vel_x = 0;
        plat_vel_y = 0;

#if defined(FEAT_PLATFORM_DASH)
        // LADDER -> DASH Check
        if (dash_press && (plat_dash_from & DASH_FROM_LADDER) && plat_dash_ready_val == 0)
        {
            plat_next_state = DASH_STATE;

            UBYTE tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top);
            UBYTE tile_end = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;
            UBYTE tile_x = tile_x_mid + (PLAYER.dir == DIR_LEFT ? -1 : 1);
            UBYTE tile_edge = (PLAYER.dir == DIR_LEFT ? COLLISION_RIGHT : COLLISION_LEFT);

            while (tile_start != tile_end)
            {
                UBYTE tile = tile_at(tile_x, tile_start);
                if (tile & tile_edge)
                {
                    plat_next_state = LADDER_STATE; // If there is a wall, cancel dash.
                    break;
                }
                tile_start++;
            }

            break;
        }
#endif

#if defined(FEAT_PLATFORM_JUMP) && defined(FEAT_PLATFORM_LADDERS_DROP)
        // LADDER -> FALL check
        if (INPUT_DOWN && INPUT_PRESSED(INPUT_PLATFORM_JUMP))
        {
            plat_next_state = FALL_STATE;
            break;
        }
#endif

#if defined(FEAT_PLATFORM_JUMP) && defined(FEAT_PLATFORM_LADDERS_JUMP)
        // LADDER -> JUMP check
        if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
        {
            plat_jump_type = JUMP_TYPE_GROUND;
            plat_next_state = JUMP_STATE;
            break;
        }
#endif

        if (INPUT_UP)
        {
            // Climb laddder
            UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top + 1);
            // Check if the tile above the player is a ladder tile. If so add ladder velocity
            if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
            {
                plat_vel_y = -plat_climb_vel;
            }
            // If reached the top of ladder and tile just below can be stood on then let go of ladder
            else if (tile_at(tile_x_mid, PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1) &
                     COLLISION_TOP)
            {
                plat_next_state = FALL_STATE;
            }
        }
        else if (INPUT_DOWN)
        {
            // Descend ladder
            UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom + 1);
            UBYTE tile = tile_at(tile_x_mid, tile_y);
            // If tile below is still a ladder climb down
            if (IS_LADDER(tile))
            {
                plat_vel_y = plat_climb_vel;
            }
            // If reached bottom of ladder then let go
            else if (tile & COLLISION_TOP)
            {
                plat_next_state = FALL_STATE;
            }
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
            else
            {
                plat_next_state = FALL_STATE; // Reached bottom of ladder with no platform below so fall off
            }
#endif
        }

        if (INPUT_LEFT)
        {
            PLAYER.dir = DIR_LEFT;

            // If tile below player can be stood on then let go of ladder
            UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;
            UBYTE tile = tile_at(tile_x_mid, tile_y);
            if (tile & COLLISION_TOP)
            {
                plat_vel_x = 0;
                plat_next_state = FALL_STATE;
                break;
            }

#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
            plat_next_state = FALL_STATE;
#endif

            UBYTE tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top);
            UBYTE tile_end = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;
            while (tile_start != tile_end)
            {
                UBYTE tile = tile_at(tile_x_mid - 1, tile_start);
                if (IS_LADDER(tile))
                {
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
                    plat_next_state = LADDER_STATE; // If there is a ladder, stay on the ladder.
#endif
                    plat_vel_x = -plat_climb_vel;
                    break;
                }
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
                else if (tile & COLLISION_RIGHT)
                {
                    plat_next_state = LADDER_STATE; // If there is a wall, stay on the ladder.
                    break;
                }
#endif
                tile_start++;
            }
        }
        else if (INPUT_RIGHT)
        {
            PLAYER.dir = DIR_RIGHT;

            // If tile below player can be stood on then let go of ladder
            UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;
            UBYTE tile = tile_at(tile_x_mid, tile_y);
            if (tile & COLLISION_TOP)
            {
                plat_vel_x = 0;
                plat_next_state = FALL_STATE;
                break;
            }

#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
            plat_next_state = FALL_STATE;
#endif

            // Check if able to leave ladder on right
            UBYTE tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top);
            UBYTE tile_end = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;
            while (tile_start != tile_end)
            {
                UBYTE tile = tile_at(tile_x_mid + 1, tile_start);
                if (IS_LADDER(tile))
                {
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
                    plat_next_state = LADDER_STATE; // If there is a ladder, stay on the ladder.
#endif
                    plat_vel_x = plat_climb_vel;
                    break;
                }
#ifdef FEAT_PLATFORM_LADDERS_WALK_OFF
                else if (tile & COLLISION_LEFT)
                {
                    plat_next_state = LADDER_STATE;
                    break;
                }
#endif
                tile_start++;
            }
        }
        PLAYER.pos.x += VEL_TO_SUBPX(plat_vel_x);
        PLAYER.pos.y += VEL_TO_SUBPX(plat_vel_y);

        // Animation---------------------------------------------------------------
        actor_set_anim(&PLAYER, ANIM_CLIMB);
        if (plat_vel_x == 0 && plat_vel_y == 0)
        {
            actor_stop_anim(&PLAYER);
        }

        // State Change------------------------------------------------------------
        // Collision logic provides options for exiting to Neutral

        move_and_collide(COL_CHECK_ACTORS | COL_CHECK_TRIGGERS);

        break;
    }
#endif

#ifdef FEAT_PLATFORM_WALL_JUMP
    case WALL_STATE: {
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
            plat_vel_y = plat_wall_grav;
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
        if (plat_col == WALL_COL_RIGHT)
        {
            actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
        }
        else if (plat_col == WALL_COL_LEFT)
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
        if (dash_press && (plat_dash_from & DASH_FROM_AIR) && plat_dash_ready_val == 0)
        {
            if ((plat_col == WALL_COL_RIGHT && !INPUT_RIGHT) || (plat_col == WALL_COL_LEFT && !INPUT_LEFT))
            {
                plat_next_state = DASH_STATE;
                break;
            }
        }
#endif

#ifdef FEAT_PLATFORM_JUMP
        // WALL -> JUMP Check
        if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || plat_jb_val != 0) && plat_wj_val != 0)
        {
            // Wall Jump
            plat_wj_val -= 1;
            plat_nocontrol_h = WALL_JUMP_NO_CONTROL_H_FRAMES;
            plat_vel_x = (plat_wall_kick + plat_walk_vel) * -plat_last_wall;
            plat_jump_type = JUMP_TYPE_WALL;
            plat_next_state = JUMP_STATE;
            break;
        }
#endif

#ifdef FEAT_PLATFORM_LADDERS
        // WALL -> LADDER Check
        ladder_check();
#endif

        break;
    }
#endif

#ifdef FEAT_PLATFORM_KNOCKBACK
    case KNOCKBACK_STATE: {
        // Horizontal Movement --------------------------------------------
        if (plat_vel_x < 0)
        {
            plat_vel_x += plat_air_dec;
            plat_vel_x = MIN(plat_vel_x, 0);
        }
        else if (plat_vel_x > 0)
        {
            plat_vel_x -= plat_air_dec;
            plat_vel_x = MAX(plat_vel_x, 0);
        }
        plat_delta_x += VEL_TO_SUBPX(plat_vel_x);

        // Vertical Movement ----------------------------------------------
        // Normal gravity
        plat_vel_y += plat_grav;
        plat_vel_y = MIN(plat_vel_y, plat_max_fall_vel);

        // Collision ------------------------------------------------------

        // Vertical Collision Checks
        plat_delta_y += VEL_TO_SUBPX(plat_vel_y);
        plat_temp_y = PLAYER.pos.y;

#ifdef FEAT_PLATFORM_DROP_THROUGH
        plat_drop_frames = 0;
#endif
        move_and_collide(COL_CHECK_ALL);

        plat_vel_y = 0;
        plat_next_state = KNOCKBACK_STATE;

        break;
    }
#endif

#ifdef FEAT_PLATFORM_BLANK
    case BLANK_STATE: {
        move_and_collide(COL_CHECK_ACTORS | COL_CHECK_TRIGGERS);
        break;
    }
#endif
    }

#ifdef FEAT_PLATFORM_DASH
    // COUNTERS================================================================
    //  Counting down until dashing is ready again
    //  XX Set in dash Init and checked in wall, fall, ground, and jump states
    COUNTER_DECREMENT(plat_dash_ready_val);
#endif

    // Counting down from the max double-tap time (left is -DOUBLE_TAP_WINDOW, right is +DOUBLE_TAP_WINDOW)
    if (plat_tap_val > 0)
    {
        plat_tap_val -= 1;
    }
    else if (plat_tap_val < 0)
    {
        plat_tap_val += 1;
    }

    // Hone Camera after the player has dashed
    if (camera_deadzone_x > plat_camera_deadzone_x)
    {
        camera_deadzone_x -= 1;
    }
}

void player_set_jump_anim(void) BANKED
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
        else if (plat_vel_x < 0)
        {
            PLAYER.dir = DIR_LEFT;
        }
        else if (plat_vel_x > 0)
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
void wall_check(void) BANKED
{
    if (plat_col != 0 && plat_wall_slide)
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
void ladder_check(void) BANKED
{
    if (INPUT_PLATFORM_JUMP)
    {
        return;
    }
    if (INPUT_UP_PRESSED)
    {
        // Grab upwards ladder
        UBYTE p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
        UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.x) + PLAYER.bounds.left + p_half_width);
        UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top + 1);
        if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
        {
            PLAYER.pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x_mid) + 4 - (PLAYER.bounds.left + p_half_width));
            plat_next_state = LADDER_STATE;
        }
    }
    else if (INPUT_DOWN_PRESSED)
    {
        // Grab downwards ladder
        UBYTE p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
        UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.x) + PLAYER.bounds.left + p_half_width);
        UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;

        if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
        {
            PLAYER.pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x_mid) + 4 - (PLAYER.bounds.left + p_half_width));
            plat_next_state = LADDER_STATE;
        }
    }
}
#endif

#ifdef FEAT_PLATFORM_DASH
void dash_init(void) BANKED
{
    WORD new_x;
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

    // Set new_x be the final destination of the dash (ie. the distance covered
    // by all of the dash frames combined)
    if (PLAYER.dir == DIR_RIGHT)
    {
        new_x = PLAYER.pos.x + (plat_dash_per_frame * plat_dash_frames);
    }
    else
    {
        new_x = PLAYER.pos.x + (-plat_dash_per_frame * plat_dash_frames);
    }

    plat_dash_end_clear = true; // Assume that the landing spot is clear, and
                                // disable if we collide below

    // Dash through walls
    if ((plat_dash_mask & COL_CHECK_WALLS) == 0)
    {
        if (plat_dash_use_grav)
        {
            plat_dash_end_clear = false;
        }

        UBYTE tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top);
        UBYTE tile_end = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;

        // Do a collision check at the final landing spot (but not all the steps
        // in-between.)
        if (PLAYER.dir == DIR_RIGHT)
        {
            // Don't dash off the screen to the right
            if (PLAYER.pos.x + PX_TO_SUBPX(PLAYER.bounds.right) + (plat_dash_per_frame * (plat_dash_frames)) >
                PX_TO_SUBPX(image_width - 16))
            {
                plat_dash_end_clear = false;
            }
            else
            {
                UBYTE tile_xr = PX_TO_TILE(SUBPX_TO_PX(new_x) + PLAYER.bounds.right) + 1;
                UBYTE tile_xl = PX_TO_TILE(SUBPX_TO_PX(new_x) + PLAYER.bounds.left);
                while (tile_xl != tile_xr)
                { // This checks all the tiles between the left
                  // bounds and the right bounds
                    while (tile_start != tile_end)
                    { // This checks all the tiles that the
                      // character occupies in height
                        if (tile_at(tile_xl, tile_start) & COLLISION_ALL)
                        {
                            plat_dash_end_clear = false;
                            goto initDash; // Gotos are still good for breaking
                                           // embedded loops.
                        }
                        tile_start++;
                    }
                    tile_start =
                        PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top); // Reset the height after each loop
                    tile_xl++;
                }
            }
        }
        else if (PLAYER.dir == DIR_LEFT)
        {
            // Don't dash off the screen to the left
            if (PLAYER.pos.x <=
                ((plat_dash_per_frame * plat_dash_frames) + PX_TO_SUBPX(PLAYER.bounds.left)) + PX_TO_SUBPX(8))
            {
                plat_dash_end_clear = false; // To get around unsigned position, test if the
                                             // player's current position is less than the total
                                             // dist.
            }
            else
            {
                UBYTE tile_xl = PX_TO_TILE(SUBPX_TO_PX(new_x) + PLAYER.bounds.left);
                UBYTE tile_xr = PX_TO_TILE(SUBPX_TO_PX(new_x) + PLAYER.bounds.right) + 1;

                while (tile_xl != tile_xr)
                {
                    while (tile_start != tile_end)
                    {
                        if (tile_at(tile_xl, tile_start) & COLLISION_ALL)
                        {
                            plat_dash_end_clear = false;
                            goto initDash;
                        }
                        tile_start++;
                    }
                    tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top);
                    tile_xl++;
                }
            }
        }
    }
initDash:
    plat_actor_attached = FALSE;
    camera_deadzone_x = plat_dash_deadzone;
    plat_dash_ready_val = plat_dash_ready_max + plat_dash_frames;
    if (!plat_dash_use_grav)
    {
        plat_vel_y = 0;
    }
    plat_dash_currentframe = plat_dash_frames;
    plat_tap_val = 0;
    plat_jump_type = JUMP_TYPE_NONE;
    plat_run_stage = RUN_STAGE_NONE;
    plat_next_state = DASH_STATE;

    plat_dash_mask |= COL_CHECK_X | COL_CHECK_Y;
    player_set_jump_anim();
}
#endif

#ifdef FEAT_PLATFORM_DROP_THROUGH
UBYTE drop_press(void) BANKED
{
    switch (plat_drop_through)
    {
    case DROP_THRU_INPUT_DOWN_HOLD:
        return INPUT_DOWN;
    case DROP_THRU_INPUT_DOWN_TAP:
        return INPUT_PRESSED(INPUT_DOWN);
    case DROP_THRU_INPUT_DOWN_JUMP_HOLD:
        return INPUT_DOWN && INPUT_PLATFORM_JUMP;
    case DROP_THRU_INPUT_DOWN_JUMP_TAP:
        return (INPUT_PRESSED(INPUT_DOWN) && INPUT_PLATFORM_JUMP) || (INPUT_DOWN && INPUT_PRESSED(INPUT_PLATFORM_JUMP));
    }
    return FALSE;
}
#endif

void handle_horizontal_input(void) BANKED
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
                goto decelerate;
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
    decelerate:
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

void move_and_collide(UBYTE mask) BANKED
{
    const WORD sp_bounds_top = PX_TO_SUBPX(PLAYER.bounds.top);
    const WORD sp_bounds_bottom = PX_TO_SUBPX(PLAYER.bounds.bottom);
    const WORD sp_bounds_left = PX_TO_SUBPX(PLAYER.bounds.left);
    const WORD sp_bounds_right = PX_TO_SUBPX(PLAYER.bounds.right);
    WORD sp_half_width = DIV_2(sp_bounds_right - sp_bounds_left);

#ifdef FEAT_PLATFORM_SLOPES
    UBYTE prev_on_slope = 0;
#endif

#ifdef FEAT_PLATFORM_DROP_THROUGH
    COUNTER_DECREMENT(plat_drop_frames);
#endif

    // Horizontal Movement
    if (mask & COL_CHECK_X)
    {
        plat_delta_x = CLAMP(plat_delta_x, -MAX_DELTA, MAX_DELTA);
#ifdef FEAT_PLATFORM_SLOPES
        prev_on_slope = plat_on_slope;
        plat_on_slope = FALSE;
#endif

        UBYTE tile_y_start = SUBPX_TO_TILE(PLAYER.pos.y + sp_bounds_bottom);
        UBYTE tile_y_end = SUBPX_TO_TILE(PLAYER.pos.y + sp_bounds_top) - 1;
        UWORD new_x = PLAYER.pos.x + plat_delta_x;

        UBYTE tile_x = 0;

        // Edge Locking
        // If the player is past the right edge (camera or screen)
        if (new_x > PX_TO_SUBPX(*plat_edge_right + SCREEN_WIDTH - 16))
        {
            // If the player is trying to go FURTHER right
            if (new_x > PLAYER.pos.x)
            {
                new_x = PLAYER.pos.x;
                plat_vel_x = 0;
            }
            else
            {
                // If the player is already off the screen, push them back
                new_x = PLAYER.pos.x - MIN(PLAYER.pos.x - PX_TO_SUBPX(*plat_edge_right + SCREEN_WIDTH - 16), 16);
            }
            // Same but for left side. This side needs a 1 tile (8px) buffer so it
            // doesn't overflow the variable.
        }
        else if (new_x < PX_TO_SUBPX(*plat_edge_left))
        {
            if (plat_delta_x < 0)
            {
                new_x = PLAYER.pos.x;
                plat_vel_x = 0;
            }
            else
            {
                new_x = PLAYER.pos.x + MIN(PX_TO_SUBPX(*plat_edge_left + 8) - PLAYER.pos.x, 16);
            }
        }

        if (!(mask & COL_CHECK_WALLS))
        {
            goto gotoXReposition;
        }

        // Step-Check for collisions one tile left or right based on movement direction
        UBYTE moving_right, hit_flag;
        enum wall_t wall;
        WORD bounds_edge;

        if (new_x > PLAYER.pos.x)
        {
            // Right movement
            moving_right = TRUE;
            hit_flag = COLLISION_LEFT;
            wall = WALL_COL_RIGHT;
            bounds_edge = sp_bounds_right;
        }
        else
        {
            // Left movement
            moving_right = FALSE;
            hit_flag = COLLISION_RIGHT;
            wall = WALL_COL_LEFT;
            bounds_edge = sp_bounds_left;
        }

        tile_x = SUBPX_TO_TILE(new_x + bounds_edge);

#ifdef FEAT_PLATFORM_SLOPES
        UBYTE tile_x_mid = SUBPX_TO_TILE(new_x + sp_bounds_left + sp_half_width + PX_TO_SUBPX(1));

        UBYTE *tile_ptr = tile_ptr_at(tile_x_mid, tile_y_start);
        UBYTE col_mid = safe_read_tile_ptr(tile_ptr, tile_x_mid, tile_y_start);

        if (IS_ON_SLOPE(col_mid))
        {
            plat_on_slope = col_mid;
            plat_slope_y = tile_y_start;
        }

        // Fix offset to point at tile_x
        tile_ptr += (tile_x - tile_x_mid);
#endif

        UBYTE tile = tile_col_test_range_y(hit_flag, tile_x, tile_y_start, tile_y_end);
        if (tile) {
#ifdef FEAT_PLATFORM_SLOPES
            // Handle case when moving up a slope and top contains a solid collision
            //   e.g.
            //
            //    /EX
            //   /XXX
            //
            //  Tile `E` would block movement up slope without these checks
            if ((tile_hit_y == plat_slope_y) &&
                ((IS_ON_SLOPE(plat_on_slope) && (IS_SLOPE_LEFT(plat_on_slope) != moving_right)) ||
                    (IS_ON_SLOPE(prev_on_slope)  && (IS_SLOPE_LEFT(prev_on_slope) != moving_right))))
            {
                goto gotoXReposition;
            }               
#endif
            if (moving_right)
            {
                new_x = TILE_TO_SUBPX(tile_hit_x) - bounds_edge - 1;
            }
            else
            {
                new_x = TILE_TO_SUBPX(tile_hit_x + 1) - bounds_edge + 1;
            }

            plat_vel_x = 0;
            plat_col = wall;
            plat_last_wall = wall;
#ifdef FEAT_PLATFORM_WALL_JUMP
            plat_wc_val = plat_coyote_max + 1;
#endif
        }

    gotoXReposition:
        PLAYER.pos.x = new_x;
    }

    // Vertical Movement
    if (mask & COL_CHECK_Y)
    {
        plat_delta_y = CLAMP(plat_delta_y, -MAX_DELTA, MAX_DELTA);

        WORD new_y = PLAYER.pos.y + plat_delta_y;
        if (!(mask & COL_CHECK_WALLS))
        {
            goto gotoYReposition;
        }
        UBYTE prev_grounded = plat_grounded;

#ifdef FEAT_PLATFORM_SLOPES
        // 1 frame leniency of grounded state if we were on a slope last frame
        plat_grounded = prev_on_slope;
#else
        plat_grounded = FALSE;
#endif

        UBYTE tile_x_start = SUBPX_TO_TILE(PLAYER.pos.x + sp_bounds_left);
        UBYTE tile_x_end = SUBPX_TO_TILE(PLAYER.pos.x + sp_bounds_right) + 1;

        if (plat_delta_y >= 0)
        {
            // Moving Downward
            UBYTE *tile_ptr;

            UBYTE new_tile_y = SUBPX_TO_TILE(new_y + sp_bounds_bottom);

#ifdef FEAT_PLATFORM_SLOPES

            UBYTE tile_y_start = SUBPX_TO_TILE(PLAYER.pos.y + sp_bounds_bottom) - 1;
            UBYTE tile_y_offset = FALSE;

            // If previously grounded and gravity is not enough to pull us down to
            // the next tile, manually check it for the next slope This prevents the
            // "animation glitch" when going down slopes
            if (prev_grounded && new_tile_y == (tile_y_start + 1)) {
                new_tile_y += 1;
                tile_y_offset = TRUE;
            }

            UWORD x_mid_coord = PLAYER.pos.x + sp_bounds_left + sp_half_width + PX_TO_SUBPX(1);

            UBYTE tile_x = SUBPX_TO_TILE(x_mid_coord);

            UBYTE col = tile_col_test_range_y(0x60, tile_x, tile_y_start, new_tile_y);
            if (col) {
                const UBYTE slope_type = (col & COLLISION_SLOPE);
                UBYTE x_offset = SUBPX_TILE_REMAINDER(x_mid_coord);
                WORD offset = 0;

                switch (slope_type) {
                    case COLLISION_SLOPE_45_RIGHT:
                        offset = (PX_TO_SUBPX(8) - x_offset) - sp_bounds_bottom;
                        break;
                    case COLLISION_SLOPE_225_RIGHT_BOT:
                        offset = (PX_TO_SUBPX(8) - DIV_2(x_offset)) - sp_bounds_bottom;
                        break;
                    case COLLISION_SLOPE_225_RIGHT_TOP:
                        offset = (PX_TO_SUBPX(4) - DIV_2(x_offset)) - sp_bounds_bottom;
                        break;
                    case COLLISION_SLOPE_45_LEFT:
                        offset = x_offset - sp_bounds_bottom;
                        break;
                    case COLLISION_SLOPE_225_LEFT_BOT:
                        offset = DIV_2(x_offset) - sp_bounds_bottom + PX_TO_SUBPX(4);
                        break;
                    case COLLISION_SLOPE_225_LEFT_TOP:
                        offset = DIV_2(x_offset) - sp_bounds_bottom;
                        break;
                }

                UWORD slope_y_coord = TILE_TO_SUBPX(tile_hit_y) + offset - 1;

                // If going downwards into a slope, don't snap to it unless
                // we've actually collided
                if (!prev_grounded && slope_y_coord > new_y)
                {
                    goto gotoYReposition;
                }
                // If we are moving up a slope, check for top collision
                UBYTE slope_top_tile_y = SUBPX_TO_TILE(slope_y_coord + sp_bounds_top);
                UBYTE tile_x_i = tile_x_start;
                while (tile_x_i != tile_x_end)
                {
                    if (tile_at(tile_x_i, slope_top_tile_y) & COLLISION_BOTTOM)
                    {
                        plat_vel_y = 0;
                        plat_vel_x = 0;
                        PLAYER.pos.x -= plat_delta_x;
                        plat_grounded = TRUE;
                        plat_next_state = GROUND_STATE;
                        plat_on_slope = col;
                        plat_slope_y = tile_hit_y;
                        goto gotoActorCol;
                    }
                    tile_x_i++;
                }

                PLAYER.pos.y = slope_y_coord;
                plat_vel_y = 0;
#ifdef FEAT_PLATFORM_DROP_THROUGH
                plat_drop_frames = 0;
#endif
                plat_grounded = TRUE;
                if (plat_state != DASH_STATE)
                {
                    plat_next_state = GROUND_STATE;
                }
                plat_on_slope = col;
                plat_slope_y = tile_hit_y;
                goto gotoActorCol;
            }
#endif

            UBYTE tile_x_i = tile_x_start;
            tile_ptr = tile_ptr_at(tile_x_i, new_tile_y);            

            // Check collisions from left to right with the bottom of the player
            while (tile_x_i != tile_x_end)
            {
                UBYTE tile = safe_read_tile_ptr(tile_ptr, tile_x_i, new_tile_y);

                if (tile & COLLISION_TOP)
                {
#ifdef FEAT_PLATFORM_DROP_THROUGH
                    // Only drop through platforms without a bottom collision
                    if (plat_drop_frames && !(tile & COLLISION_BOTTOM))
                    {
                        tile_x_i++;
                        tile_ptr++;
                        continue;
                    }
#endif
                    new_y = TILE_TO_SUBPX(new_tile_y) - sp_bounds_bottom - 1;
                    plat_actor_attached = FALSE; // Detach when MP moves through a solid tile.
                    plat_vel_y = 0;
#ifdef FEAT_PLATFORM_DROP_THROUGH
                    plat_drop_frames = 0;
#endif
                    plat_grounded = TRUE;
                    if (plat_state != DASH_STATE)
                    {
                        plat_next_state = GROUND_STATE;
                    }
                    break;
                }
                tile_x_i++;
                tile_ptr++;
            }
        gotoYReposition:
            PLAYER.pos.y = new_y;
        }
        else if (plat_delta_y < 0)
        {
            // Moving Upward
            UBYTE tile_x_i = tile_x_start;
            UBYTE tile_y = SUBPX_TO_TILE(new_y + sp_bounds_top);
            while (tile_x_i != tile_x_end)
            {
                if (tile_at(tile_x_i, tile_y) & COLLISION_BOTTOM)
                {
                    // Hit the ceiling
                    new_y = PX_TO_SUBPX((UBYTE)TILE_TO_PX(tile_y + 1) - PLAYER.bounds.top) + 1;
                    plat_vel_y = 0;
                    // MP Test: Attempting stuff to stop the player from continuing
                    // upward
                    if (plat_actor_attached)
                    {
                        plat_temp_y = plat_last_actor->pos.y;
                        if (plat_last_actor->bounds.top > 0)
                        {
                            plat_temp_y += plat_last_actor->bounds.top + plat_last_actor->bounds.bottom << 5;
                        }
                        new_y = plat_temp_y;
                    }
#ifdef FEAT_PLATFORM_COYOTE_TIME
                    plat_ct_val = 0;
#endif
                    plat_next_state = FALL_STATE;
                    break;
                }
                tile_x_i++;
            }
            PLAYER.pos.y = new_y;
        }
    }

gotoActorCol:
    plat_delta_x = 0;
    plat_delta_y = 0;

    if (mask & COL_CHECK_ACTORS)
    {
        actor_t *hit_actor;
        hit_actor = actor_overlapping_player(FALSE);
        if (hit_actor != NULL && hit_actor->collision_group)
        {
            const UBYTE is_platform =
                hit_actor->collision_group & (COLLISION_GROUP_FLAG_PLATFORM | COLLISION_GROUP_FLAG_SOLID);
            const UBYTE is_solid = is_platform & COLLISION_GROUP_FLAG_SOLID;

            if (is_platform && (!plat_actor_attached || hit_actor != plat_last_actor))
            {
                if (!is_solid && (plat_drop_frames != 0))
                {
                    plat_actor_attached = FALSE;
                    plat_next_state = FALL_STATE;
                }
                else if ((plat_temp_y + PX_TO_SUBPX(PLAYER.bounds.bottom - 7)) <
                             (hit_actor->pos.y + PX_TO_SUBPX(hit_actor->bounds.top)) &&
                         (plat_vel_y >= 0))
                {
                    // Attach to actor (solid or platform)
                    plat_last_actor = hit_actor;
                    plat_mp_last_x = hit_actor->pos.x;
                    plat_mp_last_y = hit_actor->pos.y;
                    PLAYER.pos.y =
                        hit_actor->pos.y + PX_TO_SUBPX(hit_actor->bounds.top) - PX_TO_SUBPX(PLAYER.bounds.bottom) - 4;
                    plat_vel_y = 0;
                    plat_actor_attached = TRUE;
                    if (plat_state != DASH_STATE)
                    {
                        plat_next_state = GROUND_STATE;
                    }
                }
                else if (is_solid)
                {
                    // Solid-only behavior (side/bottom collision)
                    if (plat_temp_y + PX_TO_SUBPX(PLAYER.bounds.top) >
                        hit_actor->pos.y + PX_TO_SUBPX(hit_actor->bounds.bottom))
                    {
                        plat_delta_y += (hit_actor->pos.y - PLAYER.pos.y) +
                                        PX_TO_SUBPX(-PLAYER.bounds.top + hit_actor->bounds.bottom) + 32;
                        plat_vel_y = plat_grav;

                        if (plat_next_state == JUMP_STATE || plat_actor_attached)
                        {
                            plat_next_state = FALL_STATE;
                        }
                    }
                    else if (PLAYER.pos.x != hit_actor->pos.x)
                    {
                        const UBYTE moving_right = PLAYER.pos.x < hit_actor->pos.x;

                        plat_delta_x = (hit_actor->pos.x - PLAYER.pos.x) +
                                       (moving_right ? -PX_TO_SUBPX(PLAYER.bounds.right + -hit_actor->bounds.left)
                                                     : PX_TO_SUBPX(-PLAYER.bounds.left + hit_actor->bounds.right) + 16);

                        plat_col = moving_right ? WALL_COL_RIGHT : WALL_COL_LEFT;
                        plat_last_wall = plat_col;
                        plat_wc_val = plat_coyote_max + 1;

                        if ((moving_right && !INPUT_RIGHT) || (!moving_right && !INPUT_LEFT))
                        {
                            plat_vel_x = 0;
                        }

#ifdef FEAT_PLATFORM_DASH
                        if (plat_next_state == DASH_STATE)
                        {
                            plat_next_state = FALL_STATE;
                        }
#endif
                    }
                }
            }

            // All Other Collisions
            player_register_collision_with(hit_actor);
        }
        else if (INPUT_PRESSED(INPUT_PLATFORM_INTERACT))
        {
            if (!hit_actor)
            {
                hit_actor = actor_in_front_of_player(8, TRUE);
            }
            if (hit_actor && !hit_actor->collision_group && hit_actor->script.bank)
            {
                script_execute(hit_actor->script.bank, hit_actor->script.ptr, 0, 1, 0);
            }
        }
    }

    if (IS_FRAME_EVEN && mask & COL_CHECK_TRIGGERS)
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
    plat_events[*slot].script_bank = NULL;
    plat_events[*slot].script_addr = NULL;
}

void plat_callback_execute(UBYTE i) BANKED
{
    script_event_t *event = &plat_events[i];
    if (!event->script_addr)
        return;
    if ((event->handle == 0) || ((event->handle & SCRIPT_TERMINATED) != 0))
    {
        script_execute(event->script_bank, event->script_addr, &event->handle, 0, 0);
    }
}
