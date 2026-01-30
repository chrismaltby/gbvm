#pragma bank 255

#include "data/states_defines.h"
#include "states/shmup.h"

#include "actor.h"
#include "camera.h"
#include "scroll.h"
#include "collision.h"
#include "data_manager.h"
#include "game_time.h"
#include "input.h"
#include "trigger.h"
#include "vm.h"

// Feature Flags --------------------------------------------------------------
// Optional feature flags, set in 'state_defines.h'

// End of Feature Flags -------------------------------------------------------

// Constants ------------------------------------------------------------------

#define ON_PLAYER_COLLISION 0
#define ON_SCREEN_ENTER 1

#ifndef SHOOTER_TRIGGER_ACTIVATION
#define SHOOTER_TRIGGER_ACTIVATION ON_PLAYER_COLLISION
#endif

#define MOVEMENT_TYPE_FREE 0
#define MOVEMENT_TYPE_LOCK_PERPENDICULAR 1

#ifndef SHOOTER_MOVEMENT_TYPE
#define SHOOTER_MOVEMENT_TYPE MOVEMENT_TYPE_FREE
#endif

#ifndef SHOOTER_WALL_COLLISION_GROUP
#define SHOOTER_WALL_COLLISION_GROUP COLLISION_GROUP_NONE
#endif

// End of Constants -----------------------------------------------------------

// Macros ---------------------------------------------------------------------

#if SHOOTER_MOVEMENT_TYPE == MOVEMENT_TYPE_FREE
  #define IF_FREE_MOVEMENT(code) code
#else
  #define IF_FREE_MOVEMENT(code)
#endif

// End of Macros --------------------------------------------------------------

// Engine Fields --------------------------------------------------------------

UINT8 shooter_scroll_speed;

// End of Engine Fields -------------------------------------------------------

// Runtime State --------------------------------------------------------------

UBYTE shooter_reached_end;
UWORD shooter_dest;
direction_e shooter_direction;

#if SHOOTER_TRIGGER_ACTIVATION == ON_SCREEN_ENTER
    upoint16_t scroll_pos;
    rect16_t scroll_trigger_area = {
        .left = 0,
        .right = PX_TO_SUBPX(SCREEN_WIDTH),
        .top = 0,
        .bottom = PX_TO_SUBPX(SCREEN_HEIGHT)
    };
#endif

// End of Runtime State -------------------------------------------------------

// Function Definitions -------------------------------------------------------

// Adds a signed offset to an unsigned 16-bit value with clamping
inline UWORD add_signed_clamped_u16(UWORD value, WORD offset, UWORD min, UWORD max) {
    UWORD result;

    if (offset < 0) {
        result = value + (UWORD)(-offset);
        if (result < value) result = max;
    } else {
        result = value - (UWORD)offset;
        if (result > value) result = min;
    }

    if (result < min) result = min;
    else if (result > max) result = max;

    return result;
}

// End of Function Definitions ------------------------------------------------

void shmup_init(void) BANKED {
    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = 0;
    camera_deadzone_y = 0;
    
    shooter_direction = PLAYER.dir;

    if (shooter_direction == DIR_LEFT) {
        // Right to left scrolling
        camera_offset_x = (SHOOTER_MOVEMENT_TYPE == MOVEMENT_TYPE_LOCK_PERPENDICULAR ? 64 : camera_offset_x);
        camera_deadzone_y = 16;
        shooter_dest = PX_TO_SUBPX(SCREEN_WIDTH_HALF);
        IF_FREE_MOVEMENT(camera_settings &= ~CAMERA_LOCK_X_FLAG);
    } else if (shooter_direction == DIR_RIGHT) {
        // Left to right scrolling
        camera_offset_x = (SHOOTER_MOVEMENT_TYPE == MOVEMENT_TYPE_LOCK_PERPENDICULAR ? -64 : camera_offset_x);
        camera_deadzone_y = 16;
        shooter_dest = image_width_subpx - PX_TO_SUBPX(SCREEN_WIDTH_HALF);
        IF_FREE_MOVEMENT(camera_settings &= ~CAMERA_LOCK_X_FLAG);
    } else if (shooter_direction == DIR_UP) {
        // Bottom to top scrolling
        camera_offset_y = (SHOOTER_MOVEMENT_TYPE == MOVEMENT_TYPE_LOCK_PERPENDICULAR ? 64 : camera_offset_y);
        camera_deadzone_x = 16;
        shooter_dest = PX_TO_SUBPX(SCREEN_HEIGHT_HALF);
        IF_FREE_MOVEMENT(camera_settings &= ~CAMERA_LOCK_Y_FLAG);
    } else {
        // Top to bottom scrolling
        camera_offset_y = (SHOOTER_MOVEMENT_TYPE == MOVEMENT_TYPE_LOCK_PERPENDICULAR ? -48 : camera_offset_y);
        camera_deadzone_x = 16;
        shooter_dest = image_height_subpx - PX_TO_SUBPX(SCREEN_HEIGHT_HALF);
        IF_FREE_MOVEMENT(camera_settings &= ~CAMERA_LOCK_Y_FLAG);
    }

    shooter_reached_end = FALSE;
    
    // Initialize camera position for unlocked movement
    IF_FREE_MOVEMENT({
        camera_x = add_signed_clamped_u16(PLAYER.pos.x, PX_TO_SUBPX(camera_offset_x),
            PX_TO_SUBPX(SCREEN_WIDTH_HALF),
            image_width_subpx - PX_TO_SUBPX(SCREEN_WIDTH_HALF)
        );
        camera_y = add_signed_clamped_u16(PLAYER.pos.y, PX_TO_SUBPX(camera_offset_y),
            PX_TO_SUBPX(SCREEN_HEIGHT_HALF),
            image_height_subpx - PX_TO_SUBPX(SCREEN_HEIGHT_HALF)
        );
    });
}

void shmup_update(void) BANKED {

    actor_t *hit_actor;
    UBYTE tile_start, tile_end;
    direction_e new_dir = DIR_NONE;
    UBYTE angle;

    player_moving = FALSE;
    new_dir = shooter_direction;
    angle = ANGLE_0DEG;

    // Determine movement input
#if SHOOTER_MOVEMENT_TYPE == MOVEMENT_TYPE_FREE
    UBYTE up = INPUT_UP;
    UBYTE down = INPUT_DOWN;
    UBYTE left = INPUT_LEFT;
    UBYTE right = INPUT_RIGHT;

    if (left || right || up || down) {
        player_moving = TRUE;

        if (left) {
            if (up) {
                angle = ANGLE_315DEG;
            } else if (down) {
                angle = ANGLE_225DEG;
            } else {
                angle = ANGLE_270DEG;
            }
        } else if (right) {
            if (up) {
                angle = ANGLE_45DEG;
            } else if (down) {
                angle = ANGLE_135DEG;
            } else {
                angle = ANGLE_90DEG;
            }
        } else if (up) {
            angle = ANGLE_0DEG;
        } else if (down) {
            angle = ANGLE_180DEG;
        }

        if (IS_DIR_HORIZONTAL(shooter_direction)) {
            if (up) {
                new_dir = DIR_UP;
            } else if (down) {
                new_dir = DIR_DOWN;
            } else {
                new_dir = shooter_direction;
            }
        } else {
            if (left) {
                new_dir = DIR_LEFT;
            } else if (right) {
                new_dir = DIR_RIGHT;
            } else {
                new_dir = shooter_direction;
            }
        }
    } else {
        new_dir = shooter_direction;
        angle = ANGLE_0DEG;
    }
#elif SHOOTER_MOVEMENT_TYPE == MOVEMENT_TYPE_LOCK_PERPENDICULAR
    if (IS_DIR_HORIZONTAL(shooter_direction)) {
        UBYTE up = INPUT_UP;
        UBYTE down = INPUT_DOWN;
        if (up || down) {
            player_moving = TRUE;
            if (up) {
                angle = ANGLE_0DEG;
                new_dir = DIR_UP;
            } else if (down) {
                angle = ANGLE_180DEG;
                new_dir = DIR_DOWN;
            }
        } else {
            new_dir = shooter_direction;
            angle = ANGLE_0DEG;
        }
    } else {
        UBYTE left = INPUT_LEFT;
        UBYTE right = INPUT_RIGHT;
        if (left || right) {
            player_moving = TRUE;
            if (left) {
                angle = ANGLE_270DEG;
                new_dir = DIR_LEFT;
            } else if (right) {
                angle = ANGLE_90DEG;
                new_dir = DIR_RIGHT;
            }
        } else {
            new_dir = shooter_direction;
            angle = ANGLE_0DEG;
        }
    }
#endif

    // Set animation if direction has changed
    if (new_dir != PLAYER.dir) {
        actor_set_dir(&PLAYER, new_dir, player_moving);
    }

    UBYTE tile = 0;

    // Move player from input
    if (player_moving) {
        upoint_translate_angle(&(PLAYER.pos), angle, PLAYER.move_speed);

        // Check for tile collisions
        if (angle != ANGLE_90DEG && angle != ANGLE_270DEG) { // Moved vertically
            // Step Y
            tile_start = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
            tile_end   = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);
            if (angle > ANGLE_90DEG && angle < ANGLE_270DEG) { // Moving down
                UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
                tile = tile_col_test_range_x(COLLISION_TOP, tile_y, tile_start, tile_end);
                if (tile) {
                    PLAYER.pos.y = TILE_TO_SUBPX(tile_y) - EXCLUSIVE_OFFSET(PLAYER.bounds.bottom);
                }
            } else { // Moving up
                UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
                tile = tile_col_test_range_x(COLLISION_BOTTOM, tile_y, tile_start, tile_end);
                if (tile) {
                    PLAYER.pos.y = TILE_TO_SUBPX(tile_y + 1) - PLAYER.bounds.top;
                }
            }
        }
        
        if (angle != ANGLE_0DEG && angle != ANGLE_180DEG) { // Moved horizontally
            // Step X
            tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
            tile_end   = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
            if (angle > ANGLE_0DEG && angle < ANGLE_180DEG) { // Moving right
                UBYTE tile_x = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);
                tile = tile_col_test_range_y(COLLISION_LEFT, tile_x, tile_start, tile_end);
                if (tile) {
                    PLAYER.pos.x = TILE_TO_SUBPX(tile_x) - EXCLUSIVE_OFFSET(PLAYER.bounds.right);
                }
            } else { // Moving left
                UBYTE tile_x = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
                tile = tile_col_test_range_y(COLLISION_RIGHT, tile_x, tile_start, tile_end);
                if (tile) {
                    PLAYER.pos.x = TILE_TO_SUBPX(tile_x + 1) - PLAYER.bounds.left;
                }
            }
        }

    }

    // Auto scroll background
    if (!shooter_reached_end) {
        if (shooter_direction == DIR_LEFT) {
            IF_FREE_MOVEMENT(camera_x -= shooter_scroll_speed);
            PLAYER.pos.x -= shooter_scroll_speed;
            if (camera_x < shooter_dest) {
                shooter_reached_end = TRUE;
                camera_x = shooter_dest;
            }
            // Sync camera subpixels with player to prevent visual jitter
            // (only when player isn't moving horizontally)
            IF_FREE_MOVEMENT({
                if (!player_moving || angle == ANGLE_0DEG || angle == ANGLE_180DEG) {
                    camera_x = SUBPX_SNAP_PX(camera_x) | SUBPX_PX_REMAINDER(PLAYER.pos.x);
                }
            })
        } else if (shooter_direction == DIR_RIGHT) {
            IF_FREE_MOVEMENT(camera_x += shooter_scroll_speed);
            PLAYER.pos.x += shooter_scroll_speed;
            if (camera_x > shooter_dest) {
                shooter_reached_end = TRUE;
                camera_x = shooter_dest;
            }
            // Sync camera subpixels with player to prevent visual jitter
            // (only when player isn't moving horizontally)
            IF_FREE_MOVEMENT({
                if (!player_moving || angle == ANGLE_0DEG || angle == ANGLE_180DEG) {
                    camera_x = SUBPX_SNAP_PX(camera_x) | SUBPX_PX_REMAINDER(PLAYER.pos.x);
                }
            })
        } else if (shooter_direction == DIR_UP) {
            IF_FREE_MOVEMENT(camera_y -= shooter_scroll_speed);
            PLAYER.pos.y -= shooter_scroll_speed;
            if (camera_y < shooter_dest) {
                shooter_reached_end = TRUE;
                camera_y = shooter_dest;
            }
            // Sync camera subpixels with player to prevent visual jitter
            // (only when player isn't moving vertically)
            IF_FREE_MOVEMENT({
                if (!player_moving || angle == ANGLE_90DEG || angle == ANGLE_270DEG) {
                    camera_y = SUBPX_SNAP_PX(camera_y) | SUBPX_PX_REMAINDER(PLAYER.pos.y);
                }
            })
        } else {
            IF_FREE_MOVEMENT(camera_y += shooter_scroll_speed);
            PLAYER.pos.y += shooter_scroll_speed;
            if (camera_y > shooter_dest) {
                shooter_reached_end = TRUE;
                camera_y = shooter_dest;
            }
            // Sync camera subpixels with player to prevent visual jitter
            // (only when player isn't moving vertically)
            IF_FREE_MOVEMENT({
                if (!player_moving || angle == ANGLE_90DEG || angle == ANGLE_270DEG) {
                    camera_y = SUBPX_SNAP_PX(camera_y) | SUBPX_PX_REMAINDER(PLAYER.pos.y);
                }
            })
        }
    }

    // Check for collisions caused by auto-scroll
    if (player_iframes == 0 && (!tile || tile_hit_x >= image_tile_width || tile_hit_y >= image_tile_height)) {
        if (IS_DIR_HORIZONTAL(shooter_direction)) {
            tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
            tile_end   = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
            if (shooter_direction == DIR_RIGHT) {
                UBYTE tile_x = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);
                tile = tile_col_test_range_y(COLLISION_LEFT, tile_x, tile_start, tile_end);
                IF_FREE_MOVEMENT({
                    if (tile) {
                        PLAYER.pos.x = TILE_TO_SUBPX(tile_x) - EXCLUSIVE_OFFSET(PLAYER.bounds.right);
                    }
                })
            } else { // DIR_LEFT
                UBYTE tile_x = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
                tile = tile_col_test_range_y(COLLISION_RIGHT, tile_x, tile_start, tile_end);
                IF_FREE_MOVEMENT({
                    if (tile) {
                        PLAYER.pos.x = TILE_TO_SUBPX(tile_x + 1) - PLAYER.bounds.left;
                    }
                })
            }
        } else {
            tile_start = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
            tile_end   = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);
            if (shooter_direction == DIR_DOWN) {
                UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
                tile = tile_col_test_range_x(COLLISION_TOP, tile_y, tile_start, tile_end);
                IF_FREE_MOVEMENT({
                    if (tile) {
                        PLAYER.pos.y = TILE_TO_SUBPX(tile_y) - EXCLUSIVE_OFFSET(PLAYER.bounds.bottom);
                    }
                })
            } else { // DIR_UP
                UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
                tile = tile_col_test_range_x(COLLISION_BOTTOM, tile_y, tile_start, tile_end);
                IF_FREE_MOVEMENT({
                    if (tile) {
                        PLAYER.pos.y = TILE_TO_SUBPX(tile_y + 1) - PLAYER.bounds.top;
                    }
                })
            }
        }
    }    

    IF_FREE_MOVEMENT({
        // Keep player within screen bounds
        if (IS_DIR_HORIZONTAL(shooter_direction)) {
            // Clamp X
            UWORD player_left = PLAYER.pos.x + PLAYER.bounds.left + PX_TO_SUBPX(SCREEN_WIDTH_HALF);
            UBYTE wrapped_left = (player_left < PLAYER.pos.x);

            UWORD player_right = PLAYER.pos.x + PLAYER.bounds.right;
            UBYTE wrapped_right = (player_right < PLAYER.pos.x);

            if (!wrapped_left && (player_left < camera_x)) {
                PLAYER.pos.x = camera_x - PLAYER.bounds.left - PX_TO_SUBPX(SCREEN_WIDTH_HALF);
            } else if (!wrapped_right && (player_right > camera_x + PX_TO_SUBPX(SCREEN_WIDTH_HALF))) {
                PLAYER.pos.x = camera_x - PLAYER.bounds.right + PX_TO_SUBPX(SCREEN_WIDTH_HALF);
            }
        } else {
            // Clamp Y
            UWORD player_top = PLAYER.pos.y + PLAYER.bounds.top + PX_TO_SUBPX(SCREEN_HEIGHT_HALF);
            UBYTE wrapped_top = (player_top < PLAYER.pos.y);

            UWORD player_bottom = PLAYER.pos.y + PLAYER.bounds.bottom;
            UBYTE wrapped_bottom = (player_bottom < PLAYER.pos.y);

            if (!wrapped_top && (player_top < camera_y)) {
                PLAYER.pos.y = camera_y - PLAYER.bounds.top - PX_TO_SUBPX(SCREEN_HEIGHT_HALF);
            } else if (!wrapped_bottom && (player_bottom > camera_y + PX_TO_SUBPX(SCREEN_HEIGHT_HALF))) {
                PLAYER.pos.y = camera_y - PLAYER.bounds.bottom + PX_TO_SUBPX(SCREEN_HEIGHT_HALF);
            }
        }
    })

#if SHOOTER_WALL_COLLISION_GROUP != COLLISION_GROUP_NONE
    // Collisions with tiles that aren't out of bounds trigger player hit script
    if (tile && tile_hit_x < image_tile_width && tile_hit_y < image_tile_height && player_iframes == 0 && PLAYER.script.bank) {
        player_iframes = PLAYER_HURT_IFRAMES;
        script_execute(
            PLAYER.script.bank,
            PLAYER.script.ptr, 0, 1,
            (UWORD)(SHOOTER_WALL_COLLISION_GROUP)
        );
    }
#endif

    if (IS_FRAME_ODD) {
        // Check for trigger collisions on odd frames
#if SHOOTER_TRIGGER_ACTIVATION == ON_PLAYER_COLLISION
        if (trigger_activate_at_intersection(&PLAYER.bounds, &PLAYER.pos, FALSE)) {
            // Landed on a trigger
            return;
        }
#elif SHOOTER_TRIGGER_ACTIVATION == ON_SCREEN_ENTER
        scroll_pos.x = PX_TO_SUBPX(scroll_x);
        scroll_pos.y = PX_TO_SUBPX(scroll_y);

        if (trigger_activate_at_intersection(&scroll_trigger_area, &scroll_pos, FALSE)) {
            // Trigger appeared on screen edge
            return;
        }
#endif

    } else {
        // Check for actor collisions on even frames
        hit_actor = actor_overlapping_player();
        if (hit_actor != NULL && (hit_actor->collision_group & COLLISION_GROUP_MASK)) {
            player_register_collision_with(hit_actor);
        }
    }
}
