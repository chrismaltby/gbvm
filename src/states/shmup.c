#pragma bank 255

#include "data/states_defines.h"
#include "states/shmup.h"

#include "actor.h"
#include "camera.h"
#include "collision.h"
#include "data_manager.h"
#include "game_time.h"
#include "input.h"
#include "trigger.h"
#include "vm.h"

#ifndef SHOOTER_HURT_IFRAMES
#define SHOOTER_HURT_IFRAMES 10
#endif

UINT8 shooter_scroll_speed = 16;
UBYTE shooter_reached_end;
UWORD shooter_dest;
direction_e shooter_direction;

void shmup_init(void) BANKED {

    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = 0;
    camera_deadzone_y = 0;

    shooter_direction = PLAYER.def.dir;

    if (shooter_direction == DIR_LEFT) {
        // Right to left scrolling
        camera_offset_x = 48;
        shooter_dest = PX_TO_SUBPX(SCREEN_WIDTH_HALF + 48);
    } else if (shooter_direction == DIR_RIGHT) {
        // Left to right scrolling
        camera_offset_x = -64;
        shooter_dest = PX_TO_SUBPX(image_width - SCREEN_WIDTH_HALF - 64);
    } else if (shooter_direction == DIR_UP) {
        // Bottom to top scrolling
        camera_offset_y = 48;
        shooter_dest = PX_TO_SUBPX(SCREEN_WIDTH_HALF + 40);
    } else {
        // Top to bottom scrolling
        camera_offset_y = -48;
        shooter_dest = PX_TO_SUBPX(image_height - SCREEN_WIDTH_HALF - 40);
    }

    shooter_reached_end = FALSE;
}

void shmup_update(void) BANKED {
    actor_t *hit_actor;
    UBYTE tile_start, tile_end;
    direction_e new_dir = DIR_NONE;
    player_moving = FALSE;

    if (IS_DIR_HORIZONTAL(shooter_direction)) {
        if (INPUT_UP) {
            player_moving = TRUE;
            new_dir = DIR_UP;
        } else if (INPUT_DOWN) {
            player_moving = TRUE;
            new_dir = DIR_DOWN;
        } else {
            new_dir = shooter_direction;
        }
    } else {
        if (INPUT_LEFT) {
            player_moving = TRUE;
            new_dir = DIR_LEFT;
        } else if (INPUT_RIGHT) {
            player_moving = TRUE;
            new_dir = DIR_RIGHT;
        } else {
            new_dir = shooter_direction;
        }
    }

    // Set animation if direction has changed
    if (new_dir != PLAYER.def.dir) {
        actor_set_dir(&PLAYER, new_dir, player_moving);
    }

    // Move player from input
    if (player_moving) {
        point16_t new_pos;
        new_pos.x = PLAYER.def.pos.x;
        new_pos.y = PLAYER.def.pos.y;
        point_translate_dir(&new_pos, PLAYER.def.dir, PLAYER.def.move_speed);

        // Check for tile collisions
        if (IS_DIR_HORIZONTAL(shooter_direction)) {
            // Step Y
            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.left);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.right) + 1;
            if (PLAYER.def.dir == DIR_DOWN) {
                UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(new_pos.y) + PLAYER.def.bounds.bottom);
                while (tile_start != tile_end) {
                    if (tile_at(tile_start, tile_y) & COLLISION_TOP) {
                        new_pos.y = PX_TO_SUBPX(TILE_TO_PX(tile_y) - PLAYER.def.bounds.bottom) - 1;
                        break;
                    }
                    tile_start++;
                }
                PLAYER.def.pos.y = new_pos.y;
            } else {
                UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(new_pos.y) + PLAYER.def.bounds.top);
                while (tile_start != tile_end) {
                    if (tile_at(tile_start, tile_y) & COLLISION_BOTTOM) {
                        new_pos.y = PX_TO_SUBPX(TILE_TO_PX((UBYTE)(tile_y + 1)) - PLAYER.def.bounds.top) + 1;
                        break;
                    }
                    tile_start++;
                }
                PLAYER.def.pos.y = new_pos.y;
            }
        } else {
            // Step X
            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom) + 1;
            if (PLAYER.def.dir == DIR_RIGHT) {
                UBYTE tile_x = PX_TO_TILE(SUBPX_TO_PX(new_pos.x) + PLAYER.def.bounds.right);
                while (tile_start != tile_end) {
                    if (tile_at(tile_x, tile_start) & COLLISION_LEFT) {
                        new_pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x) - PLAYER.def.bounds.right) - 1;           
                        break;
                    }
                    tile_start++;
                }
                PLAYER.def.pos.x = MIN(PX_TO_SUBPX(image_width - PLAYER.def.bounds.right - 1), new_pos.x);
            } else {
                UBYTE tile_x = PX_TO_TILE(SUBPX_TO_PX(new_pos.x) + PLAYER.def.bounds.left);
                while (tile_start != tile_end) {
                    if (tile_at(tile_x, tile_start) & COLLISION_RIGHT) {
                        new_pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x + 1) - PLAYER.def.bounds.left) + 1;         
                        break;
                    }
                    tile_start++;
                }
                PLAYER.def.pos.x = MAX(0, (WORD)new_pos.x);
            }
        }
    }

    // Auto scroll background
    if (!shooter_reached_end) {
        point_translate_dir(&PLAYER.def.pos, shooter_direction, shooter_scroll_speed);

        // Check if reached end of screen
        if ((shooter_direction == DIR_RIGHT) && (PLAYER.def.pos.x > shooter_dest)) {
            shooter_reached_end = TRUE;
            PLAYER.def.pos.x = shooter_dest;
        } else if ((shooter_direction == DIR_LEFT) && (PLAYER.def.pos.x < shooter_dest)) {
            shooter_reached_end = TRUE;
            PLAYER.def.pos.x = shooter_dest;
        } else if ((shooter_direction == DIR_DOWN) && (PLAYER.def.pos.y > shooter_dest)) {
            shooter_reached_end = TRUE;
            PLAYER.def.pos.y = shooter_dest;
        } else if ((shooter_direction == DIR_UP) && (PLAYER.def.pos.y < shooter_dest)) {
            shooter_reached_end = TRUE;
            PLAYER.def.pos.y = shooter_dest;
        }
    }

    if (IS_FRAME_ODD) {
        // Check for trigger collisions
        if (trigger_activate_at_intersection(&PLAYER.def.bounds, &PLAYER.def.pos, FALSE)) {
            // Landed on a trigger
            return;
        }

        // Check for actor collisions
        hit_actor = actor_overlapping_player(FALSE);
        if (hit_actor != NULL && hit_actor->def.collision_group) {
            player_register_collision_with(hit_actor);
        } else if (INPUT_A_PRESSED) {
            if (!hit_actor) {
                hit_actor = actor_in_front_of_player(8, TRUE);
            }
            if (hit_actor && !hit_actor->def.collision_group && hit_actor->def.script.bank) {
                script_execute(hit_actor->def.script.bank, hit_actor->def.script.ptr, 0, 1, 0);
            }
        }
    }
}
