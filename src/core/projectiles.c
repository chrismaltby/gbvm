#pragma bank 255

#include "projectiles.h"

#include <gbdk/metasprites.h>

#include <string.h>

#include "scroll.h"
#include "actor.h"
#include "linked_list.h"
#include "game_time.h"
#include "vm.h"

projectile_t projectiles[MAX_PROJECTILES];
projectile_def_t projectile_defs[MAX_PROJECTILE_DEFS];
projectile_t *projectiles_active_head;
projectile_t *projectiles_inactive_head;

void projectiles_init(void) BANKED {
    projectiles_active_head = projectiles_inactive_head = NULL;
    for (projectile_t * proj = projectiles; proj < (projectiles + MAX_PROJECTILES); ++proj) {
        LL_PUSH_HEAD(projectiles_inactive_head, proj);
    }
}

static FASTUBYTE _save_bank;
static projectile_t *projectile;
static projectile_t *prev_projectile;
static projectile_t *next_projectile;

static void remove_projectile(void) NONBANKED {
    next_projectile = projectile->next;
    LL_REMOVE_ITEM(projectiles_active_head, projectile, prev_projectile);
    LL_PUSH_HEAD(projectiles_inactive_head, projectile);
    projectile = next_projectile;
}

static UBYTE min_x;
static UBYTE max_x;
static UBYTE min_y;
static UBYTE max_y;
#define CLIP_EXT 2U

void projectiles_update(void) NONBANKED {
    static uint8_t tmp_iterator;

    projectile = projectiles_active_head;
    prev_projectile = NULL;

    UBYTE draw_scroll_tx = PX_TO_TILE(draw_scroll_x);
    UBYTE draw_scroll_ty = PX_TO_TILE(draw_scroll_y);
    UBYTE clip_x_left = draw_scroll_tx - CLIP_EXT;
    min_x = (clip_x_left < draw_scroll_tx) ? clip_x_left : 0U;
    UBYTE clip_x_right = draw_scroll_tx + DEVICE_SCREEN_WIDTH + CLIP_EXT;
    max_x = (clip_x_right > draw_scroll_tx) ? clip_x_right : 255U;
    UBYTE clip_y_top = draw_scroll_ty - CLIP_EXT;
    min_y = (clip_y_top < draw_scroll_ty) ? clip_y_top : 0U;
    UBYTE clip_y_bottom = draw_scroll_ty + DEVICE_SCREEN_HEIGHT + CLIP_EXT;
    max_y = (clip_y_bottom > draw_scroll_ty) ? clip_y_bottom : 255U;

    tmp_iterator = game_time;
    while (projectile) {
        if (projectile->def.life_time == 0) {
            remove_projectile();
            continue;
        }
        projectile->def.life_time--;

        // Check reached animation tick frame
        if ((game_time & projectile->def.anim_tick) == 0) {
            projectile->frame++;
            // Check reached end of animation
            if (projectile->frame == projectile->frame_end) {
                if (!projectile->def.anim_noloop) {
                    projectile->frame = projectile->frame_start;
                } else {
                    projectile->frame--;
                }
            }
        }

        // Move projectile
        uint16_t pos;
        pos = projectile->pos.x + projectile->delta_pos.x;
        if ((SUBPX_TO_TILE(pos) < min_x) || (SUBPX_TO_TILE(pos) >= max_x))
        {
            remove_projectile();
            continue;
        }
        projectile->pos.x = pos;

        pos = projectile->pos.y + projectile->delta_pos.y;
        if ((SUBPX_TO_TILE(pos) < min_y) || (SUBPX_TO_TILE(pos) >= max_y))
        {
            remove_projectile();
            continue;
        }
        projectile->pos.y = pos;

        if ((tmp_iterator++ & 0x3) == 0) {
            actor_t *hit_actor = NULL;
            if (projectile->def.collision_mask == COLLISION_GROUP_PLAYER) {
                if  (bb_intersects(&projectile->def.bounds, &projectile->pos, &PLAYER.bounds, &PLAYER.pos)) {
                    hit_actor = &PLAYER;
                }
            } else {
                hit_actor = actor_overlapping_bb(&projectile->def.bounds, &projectile->pos, NULL);
            }
            if (hit_actor && (hit_actor->collision_group & projectile->def.collision_mask)) {
                // Hit! - Fire collision script here
                if ((hit_actor->script.bank) && (hit_actor->hscript_hit & SCRIPT_TERMINATED)) {
                    script_execute(hit_actor->script.bank, hit_actor->script.ptr, &(hit_actor->hscript_hit), 1, (UWORD)(projectile->def.collision_group));
                }
                if (!projectile->def.strong) {
                    remove_projectile();
                    continue;
                }
            }
        }

        prev_projectile = projectile;
        projectile = projectile->next;
    }
}

void projectiles_render(void) NONBANKED {
    projectile_t* projectile = projectiles_active_head;

    _save_bank = _current_bank;

    while (projectile) {
        UINT8 screen_x = SUBPX_TO_PX(projectile->pos.x) - draw_scroll_x;
        UINT8 screen_y = SUBPX_TO_PX(projectile->pos.y) - draw_scroll_y;

        SWITCH_ROM(projectile->def.sprite.bank);
        spritesheet_t *sprite = projectile->def.sprite.ptr;

        allocated_hardware_sprites += move_metasprite(
            *(sprite->metasprites + projectile->frame),
            projectile->def.base_tile,
            allocated_hardware_sprites,
            screen_x,
            screen_y
        );

        projectile = projectile->next;
    }

    SWITCH_ROM(_save_bank);
}

void projectile_launch(UBYTE index, upoint16_t *pos, UBYTE angle) BANKED {
    projectile_t *projectile = projectiles_inactive_head;
    if (projectile) {
        memcpy(&projectile->def, &projectile_defs[index], sizeof(projectile_def_t));

        // Set correct projectile frames based on angle
        UBYTE dir = DIR_UP;
        if (angle <= 224) {
            if (angle >= 160) {
                dir = DIR_LEFT;
            } else if (angle > 96) {
                dir = DIR_DOWN;
            } else if (angle >= 32) {
                dir = DIR_RIGHT;
            }
        }

        // set animation
        projectile->frame = projectile->frame_start = projectile->def.animations[dir].start;
        projectile->frame_end = projectile->def.animations[dir].end + 1;

        // set coordinates
        UINT16 initial_offset = projectile->def.initial_offset;
        UINT8 move_speed = projectile->def.move_speed;

        projectile->pos.x = pos->x;
        projectile->pos.y = pos->y;

        if (angle == ANGLE_LEFT) {
            projectile->pos.x -= initial_offset;
            projectile->delta_pos.x = -move_speed;
            projectile->delta_pos.y = 0;
        } else if (angle == ANGLE_RIGHT) {
            projectile->pos.x += initial_offset;
            projectile->delta_pos.x = move_speed;
            projectile->delta_pos.y = 0;
        } else if (angle == ANGLE_UP) {
            projectile->pos.y -= initial_offset;
            projectile->delta_pos.x = 0;
            projectile->delta_pos.y = -move_speed;
        } else if (angle == ANGLE_DOWN) {
            projectile->pos.y += initial_offset;
            projectile->delta_pos.x = 0;
            projectile->delta_pos.y = move_speed;            
        } else {
            INT8 sinv = SIN(angle), cosv = COS(angle);

            // Offset by initial amount
            while (initial_offset > 0xFFu) {
                projectile->pos.x += ((sinv * (UINT8)(0xFF)) >> 7);
                projectile->pos.y -= ((cosv * (UINT8)(0xFF)) >> 7);
                initial_offset -= 0xFFu;
            }
            if (initial_offset > 0) {
                projectile->pos.x += ((sinv * (UINT8)(initial_offset)) >> 7);
                projectile->pos.y -= ((cosv * (UINT8)(initial_offset)) >> 7);
            }

            point_translate_angle_to_delta(&projectile->delta_pos, angle, move_speed);
        }

        LL_REMOVE_HEAD(projectiles_inactive_head);
        LL_PUSH_HEAD(projectiles_active_head, projectile);
    }
}
