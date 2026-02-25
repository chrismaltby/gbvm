#pragma bank 255

// Scene: Scene 1
// Sprites

#include "gbs_types.h"
#include "data/sprite_actor.h"

BANKREF(scene_1_sprites)

const far_ptr_t scene_1_sprites[] = {
    TO_FAR_PTR_T(sprite_actor)
};
