#pragma bank 255

// Scene: Scene
// Sprites

#include "gbs_types.h"
#include "data/sprite_actor_animated.h"

BANKREF(scene_2_sprites)

const far_ptr_t scene_2_sprites[] = {
    TO_FAR_PTR_T(sprite_actor_animated)
};
