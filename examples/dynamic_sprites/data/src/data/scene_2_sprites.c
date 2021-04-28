#pragma bank 255

// Scene: Dynamic Player Sprite
// Sprites

#include "gbs_types.h"
#include "data/spritesheet_4.h"
#include "data/spritesheet_5.h"
#include "data/spritesheet_1.h"
#include "data/spritesheet_2.h"
#include "data/spritesheet_0.h"
#include "data/spritesheet_6.h"
#include "data/spritesheet_3.h"

const void __at(255) __bank_scene_2_sprites;

const far_ptr_t scene_2_sprites[] = {
    TO_FAR_PTR_T(spritesheet_4),
    TO_FAR_PTR_T(spritesheet_5),
    TO_FAR_PTR_T(spritesheet_1),
    TO_FAR_PTR_T(spritesheet_2),
    TO_FAR_PTR_T(spritesheet_0),
    TO_FAR_PTR_T(spritesheet_6),
    TO_FAR_PTR_T(spritesheet_3)
};
