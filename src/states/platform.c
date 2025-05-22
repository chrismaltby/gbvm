/*
Future notes on things to do:
- Limit air dashes before touching the ground
- Add an option for wall jump that only allows alternating walls.
- Currently, dashing through walls checks the potential end point, and if it
isn't clear then it continues with the normal dash routine. The result is that
there could be a valid landing point across a wall, but the player is just a
little too close for it to register. I could create a 'look-back' loop that runs
through the intervening tiles until it finds an empty landing spot.
- The bounce event is a funny one, because it can have the player going up
without being in the jump state. I should perhaps add some error catching stuff
for such situations
- Can I have a wall_jump init ahead of the normal jump init? If it's just
checking a few more boxes....
- Improve ladder situation: jump from ladder option, bug with hitting the bottom
of ladders, other stuff?

- Add check for camera bounds on Dash Init
- Solid actors have a fault: they only check collisions once on enter. This is
especially problematic because of how GBStudio does invincibility frames,
because it means the player can attach to a platform without causing the hit
trigger to run.
     - 2 potential solutions:
     - give the player a minimum velocity every frame, forcing a re-collision.
This might break the moving platform code though
     - manually re-trigger the collision call if the actor is attached.




TARGETS for Optimization
- State script assignment could be 100% be re-written to avoid all those
assignments and directly use the pointers. I am not canny enough to do that.
- I should be able to combine solid actors and platform actors into a single
check...
- It's inellegant that the dash check requires me to check again later if it
succeeded or not. Can I reorganize this somehow?
- I think I can probably combine actor_attached and last_actor
- I need to refactor the downwards collision for Y, it's a bit of a mess at this
point. I just can't wrap my head around it atm
- Wall Slide could be optimized to skill the acceleration bit, as the only thing
that matters is tapping away

THINGS TO WATCH
- Does every state (that needs to) end up resetting DeltaX?

NOTES on GBStudio Quirks
- 256 velocities per position, 16 'positions' per pixel, 8 pixels per tile
- Player bounds: for an ordinary 16x16 sprite, bounds.left starts at 0 and
bounds.right starts at 16. If it's smaller, bounds.left is POSITIVE For
bounds.top, however, Y starts counting from the middle of a sprite. bounds.top
is negative and bounds.bottom is positive
- CameraX is in the middle of the screen, not left corner

GENERAL STRUCTURE OF THIS FILE
The old format was well structured as a state-machine, isolating all the
components into states. Unfortunately, it seems like the overhead of calling
collision functions on the GameBoy makes this model unperformant. However, I'm
also limited to the total amount of code that can be placed in a single bank. I
cannot get rid of the functions and move the code into the file itself. New
structure is a compromise that uses goto commands to skip some sections that are
shared by most of the states.

INIT()
    Tweak a few fields so they don't overflow variables
    Normalize some fields so that they are applied over multiple frames
    Initialize variables
UPDATE()
    A. Input Checks (Double-tap Dash, Drop-Through)    I'm considering moving
the drop-through check into a state B. STATE MACHINE 1 SWITCH: Falling, Ground,
Jumping, Dashing, Climbing a Ladder, Wall Sliding State Initialization Calculate
Change in Vertical Movement Some calculate horziontal movement Some calculate
collisions C. Shared Collision Acceleration Code Basic X Collision gotoXCol
        Basic Y Collision           gotoYCol
        Actor Collision Check       gotoActorCol
    D. STATE MACHINE 2 SWITCH:      gotoSwitch2
        Animation
        State Change Logic
        Some Counters
    E. Trigger Check                gotoTriggerCol
    G. Tic Counters                 gotoCounters


BUGS:
 - When the player is on a moving platform and is hit by another one, they get
caught mid-way on the next one.
*/
#pragma bank 3

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

#define DROP_FRAMES_MAX 15

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

#define IS_ON_SLOPE(t) ((t) & 0x60)
#define IS_SLOPE_LEFT(t) ((t) & 0x10)
#define IS_SLOPE_RIGHT(t) (((t) & 0x10) == 0)
#define IS_LADDER(t) (((t) & 0xF0) == 0x10)
#define VEL_TO_SUBPX(v) ((v) >> 8)
#define IS_FLOAT_INPUT_PRESSED                                                                                         \
    ((plat_float_input == FLOAT_INPUT_HOLD_JUMP && INPUT_PLATFORM_JUMP) ||                                             \
     (plat_float_input == FLOAT_INPUT_HOLD_UP && INPUT_UP))

// DEFAULT ENGINE VARIABLES
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

// PLATFORMER PLUS ENGINE VARIABLES
// All engine fields are prefixed with plat_

BYTE plat_camera_deadzone_x; // Camera deadzone
UBYTE plat_camera_block;     // Limit the player's movement to the camera's edges
UBYTE plat_drop_through;     // Drop-through control
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
UBYTE plat_dash_style;       // Ground, air, or both
UBYTE plat_dash_use_grav;    // Applies gravity during a dash
UBYTE plat_dash_mask;        // Choose if the player can dash through actors,
                             // triggers, and walls
WORD plat_dash_dist;         // Distance of the dash
UBYTE plat_dash_frames;      // Number of frames for dashing
UBYTE plat_dash_ready_max;   // Time before the player can dash again
UBYTE plat_dash_deadzone;

enum pStates
{ // Datatype for tracking states
    FALL_STATE = 0,
    GROUND_STATE,
    JUMP_STATE,
    DASH_STATE,
    LADDER_STATE,
    WALL_STATE,
    KNOCKBACK_STATE,
    BLANK_STATE
};
enum cStates
{ // Datatype for state callbacks
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
    BLANK_END
};

enum pStates plat_state; // Current platformer state
enum pStates que_state;
UBYTE nocontrol_h; // Turns off horizontal input, currently only for wall jumping
UBYTE drop_frames; // The number of frames remaining to drop through platforms
WORD delta_x;
WORD delta_y;

// COUNTER variables
UBYTE ct_val;        // Coyote Time Variable
UBYTE jb_val;        // Jump Buffer Variable
UBYTE wc_val;        // Wall Coyote Time Variable
UBYTE hold_jump_val; // Jump input hold variable
UBYTE dj_val;        // Current double jump
UBYTE wj_val;        // Current wall jump

// WALL variables
BYTE last_wall; // tracks the last wall the player touched
BYTE col;

// DASH VARIABLES
UBYTE dash_ready_val;    // tracks the current amount before the dash is ready
WORD dash_dist;          // Takes overall dash distance and holds the amount per-frame
UBYTE dash_currentframe; // Tracks the current frame of the overall dash
BYTE tap_val;            // Number of frames since the last time left or right button was
                         // tapped
UBYTE dash_end_clear;    // Used to store the result of whether the end-position
                         // of a dash is empty

// COLLISION VARS
actor_t *last_actor;  // The last actor the player hit, and that they were
                      // attached to
UBYTE actor_attached; // Keeps track of whether the player is currently on an
                      // actor and inheriting its movement
WORD mp_last_x;       // Keeps track of the pos.x of the attached actor from the
                      // previous frame
WORD mp_last_y;       // Keeps track of the pos.y of the attached actor from the
                      // previous frame

// JUMPING VARIABLES
WORD jump_reduction_val; // Holds a temporary jump velocity reduction
WORD jump_per_frame;     // Holds a jump amount that has been normalized over the
                         // number of jump frames
WORD jump_reduction;     // Holds the reduction amount that has been normalized
                         // over the number of jump frames
WORD boost_val;

// WALKING AND RUNNING VARIABLES
WORD pl_vel_x; // Tracks the player's x-velocity between frames
WORD pl_vel_y; // Tracks the player's y-velocity between frames

// VARIABLES FOR CAMERAS
WORD *edge_left;
WORD *edge_right;
WORD mod_image_left;

// VARIABLES FOR EVENT PLUGINS
// UBYTE grounded;             //Variable to keep compatability with other
// plugins that use the older 'grounded' check
BYTE run_stage;  // Tracks the stage of running based on the run type
UBYTE jump_type; // Tracks the type of jumping, from the ground, in the air, or
                 // off the wall

// SLOPE VARIABLES
UBYTE grounded; // Needed? Add for compatability?
UBYTE on_slope;
UBYTE slope_y;

WORD temp_y = 0;

static void basic_anim(void) BANKED;
static void wall_check(void) BANKED;
static void ladder_check(void) BANKED;
static void dash_init_switch(void) BANKED;
static UBYTE drop_press(void) BANKED;
static void handle_horizontal_input(void) BANKED;
static void move_and_collide(UBYTE mask) BANKED;

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
    mod_image_left = 0;

    if (plat_camera_block & CAMERA_LOCK_SCREEN_LEFT)
    {
        edge_left = &scroll_x;
    }
    else
    {
        edge_left = &mod_image_left;
    }
    if (plat_camera_block & CAMERA_LOCK_SCREEN_RIGHT)
    {
        edge_right = &scroll_x;
    }
    else
    {
        edge_right = &image_width;
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
    jump_per_frame = plat_jump_vel / MIN(15, plat_hold_jump_max); // jump force applied per
                                                                  // frame in the JUMP_STATE
    jump_reduction = plat_jump_reduction / plat_hold_jump_max;    // Amount to reduce subequent jumps
                                                                  // per frame in JUMP_STATE
#ifdef FEAT_PLATFORM_DASH
    dash_dist = plat_dash_dist / plat_dash_frames; // Dash distance per frame in the DASH_STATE
#endif

    boost_val = plat_run_boost / plat_hold_jump_max; // Vertical boost from horizontal
                                                     // speed per frame in JUMP STATE

    // Initialize State
    plat_state = GROUND_STATE;
    que_state = GROUND_STATE;
    actor_attached = FALSE;
    run_stage = RUN_STAGE_NONE;
    nocontrol_h = 0;

#ifdef FEAT_PLATFORM_DROP_THROUGH
    drop_frames = 0;
#endif
    if (PLAYER.dir == DIR_UP || PLAYER.dir == DIR_DOWN || PLAYER.dir == DIR_NONE)
    {
        PLAYER.dir = DIR_RIGHT;
    }

    // Initialize other vars
    game_time = 0;
    pl_vel_x = 0;
    pl_vel_y = 4000;           // Magic number for preventing a small glitch when loading
                               // into a scene
    last_wall = WALL_COL_NONE; // This could be 1 bit
    hold_jump_val = plat_hold_jump_max;
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
    dj_val = 0;
#endif
    wj_val = plat_wall_jump_max;
    dash_end_clear = FALSE; // could also be mixed into the collision bitmask
    jump_type = JUMP_TYPE_NONE;
    delta_x = 0;
    delta_y = 0;
}

void platform_update(void) BANKED
{
    // State transitions

    if (plat_state != que_state)
    {
        // Exit state

        switch (plat_state)
        {
        case FALL_STATE: {
            state_events_execute(FALL_END);
            break;
        }
        case JUMP_STATE: {
            state_events_execute(JUMP_END);
            break;
        }
        case GROUND_STATE: {
            state_events_execute(GROUND_END);
            break;
        }
#ifdef FEAT_PLATFORM_LADDERS
        case LADDER_STATE: {
            state_events_execute(LADDER_END);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_DASH
        case DASH_STATE: {
            state_events_execute(DASH_END);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
        case WALL_STATE: {
            state_events_execute(WALL_END);
            break;
        }
#endif
        }

        plat_state = que_state;

        // Enter state

        switch (plat_state)
        {
        case FALL_STATE: {
            actor_attached = FALSE;
            state_events_execute(FALL_INIT);
            break;
        }
        case JUMP_STATE: {
            // Right now this has a limited use for triggered jumps because
            // many of the jump effects depend on testing
            // INPUT_PLATFORM_JUMP But if the player switches to this state
            // without pressing jump, then these won't fire...
            hold_jump_val = plat_hold_jump_max;
            actor_attached = FALSE;
            pl_vel_y = MIN(-plat_jump_min, pl_vel_y);
            jb_val = 0;
#ifdef FEAT_PLATFORM_COYOTE_TIME
            ct_val = 0;
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
            wc_val = 0;
#endif
            state_events_execute(JUMP_INIT);
            break;
        }
        case GROUND_STATE: {
            pl_vel_y = 0;
            jump_type = JUMP_TYPE_NONE;
#ifdef FEAT_PLATFORM_WALL_JUMP
            wc_val = 0;
#endif
#ifdef FEAT_PLATFORM_COYOTE_TIME
            ct_val = plat_coyote_max;
#endif
#ifdef FEAT_PLATFORM_DROP_THROUGH
            drop_frames = 0;
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
            dj_val = plat_extra_jumps;
#endif
            wj_val = plat_wall_jump_max;
            jump_reduction_val = 0;
            state_events_execute(GROUND_INIT);
            break;
        }
#ifdef FEAT_PLATFORM_LADDERS
        case LADDER_STATE: {
            jump_type = JUMP_TYPE_NONE;
            state_events_execute(LADDER_INIT);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_DASH
        case DASH_STATE: {
#ifdef FEAT_PLATFORM_COYOTE_TIME
            ct_val = plat_coyote_max;
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
            dj_val = plat_extra_jumps;
#endif
            dash_init_switch();
            state_events_execute(DASH_INIT);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
        case WALL_STATE: {
            jump_type = JUMP_TYPE_NONE;
            run_stage = RUN_STAGE_NONE;
            state_events_execute(WALL_INIT);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_KNOCKBACK
        case KNOCKBACK_STATE: {
            run_stage = RUN_STAGE_NONE;
            jump_type = JUMP_TYPE_NONE;
            state_events_execute(KNOCKBACK_INIT);
            break;
        }
#endif
#ifdef FEAT_PLATFORM_BLANK
        case BLANK_STATE: {
            pl_vel_x = 0;
            pl_vel_y = 0;
            run_stage = RUN_STAGE_NONE;
            jump_type = JUMP_TYPE_NONE;
            state_events_execute(BLANK_INIT);
            break;
        }
#endif
        }
    }

    // INITIALIZE VARS

    col = WALL_COL_NONE; // tracks if there is a block left or right

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
            if (tap_val < 0)
            {
                dash_press = TRUE;
            }
            else
            {
                tap_val = -15;
            }
        }
        else if (INPUT_PRESSED(INPUT_RIGHT))
        {
            if (tap_val > 0)
            {
                dash_press = TRUE;
            }
            else
            {
                tap_val = 15;
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
        jump_type = JUMP_TYPE_NONE;

#ifdef FEAT_PLATFORM_DROP_THROUGH
        if (drop_press())
        {
            drop_frames = DROP_FRAMES_MAX;
            actor_attached = FALSE;
        }
#endif

        // Vertical Movement ----------------------------------------------

#ifdef FEAT_PLATFORM_FLOAT
        if (IS_FLOAT_INPUT_PRESSED && pl_vel_y >= 0 && !drop_frames)
        {
            jump_type = JUMP_TYPE_FLOATING;
            pl_vel_y = plat_float_grav;
        }
        else
#endif
            if (INPUT_PLATFORM_JUMP && pl_vel_y < 0)
        {
            // Gravity while holding jump
            pl_vel_y += plat_hold_grav;
            pl_vel_y = MIN(pl_vel_y, plat_max_fall_vel);
        }
        else
        {
            // Normal gravity
            pl_vel_y += plat_grav;
            pl_vel_y = MIN(pl_vel_y, plat_max_fall_vel);
        }

        // Collision ------------------------------------------------------
        // Vertical Collision Checks
        delta_y += VEL_TO_SUBPX(pl_vel_y);
        temp_y = PLAYER.pos.y;

        // Horizontal Movement --------------------------------------------
        if (nocontrol_h != 0 || plat_air_control == 0)
        {
            // No horizontal input
            delta_x += VEL_TO_SUBPX(pl_vel_x);
        }
        else
        {
            handle_horizontal_input();
        }

        move_and_collide(COL_CHECK_ALL);

        // ANIMATION ------------------------------------------------------
        basic_anim();

        // STATE CHANGE ---------------------------------------------------
        // Above: FALL -> GROUND in basic_y_col()

#ifdef FEAT_PLATFORM_WALL_JUMP
        // FALL -> WALL check
        wall_check();
#endif

#ifdef FEAT_PLATFORM_DASH
        // FALL -> DASH check
        if (dash_press && dash_ready_val == 0)
        {
            if (plat_dash_style != 0)
            {
                if (col == WALL_COL_NONE || (col == WALL_COL_RIGHT && !INPUT_RIGHT) ||
                    (col == WALL_COL_LEFT && !INPUT_LEFT))
                {
                    que_state = DASH_STATE;
                    break;
                }
            }
            else if (que_state == GROUND_STATE && plat_dash_style != 1)
            {
                que_state = DASH_STATE;
                break;
            }
        }
#endif

#ifdef FEAT_PLATFORM_JUMP
        // FALL -> JUMP check
        if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
        {
#ifdef FEAT_PLATFORM_WALL_JUMP
            // Wall Jump
            if (wc_val != 0 && wj_val != 0)
            {
                jump_type = JUMP_TYPE_WALL;
                wj_val -= 1;
                nocontrol_h = 5;
                pl_vel_x += (plat_wall_kick + plat_walk_vel) * -last_wall;
                que_state = JUMP_STATE;
                break;
            }
#endif
#ifdef FEAT_PLATFORM_COYOTE_TIME
            if (ct_val != 0)
            {
                // Coyote Time Jump
                jump_type = JUMP_TYPE_GROUND;
                que_state = JUMP_STATE;
                break;
            }
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
            if (dj_val != 0)
            {
                // Double Jump
                jump_type = JUMP_TYPE_DOUBLE;
                if (dj_val != 255)
                {
                    dj_val -= 1;
                }
                jump_reduction_val += jump_reduction;
                que_state = JUMP_STATE;
                break;
            }
#endif

            // Setting the Jump Buffer when jump is pressed while not on
            // the ground
            jb_val = plat_buffer_max;
        }
        // NEUTRAL -> LADDER check
#endif

#ifdef FEAT_PLATFORM_LADDERS
        ladder_check();
#endif

        // COUNTERS
        //  Counting down Jump Buffer Window
        //  Set in Fall and checked in Ground state
        if (jb_val != 0)
        {
            jb_val -= 1;
        }

        // Counting down No Control frames
        // Set in Wall and Fall states, checked in Fall and Jump states
        if (nocontrol_h != 0)
        {
            nocontrol_h -= 1;
        }

#ifdef FEAT_PLATFORM_COYOTE_TIME
        // Counting down Coyote Time Window
        // Set in ground and checked in fall state
        if (ct_val != 0)
        {
            ct_val -= 1;
        }
#endif
#ifdef FEAT_PLATFORM_WALL_JUMP
        // Counting down Wall Coyote Time
        //  Set in collisions and checked in fall state
        if (wc_val != 0 && col == WALL_COL_NONE)
        {
            wc_val -= 1;
        }
#endif

        break;
    }

    case GROUND_STATE: {
        // Add X & Y motion from moving platforms
        // Transform velocity into positional data, to keep the precision of
        // the platform's movement
        grounded = true;

#ifdef FEAT_PLATFORM_DROP_THROUGH
        if (drop_press())
        {
            drop_frames = DROP_FRAMES_MAX;
            actor_attached = FALSE;
        }
#endif

        if (actor_attached)
        {
            // If the platform has been disabled, detach the player
            if (last_actor->disabled == TRUE)
            {
                que_state = FALL_STATE;
                actor_attached = FALSE;
            }
            // If the player is off the platform to the right, detach
            // from the platform
            else if (PLAYER.pos.x + PX_TO_SUBPX(PLAYER.bounds.left) >
                     last_actor->pos.x + 16 + PX_TO_SUBPX(last_actor->bounds.right))
            {
                que_state = FALL_STATE;
                actor_attached = FALSE;
            }
            // If the player is off the platform to the left, detach
            else if (PLAYER.pos.x + 16 + PX_TO_SUBPX(PLAYER.bounds.right) <
                     last_actor->pos.x + PX_TO_SUBPX(last_actor->bounds.left))
            {
                que_state = FALL_STATE;
                actor_attached = FALSE;
            }
            // Otherwise, add any change in movement from platform
            else
            {
                delta_x += (last_actor->pos.x - mp_last_x);
                mp_last_x = last_actor->pos.x;
            }

            // If we're on a platform, zero out any other motion from
            // gravity or other sources
            pl_vel_y = 0;

            // Add any change from the platform we're standing on
            delta_y += last_actor->pos.y - mp_last_y;

            // We're setting these to the platform's position, rather than
            // the actor so that if something causes the player to detach
            // (like hitting the roof), they won't automatically get
            // re-attached in the subsequent actor collision step.
            mp_last_y = last_actor->pos.y;
            temp_y = last_actor->pos.y;
        }
        else
        {

            // Normal gravity
            pl_vel_y += plat_grav;
            temp_y = PLAYER.pos.y;
            // queue falling state which will be set back to ground
            // if collision is detected in move_and_collide
            que_state = FALL_STATE;
        }

        // Add Collision Offset from Moving Platforms
        delta_y += VEL_TO_SUBPX(pl_vel_y);

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
        else if (pl_vel_x < 0)
        {
            actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
        }
        else if (pl_vel_x > 0)
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
        if (dash_press && plat_dash_style != 1 && dash_ready_val == 0)
        {
            que_state = DASH_STATE;
            break;
        }
#endif

#ifdef FEAT_PLATFORM_JUMP
        // GROUND -> JUMP Check
        if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || jb_val != 0) && !drop_frames)
        {
            // Standard Jump
            jump_type = JUMP_TYPE_GROUND;
            que_state = JUMP_STATE;
            break;
        }
        jb_val = 0;
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
        if (hold_jump_val != 0 && INPUT_PLATFORM_JUMP)
        {
            // Add the boost per frame amount.
            pl_vel_y -= jump_per_frame;
            // Reduce subsequent jump amounts (for double jumps)
            if (plat_jump_vel >= jump_reduction_val)
            {
                pl_vel_y += jump_reduction_val;
            }
            else
            {
                // When reducing that value, zero out if it's negative
                pl_vel_y = 0;
            }
            // Add jump boost from horizontal movement
            WORD tempBoost = VEL_TO_SUBPX(pl_vel_x) * boost_val;
            // Take the positive value of x-vel
            tempBoost = MAX(tempBoost, -tempBoost);
            // This is a test to see if the results will overflow pl_vel_y.
            // Note, pl_vel_y is negative here.
            if (tempBoost > 32767 + pl_vel_y)
            {
                pl_vel_y = -32767;
            }
            else
            {
                pl_vel_y += -tempBoost;
            }
            hold_jump_val -= 1;
        }
        else if (INPUT_PLATFORM_JUMP && pl_vel_y < 0)
        {
            // After the jump frames end, use the reduced gravity
            pl_vel_y += plat_hold_grav;
        }
        else if (pl_vel_y >= 0)
        {
            que_state = FALL_STATE;
            pl_vel_y += plat_grav;
        }
        else
        {
            pl_vel_y += plat_grav;
        }

        temp_y = PLAYER.pos.y;
        // Start DeltaX with Actor offsets
        delta_y += VEL_TO_SUBPX(pl_vel_y);

        // Horizontal Movement --------------------------------------------
        if (nocontrol_h != 0 || plat_air_control == 0)
        {
            // If the player doesn't have control of their horizontal
            // movement, skip acceleration phase
            delta_x += VEL_TO_SUBPX(pl_vel_x);
        }
        else
        {
            handle_horizontal_input();
        }

        move_and_collide(COL_CHECK_ALL);

        // ANIMATION ------------------------------------------------------
        basic_anim();

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
        if (dash_press && dash_ready_val == 0)
        {
#ifdef FEAT_PLATFORM_COYOTE_TIME
            if (plat_dash_style != 0 || ct_val != 0)
#else
            if (plat_dash_style != 0)
#endif
            {
                que_state = DASH_STATE;
                break;
            }
        }
#endif

        // JUMP -> JUMP check
        if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
        {
#ifdef FEAT_PLATFORM_WALL_JUMP
            // Wall Jump
            if (wc_val != 0 && wj_val != 0)
            {
                jump_type = JUMP_TYPE_WALL;
                wj_val -= 1;
                nocontrol_h = 5;
                pl_vel_x = (plat_wall_kick + plat_walk_vel) * -last_wall;
                que_state = JUMP_STATE;
            }
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
            else
#endif
#endif
#ifdef FEAT_PLATFORM_DOUBLE_JUMP
                if (dj_val != 0)
            {
                // Double Jump
                jump_type = JUMP_TYPE_DOUBLE;
                if (dj_val != 255)
                {
                    dj_val -= 1;
                }
                jump_reduction_val += jump_reduction;
                que_state = JUMP_STATE;
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
        if (nocontrol_h != 0)
        {
            nocontrol_h -= 1;
        }

        break;
    }
#endif

#ifdef FEAT_PLATFORM_DASH
    case DASH_STATE: {

        if (!dash_end_clear)
        {
            que_state = FALL_STATE;
            break;
        }

        BYTE dir = (PLAYER.dir == DIR_LEFT ? -1 : 1);
        WORD remaining_dash_dist = dash_dist;

        pl_vel_x = plat_run_vel * dir;
        delta_y = plat_dash_use_grav ? VEL_TO_SUBPX(plat_grav) : -1;

        while (remaining_dash_dist)
        {
            WORD dist = MIN(remaining_dash_dist, 127);
            delta_x = dist * dir;
            move_and_collide(plat_dash_mask);
            remaining_dash_dist -= dist;
        }
        basic_anim();

        dash_currentframe -= 1;
        if (dash_currentframe == 0)
        {
            que_state = FALL_STATE;
        }

#ifdef FEAT_PLATFORM_JUMP
        // DASH -> JUMP Check
        if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || jb_val != 0) && (grounded || dj_val != 0 || ct_val != 0) &&
            !drop_frames)
        {
            // Standard Jump
            jump_type = JUMP_TYPE_GROUND;
            que_state = JUMP_STATE;
            break;
        }
        jb_val = 0;
#endif
        break;
    }
#endif

#ifdef FEAT_PLATFORM_LADDERS
    case LADDER_STATE: {
        // For positioning the player in the middle of the ladder
        UBYTE p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
        UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.x) + PLAYER.bounds.left + p_half_width);
        pl_vel_y = 0;
        if (INPUT_UP)
        {
            // Climb laddder
            UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top + 1);
            // Check if the tile above the player is a ladder tile. If so add ladder
            // velocity
            if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
            {
                pl_vel_y = -plat_climb_vel;
            }
        }
        else if (INPUT_DOWN)
        {
            // Descend ladder
            UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom + 1);
            if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
            {
                pl_vel_y = plat_climb_vel;
            }
        }
        else if (INPUT_LEFT)
        {
            que_state = FALL_STATE; // Assume we're going to leave the ladder state,
            // Check if able to leave ladder on left
            UBYTE tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top);
            UBYTE tile_end = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;
            while (tile_start != tile_end)
            {
                if (tile_at(tile_x_mid - 1, tile_start) & COLLISION_RIGHT)
                {
                    que_state = LADDER_STATE; // If there is a wall, stay on the ladder.
                    break;
                }
                tile_start++;
            }
        }
        else if (INPUT_RIGHT)
        {
            que_state = FALL_STATE;
            // Check if able to leave ladder on right
            UBYTE tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top);
            UBYTE tile_end = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;
            while (tile_start != tile_end)
            {
                if (tile_at(tile_x_mid + 1, tile_start) & COLLISION_LEFT)
                {
                    que_state = LADDER_STATE;
                    break;
                }
                tile_start++;
            }
        }
        PLAYER.pos.y += VEL_TO_SUBPX(pl_vel_y);

        // Animation---------------------------------------------------------------
        actor_set_anim(&PLAYER, ANIM_CLIMB);
        if (pl_vel_y == 0)
        {
            actor_stop_anim(&PLAYER);
        }

        // State Change------------------------------------------------------------
        // Collision logic provides options for exiting to Neutral

        // Above is the default GBStudio setup. However it seems worth adding a
        // jump-from-ladder option, at the very least to drop down.
        if (INPUT_PRESSED(INPUT_PLATFORM_JUMP))
        {
            que_state = FALL_STATE;
        }

        move_and_collide(COL_CHECK_ACTORS | COL_CHECK_TRIGGERS);

        break;
    }
#endif

#ifdef FEAT_PLATFORM_WALL_JUMP
    case WALL_STATE: {
        // Vertical Movement ----------------------------------------------
        // WALL SLIDE
        if (pl_vel_y < 0)
        {
            // If the player is still ascending, don't apply wall-gravity
            pl_vel_y += plat_grav;
        }
        else if (plat_wall_slide)
        {
            // If the toggle is on, use wall gravity
            pl_vel_y = plat_wall_grav;
        }
        else
        {
            // Otherwise use regular gravity
            pl_vel_y += plat_grav;
        }

        // Collision ------------------------------------------------------
        // Vertical Collision Checks
        delta_y += VEL_TO_SUBPX(pl_vel_y);
        temp_y = PLAYER.pos.y;

        handle_horizontal_input();
        move_and_collide(COL_CHECK_ALL);

        // ANIMATION ------------------------------------------------------
        // Face away from walls
        if (col == WALL_COL_RIGHT)
        {
            actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
        }
        else if (col == WALL_COL_LEFT)
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
        if (dash_press && plat_dash_style != 0 && dash_ready_val == 0)
        {
            if ((col == WALL_COL_RIGHT && !INPUT_RIGHT) || (col == WALL_COL_LEFT && !INPUT_LEFT))
            {
                que_state = DASH_STATE;
                break;
            }
        }
#endif

#ifdef FEAT_PLATFORM_JUMP
        // WALL -> JUMP Check
        if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || jb_val != 0) && wj_val != 0)
        {
            // Wall Jump
            wj_val -= 1;
            nocontrol_h = 5;
            pl_vel_x = (plat_wall_kick + plat_walk_vel) * -last_wall;
            jump_type = JUMP_TYPE_WALL;
            que_state = JUMP_STATE;
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
        if (pl_vel_x < 0)
        {
            pl_vel_x += plat_air_dec;
            pl_vel_x = MIN(pl_vel_x, 0);
        }
        else if (pl_vel_x > 0)
        {
            pl_vel_x -= plat_air_dec;
            pl_vel_x = MAX(pl_vel_x, 0);
        }
        delta_x += VEL_TO_SUBPX(pl_vel_x);

        // Vertical Movement ----------------------------------------------
        // Normal gravity
        pl_vel_y += plat_grav;
        pl_vel_y = MIN(pl_vel_y, plat_max_fall_vel);

        // Collision ------------------------------------------------------

        // Vertical Collision Checks
        delta_y += VEL_TO_SUBPX(pl_vel_y);
        temp_y = PLAYER.pos.y;

#ifdef FEAT_PLATFORM_DROP_THROUGH
        drop_frames = 0;
#endif
        move_and_collide(COL_CHECK_ALL);

        pl_vel_y = 0;
        que_state = KNOCKBACK_STATE;

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
    if (dash_ready_val != 0)
    {
        dash_ready_val -= 1;
    }
#endif

    // Counting down from the max double-tap time (left is -15, right is +15)
    if (tap_val > 0)
    {
        tap_val -= 1;
    }
    else if (tap_val < 0)
    {
        tap_val += 1;
    }

    // Hone Camera after the player has dashed
    if (camera_deadzone_x > plat_camera_deadzone_x)
    {
        camera_deadzone_x -= 1;
    }
}

static void basic_anim(void) BANKED
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
        else if (pl_vel_x < 0)
        {
            PLAYER.dir = DIR_LEFT;
        }
        else if (pl_vel_x > 0)
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
static void wall_check(void) BANKED
{
    if (col != 0 && plat_wall_slide)
    {
        que_state = WALL_STATE;
    }
    else if (que_state == WALL_STATE)
    {
        que_state = FALL_STATE;
    }
}
#endif

#ifdef FEAT_PLATFORM_LADDERS
static void ladder_check(void) BANKED
{
    UBYTE p_half_width = DIV_2(PLAYER.bounds.right - PLAYER.bounds.left);
    if (INPUT_UP || INPUT_DOWN)
    {
        // Grab upwards ladder
        UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.x) + PLAYER.bounds.left + p_half_width);
        UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top + 1);
        if (IS_LADDER(tile_at(tile_x_mid, tile_y)))
        {
            PLAYER.pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x_mid) + 4 - (PLAYER.bounds.left + p_half_width));
            que_state = LADDER_STATE;
            pl_vel_x = 0;
        }
    }
}
#endif

#ifdef FEAT_PLATFORM_DASH
static void dash_init_switch(void) BANKED
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

    // Set new_x be the final destination of the dash (ie. the distance covered
    // by all of the dash frames combined)
    if (PLAYER.dir == DIR_RIGHT)
    {
        new_x = PLAYER.pos.x + (dash_dist * plat_dash_frames);
    }
    else
    {
        new_x = PLAYER.pos.x + (-dash_dist * plat_dash_frames);
    }

    dash_end_clear = true; // Assume that the landing spot is clear, and
                           // disable if we collide below

    // Dash through walls
    if ((plat_dash_mask & COL_CHECK_WALLS) == 0)
    {
        if (plat_dash_use_grav)
        {
            dash_end_clear = false;
        }

        UBYTE tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.top);
        UBYTE tile_end = PX_TO_TILE(SUBPX_TO_PX(PLAYER.pos.y) + PLAYER.bounds.bottom) + 1;

        // Do a collision check at the final landing spot (but not all the steps
        // in-between.)
        if (PLAYER.dir == DIR_RIGHT)
        {
            // Don't dash off the screen to the right
            if (PLAYER.pos.x + PX_TO_SUBPX(PLAYER.bounds.right) + (dash_dist * (plat_dash_frames)) >
                PX_TO_SUBPX(image_width - 16))
            {
                dash_end_clear = false;
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
                            dash_end_clear = false;
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
            if (PLAYER.pos.x <= ((dash_dist * plat_dash_frames) + PX_TO_SUBPX(PLAYER.bounds.left)) + PX_TO_SUBPX(8))
            {
                dash_end_clear = false; // To get around unsigned position, test if the
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
                            dash_end_clear = false;
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
    actor_attached = FALSE;
    camera_deadzone_x = plat_dash_deadzone;
    dash_ready_val = plat_dash_ready_max + plat_dash_frames;
    if (!plat_dash_use_grav)
    {
        pl_vel_y = 0;
    }
    dash_currentframe = plat_dash_frames;
    tap_val = 0;
    jump_type = JUMP_TYPE_NONE;
    run_stage = RUN_STAGE_NONE;
    que_state = DASH_STATE;

    plat_dash_mask |= COL_CHECK_X | COL_CHECK_Y;
}
#endif

#ifdef FEAT_PLATFORM_DROP_THROUGH
static UBYTE drop_press(void) BANKED
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

static void handle_horizontal_input(void) BANKED
{
    if (INPUT_LEFT || INPUT_RIGHT)
    {
        BYTE dir;
        WORD input_aligned_vel_x;

        if (INPUT_LEFT)
        {
            dir = -1;
            input_aligned_vel_x = pl_vel_x * -1;
        }
        else
        {
            dir = 1;
            input_aligned_vel_x = pl_vel_x;
        }

        // Currently moving opposite direction to input, add turning friction
        if (input_aligned_vel_x < 0)
        {
            input_aligned_vel_x = MIN(input_aligned_vel_x + plat_turn_acc, 0);
#ifdef FEAT_PLATFORM_RUN
            run_stage = RUN_STAGE_TURNING;
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
                run_stage = RUN_STAGE_RUN_MAX;
            }
            else
            {
                // Walking
                input_aligned_vel_x = CLAMP(input_aligned_vel_x + accel, plat_min_vel, max_vel);
                run_stage = RUN_STAGE_NONE;
            }
#elif defined(FEAT_PLATFORM_RUN) && PLATFORM_RUN_STYLE == RUN_STYLE_SMOOTH
            if (running)
            {
                // Accelerate to walk speed
                if (input_aligned_vel_x < plat_walk_vel)
                {
                    input_aligned_vel_x = MAX(input_aligned_vel_x + plat_walk_acc, plat_min_vel);
                    run_stage = RUN_STAGE_WALK_ACC;
                }
                // Accelerate to run speed
                else if (input_aligned_vel_x < max_vel)
                {
                    input_aligned_vel_x = MIN(input_aligned_vel_x + plat_run_acc, max_vel);
                    run_stage = RUN_STAGE_RUN_ACC;
                }
                // At max speed
                else
                {
                    input_aligned_vel_x = max_vel;
                    run_stage = RUN_STAGE_RUN_MAX;
                }
            }
            else
            {
                // Walking
                input_aligned_vel_x = CLAMP(input_aligned_vel_x + accel, plat_min_vel, max_vel);
                run_stage = RUN_STAGE_NONE;
            }
#else
            input_aligned_vel_x = CLAMP(input_aligned_vel_x + accel, plat_min_vel, max_vel);
#ifdef FEAT_PLATFORM_RUN
            run_stage = running ? RUN_STAGE_RUN_MAX : RUN_STAGE_NONE;
#endif

#endif
        }
        // Restore velocity to original sign
        pl_vel_x = dir == 1 ? input_aligned_vel_x : input_aligned_vel_x * -1;
        delta_x += VEL_TO_SUBPX(pl_vel_x);
    }
    else // No Horizontal Input
    {
    decelerate:
        // Deceleration
        if (pl_vel_x != 0)
        {
            // Set deceleration value based on state
            WORD dec = (plat_state == GROUND_STATE) ? plat_dec : plat_air_dec;

            if (pl_vel_x < 0)
            {
                // Decelerate while moving left
                pl_vel_x = MIN(pl_vel_x + dec, 0);
            }
            else
            {
                // Decelerate while moving right
                pl_vel_x = MAX(pl_vel_x - dec, 0);
            }
            delta_x += VEL_TO_SUBPX(pl_vel_x);
        }
        run_stage = RUN_STAGE_NONE;
    }
}

static void move_and_collide(UBYTE mask) BANKED
{
    const WORD sp_bounds_top = PX_TO_SUBPX(PLAYER.bounds.top);
    const WORD sp_bounds_bottom = PX_TO_SUBPX(PLAYER.bounds.bottom);
    const WORD sp_bounds_left = PX_TO_SUBPX(PLAYER.bounds.left);
    const WORD sp_bounds_right = PX_TO_SUBPX(PLAYER.bounds.right);
    WORD sp_half_width = DIV_2(sp_bounds_right - sp_bounds_left);

    UBYTE old_x = 0;
#ifdef FEAT_PLATFORM_SLOPES
    UBYTE prev_on_slope = 0;
#endif

#ifdef FEAT_PLATFORM_DROP_THROUGH
    if (drop_frames != 0)
    {
        drop_frames -= 1;
    }
#endif

    // Horizontal Movement
    if (mask & COL_CHECK_X)
    {
        delta_x = CLAMP(delta_x, -127, 127);
#ifdef FEAT_PLATFORM_SLOPES
        prev_on_slope = on_slope;
        on_slope = FALSE;
#endif
        old_x = PLAYER.pos.x;

        UBYTE tile_y_start = SUBPX_TO_TILE(PLAYER.pos.y + sp_bounds_top);
        UBYTE tile_y_end = SUBPX_TO_TILE(PLAYER.pos.y + sp_bounds_bottom) + 1;
        UWORD new_x = PLAYER.pos.x + delta_x;

        UBYTE tile_x = 0;

        // Edge Locking
        // If the player is past the right edge (camera or screen)
        if (new_x > PX_TO_SUBPX(*edge_right + SCREEN_WIDTH - 16))
        {
            // If the player is trying to go FURTHER right
            if (new_x > PLAYER.pos.x)
            {
                new_x = PLAYER.pos.x;
                pl_vel_x = 0;
            }
            else
            {
                // If the player is already off the screen, push them back
                new_x = PLAYER.pos.x - MIN(PLAYER.pos.x - PX_TO_SUBPX(*edge_right + SCREEN_WIDTH - 16), 16);
            }
            // Same but for left side. This side needs a 1 tile (8px) buffer so it
            // doesn't overflow the variable.
        }
        else if (new_x < PX_TO_SUBPX(*edge_left))
        {
            if (delta_x < 0)
            {
                new_x = PLAYER.pos.x;
                pl_vel_x = 0;
            }
            else
            {
                new_x = PLAYER.pos.x + MIN(PX_TO_SUBPX(*edge_left + 8) - PLAYER.pos.x, 16);
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
        UBYTE tile_y = tile_y_end - 1;

#ifdef FEAT_PLATFORM_SLOPES
        UBYTE tile_x_mid = SUBPX_TO_TILE(new_x + sp_bounds_left + sp_half_width + PX_TO_SUBPX(1));
        UBYTE col_mid = tile_at(tile_x_mid, tile_y);

        if (IS_ON_SLOPE(col_mid))
        {
            on_slope = col_mid;
            slope_y = tile_y;
        }
        UBYTE slope_on_y = FALSE;
#endif

        while (tile_y_start != tile_y_end)
        {
            // New Slope 4
            UBYTE tile = tile_at(tile_x, tile_y_start);

#ifdef FEAT_PLATFORM_SLOPES
            if (IS_ON_SLOPE(tile))
            {
                slope_on_y = TRUE;
            }
#endif

            if (tile & hit_flag)
            {
#ifdef FEAT_PLATFORM_SLOPES
                // Handle case when moving up a slope and top contains a solid collision
                //   e.g.
                //
                //    /EX
                //   /XXX
                //
                //  Tile `E` would block movement up slope without these checks
                if (slope_on_y || tile_y_start == slope_y)
                {
                    // Slope in in same direction as movement
                    if ((IS_ON_SLOPE(on_slope) && (IS_SLOPE_LEFT(on_slope) != moving_right)) ||
                        (IS_ON_SLOPE(prev_on_slope) && (IS_SLOPE_LEFT(prev_on_slope) != moving_right)))
                    {
                        if (tile_y_start <= slope_y)
                        {
                            tile_y_start++;
                            continue;
                        }
                    }
                }
                if (slope_on_y)
                {
                    // Slope is in opposite direction to movement
                    if ((IS_ON_SLOPE(on_slope) && (IS_SLOPE_LEFT(on_slope) == moving_right)) ||
                        (IS_ON_SLOPE(prev_on_slope) && (IS_SLOPE_LEFT(prev_on_slope) == moving_right)))
                    {
                        if (tile_y_start >= slope_y)
                        {
                            tile_y_start++;
                            continue;
                        }
                    }
                }
#endif
                if (moving_right)
                {
                    new_x = TILE_TO_SUBPX(tile_x) - bounds_edge - 1;
                }
                else
                {
                    new_x = TILE_TO_SUBPX(tile_x + 1) - bounds_edge + 1;
                }

                pl_vel_x = 0;
                col = wall;
                last_wall = wall;
#ifdef FEAT_PLATFORM_WALL_JUMP
                wc_val = plat_coyote_max + 1;
#endif
                break;
            }
            tile_y_start++;
        }
    gotoXReposition:
        PLAYER.pos.x = new_x;
    }

    // Vertical Movement
    if (mask & COL_CHECK_Y)
    {
        delta_y = CLAMP(delta_y, -127, 127);

        WORD new_y = PLAYER.pos.y + delta_y;
        if (!(mask & COL_CHECK_WALLS))
        {
            goto gotoYReposition;
        }
        UBYTE prev_grounded = grounded;
        UWORD old_y = PLAYER.pos.y;

#ifdef FEAT_PLATFORM_SLOPES
        // 1 frame leniency of grounded state if we were on a slope last frame
        grounded = prev_on_slope;
#else
        grounded = FALSE;
#endif

        UBYTE tile_x_start = SUBPX_TO_TILE(PLAYER.pos.x + sp_bounds_left);
        UBYTE tile_x_end = SUBPX_TO_TILE(PLAYER.pos.x + sp_bounds_right) + 1;

        if (delta_y >= 0)
        {
            // Moving Downward
            UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + sp_bounds_bottom) - 1;

#ifdef FEAT_PLATFORM_SLOPES
            // New Slope Y 2
            UBYTE new_tile_y = SUBPX_TO_TILE(new_y + sp_bounds_bottom);
            // If previously grounded and gravity is not enough to pull us down to
            // the next tile, manually check it for the next slope This prevents the
            // "animation glitch" when going down slopes
            if (prev_grounded && new_tile_y == (tile_y + 1))
                new_tile_y += 1;
            UWORD x_mid_coord = SUBPX_TO_PX(PLAYER.pos.x + sp_bounds_left + sp_half_width) + 1;

            while (tile_y <= new_tile_y)
            {
                UBYTE col = tile_at(PX_TO_TILE(x_mid_coord), tile_y);
                UWORD tile_x_coord = PX_SNAP_TILE(x_mid_coord);
                UWORD x_offset = x_mid_coord - tile_x_coord;

                UWORD slope_y_coord = 0;
                if (IS_ON_SLOPE(col))
                {
                    slope_y_coord = TILE_TO_SUBPX(tile_y);
                    // Slope right
                    if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_45_RIGHT)
                    {
                        slope_y_coord += PX_TO_SUBPX((8 - x_offset) - PLAYER.bounds.bottom) - 1;
                    }
                    else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_RIGHT_BOT)
                    {
                        slope_y_coord += PX_TO_SUBPX((8 - DIV_2(x_offset)) - PLAYER.bounds.bottom) - 1;
                    }
                    else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_RIGHT_TOP)
                    {
                        slope_y_coord += PX_TO_SUBPX((4 - DIV_2(x_offset)) - PLAYER.bounds.bottom) - 1;
                    }
                    // Slope left
                    else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_45_LEFT)
                    {
                        slope_y_coord += PX_TO_SUBPX((x_offset)-PLAYER.bounds.bottom) - 1;
                    }
                    else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_LEFT_BOT)
                    {
                        slope_y_coord += PX_TO_SUBPX(DIV_2(x_offset) - PLAYER.bounds.bottom + 4) - 1;
                    }
                    else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_LEFT_TOP)
                    {
                        slope_y_coord += PX_TO_SUBPX(DIV_2(x_offset) - PLAYER.bounds.bottom) - 1;
                    }

                    // If going downwards into a slope, don't snap to it unless
                    // we've actually collided
                    if (!prev_grounded && slope_y_coord > new_y)
                    {
                        tile_y++;
                        continue;
                    }
                    // If we are moving up a slope, check for top collision
                    UBYTE slope_top_tile_y = SUBPX_TO_TILE(slope_y_coord + sp_bounds_top);
                    UBYTE tile_x_i = tile_x_start;
                    while (tile_x_i != tile_x_end)
                    {
                        if (tile_at(tile_x_i, slope_top_tile_y) & COLLISION_BOTTOM)
                        {
                            pl_vel_y = 0;
                            pl_vel_x = 0;
                            PLAYER.pos.y = old_y;
                            PLAYER.pos.x = old_x;
                            grounded = TRUE;
                            on_slope = col;
                            slope_y = tile_y;
                            goto gotoActorCol;
                        }
                        tile_x_i++;
                    }

                    PLAYER.pos.y = slope_y_coord;
                    pl_vel_y = 0;
#ifdef FEAT_PLATFORM_DROP_THROUGH
                    drop_frames = 0;
#endif
                    grounded = TRUE;
                    if (plat_state != DASH_STATE)
                    {
                        que_state = GROUND_STATE;
                    }
                    on_slope = col;
                    slope_y = tile_y;
                    goto gotoActorCol;
                }
                tile_y++;
            }
            // End New Slope Y 2

#endif

            UBYTE tile_x_i = tile_x_start;
            tile_y = SUBPX_TO_TILE(new_y + sp_bounds_bottom);

            // Check collisions from left to right with the bottom of the player
            while (tile_x_i != tile_x_end)
            {
                UBYTE tile = tile_at(tile_x_i, tile_y);
                if (tile & COLLISION_TOP)
                {
#ifdef FEAT_PLATFORM_DROP_THROUGH
                    // Only drop through platforms without a bottom collision
                    if (drop_frames && !(tile & COLLISION_BOTTOM))
                    {
                        tile_x_i++;
                        continue;
                    }
#endif
                    new_y = PX_TO_SUBPX(TILE_TO_PX(tile_y) - PLAYER.bounds.bottom) - 1;
                    actor_attached = FALSE; // Detach when MP moves through a solid tile.
                    pl_vel_y = 0;
#ifdef FEAT_PLATFORM_DROP_THROUGH
                    drop_frames = 0;
#endif
                    grounded = TRUE;
                    if (plat_state != DASH_STATE)
                    {
                        que_state = GROUND_STATE;
                    }
                    break;
                }
                tile_x_i++;
            }
        gotoYReposition:
            PLAYER.pos.y = new_y;
        }
        else if (delta_y < 0)
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
                    pl_vel_y = 0;
                    // MP Test: Attempting stuff to stop the player from continuing
                    // upward
                    if (actor_attached)
                    {
                        temp_y = last_actor->pos.y;
                        if (last_actor->bounds.top > 0)
                        {
                            temp_y += last_actor->bounds.top + last_actor->bounds.bottom << 5;
                        }
                        new_y = temp_y;
                    }
#ifdef FEAT_PLATFORM_COYOTE_TIME
                    ct_val = 0;
#endif
                    que_state = FALL_STATE;
                    break;
                }
                tile_x_i++;
            }
            PLAYER.pos.y = new_y;
        }
    }

gotoActorCol:
    delta_x = 0;
    delta_y = 0;

    if (mask & COL_CHECK_ACTORS)
    {
        actor_t *hit_actor;
        hit_actor = actor_overlapping_player(FALSE);
        if (hit_actor != NULL && hit_actor->collision_group)
        {
            const UBYTE is_platform =
                hit_actor->collision_group & (COLLISION_GROUP_FLAG_PLATFORM | COLLISION_GROUP_FLAG_SOLID);
            const UBYTE is_solid = is_platform & COLLISION_GROUP_FLAG_SOLID;

            if (is_platform && (!actor_attached || hit_actor != last_actor))
            {
                if (!is_solid && (drop_frames != 0))
                {
                    actor_attached = FALSE;
                    last_actor = FALSE;
                    que_state = FALL_STATE;
                }
                else if ((temp_y + PX_TO_SUBPX(PLAYER.bounds.bottom - 7)) <
                             (hit_actor->pos.y + PX_TO_SUBPX(hit_actor->bounds.top)) &&
                         (pl_vel_y >= 0))
                {
                    // Attach to actor (solid or platform)
                    last_actor = hit_actor;
                    mp_last_x = hit_actor->pos.x;
                    mp_last_y = hit_actor->pos.y;
                    PLAYER.pos.y =
                        hit_actor->pos.y + PX_TO_SUBPX(hit_actor->bounds.top) - PX_TO_SUBPX(PLAYER.bounds.bottom) - 4;
                    pl_vel_y = 0;
                    actor_attached = TRUE;
                    if (plat_state != DASH_STATE)
                    {
                        que_state = GROUND_STATE;
                    }
                }
                else if (is_solid)
                {
                    // Solid-only behavior (side/bottom collision)
                    if (temp_y + PX_TO_SUBPX(PLAYER.bounds.top) >
                        hit_actor->pos.y + PX_TO_SUBPX(hit_actor->bounds.bottom))
                    {
                        delta_y += (hit_actor->pos.y - PLAYER.pos.y) +
                                   PX_TO_SUBPX(-PLAYER.bounds.top + hit_actor->bounds.bottom) + 32;
                        pl_vel_y = plat_grav;

                        if (que_state == JUMP_STATE || actor_attached)
                        {
                            que_state = FALL_STATE;
                        }
                    }
                    else if (PLAYER.pos.x != hit_actor->pos.x)
                    {
                        const UBYTE moving_right = PLAYER.pos.x < hit_actor->pos.x;

                        delta_x = (hit_actor->pos.x - PLAYER.pos.x) +
                                  (moving_right ? -PX_TO_SUBPX(PLAYER.bounds.right + -hit_actor->bounds.left)
                                                : PX_TO_SUBPX(-PLAYER.bounds.left + hit_actor->bounds.right) + 16);

                        col = moving_right ? WALL_COL_RIGHT : WALL_COL_LEFT;
                        last_wall = col;
                        wc_val = plat_coyote_max + 1;

                        if ((moving_right && !INPUT_RIGHT) || (!moving_right && !INPUT_LEFT))
                        {
                            pl_vel_x = 0;
                        }

#ifdef FEAT_PLATFORM_DASH
                        if (que_state == DASH_STATE)
                        {
                            que_state = FALL_STATE;
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

    if (mask & COL_CHECK_TRIGGERS)
    {
        trigger_activate_at_intersection(&PLAYER.bounds, &PLAYER.pos, INPUT_UP_PRESSED);
    }
}
