#pragma bank 255

#include "data/states_defines.h"
#include "states/topdown.h"

#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "data_manager.h"
#include "game_time.h"
#include "input.h"
#include "trigger.h"
#include "math.h"
#include "vm.h"

#ifndef INPUT_TOPDOWN_INTERACT
#define INPUT_TOPDOWN_INTERACT INPUT_A
#endif

UBYTE topdown_grid;

void topdown_init(void) BANKED {
    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = 0;
    camera_deadzone_y = 0;

    if (topdown_grid == 16) {
        // Snap to 16px grid
        PLAYER.pos.x = SUBPX_SNAP_TILE16(PLAYER.pos.x);
        PLAYER.pos.y = SUBPX_SNAP_TILE16(PLAYER.pos.y) + TILE_TO_SUBPX(1);
    } else {
        PLAYER.pos.x = SUBPX_SNAP_TILE(PLAYER.pos.x);
        PLAYER.pos.y = SUBPX_SNAP_TILE(PLAYER.pos.y);
    }
}

void topdown_update(void) BANKED {
    actor_t *hit_actor;
    UBYTE tile_start, tile_end;
    direction_e new_dir = DIR_NONE;
    static UWORD max_pos = 0;

    // Is player on an 8x8px tile?
    if ((topdown_grid == 16 && ON_16PX_GRID(PLAYER.pos)) ||
        (topdown_grid == 8 && ON_8PX_GRID(PLAYER.pos))) {
        // Player landed on an tile
        // so stop movement for now
        player_moving = FALSE;

        // Check for trigger collisions
        if (trigger_activate_at_intersection(&PLAYER.bounds, &PLAYER.pos, FALSE)) {
            // Landed on a trigger
            return;
        }

        // Check input to set player movement
        if (INPUT_RECENT_LEFT) {
            player_moving = TRUE;
            new_dir = DIR_LEFT;

            // Check for collisions to left of player
            tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
            tile_end   = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
            UBYTE tile_x = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
            if (tile_col_test_range_y(COLLISION_RIGHT, tile_x - 1, tile_start, tile_end)) {
                player_moving = FALSE;
            }
        } else if (INPUT_RECENT_RIGHT) {
            player_moving = TRUE;
            new_dir = DIR_RIGHT;

            // Check for collisions to right of player
            tile_start = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
            tile_end   = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
            UBYTE tile_x = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);
            if (tile_col_test_range_y(COLLISION_LEFT, tile_x + 1, tile_start, tile_end)) {
                player_moving = FALSE;
            }
        } else if (INPUT_RECENT_UP) {
            player_moving = TRUE;
            new_dir = DIR_UP;

            // Check for collisions below player
            tile_start = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
            tile_end   = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);
            UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.top);
            if (tile_col_test_range_x(COLLISION_BOTTOM, tile_y - 1, tile_start, tile_end)) {
                player_moving = FALSE;
            }
        } else if (INPUT_RECENT_DOWN) {
            player_moving = TRUE;
            new_dir = DIR_DOWN;

            // Check for collisions below player
            tile_start = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.left);
            tile_end   = SUBPX_TO_TILE(PLAYER.pos.x + PLAYER.bounds.right);
            UBYTE tile_y = SUBPX_TO_TILE(PLAYER.pos.y + PLAYER.bounds.bottom);
            if (tile_col_test_range_x(COLLISION_TOP, tile_y + 1, tile_start, tile_end)) {
                player_moving = FALSE;
            }
        }

        // Update direction animation
        if (new_dir != DIR_NONE) {
            actor_set_dir(&PLAYER, new_dir, player_moving);
        } else {
            actor_set_anim_idle(&PLAYER);
        }

        // Check for actor overlap
        hit_actor = actor_overlapping_player();
        if (hit_actor != NULL && (hit_actor->collision_group & COLLISION_GROUP_MASK)) {
            player_register_collision_with(hit_actor);
        }

        // Check if walked in to actor
        if (player_moving) {
            hit_actor = actor_in_front_of_player(topdown_grid, FALSE);
            if (hit_actor != NULL) {
                player_register_collision_with(hit_actor);
                actor_stop_anim(&PLAYER);
                player_moving = FALSE;
            }
        }

        if (INPUT_PRESSED(INPUT_TOPDOWN_INTERACT)) {
            hit_actor = actor_with_script_in_front_of_player(topdown_grid);
            if (hit_actor != NULL && !(hit_actor->collision_group & COLLISION_GROUP_MASK)) {
                actor_set_dir(hit_actor, FLIPPED_DIR(PLAYER.dir), FALSE);
                player_moving = FALSE;
                if (hit_actor->script.bank) {
                    script_execute(hit_actor->script.bank, hit_actor->script.ptr, 0, 1, 0);
                }
            }
        }

        // Calculate max position for movement clamping
        UBYTE tile_offset = (topdown_grid == 16) ? 2 : 1;
        if (PLAYER.dir == DIR_RIGHT) {
            max_pos = TILE_TO_SUBPX(SUBPX_TO_TILE(PLAYER.pos.x) + tile_offset);
        } else if (PLAYER.dir == DIR_LEFT) {
            max_pos = TILE_TO_SUBPX(SUBPX_TO_TILE(PLAYER.pos.x) - tile_offset);
        } else if (PLAYER.dir == DIR_DOWN) {
            max_pos = TILE_TO_SUBPX(SUBPX_TO_TILE(PLAYER.pos.y) + tile_offset);
        } else if (PLAYER.dir == DIR_UP) {
            max_pos = TILE_TO_SUBPX(SUBPX_TO_TILE(PLAYER.pos.y) - tile_offset);
        }
    }

    if (player_moving) {
        point_translate_dir(&PLAYER.pos, PLAYER.dir, PLAYER.move_speed);

        // Clamp to grid
        if (PLAYER.dir == DIR_RIGHT) {
            if (PLAYER.pos.x > max_pos) {
                PLAYER.pos.x = max_pos;
            }
        } else if (PLAYER.dir == DIR_LEFT) {
            if (PLAYER.pos.x < max_pos) {
                PLAYER.pos.x = max_pos;
            } else if (max_pos == 0 && PLAYER.pos.x >= (UWORD_MAX - PLAYER.move_speed)) {
                PLAYER.pos.x = 0;
            }
        } else if (PLAYER.dir == DIR_DOWN) {
            if (PLAYER.pos.y > max_pos) {
                PLAYER.pos.y = max_pos;
            }
        } else if (PLAYER.dir == DIR_UP) {
            if (PLAYER.pos.y < max_pos) {
                PLAYER.pos.y = max_pos;
            } else if (max_pos == 0 && PLAYER.pos.y >= (UWORD_MAX - PLAYER.move_speed)) {
                PLAYER.pos.y = 0;
            }
        }
    }
}
