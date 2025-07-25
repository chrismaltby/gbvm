#pragma bank 255

// Scene: Dancefloor
// Triggers

#include "gbs_types.h"
#include "data/trigger_25_interact.h"
#include "data/trigger_26_interact.h"

BANKREF(scene_dancefloor_triggers)

const struct trigger_t scene_dancefloor_triggers[] = {
    {
        // Trigger 1,
        .left = 0,
        .top = 0,
        .right = 0,
        .bottom = 13,
        .script = TO_FAR_PTR_T(trigger_25_interact),
        .script_flags = TRIGGER_HAS_ENTER_SCRIPT
    },
    {
        // Trigger 2,
        .left = 19,
        .top = 0,
        .right = 19,
        .bottom = 13,
        .script = TO_FAR_PTR_T(trigger_26_interact),
        .script_flags = TRIGGER_HAS_ENTER_SCRIPT
    }
};
