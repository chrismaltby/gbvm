#pragma bank 255

// Scene: Scene 1
// Sprites

#include "gbs_types.h"
#include "data/sprite_static.h"
#include "data/sprite_actor_animated.h"

BANKREF(scene_1_sprites)

const far_ptr_t scene_1_sprites[] = {
    TO_FAR_PTR_T(sprite_static),
    TO_FAR_PTR_T(sprite_actor_animated)
};
