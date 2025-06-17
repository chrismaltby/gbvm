#pragma bank 255

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
#ifndef PLATFORM_CAMERA_DEADZONE_X
#define PLATFORM_CAMERA_DEADZONE_X 4
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

#define VEL_TO_SUBPX(v) ((v) >> 8)

UBYTE grounded;
UBYTE on_slope;
UBYTE slope_y;
UBYTE on_ladder;
WORD pl_vel_x;
WORD pl_vel_y;
WORD plat_min_vel;
WORD plat_walk_vel;
WORD plat_climb_vel;
WORD plat_run_vel;
WORD plat_walk_acc;
WORD plat_run_acc;
WORD plat_dec;
WORD plat_jump_vel;
WORD plat_grav;
WORD plat_hold_grav;
WORD plat_max_fall_vel;

void platform_init(void) BANKED {
    UBYTE tile_x, tile_y;

    pl_vel_x = 0;
    pl_vel_y = plat_grav << 2;

    if (PLAYER.def.dir == DIR_UP || PLAYER.def.dir == DIR_DOWN) {
        PLAYER.def.dir = DIR_RIGHT;
    }

    tile_x = SUBPX_TO_TILE(PLAYER.def.pos.x);
    tile_y = SUBPX_TO_TILE(PLAYER.def.pos.y);

    grounded = FALSE;

    // If starting tile was a ladder start scene attached to it
    if (IS_LADDER(tile_at(tile_x, tile_y - 1))) {
        // Snap to ladder
        UBYTE p_half_width = (PLAYER.def.bounds.right - PLAYER.def.bounds.left) >> 1;
        PLAYER.def.pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x) + 3 - (PLAYER.def.bounds.left + p_half_width));
        actor_set_anim(&PLAYER, ANIM_CLIMB);
        actor_stop_anim(&PLAYER);
        on_ladder = TRUE;
    } else {
        on_ladder = FALSE;
        actor_set_anim_idle(&PLAYER);
    }

    camera_offset_x = 0;
    camera_offset_y = 0;
    camera_deadzone_x = PLATFORM_CAMERA_DEADZONE_X;
    camera_deadzone_y = PLATFORM_CAMERA_DEADZONE_Y;

    game_time = 0;
}

void platform_update(void) BANKED {
    UBYTE tile_start, tile_end;
    actor_t *hit_actor;
    UBYTE p_half_width = (PLAYER.def.bounds.right - PLAYER.def.bounds.left) >> 1;
    UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.left + p_half_width); 
    UBYTE tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top + 1);

    // Input
    if (on_ladder) {
        // PLAYER.def.pos.x = 0;
        pl_vel_y = 0;
        if (INPUT_UP) {
            // Climb ladder
            if(IS_LADDER( tile_at(tile_x_mid, PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom)))) { // Grab with bottom edge
                pl_vel_y = -plat_climb_vel;
            }
            else {
                on_ladder = FALSE; // go back to standing when leaving the top of a ladder
            }
        } else if (INPUT_DOWN) {
            // Descend ladder
            tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom + 1);
            if (IS_LADDER(tile_at(tile_x_mid, tile_y))) {
                pl_vel_y = plat_climb_vel;
            }
        } else if (INPUT_LEFT) {
            on_ladder = FALSE;
            // Check if able to leave ladder on left
            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom) + 1;
            while (tile_start != tile_end) {
                if (tile_at(tile_x_mid - 1, tile_start) & COLLISION_RIGHT) {
                    on_ladder = TRUE;
                    break;
                }
                tile_start++;
            }            
        } else if (INPUT_RIGHT) {
            on_ladder = FALSE;
            // Check if able to leave ladder on right
            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom) + 1;
            while (tile_start != tile_end) {
                if (tile_at(tile_x_mid + 1, tile_start) & COLLISION_LEFT) {
                    on_ladder = TRUE;
                    break;
                }
                tile_start++;
            }
        }
        PLAYER.def.pos.y += VEL_TO_SUBPX(pl_vel_y);
    } else {
        // Horizontal Movement
        if (INPUT_LEFT) {
            if (INPUT_PLATFORM_RUN) {
                pl_vel_x -= plat_run_acc;
                pl_vel_x = CLAMP(pl_vel_x, -plat_run_vel, -plat_min_vel);
            } else {
                pl_vel_x -= plat_walk_acc;
                pl_vel_x = CLAMP(pl_vel_x, -plat_walk_vel, -plat_min_vel);
            } 
        } else if (INPUT_RIGHT) {
            if (INPUT_PLATFORM_RUN) {
                pl_vel_x += plat_run_acc;
                pl_vel_x = CLAMP(pl_vel_x, plat_min_vel, plat_run_vel);
            } else {
                pl_vel_x += plat_walk_acc;
                pl_vel_x = CLAMP(pl_vel_x, plat_min_vel, plat_walk_vel);
            }
        } else if (grounded) {
            if (pl_vel_x < 0) {
                pl_vel_x += plat_dec;
                if (pl_vel_x > 0) {
                    pl_vel_x = 0;
                }
            } else if (pl_vel_x > 0) {
                pl_vel_x -= plat_dec;
                if (pl_vel_x < 0) {
                    pl_vel_x = 0;
                }
            }
        }

        UBYTE col = 0;
        // Vertical Movement
        if (INPUT_UP) {
            // Grab upwards ladder
            tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom); // was top, use feet instead
            col = tile_at(tile_x_mid, tile_y);
            if (IS_LADDER(col)) {
                PLAYER.def.pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x_mid) + 3 - (PLAYER.def.bounds.left + p_half_width));
                on_ladder = TRUE;
                pl_vel_x = 0;
            }
        } else if (INPUT_DOWN) {
            // Grab downwards ladder
            tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom + 1);
            col = tile_at(tile_x_mid, tile_y);
            if (IS_LADDER(col)) {
                PLAYER.def.pos.x = PX_TO_SUBPX(TILE_TO_PX(tile_x_mid) + 3 - (PLAYER.def.bounds.left + p_half_width));
                on_ladder = TRUE;
                pl_vel_x = 0;
            }
        }

        // Gravity
        if (INPUT_PLATFORM_JUMP && pl_vel_y < 0) {
            pl_vel_y += plat_hold_grav;
        } else {
            pl_vel_y += plat_grav;
        }

        // Step X
        UBYTE prev_on_slope = on_slope;
        on_slope = FALSE;
        tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top);
        tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom) + 1;
        UWORD old_x = PLAYER.def.pos.x;
        WORD new_x = PLAYER.def.pos.x + VEL_TO_SUBPX(pl_vel_x);
        UBYTE tile_x = 0;
        UBYTE col_mid = 0;
        if (pl_vel_x > 0) {
            tile_x = PX_TO_TILE(SUBPX_TO_PX(new_x) + PLAYER.def.bounds.right);
            tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom);
            UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(new_x) + PLAYER.def.bounds.left + p_half_width + 1); 
            col_mid = tile_at(tile_x_mid, tile_y);
            if (IS_ON_SLOPE(col_mid)) {
                on_slope = col_mid;
                slope_y = tile_y;
            }

            UBYTE slope_on_y = FALSE;
            while (tile_start != tile_end) {
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
                    new_x = PX_TO_SUBPX(TILE_TO_PX(tile_x) - PLAYER.def.bounds.right) - 1;
                    pl_vel_x = 0;
                    break;
                }
                tile_start++;
            }
            PLAYER.def.pos.x = MIN(PX_TO_SUBPX(image_width - PLAYER.def.bounds.right - 1), new_x);
        } else if (pl_vel_x < 0) {
            tile_x = PX_TO_TILE(SUBPX_TO_PX(new_x) + PLAYER.def.bounds.left);
            tile_y   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom);
            UBYTE tile_x_mid = PX_TO_TILE(SUBPX_TO_PX(new_x) + PLAYER.def.bounds.left + p_half_width + 1); 
            col_mid = tile_at(tile_x_mid, tile_y);
            if (IS_ON_SLOPE(col_mid)) {
                on_slope = col_mid;
                slope_y = tile_y;
            }

            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.top);
            UBYTE slope_on_y = FALSE;
            while (tile_start != tile_end) {
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
                    new_x = PX_TO_SUBPX(TILE_TO_PX(tile_x + 1) - PLAYER.def.bounds.left) + 1;
                    pl_vel_x = 0;
                    break;
                }
                tile_start++;
            }
            PLAYER.def.pos.x = MAX(0, new_x);
        }

        // Step Y
        UBYTE prev_grounded = grounded;
        UWORD old_y = PLAYER.def.pos.y;
        grounded = FALSE;
        // 1 frame leniency of grounded state if we were on a slope last frame
        if (prev_on_slope) grounded = TRUE;
        tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.left);
        tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.right) + 1;
        if (pl_vel_y > 0) {
            UWORD new_y = PLAYER.def.pos.y + VEL_TO_SUBPX(pl_vel_y);
            tile_y = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom) - 1;
            UBYTE new_tile_y = PX_TO_TILE(SUBPX_TO_PX(new_y) + PLAYER.def.bounds.bottom);
            // If previously grounded and gravity is not enough to pull us down to the next tile, manually check it for the next slope
            // This prevents the "animation glitch" when going down slopes
            if (prev_grounded && new_tile_y == (tile_y + 1)) new_tile_y += 1;
            UWORD x_mid_coord = (SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.left + p_half_width + 1);
            while (tile_y <= new_tile_y) {
                UBYTE col = tile_at(PX_TO_TILE(x_mid_coord), tile_y);
                UWORD tile_x_coord = TILE_TO_PX(PX_TO_TILE(x_mid_coord));
                UWORD x_offset = x_mid_coord - tile_x_coord;
                UWORD slope_y_coord = 0;
                if (IS_ON_SLOPE(col)) {
                    if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_45_RIGHT) {
                        slope_y_coord = PX_TO_SUBPX(TILE_TO_PX(tile_y) + (8 - x_offset) - PLAYER.def.bounds.bottom) - 1;
                    } else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_RIGHT_BOT) {
                        slope_y_coord = PX_TO_SUBPX(TILE_TO_PX(tile_y) + (8 - (x_offset >> 1)) - PLAYER.def.bounds.bottom) - 1;
                    } else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_RIGHT_TOP) {
                        slope_y_coord = PX_TO_SUBPX(TILE_TO_PX(tile_y) + (4 - (x_offset >> 1)) - PLAYER.def.bounds.bottom) - 1;
                    }

                    else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_45_LEFT) {
                        slope_y_coord = PX_TO_SUBPX(TILE_TO_PX(tile_y) + (x_offset) - PLAYER.def.bounds.bottom) - 1;
                    } else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_LEFT_BOT) {
                        slope_y_coord = PX_TO_SUBPX(TILE_TO_PX(tile_y) + (x_offset >> 1) - PLAYER.def.bounds.bottom + 4) - 1;
                    } else if ((col & COLLISION_SLOPE) == COLLISION_SLOPE_225_LEFT_TOP) {
                        slope_y_coord = PX_TO_SUBPX(TILE_TO_PX(tile_y) + (x_offset >> 1) - PLAYER.def.bounds.bottom) - 1;
                    }
                }

                if (slope_y_coord) {
                    // If going downwards into a slope, don't snap to it unless we've actually collided
                    if (!prev_grounded && slope_y_coord > new_y) {
                        tile_y++;
                        continue;
                    }
                    // If we are moving up a slope, check for top collision
                    UBYTE slope_top_tile_y = PX_TO_TILE(SUBPX_TO_PX(slope_y_coord) + PLAYER.def.bounds.top);
                    while (tile_start != tile_end) {
                        if (tile_at(tile_start, slope_top_tile_y) & COLLISION_BOTTOM) {
                            pl_vel_y = 0;
                            pl_vel_x = 0;
                            PLAYER.def.pos.y = old_y;
                            PLAYER.def.pos.x = old_x;
                            grounded = TRUE;
                            on_slope = col;
                            slope_y = tile_y;
                            goto end_y_collision;
                        }
                        tile_start++;
                    }

                    PLAYER.def.pos.y = slope_y_coord;
                    pl_vel_y = 0;
                    grounded = TRUE;
                    on_slope = col;
                    slope_y = tile_y;
                    goto end_y_collision;
                }
                tile_y++;
            }

            tile_start = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.left);
            tile_end   = PX_TO_TILE(SUBPX_TO_PX(PLAYER.def.pos.x) + PLAYER.def.bounds.right) + 1;
            tile_y = PX_TO_TILE(SUBPX_TO_PX(new_y) + PLAYER.def.bounds.bottom);
            while (tile_start != tile_end) {
                // only snap to the top of a platform if feet are above the line
                if (tile_at(tile_start, tile_y) & COLLISION_TOP && (SUBPX_TO_PX(PLAYER.def.pos.y) + PLAYER.def.bounds.bottom - 2) < TILE_TO_PX(tile_y) ) {
                    new_y = PX_TO_SUBPX(TILE_TO_PX(tile_y) - PLAYER.def.bounds.bottom) - 1;
                    grounded = TRUE;
                    pl_vel_y = 0;
                    break;
                }
                tile_start++;
            }
            PLAYER.def.pos.y = new_y;
        } else if (pl_vel_y < 0) {
            UWORD new_y = PLAYER.def.pos.y + VEL_TO_SUBPX(pl_vel_y);
            tile_y = PX_TO_TILE(SUBPX_TO_PX(new_y) + PLAYER.def.bounds.top);
            while (tile_start != tile_end) {
                if (tile_at(tile_start, tile_y) & COLLISION_BOTTOM) {
                    new_y = PX_TO_SUBPX(TILE_TO_PX((UBYTE)(tile_y + 1)) - PLAYER.def.bounds.top) + 1;
                    pl_vel_y = 0;
                    break;
                }
                tile_start++;
            }
            PLAYER.def.pos.y = new_y;
        }
end_y_collision:

        // Clamp Y Velocity
        pl_vel_y = MIN(pl_vel_y, plat_max_fall_vel);
    }

    // Check for trigger collisions
    if (trigger_activate_at_intersection(&PLAYER.def.bounds, &PLAYER.def.pos, INPUT_UP_PRESSED)) {
        // Landed on a trigger
        return;
    }

    // Actor Collisions
    UBYTE can_jump = TRUE;
    hit_actor = actor_overlapping_player(FALSE);
    if (hit_actor != NULL && hit_actor->def.collision_group) {
        player_register_collision_with(hit_actor);
    } else if (INPUT_PRESSED(INPUT_PLATFORM_INTERACT)) {
        if (!hit_actor) {
            hit_actor = actor_in_front_of_player(8, TRUE);
        }
        if (hit_actor && !hit_actor->def.collision_group && hit_actor->def.script.bank) {
            script_execute(hit_actor->def.script.bank, hit_actor->def.script.ptr, 0, 1, 0);
            can_jump = FALSE;
        }
    }

    // Jump
    if (INPUT_PRESSED(INPUT_PLATFORM_JUMP) && grounded && can_jump) {
        pl_vel_y = -plat_jump_vel;
        grounded = FALSE;
    }

    // Player animation
    if (on_ladder) {
        actor_set_anim(&PLAYER, ANIM_CLIMB);
        if (pl_vel_y == 0) {
            actor_stop_anim(&PLAYER);
        }
    } else if (grounded) {
        if (pl_vel_x < 0) {
            actor_set_dir(&PLAYER, DIR_LEFT, TRUE);
        } else if (pl_vel_x > 0) {
            actor_set_dir(&PLAYER, DIR_RIGHT, TRUE);
        } else {
            actor_set_anim_idle(&PLAYER);
        }
    } else {
        if (PLAYER.def.dir == DIR_LEFT) {
            actor_set_anim(&PLAYER, ANIM_JUMP_LEFT);
        } else {
            actor_set_anim(&PLAYER, ANIM_JUMP_RIGHT);
        }
    }
}