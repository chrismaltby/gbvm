#ifndef GBS_TYPES_H
#define GBS_TYPES_H

#include "BankData.h"

typedef enum {
    SCENE_TYPE_TOPDOWN = 0,
    SCENE_TYPE_PLATFORM,
    SCENE_TYPE_ADVENTURE,
    SCENE_TYPE_SHMUP,
    SCENE_TYPE_POINTNCLICK
} scene_type_e;

typedef struct actor_t
{
  UINT8 enabled; 
  UINT16 x;
  UINT16 y;
  BYTE dir_x;
  BYTE dir_y;
  UINT8 sprite_no;
  UINT8 pinned;
  UINT8 animate;
  UINT8 frame;
  UINT8 frame_start;
  UINT8 frame_end;
  UINT8 anim_tick;
  UINT8 flip_x;
  UINT8 rerender;
  UINT8 move_speed;

  UINT8 sprite, sprite_type, palette;
  UINT8 n_frames, initial_frame;
  UINT8 direction;
  UINT8 anim_speed;
  far_ptr_t script, script_update, script_hit1, script_hit2, script_hit3;

  // Collisions
  UBYTE collision_group;
  UBYTE collision_enabled;

  // Linked list
  struct actor_t *next;
  struct actor_t *prev;
} actor_t;

typedef struct trigger_t {
    UINT8 x, y, width, height;
    far_ptr_t script;
} trigger_t;

typedef struct scene_t {
    UINT8 width, height;
    scene_type_e type;
    UINT8 n_actors, n_triggers, n_sprites;
    far_ptr_t background, collisions, colors, palette, sprite_palette;
    far_ptr_t script_init, script_p_hit1, script_p_hit2, script_p_hit3;
    far_ptr_t sprites;
    far_ptr_t actors;
    far_ptr_t triggers;
} scene_t;

typedef struct background_t {
    UINT8 width, height;
    far_ptr_t tileset;
    UINT8 tiles[];
} background_t;

typedef struct tileset_t {
    UINT8 n_tiles;
    UINT8 tiles[];
} tileset_t;

typedef struct spritesheet_t {
    UINT8 n_frames;
    UINT8 frames[];
} spritesheet_t;

#endif