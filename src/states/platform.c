/*
Future notes on things to do:
- Limit air dashes before touching the ground
- Add an option for wall jump that only allows alternating walls.
- Currently, dashing through walls checks the potential end point, and if it isn't clear then it continues with the normal dash routine. 
    The result is that there could be a valid landing point across a wall, but the player is just a little too close for it to register. 
    I could create a 'look-back' loop that runs through the intervening tiles until it finds an empty landing spot.
- The bounce event is a funny one, because it can have the player going up without being in the jump state. I should perhaps add some error catching stuff for such situations
- Can I have a wall_jump init ahead of the normal jump init? If it's just checking a few more boxes....
- Improve ladder situation: jump from ladder option, bug with hitting the bottom of ladders, other stuff?

- Add check for camera bounds on Dash Init
- Solid actors have a fault: they only check collisions once on enter. This is especially problematic because of how GBStudio does invincibility frames,
  because it means the player can attach to a platform without causing the hit trigger to run. 
     - 2 potential solutions: 
     - give the player a minimum velocity every frame, forcing a re-collision. This might break the moving platform code though
     - manually re-trigger the collision call if the actor is attached.




TARGETS for Optimization
- State script assignment could be 100% be re-written to avoid all those assignments and directly use the pointers. I am not canny enough to do that.
- I should be able to combine solid actors and platform actors into a single check...
- It's inellegant that the dash check requires me to check again later if it succeeded or not. Can I reorganize this somehow?
- I think I can probably combine actor_attached and last_actor
- I need to refactor the downwards collision for Y, it's a bit of a mess at this point. I just can't wrap my head around it atm
- Wall Slide could be optimized to skill the acceleration bit, as the only thing that matters is tapping away

THINGS TO WATCH
- Does every state (that needs to) end up resetting DeltaX?

NOTES on GBStudio Quirks
- 256 velocities per position, 16 'positions' per pixel, 8 pixels per tile
- Player bounds: for an ordinary 16x16 sprite, bounds.left starts at 0 and bounds.right starts at 16. If it's smaller, bounds.left is POSITIVE
    For bounds.top, however, Y starts counting from the middle of a sprite. bounds.top is negative and bounds.bottom is positive
- CameraX is in the middle of the screen, not left corner

GENERAL STRUCTURE OF THIS FILE
The old format was well structured as a state-machine, isolating all the components into states. Unfortunately, it seems like the overhead of calling 
collision functions on the GameBoy makes this model unperformant. However, I'm also limited to the total amount of code that can be placed in a single bank. 
I cannot get rid of the functions and move the code into the file itself. New structure is a compromise that uses goto commands to skip some sections that are
shared by most of the states. 
    
INIT()
    Tweak a few fields so they don't overflow variables
    Normalize some fields so that they are applied over multiple frames
    Initialize variables
UPDATE()
    A. Input Checks (Double-tap Dash, Drop-Through)    I'm considering moving the drop-through check into a state
    B. STATE MACHINE 1 SWITCH: Falling, Ground, Jumping, Dashing, Climbing a Ladder, Wall Sliding
        State Initialization
        Calculate Change in Vertical Movement
        Some calculate horziontal movement
        Some calculate collisions
    C. Shared Collision
        Acceleration Code   
        Basic X Collision           gotoXCol
        Basic Y Collision           gotoYCol
        Actor Collision Check       gotoActorCol
    D. STATE MACHINE 2 SWITCH:      gotoSwitch2
        Animation
        State Change Logic
        Some Counters
    E. Trigger Check                gotoTriggerCol
    G. Tic Counters                 gotoCounters


BUGS:
 - When the player is on a moving platform and is hit by another one, they get caught mid-way on the next one.
*/
#pragma bank 3

#include "data/states_defines.h"
#include "states/platform.h"

#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "data_manager.h"
#include "game_time.h"
#include "input.h"
#include "math.h"
#include "scroll.h"
#include "trigger.h"
#include "vm.h"



#ifndef INPUT_PLATFORM_JUMP
#define INPUT_PLATFORM_JUMP        INPUT_A
#endif
#ifndef INPUT_PLATFORM_RUN
#define INPUT_PLATFORM_RUN         INPUT_B
#endif
#ifndef INPUT_PLATFORM_INTERACT
#define INPUT_PLATFORM_INTERACT    INPUT_A
#endif
#ifndef PLATFORM_CAMERA_DEADZONE_Y
#define PLATFORM_CAMERA_DEADZONE_Y 16
#endif

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

//TEST
script_state_t state_events[21];



//DEFAULT ENGINE VARIABLES
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

//PLATFORMER PLUS ENGINE VARIABLES
//All engine fields are prefixed with plat_
BYTE plat_camera_deadzone_x; // Camera deadzone
UBYTE plat_camera_block;    //Limit the player's movement to the camera's edges
UBYTE plat_drop_through;    //Drop-through control
UBYTE plat_mp_group;        //Collision group for platform actors
UBYTE plat_solid_group;     //Collision group for solid actors
WORD plat_jump_min;         //Jump amount applied on the first frame of jumping
UBYTE plat_hold_jump_max;   //Maximum number for frames for continuous input
UBYTE plat_extra_jumps;     //Number of jumps while in the air
WORD plat_jump_reduction;   //Reduce height each double jump
UBYTE plat_coyote_max;      //Coyote Time maximum frames
UBYTE plat_buffer_max;      //Jump Buffer maximum frames
UBYTE plat_wall_jump_max;   //Number of wall jumps in a row
UBYTE plat_wall_slide;      //Enables/Disables wall sliding
WORD plat_wall_grav;        //Gravity while clinging to the wall
WORD plat_wall_kick;        //Horizontal force for pushing off the wall
UBYTE plat_float_input;     //Input type for float (hold up or hold jump)
WORD plat_float_grav;       //Speed of fall descent while floating
UBYTE plat_air_control;     //Enables/Disables air control
UBYTE plat_turn_control;    //Controls the amount of slippage when the player turns while running.
WORD plat_air_dec;          // air deceleration rate
UBYTE plat_run_type;        //Chooses type of acceleration for jumping
WORD plat_turn_acc;         //Speed with which a character turns
UBYTE plat_run_boost;        //Additional jump height based on player horizontal speed
UBYTE plat_dash;            //Choice of input for dashing: double-tap, interact, or down and interact
UBYTE plat_dash_style;      //Ground, air, or both
UBYTE plat_dash_momentum;   //Applies horizontal momentum or vertical momentum, neither or both
UBYTE plat_dash_through;    //Choose if the player can dash through actors, triggers, and walls
WORD plat_dash_dist;        //Distance of the dash
UBYTE plat_dash_frames;     //Number of frames for dashing
UBYTE plat_dash_ready_max;  //Time before the player can dash again
UBYTE plat_dash_deadzone;

enum pStates {              //Datatype for tracking states
    FALL_INIT = 0,
    FALL_STATE,
    FALL_END,
    GROUND_INIT,
    GROUND_STATE,
    GROUND_END,
    JUMP_INIT,
    JUMP_STATE,
    JUMP_END,
    DASH_INIT,
    DASH_STATE,
    DASH_END,
    LADDER_INIT,
    LADDER_STATE,
    LADDER_END,
    WALL_INIT,
    WALL_STATE,
    WALL_END,
    KNOCKBACK_INIT,
    KNOCKBACK_STATE,
    BLANK_INIT,
    BLANK_STATE
}; 
enum pStates plat_state;    //Current platformer state
enum pStates que_state;
UBYTE nocontrol_h;          //Turns off horizontal input, currently only for wall jumping
UBYTE nocollide;            //Turns off vertical collisions, currently only for dropping through platforms
WORD deltaX;
WORD deltaY;

//COUNTER variables
UBYTE ct_val;               //Coyote Time Variable
UBYTE jb_val;               //Jump Buffer Variable
UBYTE wc_val;               //Wall Coyote Time Variable
UBYTE hold_jump_val;        //Jump input hold variable
UBYTE dj_val;               //Current double jump
UBYTE wj_val;               //Current wall jump

//WALL variables 
BYTE last_wall;             //tracks the last wall the player touched
BYTE col;

//DASH VARIABLES
UBYTE dash_ready_val;       //tracks the current amount before the dash is ready
WORD dash_dist;             //Takes overall dash distance and holds the amount per-frame
UBYTE dash_currentframe;    //Tracks the current frame of the overall dash
BYTE tap_val;               //Number of frames since the last time left or right button was tapped
UBYTE dash_end_clear;       //Used to store the result of whether the end-position of a dash is empty

//COLLISION VARS
actor_t *last_actor;        //The last actor the player hit, and that they were attached to
UBYTE actor_attached;       //Keeps track of whether the player is currently on an actor and inheriting its movement
WORD mp_last_x;             //Keeps track of the pos.x of the attached actor from the previous frame
WORD mp_last_y;             //Keeps track of the pos.y of the attached actor from the previous frame


//JUMPING VARIABLES
WORD jump_reduction_val;    //Holds a temporary jump velocity reduction
WORD jump_per_frame;        //Holds a jump amount that has been normalized over the number of jump frames
WORD jump_reduction;        //Holds the reduction amount that has been normalized over the number of jump frames
WORD boost_val;

//WALKING AND RUNNING VARIABLES
WORD pl_vel_x;              //Tracks the player's x-velocity between frames
WORD pl_vel_y;              //Tracks the player's y-velocity between frames

//VARIABLES FOR CAMERAS
WORD *edge_left;
WORD *edge_right;
WORD mod_image_right;
WORD mod_image_left;

//VARIABLES FOR EVENT PLUGINS
//UBYTE grounded;             //Variable to keep compatability with other plugins that use the older 'grounded' check
BYTE run_stage;             //Tracks the stage of running based on the run type
UBYTE jump_type;            //Tracks the type of jumping, from the ground, in the air, or off the wall

//SLOPE VARIABLES
UBYTE grounded;             //Needed? Add for compatability?
UBYTE on_slope;
UBYTE slope_y;


void platform_init(void) BANKED {
    //Initialize Camera
    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = plat_camera_deadzone_x;
    camera_deadzone_y = PLATFORM_CAMERA_DEADZONE_Y;
    if ((camera_settings & CAMERA_LOCK_X_FLAG)){
        camera_x = (PLAYER.pos.x >> 4) + 8;
    } else{
        camera_x = 0;
    }
    if ((camera_settings & CAMERA_LOCK_Y_FLAG)){
        camera_y = (PLAYER.pos.y >> 4) + 8;
    } else{
        camera_y = 0;
    }

    //Initialize Camera Bounds
    mod_image_right = image_width - SCREEN_WIDTH;
    mod_image_left = 0;
    if (plat_camera_block & 1){
        edge_left = &scroll_x;
    }
    else{
        edge_left = &mod_image_left;
    }

    if (plat_camera_block & 2){
        edge_right = &scroll_x;
    }
    else{
        edge_right = &image_width;
    }

    
    //Make sure jumping doesn't overflow variables
    //First, check for jumping based on Frames and Initial Jump Min
    while (32000 - (plat_jump_vel/MIN(15,plat_hold_jump_max)) - plat_jump_min < 0){
        plat_hold_jump_max += 1;
    }

    //This ensures that, by itself, the plat run boost active on any single frame cannot overflow a WORD.
    //It is complemented by another check in the jump itself that works with the actual velocity. 
    if (plat_run_boost != 0){
        while((32000/plat_run_boost) < ((plat_run_vel>>8)/plat_hold_jump_max)){
            plat_run_boost--;
        }
    }

    //Normalize variables by number of frames
    jump_per_frame = plat_jump_vel / MIN(15, plat_hold_jump_max);   //jump force applied per frame in the JUMP_STATE
    jump_reduction = plat_jump_reduction / plat_hold_jump_max;      //Amount to reduce subequent jumps per frame in JUMP_STATE
    dash_dist = plat_dash_dist / plat_dash_frames;                    //Dash distance per frame in the DASH_STATE
    boost_val = plat_run_boost / plat_hold_jump_max;                  //Vertical boost from horizontal speed per frame in JUMP STATE

    //Initialize State
    plat_state = GROUND_STATE;
    que_state = GROUND_STATE;
    actor_attached = FALSE;
    run_stage = 0;
    nocontrol_h = 0;
    nocollide = 0;
    if (PLAYER.dir == DIR_UP || PLAYER.dir == DIR_DOWN || PLAYER.dir == DIR_NONE) {
        PLAYER.dir = DIR_RIGHT;
    }

    //Initialize other vars
    game_time = 0;
    pl_vel_x = 0;
    pl_vel_y = 4000;                //Magic number for preventing a small glitch when loading into a scene
    last_wall = 0;                  //This could be 1 bit
    hold_jump_val = plat_hold_jump_max;
    dj_val = 0;
    wj_val = plat_wall_jump_max;
    dash_end_clear = FALSE;         //could also be mixed into the collision bitmask
    jump_type = 0;
    deltaX = 0;
    deltaY = 0;

}

void platform_update(void) BANKED {
    //INITIALIZE VARS
    WORD temp_y = 0;
    col = 0;                   //tracks if there is a block left or right
    UBYTE p_half_width = (PLAYER.bounds.right - PLAYER.bounds.left) >> 1;
    UBYTE tile_x_mid = ((PLAYER.pos.x >> 4) + PLAYER.bounds.left + p_half_width) >> 3; 
    UBYTE tile_y = ((PLAYER.pos.y >> 4) + PLAYER.bounds.top + 1) >> 3;
    UBYTE prev_on_slope = 0;
    UBYTE old_x = 0;
    
    //A. INPUT CHECK=================================================================================================
    //Dash Input Check
    UBYTE dash_press = FALSE;
    switch(plat_dash){
        case 1:
            //Interact Dash
            if (INPUT_PRESSED(INPUT_PLATFORM_INTERACT)){
                dash_press = TRUE;
            }
        break;
        case 2:
            //Double-Tap Dash
            if (INPUT_PRESSED(INPUT_LEFT)){
                if(tap_val < 0){
                    dash_press = TRUE;
                } else{
                    tap_val = -15;
                }
            } else if (INPUT_PRESSED(INPUT_RIGHT)){
                if(tap_val > 0){
                    dash_press = TRUE;
                } else{
                    tap_val = 15;
                }
            }
        break;
        case 3:
            //Down and Interact (need to check both orders)
            if ((INPUT_PRESSED(INPUT_DOWN) && INPUT_PLATFORM_JUMP) || (INPUT_DOWN && INPUT_PRESSED(INPUT_PLATFORM_JUMP))){
                dash_press = TRUE;
            }
        break;
    }

    // B. STATE MACHINE==================================================================================================
    // SWITCH that includes state initialization, calculation of horizontal motion and vertical Motion
    plat_state = que_state;
    switch(plat_state){
        case FALL_INIT:
            que_state = FALL_STATE;
        case FALL_STATE: {
            jump_type = 0;  //Keep this here, rather than in init, so that we can easily track float as a jump type
            
            //Vertical Movement--------------------------------------------------------------------------------------------
            //FLOAT INPUT
            if (((plat_float_input == 1 && INPUT_PLATFORM_JUMP) || (plat_float_input == 2 && INPUT_UP)) && pl_vel_y >= 0){
                jump_type = 4;
                pl_vel_y = plat_float_grav;
            } else if (nocollide != 0){
                //magic number, rough minimum for actually having the player descend through a platform
                pl_vel_y = 7000; 
            } else if (INPUT_PLATFORM_JUMP && pl_vel_y < 0) {
                //Gravity while holding jump
                pl_vel_y += plat_hold_grav;
                pl_vel_y = MIN(pl_vel_y,plat_max_fall_vel);
            } else {
                //Normal gravity
                pl_vel_y += plat_grav;
                pl_vel_y = MIN(pl_vel_y,plat_max_fall_vel);
            }
        
            //Collision ---------------------------------------------------------------------------------------------------
            //Vertical Collision Checks
            deltaY += pl_vel_y >> 8;
            temp_y = PLAYER.pos.y;    

            //Horizontal Movement----------------------------------------------------------------------------------------
            if (nocontrol_h != 0 || plat_air_control == 0){
                //No horizontal input
                deltaX += pl_vel_x >> 8;
                goto gotoXCol;
            } 
        }
        break;
    //================================================================================================================
        case GROUND_INIT:
            que_state = GROUND_STATE;
            pl_vel_y = 256;
            jump_type = 0;
            wc_val = 0;
            ct_val = plat_coyote_max; 
            dj_val = plat_extra_jumps; 
            wj_val = plat_wall_jump_max;
            jump_reduction_val = 0;
            
        case GROUND_STATE:{
                        
            //Add X & Y motion from moving platforms
            //Transform velocity into positional data, to keep the precision of the platform's movement
            grounded = true;
            if (actor_attached){
                //If the platform has been disabled, detach the player
                if(last_actor->disabled == TRUE){
                    que_state = FALL_INIT;
                    actor_attached = FALSE;
                //If the player is off the platform to the right, detach from the platform
                } else if (PLAYER.pos.x + (PLAYER.bounds.left << 4) > last_actor->pos.x + 16 + (last_actor->bounds.right<< 4)) {
                    que_state = FALL_INIT;
                    actor_attached = FALSE;
                //If the player is off the platform to the left, detach
                } else if (PLAYER.pos.x + 16 + (PLAYER.bounds.right << 4) < last_actor->pos.x + (last_actor->bounds.left << 4)){
                    que_state = FALL_INIT;
                    actor_attached = FALSE;
                } else{
                //Otherwise, add any change in movement from platform
                    deltaX += (last_actor->pos.x - mp_last_x);
                    mp_last_x = last_actor->pos.x;
                }

                //If we're on a platform, zero out any other motion from gravity or other sources
                pl_vel_y = 0;
                
                //Add any change from the platform we're standing on
                deltaY += last_actor->pos.y - mp_last_y;

                //We're setting these to the platform's position, rather than the actor so that if something causes the player to
                //detach (like hitting the roof), they won't automatically get re-attached in the subsequent actor collision step.
                mp_last_y = last_actor->pos.y;
                temp_y = last_actor->pos.y;
            } else if (nocollide != 0){
                //If we're dropping through a platform
                pl_vel_y = 7000; //magic number, rough minimum for actually having the player descend through a platform
                temp_y = PLAYER.pos.y;
            } else {
                //Normal gravity
                pl_vel_y += plat_grav;
                temp_y = PLAYER.pos.y;
                que_state = FALL_INIT; //Use this to test for Falling, avoids an If test in YCollision
            }
            // Add Collision Offset from Moving Platforms
            deltaY += pl_vel_y >> 8;

        }
        break;
    //================================================================================================================
        case JUMP_INIT:
            //Right now this has a limited use for triggered jumps because many of the jump effects depend on testing INPUT_PLATFORM_JUMP
            //But if the player switches to this state without pressing jump, then these won't fire...
            hold_jump_val = plat_hold_jump_max; 
            actor_attached = FALSE;
            pl_vel_y = -plat_jump_min;
            jb_val = 0;
            ct_val = 0;
            wc_val = 0;
            que_state = JUMP_STATE;
        case JUMP_STATE: {
            //Vertical Movement-------------------------------------------------------------------------------------------
            //Add jump force during each jump frame
            if (hold_jump_val !=0 && INPUT_PLATFORM_JUMP){
                //Add the boost per frame amount.
                pl_vel_y -= jump_per_frame;
                //Reduce subsequent jump amounts (for double jumps)
                if (plat_jump_vel >= jump_reduction_val){
                    pl_vel_y += jump_reduction_val;
                } else {
                    //When reducing that value, zero out if it's negative
                    pl_vel_y = 0;
                }
                //Add jump boost from horizontal movement
                WORD tempBoost = (pl_vel_x >> 8) * boost_val;
                //Take the positive value of x-vel
                tempBoost = MAX(tempBoost, -tempBoost);
                //This is a test to see if the results will overflow pl_vel_y. Note, pl_vel_y is negative here.
                if (tempBoost > 32767 + pl_vel_y){
                    pl_vel_y = -32767;
                }
                else{
                    pl_vel_y += -tempBoost;
                }
                hold_jump_val -=1;
            } else if (INPUT_PLATFORM_JUMP && pl_vel_y < 0){
                //After the jump frames end, use the reduced gravity
                pl_vel_y += plat_hold_grav;
            } else if (pl_vel_y >= 0){
                que_state = FALL_INIT;
                pl_vel_y += plat_grav;
            } else {
                pl_vel_y += plat_grav;
            }

            temp_y = PLAYER.pos.y;
            //Start DeltaX with Actor offsets
            deltaY += pl_vel_y >> 8;

            //Horizontal Movement-----------------------------------------------------------------------------------------
            if (nocontrol_h != 0 || plat_air_control == 0){
                //If the player doesn't have control of their horizontal movement, skip acceleration phase
                deltaX += pl_vel_x >> 8;
                goto gotoXCol;
            } 
        }
        break;
    //================================================================================================================
        case DASH_INIT:{
            dash_init_switch();
        }
        goto gotoCounters; //Dash Init has a return, unlike other initialization phases, because its calculations are time consuming and we don't want to deal with collision in the same frame.
        case DASH_STATE: {
            //Movement & Collision Combined----------------------------------------------------------------------------------
            //Dashing uses much of the basic collision code. Comments here focus on the differences.
            UBYTE tile_current; //For tracking collisions across longer distances
            UBYTE tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
            UBYTE tile_end   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) + 1;        
            col = 0;

            //Right Dash Movement & Collision
            if (PLAYER.dir == DIR_RIGHT){
                //Get tile x-coord of player position
                tile_current = ((PLAYER.pos.x >> 4) + PLAYER.bounds.right) >> 3;
                //Get tile x-coord of final position
                UWORD new_x = PLAYER.pos.x + (dash_dist);
                UBYTE tile_x = (((new_x >> 4) + PLAYER.bounds.right) >> 3) + 1;
                //check each space from the start of the dash until the end of the dash.
                //in the future, I should build a reversed version of this section for dashing through walls.
                //However, it's not quite as simple as reversing the direction of the check. The loops need to store the player's width and only return when there are enough spaces in a row
                while (tile_current != tile_x){
                    //Don't go past camera bounds
                    if ((plat_camera_block & 2) && tile_current > (camera_x + SCREEN_WIDTH_HALF - 16) >> 3){
                        new_x = ((((tile_current) << 3) - PLAYER.bounds.right) << 4) -1;
                        dash_currentframe == 0;
                        goto endRcol;
                    }
                        //CHECK TOP AND BOTTOM
                    while (tile_start != tile_end) {
                        //Check for Collisions (if the player collides with walls)
                        if(plat_dash_through != 3 || dash_end_clear == FALSE){                    
                            if (tile_at(tile_current, tile_start) & COLLISION_LEFT) {
                                //The landing space is the tile we collided on, but one to the left
                                new_x = ((((tile_current) << 3) - PLAYER.bounds.right) << 4) -1;
                                col = 1;
                                last_wall = 1;
                                wc_val = plat_coyote_max;
                                dash_currentframe == 0;
                                goto endRcol;
                            }   
                        }
                        //Check for Triggers at each step. If there is a trigger stop the dash (but don't run the trigger yet).
                        /*if (plat_dash_through < 2){
                            if (trigger_at_tile(tile_current, tile_start) != NO_TRIGGER_COLLISON) {
                                new_x = ((((tile_current+1) << 3) - PLAYER.bounds.right) << 4);
                            }
                        }*/
                        tile_start++;
                    }
                    
                    tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top) >> 3);
                    tile_current += 1;
                }
                endRcol: 
                if(plat_dash_momentum == 1 || plat_dash_momentum == 3){           
                    //Dashes don't actually use velocity, so we will simulate the momentum by adding the full run speed. 
                    pl_vel_x = plat_run_vel;
                } else{
                    pl_vel_x = 0;
                }
                PLAYER.pos.x = MIN((image_width - 16) << 4, new_x);
            }

            //Left Dash Movement & Collision
            else if (PLAYER.dir == DIR_LEFT){
                //Get tile x-coord of player position
                tile_current = ((PLAYER.pos.x >> 4) + PLAYER.bounds.left) >> 3;
                //Get tile x-coord of final position
                WORD new_x = PLAYER.pos.x - (dash_dist);
                UBYTE tile_x = (((new_x >> 4) + PLAYER.bounds.left) >> 3)-1;
                //CHECK EACH SPACE FROM START TO END
                while (tile_current != tile_x){
                    //Camera lock check
                    if ((plat_camera_block & 1) && tile_current < (camera_x - SCREEN_WIDTH_HALF) >> 3){
                        new_x = ((((tile_current + 1) << 3) - PLAYER.bounds.left) << 4)+1;
                        dash_currentframe == 0;
                        goto endLcol;
                    }
                    //CHECK TOP AND BOTTOM
                    while (tile_start != tile_end) {   
                        //check for walls
                        if(plat_dash_through != 3 || dash_end_clear == FALSE){  //If you collide with walls
                            if (tile_at(tile_current, tile_start) & COLLISION_RIGHT) {
                                new_x = ((((tile_current + 1) << 3) - PLAYER.bounds.left) << 4)+1;
                                col = -1;
                                last_wall = -1;
                                dash_currentframe == 0;
                                wc_val = plat_coyote_max;
                                goto endLcol;
                            }
                        }
                        //Check for triggers
                        /*if (plat_dash_through  < 2){
                            if (trigger_at_tile(tile_current, tile_start) != NO_TRIGGER_COLLISON) {
                                new_x = ((((tile_current - 1) << 3) - PLAYER.bounds.left) << 4);
                                goto endLcol;
                            }
                        }*/  
                        tile_start++;
                    }
                    tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top) >> 3);
                    tile_current -= 1;
                }
                endLcol: 
                if(plat_dash_momentum == 1 || plat_dash_momentum == 3){            
                    pl_vel_x = -plat_run_vel;
                } else{
                    pl_vel_x = 0;
                }
                PLAYER.pos.x = MAX(0, new_x);
            }

            //Vertical Movement & Collision-------------------------------------------------------------------------
            if(plat_dash_momentum >= 2){
                //If we're using vertical momentum, add gravity as normal (otherwise, vel_y = 0)
                pl_vel_y += plat_hold_grav;

                //Add Jump force
                if (INPUT_PRESSED(INPUT_PLATFORM_JUMP)){
                    //Coyote Time (CT) functions here as a proxy for being grounded. 
                    if (ct_val != 0){
                        actor_attached = FALSE;
                        pl_vel_y = -(plat_jump_min + (plat_jump_vel/2));
                        jb_val = 0;
                        ct_val = 0;
                        jump_type = 1;
                    } else if (dj_val != 0){
                    //If the player is in the air, and can double jump
                        dj_val -= 1;
                        jump_reduction_val += jump_reduction;
                        actor_attached = FALSE;
                        //We can't switch states for jump frames, so approximate the height. Engine val limits ensure this doesn't overflow.
                        pl_vel_y = -(plat_jump_min + (plat_jump_vel/2));    
                        jb_val = 0;
                        ct_val = 0;
                        jump_type = 2;
                    }
                } 

                //Vertical Collisions
                temp_y = PLAYER.pos.y;    
                deltaY += pl_vel_y >> 8;
                deltaY = CLAMP(deltaY, -127, 127);
                UBYTE tile_start = (((PLAYER.pos.x >> 4) + PLAYER.bounds.left)  >> 3);
                UBYTE tile_end   = (((PLAYER.pos.x >> 4) + PLAYER.bounds.right) >> 3) + 1;
                if (deltaY > 0) {

                //Moving Downward
                    WORD new_y = PLAYER.pos.y + deltaY;
                    UBYTE tile_y = ((new_y >> 4) + PLAYER.bounds.bottom) >> 3;
                    while (tile_start != tile_end) {
                        if (tile_at(tile_start, tile_y) & COLLISION_TOP) {                    
                            //Land on Floor
                            new_y = ((((tile_y) << 3) - PLAYER.bounds.bottom) << 4) - 1;
                            actor_attached = FALSE; //Detach when MP moves through a solid tile.                                   
                            pl_vel_y = 256;
                            break;
                        }
                        tile_start++;
                    }
                    PLAYER.pos.y = new_y;
                } else if (deltaY < 0) {

                    //Moving Upward
                    WORD new_y = PLAYER.pos.y + deltaY;
                    UBYTE tile_y = (((new_y >> 4) + PLAYER.bounds.top) >> 3);
                    while (tile_start != tile_end) {
                        if (tile_at(tile_start, tile_y) & COLLISION_BOTTOM) {
                            new_y = ((((UBYTE)(tile_y + 1) << 3) - PLAYER.bounds.top) << 4) + 1;
                            pl_vel_y = 0;
                            break;
                        }
                        tile_start++;
                    }
                    PLAYER.pos.y = new_y;
                }
                // Clamp Y Velocity
                pl_vel_y = CLAMP(pl_vel_y,-plat_max_fall_vel, plat_max_fall_vel);
            } else{
                temp_y = PLAYER.pos.y;  
            }
        
        }
                //CHECKS-------------------------------------------------------------------------------------------------------
        if (plat_dash_through >= 1){
            goto gotoSwitch2;
        }
        goto gotoActorCol;
    //================================================================================================================
        case LADDER_INIT:
            que_state = LADDER_STATE;
            jump_type = 0;
        case LADDER_STATE:{
            ladder_switch();
        }
        goto gotoActorCol;
    //================================================================================================================
        case WALL_INIT:
            que_state = WALL_STATE;
            jump_type = 0;
            run_stage = 0;
        case WALL_STATE:{
            //Vertical Movement------------------------------------------------------------------------------------------
            //WALL SLIDE
            if (nocollide != 0){
                pl_vel_y += 7000; //magic number, rough minimum for actually having the player descend through a platform
            } else if (pl_vel_y < 0){
                //If the player is still ascending, don't apply wall-gravity
                pl_vel_y += plat_grav;
            } else if (plat_wall_slide) {
                //If the toggle is on, use wall gravity
                pl_vel_y = plat_wall_grav;
            } else{
                //Otherwise use regular gravity
                pl_vel_y += plat_grav;
            }

            //Collision--------------------------------------------------------------------------------------------------
            //Vertical Collision Checks
            deltaY += pl_vel_y >> 8;
            temp_y = PLAYER.pos.y;    
        }
        break;
    //================================================================================================================
        case KNOCKBACK_INIT:
        run_stage = 0;
        jump_type = 0;
        que_state = KNOCKBACK_STATE;
        case KNOCKBACK_STATE: {
           //Horizontal Movement----------------------------------------------------------------------------------------
            if (pl_vel_x < 0) {
                    pl_vel_x += plat_air_dec;
                    pl_vel_x = MIN(pl_vel_x, 0);
            } else if (pl_vel_x > 0) {
                    pl_vel_x -= plat_air_dec;
                    pl_vel_x = MAX(pl_vel_x, 0);
            }
            deltaX += pl_vel_x >> 8;
        
            //Vertical Movement--------------------------------------------------------------------------------------------
            //Normal gravity
            pl_vel_y += plat_grav;
            pl_vel_y = MIN(pl_vel_y,plat_max_fall_vel);
        
            //Collision ---------------------------------------------------------------------------------------------------


            //Vertical Collision Checks
            deltaY += pl_vel_y >> 8;
            temp_y = PLAYER.pos.y;    

            nocollide = 0;
        }
        goto gotoXCol;
    //================================================================================================================
        case BLANK_INIT:
        que_state = BLANK_STATE;
        pl_vel_x = 0;
        pl_vel_y = 0;
        run_stage = 0;
        jump_type = 0;
        case BLANK_STATE: 
        goto gotoActorCol;
    }
    //END SWITCH


    //FUNCTION ACCELERATION
    if (INPUT_LEFT || INPUT_RIGHT){
        BYTE dir = 1;
        if (INPUT_LEFT){
            dir = -1;
            pl_vel_x = -pl_vel_x;
        }

        if (INPUT_PLATFORM_RUN){
            switch(plat_run_type){
                case 0:
                //Ordinay Walk (same as below). I can't think of a way to collapse these two uses.
                    if(pl_vel_x < 0 && plat_turn_acc != 0){
                        pl_vel_x += plat_turn_acc;
                        run_stage = -1;
                    } else{
                        run_stage = 0;
                        pl_vel_x = CLAMP(pl_vel_x + plat_walk_acc, plat_min_vel, plat_walk_vel); 
                    }
                    pl_vel_x *= dir;
                    deltaX += pl_vel_x >> 8;
                    
                break;
                case 1:
                //Type 1: Smooth Acceleration as the Default in GBStudio
                    pl_vel_x = CLAMP(pl_vel_x + plat_run_acc, plat_min_vel, plat_run_vel);
                    pl_vel_x *= dir;
                    deltaX += pl_vel_x >> 8;
                    run_stage = 1;
                break;
                case 2:
                //Type 2: Enhanced Smooth Acceleration
                    if(pl_vel_x < 0){
                        pl_vel_x += plat_turn_acc;
                        run_stage = -1;
                    }
                    else if (pl_vel_x < plat_walk_vel){
                        pl_vel_x = MAX(pl_vel_x + plat_walk_acc, plat_min_vel);
                        run_stage = 1;
                    }
                    else{
                        pl_vel_x = MIN(pl_vel_x + plat_run_acc, plat_run_vel);
                        run_stage = 2;
                    }
                    pl_vel_x *= dir;
                    deltaX += pl_vel_x >> 8;
                break;
                case 3:
                //Type 3: Instant acceleration to full speed
                    run_stage = 1;
                    pl_vel_x = plat_run_vel * dir;
                    deltaX += pl_vel_x >> 8;
                break;
            }
        } else {
            //Ordinay Walk
            if(pl_vel_x < 0 && plat_turn_acc != 0){
                pl_vel_x += plat_turn_acc;
                run_stage = -1;
            } else {
                run_stage = 0;
                pl_vel_x += plat_walk_acc;
                pl_vel_x = CLAMP(pl_vel_x, plat_min_vel, plat_walk_vel); 
            }
            pl_vel_x *= dir;
            deltaX += pl_vel_x >> 8;

        }
    } else{
        //DECELERATION
        if (pl_vel_x < 0) {
            if (plat_state == GROUND_STATE){
                pl_vel_x += plat_dec;
            } else { 
                pl_vel_x += plat_air_dec;
            }
            if (pl_vel_x > 0) {
                pl_vel_x = 0;
            }
        } else if (pl_vel_x > 0) {
            if (plat_state == GROUND_STATE){
                pl_vel_x -= plat_dec;
                }
            else { 
                pl_vel_x -= plat_air_dec;
                }
            if (pl_vel_x < 0) {
                pl_vel_x = 0;
            }
        }
        run_stage = 0;
        deltaX += pl_vel_x >> 8;
    }

    //FUNCTION X COLLISION

    gotoXCol:
    {
        deltaX = CLAMP(deltaX, -127, 127);
        prev_on_slope = on_slope;
        old_x = PLAYER.pos.x;
        on_slope = FALSE;
        UBYTE tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
        UBYTE tile_end   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) + 1;       
        UWORD new_x = PLAYER.pos.x + deltaX;
        
        UBYTE tile_x = 0;
        UBYTE col_mid = 0;
        
        //Edge Locking
        //If the player is past the right edge (camera or screen)
        if (new_x > (*edge_right + SCREEN_WIDTH - 16) <<4){
            //If the player is trying to go FURTHER right
            if (new_x > PLAYER.pos.x){
                new_x = PLAYER.pos.x;
                pl_vel_x = 0;
            } else {
            //If the player is already off the screen, push them back
                new_x = PLAYER.pos.x - MIN(PLAYER.pos.x - ((*edge_right + SCREEN_WIDTH - 16)<<4), 16);
            }
        //Same but for left side. This side needs a 1 tile (8px) buffer so it doesn't overflow the variable.
        } else if (new_x < *edge_left << 4){
            if (deltaX < 0){
                new_x = PLAYER.pos.x;
                pl_vel_x = 0;
            } else {
                new_x = PLAYER.pos.x + MIN(((*edge_left+8)<<4)-PLAYER.pos.x, 16);
            }
        }

        //Step-Check for collisions one tile left or right for each avatar height tile
        if (new_x > PLAYER.pos.x) {
            tile_x = ((new_x >> 4) + PLAYER.bounds.right) >> 3;

            //New Slope Stuff Part 1
            tile_y   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3);
            UBYTE tile_x_mid = ((new_x >> 4) + PLAYER.bounds.left + p_half_width + 1) >> 3; 
            col_mid = tile_at(tile_x_mid, tile_y);
            if (IS_ON_SLOPE(col_mid)) {
                on_slope = col_mid;
                slope_y = tile_y;
            }
            UBYTE slope_on_y = FALSE;
            //New Slope Stuff P1 End

            while (tile_start != tile_end) {
               
                //New Slope Stuff P2
                col = tile_at(tile_x, tile_start);
                if (IS_ON_SLOPE(col)) {
                    slope_on_y = TRUE;
                }
                if (col & COLLISION_LEFT) {
                    // only ignore collisions if there is a slope on this y column somewhere
                    if (slope_on_y || tile_start == slope_y) {
                        // Right slope
                        if ((IS_ON_SLOPE(on_slope) && IS_SLOPE_RIGHT(on_slope)) ||
                            (IS_ON_SLOPE(prev_on_slope) && IS_SLOPE_RIGHT(prev_on_slope))
                            )
                            {
                            if (tile_start <= slope_y) {
                                tile_start++;
                                continue;
                            }
                        }
                    }
                    if (slope_on_y) {
                        // Left slope
                        if ((IS_ON_SLOPE(on_slope) && IS_SLOPE_LEFT(on_slope)) ||
                            (IS_ON_SLOPE(prev_on_slope) && IS_SLOPE_LEFT(prev_on_slope))
                            )
                            {
                            if (tile_start >= slope_y) {
                                tile_start++;
                                continue;
                            }
                        }
                    }
                //End New Slope Stuff P2
                new_x = (((tile_x << 3) - PLAYER.bounds.right) << 4) - 1;
                pl_vel_x = 0;
                col = 1;
                last_wall = 1;
                wc_val = plat_coyote_max + 1;
                break;
                }
                tile_start++;
            }
        } else if (new_x < PLAYER.pos.x) {
            //New Slope 3
            tile_x = ((new_x >> 4) + PLAYER.bounds.left) >> 3;
            tile_y   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3);
            UBYTE tile_x_mid = ((new_x >> 4) + PLAYER.bounds.left + p_half_width + 1) >> 3; 
            col_mid = tile_at(tile_x_mid, tile_y);
            if (IS_ON_SLOPE(col_mid)) {
                on_slope = col_mid;
                slope_y = tile_y;
            }

            tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
            UBYTE slope_on_y = FALSE;
            //End New Slope 3

            while (tile_start != tile_end) {
            //New Slope 4
                col = tile_at(tile_x, tile_start);
                if (IS_ON_SLOPE(col)) {
                    slope_on_y = TRUE;
                }

                if (col & COLLISION_RIGHT) {
                    // only ignore collisions if there is a slope on this y column somewhere
                    if (slope_on_y || tile_start == slope_y) {
                        // Left slope
                        if ((IS_ON_SLOPE(on_slope) && IS_SLOPE_LEFT(on_slope)) ||
                            (IS_ON_SLOPE(prev_on_slope) && IS_SLOPE_LEFT(prev_on_slope))                            
                            )
                            {
                            if (tile_start <= slope_y) {
                                tile_start++;
                                continue;
                            }
                        }
                    }
                    if (slope_on_y) {
                        // Right slope
                        if ((IS_ON_SLOPE(on_slope) && IS_SLOPE_RIGHT(on_slope)) ||
                            (IS_ON_SLOPE(prev_on_slope) && IS_SLOPE_RIGHT(prev_on_slope))
                            )
                            {
                            if (tile_start >= slope_y) {
                                tile_start++;
                                continue;
                            }
                        }
                    }
                    new_x = ((((tile_x + 1) << 3) - PLAYER.bounds.left) << 4) + 1;
                    pl_vel_x = 0;
                    col = -1;
                    last_wall = -1;
                    wc_val = plat_coyote_max + 1;
                    break;
                }
                tile_start++;
            }
        }
        PLAYER.pos.x = new_x;
    }

    gotoYCol:
    {
        //FUNCTION Y COLLISION
        deltaY = CLAMP(deltaY, -127, 127);

        //New Y Slopes 1
        UBYTE prev_grounded = grounded;
        UWORD old_y = PLAYER.pos.y;
        grounded = FALSE;
        // 1 frame leniency of grounded state if we were on a slope last frame
        if (prev_on_slope) grounded = TRUE;
        //End New Y Slopes 1

        UBYTE tile_start = (((PLAYER.pos.x >> 4) + PLAYER.bounds.left)  >> 3);
        UBYTE tile_end   = (((PLAYER.pos.x >> 4) + PLAYER.bounds.right) >> 3) + 1;
        if (deltaY > 0) {
            //Moving Downward
            WORD new_y = PLAYER.pos.y + deltaY;

            //New Slope Y 2
            UBYTE tile_y = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) - 1;
            UBYTE new_tile_y = ((new_y >> 4) + PLAYER.bounds.bottom) >> 3;
            // If previously grounded and gravity is not enough to pull us down to the next tile, manually check it for the next slope
            // This prevents the "animation glitch" when going down slopes
            if (prev_grounded && new_tile_y == (tile_y + 1)) new_tile_y += 1;
            UWORD x_mid_coord = ((PLAYER.pos.x >> 4) + PLAYER.bounds.left + p_half_width + 1);
            while (tile_y <= new_tile_y) {
                UBYTE col = tile_at(x_mid_coord >> 3, tile_y);
                UWORD tile_x_coord = (x_mid_coord >> 3) << 3;
                UWORD x_offset = x_mid_coord - tile_x_coord;
                UWORD slope_y_coord = 0;
                if (IS_ON_SLOPE(col)) {
                    if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_45_RIGHT) {
                        slope_y_coord = (((tile_y << 3) + (8 - x_offset) - PLAYER.bounds.bottom) << 4) - 1;
                    } else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_RIGHT_BOT) {
                        slope_y_coord = (((tile_y << 3) + (8 - (x_offset >> 1)) - PLAYER.bounds.bottom) << 4) - 1;
                    } else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_RIGHT_TOP) {
                        slope_y_coord = (((tile_y << 3) + (4 - (x_offset >> 1)) - PLAYER.bounds.bottom) << 4) - 1;
                    }

                    else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_45_LEFT) {
                        slope_y_coord = (((tile_y << 3) + (x_offset) - PLAYER.bounds.bottom) << 4) - 1;
                    } else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_LEFT_BOT) {
                        slope_y_coord = (((tile_y << 3) + (x_offset >> 1) - PLAYER.bounds.bottom + 4) << 4) - 1;
                    } else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_LEFT_TOP) {
                        slope_y_coord = (((tile_y << 3) + (x_offset >> 1) - PLAYER.bounds.bottom) << 4) - 1;
                    }
                }

                if (slope_y_coord) {
                    // If going downwards into a slope, don't snap to it unless we've actually collided
                    if (!prev_grounded && slope_y_coord > new_y) {
                        tile_y++;
                        continue;
                    }
                    // If we are moving up a slope, check for top collision
                    UBYTE slope_top_tile_y = (((slope_y_coord >> 4) + PLAYER.bounds.top) >> 3);
                    while (tile_start != tile_end) {
                        if (tile_at(tile_start, slope_top_tile_y) & COLLISION_BOTTOM) {
                            pl_vel_y = 0;
                            pl_vel_x = 0;
                            PLAYER.pos.y = old_y;
                            PLAYER.pos.x = old_x;
                            grounded = TRUE;
                            on_slope = col;
                            slope_y = tile_y;
                            goto gotoActorCol;
                        }
                        tile_start++;
                    }

                    PLAYER.pos.y = slope_y_coord;
                    pl_vel_y = 0;
                    grounded = TRUE;
                    if(plat_state == GROUND_STATE){
                            que_state = GROUND_STATE; 
                            pl_vel_y = 256;
                    } else if(plat_state == GROUND_INIT){
                            que_state = GROUND_STATE;
                    } else {que_state = GROUND_INIT;}
                    on_slope = col;
                    slope_y = tile_y;
                    goto gotoActorCol;
                }
                tile_y++;
            }

            tile_start = (((PLAYER.pos.x >> 4) + PLAYER.bounds.left)  >> 3);
            tile_end   = (((PLAYER.pos.x >> 4) + PLAYER.bounds.right) >> 3) + 1;
            tile_y = ((new_y >> 4) + PLAYER.bounds.bottom) >> 3;
            //End New Slope Y 2


            if (nocollide == 0){
                //Check collisions from left to right with the bottom of the player
                while (tile_start != tile_end) {
                    if (tile_at(tile_start, tile_y) & COLLISION_TOP) {
                        //Drop-Through Floor Check 
                        if (drop_press()){
                            //If it's a regular tile, do not drop through
                            while (tile_start != tile_end) {
                                if (tile_at(tile_start, tile_y) & COLLISION_BOTTOM){
                                    //Escape two levels of looping.
                                    goto land;
                                }
                            tile_start++;
                            }
                            nocollide = 5; //Magic Number, how many frames to steal vertical control
                            pl_vel_y += plat_grav;
                            break; 
                        }
                        //Land on Floor
                        land:
                        new_y = ((((tile_y) << 3) - PLAYER.bounds.bottom) << 4) - 1;
                        actor_attached = FALSE; //Detach when MP moves through a solid tile.
                        //The distinction here is used so that we can check the velocity when the player hits the ground.
                        if(plat_state == GROUND_STATE){
                            que_state = GROUND_STATE; 
                            pl_vel_y = 256;
                        } else if(plat_state == GROUND_INIT){
                            que_state = GROUND_STATE;
                        } else {que_state = GROUND_INIT;}
                        break;
                    }
                    tile_start++;
                }
            }
            PLAYER.pos.y = new_y;

        } else if (deltaY < 0) {
            //Moving Upward
            WORD new_y = PLAYER.pos.y + deltaY;
            UBYTE tile_y = (((new_y >> 4) + PLAYER.bounds.top) >> 3);
            while (tile_start != tile_end) {
                if (tile_at(tile_start, tile_y) & COLLISION_BOTTOM) {
                    new_y = ((((UBYTE)(tile_y + 1) << 3) - PLAYER.bounds.top) << 4) + 1;
                    pl_vel_y = 0;
                    //MP Test: Attempting stuff to stop the player from continuing upward
                    if(actor_attached){
                        temp_y = last_actor->pos.y;
                        if (last_actor->bounds.top > 0){
                            temp_y += last_actor->bounds.top + last_actor->bounds.bottom << 5;
                        }
                        new_y = temp_y;
                    }
                    ct_val = 0;
                    que_state = FALL_INIT;
                    break;
                }
                tile_start++;
            }
            PLAYER.pos.y = new_y;
        }
    }

    //FUNCTION ACTOR CHECK
    //Actor Collisions
    gotoActorCol:
    {
        deltaX = 0;
        deltaY = 0;
        actor_t *hit_actor;
        hit_actor = actor_overlapping_player(FALSE);
        if (hit_actor != NULL && hit_actor->collision_group) {
            //Solid Actors
            if (hit_actor->collision_group == plat_solid_group){
                if(!actor_attached || hit_actor != last_actor){
                    if (temp_y < (hit_actor->pos.y + (hit_actor->bounds.top << 4)) && pl_vel_y >= 0){
                        //Attach to MP
                        last_actor = hit_actor;
                        mp_last_x = hit_actor->pos.x;
                        mp_last_y = hit_actor->pos.y;
                        PLAYER.pos.y = hit_actor->pos.y + (hit_actor->bounds.top << 4) - (PLAYER.bounds.bottom << 4) - 4;
                        //Other cleanup
                        pl_vel_y = 0;
                        actor_attached = TRUE;                        
                        que_state = GROUND_INIT;
                        //PLAYER bounds top seems to be 0 and counting down...
                    } else if (temp_y + (PLAYER.bounds.top << 4) > hit_actor->pos.y + (hit_actor->bounds.bottom<<4)){
                        deltaY += (hit_actor->pos.y - PLAYER.pos.y) + ((-PLAYER.bounds.top + hit_actor->bounds.bottom)<<4) + 32;
                        pl_vel_y = plat_grav;

                        if(que_state == JUMP_STATE || actor_attached){
                            que_state = FALL_INIT;
                        }

                    } else if (PLAYER.pos.x < hit_actor->pos.x){
                        deltaX = (hit_actor->pos.x - PLAYER.pos.x) - ((PLAYER.bounds.right + -hit_actor->bounds.left)<<4);
                        col = 1;
                        last_wall = 1;
                        wc_val = plat_coyote_max + 1;
                        if(!INPUT_RIGHT){
                            pl_vel_x = 0;
                        }
                        if(que_state == DASH_STATE){
                            que_state = FALL_INIT;
                        }
                    } else if (PLAYER.pos.x > hit_actor->pos.x){
                        deltaX = (hit_actor->pos.x - PLAYER.pos.x) + ((-PLAYER.bounds.left + hit_actor->bounds.right)<<4)+16;
                        col = -1;
                        last_wall = -1;
                        wc_val = plat_coyote_max  + 1;
                        if (!INPUT_LEFT){
                            pl_vel_x = 0;
                        }
                        if(que_state == DASH_STATE){
                            que_state = FALL_INIT;
                        }
                    }

                }
            } else if (hit_actor->collision_group == plat_mp_group){
                //Platform Actors
                if(!actor_attached || hit_actor != last_actor){
                    if (temp_y < hit_actor->pos.y + (hit_actor->bounds.top << 4) && pl_vel_y >= 0){
                        //Attach to MP
                        last_actor = hit_actor;
                        mp_last_x = hit_actor->pos.x;
                        mp_last_y = hit_actor->pos.y;
                        PLAYER.pos.y = hit_actor->pos.y + (hit_actor->bounds.top << 4) - (PLAYER.bounds.bottom << 4) - 4;
                        //Other cleanup
                        pl_vel_y = 0;
                        actor_attached = TRUE;                        
                        que_state = GROUND_INIT;
                    }
                }
            }
            //All Other Collisions
            player_register_collision_with(hit_actor);
        } else if (INPUT_PRESSED(INPUT_PLATFORM_INTERACT)) {
            if (!hit_actor) {
                hit_actor = actor_in_front_of_player(8, TRUE);
            }
            if (hit_actor && !hit_actor->collision_group && hit_actor->script.bank) {
                script_execute(hit_actor->script.bank, hit_actor->script.ptr, 0, 1, 0);
            }
        }
    }




    gotoSwitch2:
    //SWITCH for Animation and State Change==========================================================================
    switch(plat_state){
        case FALL_INIT:
            actor_attached = FALSE;
        case FALL_STATE: {
            //ANIMATION--------------------------------------------------------------------------------------------------
            basic_anim();

            //STATE CHANGE------------------------------------------------------------------------------------------------
            //Above: FALL -> GROUND in basic_y_col()
            
            //FALL -> WALL check
            wall_check();

            //FALL -> DASH check
            if(dash_press && dash_ready_val == 0){
                if (plat_dash_style != 0){
                    if (col == 0 || (col == 1 && !INPUT_RIGHT) || (col == -1 && !INPUT_LEFT)){
                    que_state = DASH_INIT;
                    plat_state = FALL_END;
                    break;
                    }
                }
                else if (que_state == GROUND_INIT && plat_dash_style != 1){
                    que_state = DASH_INIT;
                    plat_state = FALL_END;
                    break;
                }
            } 

            //FALL -> JUMP check 
            if (INPUT_PRESSED(INPUT_PLATFORM_JUMP)){
                //Wall Jump
                if(wc_val != 0 && wj_val != 0){
                    jump_type = 3;
                    wj_val -= 1;
                    nocontrol_h = 5;
                    pl_vel_x += (plat_wall_kick + plat_walk_vel)*-last_wall;
                    que_state = JUMP_INIT;
                    plat_state = FALL_END;
                    break;
                } else if (ct_val != 0){
                //Coyote Time Jump
                    jump_type = 1;
                    que_state = JUMP_INIT;
                    plat_state = FALL_END;
                    break;
                } else if (dj_val != 0){
                //Double Jump
                    jump_type = 2;
                    if (dj_val != 255){
                        dj_val -= 1;
                    }
                    jump_reduction_val += jump_reduction;
                    que_state = JUMP_INIT;
                    plat_state = FALL_END;
                    break;
                } else {
                // Setting the Jump Buffer when jump is pressed while not on the ground
                jb_val = plat_buffer_max; 
                }
            } 
        //NEUTRAL -> LADDER check
            ladder_check();

        //Check for final frame
        if (que_state != FALL_STATE){
            plat_state = FALL_END;
        }
        
        //COUNTERS
            // Counting down Jump Buffer Window
            // Set in Fall and checked in Ground state
            if (jb_val != 0){
                jb_val -= 1;
            }

            // Counting down No Control frames
            // Set in Wall and Fall states, checked in Fall and Jump states
            if (nocontrol_h != 0){
                nocontrol_h -= 1;
            }

            // Counting down Coyote Time Window
            // Set in ground and checked in fall state
            if (ct_val != 0 && que_state != GROUND_STATE){
                ct_val -= 1;
            }
            //Counting down Wall Coyote Time
            // Set in collisions and checked in fall state
            if (wc_val !=0 && col == 0){
                wc_val -= 1;
            }
            // Counting down the drop-through floor frames
           // XX Checked in Fall, Wall, Ground, and basic_y_col, set in basic_y_col
            if (nocollide != 0){
                nocollide -= 1;
            }
        }
        break;
    //================================================================================================================
        case GROUND_INIT:
        case GROUND_STATE:{
            //ANIMATION---------------------------------------------------------------------------------------------------
            //Button direction overrides velocity, for slippery run reasons
            if (INPUT_LEFT){
                actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
            } else if (INPUT_RIGHT){
                actor_set_dir(&PLAYER, DIR_RIGHT, TRUE);
            } else if (pl_vel_x < 0) {
                actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
            } else if (pl_vel_x > 0) {
                actor_set_dir(&PLAYER, DIR_RIGHT, TRUE);
            } else {
                actor_set_anim_idle(&PLAYER);
            }

            //STATE CHANGE: Above, basic_y_col can shift to FALL_STATE.--------------------------------------------------
            //GROUND -> DASH Check
            if (dash_press && plat_dash_style != 1 && dash_ready_val == 0) {
                que_state = DASH_INIT;
                plat_state = GROUND_END;
                break;
            }
            //GROUND -> JUMP Check

            if (INPUT_PRESSED(INPUT_PLATFORM_JUMP) || jb_val != 0){
                if (nocollide == 0){
                    //Standard Jump
                    jump_type = 1;
                    que_state = JUMP_INIT;
                    plat_state = GROUND_END;
                    break;
                }
            }
            jb_val = 0;

            //GROUND -> LADDER Check
            ladder_check();

            //Check for final frame
            if (que_state != GROUND_STATE){
                plat_state = GROUND_END;
            }

            //COUNTERS
            // Counting down the drop-through floor frames
           // XX Checked in Fall, Wall, Ground, and basic_y_col, set in basic_y_col
            if (nocollide != 0){
                nocollide -= 1;
            }
        }
        break;
    //================================================================================================================
        case JUMP_INIT:
        case JUMP_STATE: {
            //ANIMATION---------------------------------------------------------------------------------------------------
            basic_anim();

            //STATE CHANGE------------------------------------------------------------------------------------------------
            //Above: JUMP-> NEUTRAL when a) player starts descending, b) player hits roof, c) player stops pressing, d)jump frames run out.
            //JUMP -> WALL check
            wall_check();

            //JUMP -> DASH check
            if(dash_press && dash_ready_val == 0){
                if(plat_dash_style != 0 || ct_val != 0){
                    que_state = DASH_INIT;
                    plat_state = JUMP_END;
                    break;
                }
            } 

            //JUMP -> JUMP check 
            if (INPUT_PRESSED(INPUT_PLATFORM_JUMP)){
                //Wall Jump
                if(wc_val != 0 && wj_val != 0){
                    jump_type = 3;
                    wj_val -= 1;
                    nocontrol_h = 5;
                    pl_vel_x = (plat_wall_kick + plat_walk_vel)*-last_wall;
                    que_state = JUMP_INIT;
                    plat_state = JUMP_END;
                }  else if (dj_val != 0){
                //Double Jump
                    jump_type = 2;
                    if (dj_val != 255){
                        dj_val -= 1;
                    }
                    jump_reduction_val += jump_reduction;
                    que_state = JUMP_INIT;
                    plat_state = JUMP_END;
                }
                break;
            } 

            //JUMP -> LADDER check
            ladder_check();


            //Check for final frame
            if (que_state != JUMP_STATE){
                plat_state = JUMP_END;
            }



            // Counting down No Control frames
            // Set in Wall and Fall states, checked in Fall and Jump states
            if (nocontrol_h != 0){
                nocontrol_h -= 1;
            }
        }
        break;
    //================================================================================================================
        case DASH_STATE: {
            //ANIMATION-------------------------------------------------------------------------------------------------------
            //Currently this animation uses the 'jump' animation is it's default. 
            basic_anim();

            //STATE CHANGE: No exits above.------------------------------------------------------------------------------------
            //DASH -> NEUTRAL Check
            //Colliding with a wall sets the currentframe to 0 above.
            if (dash_currentframe == 0){
                que_state = FALL_INIT;
            } else{
                dash_currentframe -= 1;
            }
            
            //Check for final frame
            if (que_state != DASH_STATE){
                plat_state = DASH_END;
            }

            if(plat_dash_through >= 2){
                goto gotoCounters;
            }


        
        }
        break;  
    //================================================================================================================
        case WALL_INIT:
        case WALL_STATE:{
            //ANIMATION---------------------------------------------------------------------------------------------------
            //Face away from walls
            if (col == 1){
                actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
            } else if (col == -1){
                actor_set_dir(&PLAYER, DIR_RIGHT, TRUE);
            }

            //STATE CHANGE------------------------------------------------------------------------------------------------
            //Above, basic_y_col can cause WALL -> GROUNDED.
            //Exit state as baseline
            //WALL CHECK
            wall_check();
            
            //WALL -> DASH Check
            if(dash_press && plat_dash_style != 0 && dash_ready_val == 0){
                if ((col == 1 && !INPUT_RIGHT) || (col == -1 && !INPUT_LEFT)){
                    que_state = DASH_INIT;
                    plat_state = WALL_END;
                    break;
                }
            }

            //WALL -> JUMP Check
            if ((INPUT_PRESSED(INPUT_PLATFORM_JUMP) || jb_val != 0) && wj_val != 0){
                //Wall Jump
                wj_val -= 1;
                nocontrol_h = 5;
                pl_vel_x = (plat_wall_kick + plat_walk_vel)*-last_wall;
                jump_type = 3;
                que_state = JUMP_INIT;
                plat_state = WALL_END;
                break;
            }

            //WALL -> LADDER Check
            ladder_check();

            //Check for final frame
            if (que_state != WALL_STATE){
                plat_state = WALL_END;
            }

            //COUNTERS
            // Counting down the drop-through floor frames
           // XX Checked in Fall, Wall, Ground, and basic_y_col, set in basic_y_col
            if (nocollide != 0){
                nocollide -= 1;
            }
        }
        break;
    //================================================================================================================
        case KNOCKBACK_INIT:
        case KNOCKBACK_STATE:
        if (que_state == GROUND_INIT){
            pl_vel_y = 256;
        }
        que_state = KNOCKBACK_STATE;
    }

    gotoTriggerCol:
    //FUNCTION TRIGGERS
    trigger_activate_at_intersection(&PLAYER.bounds, &PLAYER.pos, INPUT_UP_PRESSED);

    gotoCounters:
    //COUNTERS===============================================================
    // Counting down until dashing is ready again
    // XX Set in dash Init and checked in wall, fall, ground, and jump states
    if (dash_ready_val != 0){
        dash_ready_val -=1;
    }

    //Counting down from the max double-tap time (left is -15, right is +15)
    if (tap_val > 0){
        tap_val -= 1;
    } else if (tap_val < 0){
        tap_val += 1;
    }

    //Hone Camera after the player has dashed
    if (camera_deadzone_x > plat_camera_deadzone_x){
        camera_deadzone_x -= 1;
    }

    //State-Based Events


    //script_execute(BANK(test_symbol0), test_symbol0, 0, 0);
    //script_event_t * event = &state_events[plat_state];
    /*if(event->script_bank == test){
        PLAYER.pos.x += 100;
        //
    }*/

    if(state_events[plat_state].script_addr != 0){
        script_execute(state_events[plat_state].script_bank, state_events[plat_state].script_addr, 0, 0);
    }
}


void basic_anim(void) BANKED{
    //This animation is currently shared by jumping, dashing, and falling. Dashing doesn't need this complexity though.
    //Here velocity overrides direction. Whereas on the ground it is the reverse. 
    if(plat_turn_control){
        if (INPUT_LEFT){
            PLAYER.dir = DIR_LEFT;
        } else if (INPUT_RIGHT){
            PLAYER.dir = DIR_RIGHT;
        } else if (pl_vel_x < 0) {
            PLAYER.dir = DIR_LEFT;
        } else if (pl_vel_x > 0) {
            PLAYER.dir = DIR_RIGHT;
        }
    }

    if (PLAYER.dir == DIR_LEFT){
        actor_set_anim(&PLAYER, ANIM_JUMP_LEFT);
    } else {
        actor_set_anim(&PLAYER, ANIM_JUMP_RIGHT);
    }
}

void wall_check(void) BANKED {
    if(col != 0 && pl_vel_y >= 0 && plat_wall_slide){
        if (que_state != WALL_STATE ){
            que_state = WALL_INIT;
        }
    } else if (que_state == WALL_STATE){
        que_state = FALL_INIT;
    }
}

void ladder_check(void) BANKED {
    UBYTE p_half_width = (PLAYER.bounds.right - PLAYER.bounds.left) >> 1;
    if (INPUT_UP || INPUT_DOWN) {
        // Grab upwards ladder
        UBYTE tile_x_mid = ((PLAYER.pos.x >> 4) + PLAYER.bounds.left + p_half_width) >> 3;
        UBYTE tile_y = ((PLAYER.pos.y >> 4) + PLAYER.bounds.top + 1) >> 3;
        if (IS_LADDER(tile_at(tile_x_mid, tile_y))) {
            PLAYER.pos.x = (((tile_x_mid << 3) + 4 - (PLAYER.bounds.left + p_half_width) << 4));
            que_state = LADDER_INIT;
            pl_vel_x = 0;
        }
    } 
}

void ladder_switch(void) BANKED{
     //For positioning the player in the middle of the ladder
    UBYTE p_half_width = (PLAYER.bounds.right - PLAYER.bounds.left) >> 1;
    UBYTE tile_x_mid = ((PLAYER.pos.x >> 4) + PLAYER.bounds.left + p_half_width) >> 3; 
    pl_vel_y = 0;
    if (INPUT_UP) {
        // Climb laddder
        UBYTE tile_y = ((PLAYER.pos.y >> 4) + PLAYER.bounds.top + 1) >> 3;
        //Check if the tile above the player is a ladder tile. If so add ladder velocity
        if (IS_LADDER(tile_at(tile_x_mid, tile_y))) {
            pl_vel_y = -plat_climb_vel;
        }
    } else if (INPUT_DOWN) {
        // Descend ladder
        UBYTE tile_y = ((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom + 1) >> 3;
        if (IS_LADDER(tile_at(tile_x_mid, tile_y))) {
            pl_vel_y = plat_climb_vel;
        }
    } else if (INPUT_LEFT) {
        que_state = FALL_INIT; //Assume we're going to leave the ladder state, 
        // Check if able to leave ladder on left
        UBYTE tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
        UBYTE tile_end   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) + 1;
        while (tile_start != tile_end) {
            if (tile_at(tile_x_mid - 1, tile_start) & COLLISION_RIGHT) {
                que_state = LADDER_STATE; //If there is a wall, stay on the ladder.
                break;
            }
            tile_start++;
        }            
    } else if (INPUT_RIGHT) {
        que_state = FALL_INIT;
        // Check if able to leave ladder on right
        UBYTE tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
        UBYTE tile_end   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) + 1;
        while (tile_start != tile_end) {
            if (tile_at(tile_x_mid + 1, tile_start) & COLLISION_LEFT) {
                que_state = LADDER_STATE;
                break;
            }
            tile_start++;
        }
    }
    PLAYER.pos.y += (pl_vel_y >> 8);

    //Animation----------------------------------------------------------------------------------------------------
    actor_set_anim(&PLAYER, ANIM_CLIMB);
    if (pl_vel_y == 0) {
        actor_stop_anim(&PLAYER);
    }

    //State Change-------------------------------------------------------------------------------------------------
    //Collision logic provides options for exiting to Neutral

    //Above is the default GBStudio setup. However it seems worth adding a jump-from-ladder option, at the very least to drop down.
    if (INPUT_PRESSED(INPUT_PLATFORM_JUMP)){
        que_state = FALL_INIT;
    }
    //Check for final frame
    if (que_state != LADDER_STATE){
        plat_state = LADDER_END;
    }
}

void dash_init_switch(void) BANKED{
    WORD new_x;
    //If the player is pressing a direction (but not facing a direction, ie on a wall or on a changed frame)
    if (INPUT_RIGHT){
        PLAYER.dir = DIR_RIGHT;
    }
    else if(INPUT_LEFT){
        PLAYER.dir = DIR_LEFT;
    }

    //Set new_x be the final destination of the dash (ie. the distance covered by all of the dash frames combined)
    if (PLAYER.dir == DIR_RIGHT){
        new_x = PLAYER.pos.x + (dash_dist*plat_dash_frames);
    }
    else{
        new_x = PLAYER.pos.x + (-dash_dist*plat_dash_frames);
    }

    //Dash through walls
    if(plat_dash_through == 3 && plat_dash_momentum < 2){
        dash_end_clear = true;                              //Assume that the landing spot is clear, and disable if we collide below
        UBYTE tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
        UBYTE tile_end   = (((PLAYER.pos.y >> 4) + PLAYER.bounds.bottom) >> 3) + 1;     

        //Do a collision check at the final landing spot (but not all the steps in-between.)
        if (PLAYER.dir == DIR_RIGHT){
            //Don't dash off the screen to the right
            if (PLAYER.pos.x + (PLAYER.bounds.right <<4) + (dash_dist*(plat_dash_frames)) > (image_width -16) << 4){   
                dash_end_clear = false;                                     
            } else {
                UBYTE tile_xr = (((new_x >> 4) + PLAYER.bounds.right) >> 3) +1;  
                UBYTE tile_xl = ((new_x >> 4) + PLAYER.bounds.left) >> 3;   
                while (tile_xl != tile_xr){                                             //This checks all the tiles between the left bounds and the right bounds
                    while (tile_start != tile_end) {                                    //This checks all the tiles that the character occupies in height
                        if (tile_at(tile_xl, tile_start) & COLLISION_ALL) {
                                dash_end_clear = false;
                                goto initDash;                                          //Gotos are still good for breaking embedded loops.
                        }
                        tile_start++;
                    }
                    tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);   //Reset the height after each loop
                    tile_xl++;
                }
            }
        } else if(PLAYER.dir == DIR_LEFT) {
            //Don't dash off the screen to the left
            if (PLAYER.pos.x <= ((dash_dist*plat_dash_frames)+(PLAYER.bounds.left << 4))+(8<<4)){
                dash_end_clear = false;         //To get around unsigned position, test if the player's current position is less than the total dist.
            } else {
                UBYTE tile_xl = ((new_x >> 4) + PLAYER.bounds.left) >> 3;
                UBYTE tile_xr = (((new_x >> 4) + PLAYER.bounds.right) >> 3) +1;  

                while (tile_xl != tile_xr){   
                    while (tile_start != tile_end) {
                        if (tile_at(tile_xl, tile_start) & COLLISION_ALL) {
                                dash_end_clear = false;
                                goto initDash;
                        }
                        tile_start++;
                    }
                    tile_start = (((PLAYER.pos.y >> 4) + PLAYER.bounds.top)    >> 3);
                    tile_xl++;
                }
            }
        }
    }
    initDash:
    actor_attached = FALSE;
    camera_deadzone_x = plat_dash_deadzone;
    dash_ready_val = plat_dash_ready_max + plat_dash_frames;
    if(plat_dash_momentum < 2){
        pl_vel_y = 0;
    }
    dash_currentframe = plat_dash_frames;
    tap_val = 0;
    jump_type = 0;
    run_stage = 0;
    que_state = DASH_STATE;

}

UBYTE drop_press(void) BANKED{
    switch(plat_drop_through){
        case 1:
        if(INPUT_DOWN){
            return 1;
        }
        return 0;
        case 2:
        if (INPUT_PRESSED(INPUT_DOWN)){
            return 1;
        }
        return 0;
        case 3:
        if (INPUT_DOWN && INPUT_PLATFORM_JUMP){
            return 1;
        }
        return 0;
        case 4:
        if ((INPUT_PRESSED(INPUT_DOWN) && INPUT_PLATFORM_JUMP) || (INPUT_DOWN && INPUT_PRESSED(INPUT_PLATFORM_JUMP))){
            return 1;
        }
        return 0;
    }
    return 0;
}
//UBYTE slot, UBYTE bank, UBYTE * pc
//                      
void assign_state_script(SCRIPT_CTX * THIS) OLDCALL BANKED {
    UWORD *slot = VM_REF_TO_PTR(FN_ARG2);
    UBYTE *bank = VM_REF_TO_PTR(FN_ARG1);
    UBYTE **ptr = VM_REF_TO_PTR(FN_ARG0);
    state_events[*slot].script_bank = *bank;
    state_events[*slot].script_addr = *ptr;
}

void clear_state_script(SCRIPT_CTX * THIS) OLDCALL BANKED {
    UWORD *slot = VM_REF_TO_PTR(FN_ARG0);
    state_events[*slot].script_bank = NULL;
    state_events[*slot].script_addr = NULL;


}