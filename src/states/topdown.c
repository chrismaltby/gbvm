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
        PLAYER.def.pos.x = SUBPX_SNAP_TILE16(PLAYER.def.pos.x);
        PLAYER.def.pos.y = SUBPX_SNAP_TILE16(PLAYER.def.pos.y) + TILE_TO_SUBPX(1);
    } else {
        PLAYER.def.pos.x = SUBPX_SNAP_TILE(PLAYER.def.pos.x);
        PLAYER.def.pos.y = SUBPX_SNAP_TILE(PLAYER.def.pos.y);
    }
}

void topdown_update(void) BANKED {
    actor_t *hit_actor;
    UBYTE tile_start, tile_end;
    direction_e new_dir = DIR_NONE;

    // Is player on an 8x8px tile?
    if ((topdown_grid == 16 && ON_16PX_GRID(PLAYER.def.pos)) ||
        (topdown_grid == 8 && ON_8PX_GRID(PLAYER.def.pos))) {
        // Player landed on an tile
        // so stop movement for now
        player_moving = FALSE;

        // Check for trigger collisions
        if (trigger_activate_at_intersection(&PLAYER.def.bounds, &PLAYER.def.pos, FALSE)) {
            // Landed on a trigger
            return;
        }

        // Check input to set player movement
        if (INPUT_RECENT_LEFT) {
            player_moving = TRUE;
            new_dir = DIR_LEFT;

            // Check for collisions to left of player
            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom) + 1;
            UBYTE tile_x = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.left);
            while (tile_start != tile_end) {
                if (tile_at(tile_x - 1, tile_start) & COLLISION_RIGHT) {
                    player_moving = FALSE;
                    break;
                }
                tile_start++;
            }
        } else if (INPUT_RECENT_RIGHT) {
            player_moving = TRUE;
            new_dir = DIR_RIGHT;

            // Check for collisions to right of player
            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom) + 1;
            UBYTE tile_x = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.right);
            while (tile_start != tile_end) {
                if (tile_at(tile_x + 1, tile_start) & COLLISION_LEFT) {
                    player_moving = FALSE;
                    break;
                }
                tile_start++;
            }
        } else if (INPUT_RECENT_UP) {
            player_moving = TRUE;
            new_dir = DIR_UP;

            // Check for collisions below player
            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.left);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.right) + 1;
            UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top);
            while (tile_start != tile_end) {
                if (tile_at(tile_start, tile_y - 1) & COLLISION_BOTTOM) {
                    player_moving = FALSE;
                    break;
                }
                tile_start++;
            }
        } else if (INPUT_RECENT_DOWN) {
            player_moving = TRUE;
            new_dir = DIR_DOWN;

            // Check for collisions below player
            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.left);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.right) + 1;
            UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom);
            while (tile_start != tile_end) {
                if (tile_at(tile_start, tile_y + 1) & COLLISION_TOP) {
                    player_moving = FALSE;
                    break;
                }
                tile_start++;
            }
        }

        // Update direction animation
        if (new_dir != DIR_NONE) {
            actor_set_dir(&PLAYER, new_dir, player_moving);
        } else {
            actor_set_anim_idle(&PLAYER);
        }

        if (IS_FRAME_ODD) {
            // Check for actor overlap
            hit_actor = actor_overlapping_player(FALSE);
            if (hit_actor != NULL && hit_actor->def.collision_group) {
                player_register_collision_with(hit_actor);
            }
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
            hit_actor = actor_in_front_of_player(topdown_grid, TRUE);
            if (hit_actor != NULL && !hit_actor->def.collision_group) {
                actor_set_dir(hit_actor, FLIPPED_DIR(PLAYER.def.dir), FALSE);
                player_moving = FALSE;
                if (hit_actor->def.script.bank) {
                    script_execute(hit_actor->def.script.bank, hit_actor->def.script.ptr, 0, 1, 0);
                }
            }
        }
    }

    if (player_moving) point_translate_dir(&PLAYER.def.pos, PLAYER.def.dir, PLAYER.def.move_speed);
}
