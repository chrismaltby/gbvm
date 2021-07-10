#pragma bank 255

// Scene: Scene 1
// Triggers

#include "gbs_types.h"
#include "data/script_s0t0_interact.h"
#include "data/script_s0t1_interact.h"
#include "data/script_s0t2_interact.h"
#include "data/script_s0t3_leave.h"
#include "data/script_s0t4_leave.h"
#include "data/script_s0t5_leave.h"
#include "data/script_s0t6_interact.h"
#include "data/script_s0t7_interact.h"
#include "data/script_s0t8_interact.h"
#include "data/script_s0t9_interact.h"
#include "data/script_s0t9_leave.h"
#include "data/script_s0t10_interact.h"
#include "data/script_s0t10_leave.h"
#include "data/script_s0t11_interact.h"
#include "data/script_s0t11_leave.h"
#include "data/script_s0t12_interact.h"
#include "data/script_s0t12_leave.h"
#include "data/script_s0t13_interact.h"
#include "data/script_s0t13_leave.h"
#include "data/script_s0t14_interact.h"
#include "data/script_s0t14_leave.h"
#include "data/script_s0t15_interact.h"
#include "data/script_s0t15_leave.h"
#include "data/script_s0t16_interact.h"
#include "data/script_s0t16_leave.h"
#include "data/script_s0t17_leave.h"
#include "data/script_s0t18_leave.h"
#include "data/script_s0t19_leave.h"
#include "data/script_s0t20_leave.h"
#include "data/script_s0t21_leave.h"
#include "data/script_s0t22_leave.h"
#include "data/script_s0t23_interact.h"

const void __at(255) __bank_scene_0_triggers;

const struct trigger_t scene_0_triggers[] = {
    {
        // Trigger 1,
        .x = 3,
        .y = 2,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t0_interact)
    },
    {
        // Trigger 2,
        .x = 9,
        .y = 2,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t1_interact)
    },
    {
        // Trigger 3,
        .x = 15,
        .y = 2,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t2_interact)
    },
    {
        // Trigger 4,
        .x = 3,
        .y = 5,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t3_leave)
    },
    {
        // Trigger 5,
        .x = 9,
        .y = 5,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t4_leave)
    },
    {
        // Trigger 6,
        .x = 15,
        .y = 5,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t5_leave)
    },
    {
        // Trigger 7,
        .x = 10,
        .y = 2,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t6_interact)
    },
    {
        // Trigger 8,
        .x = 10,
        .y = 5,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t7_interact)
    },
    {
        // Trigger 9,
        .x = 10,
        .y = 8,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t8_interact)
    },
    {
        // Trigger 10,
        .x = 3,
        .y = 8,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t9_interact),
        .script_leave = TO_FAR_PTR_T(script_s0t9_leave)
    },
    {
        // Trigger 11,
        .x = 3,
        .y = 11,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t10_interact),
        .script_leave = TO_FAR_PTR_T(script_s0t10_leave)
    },
    {
        // Trigger 12,
        .x = 9,
        .y = 8,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t11_interact),
        .script_leave = TO_FAR_PTR_T(script_s0t11_leave)
    },
    {
        // Trigger 13,
        .x = 15,
        .y = 8,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t12_interact),
        .script_leave = TO_FAR_PTR_T(script_s0t12_leave)
    },
    {
        // Trigger 14,
        .x = 4,
        .y = 11,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t13_interact),
        .script_leave = TO_FAR_PTR_T(script_s0t13_leave)
    },
    {
        // Trigger 15,
        .x = 10,
        .y = 11,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t14_interact),
        .script_leave = TO_FAR_PTR_T(script_s0t14_leave)
    },
    {
        // Trigger 16,
        .x = 16,
        .y = 11,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t15_interact),
        .script_leave = TO_FAR_PTR_T(script_s0t15_leave)
    },
    {
        // Trigger 17,
        .x = 16,
        .y = 14,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t16_interact),
        .script_leave = TO_FAR_PTR_T(script_s0t16_leave)
    },
    {
        // Trigger 18,
        .x = 9,
        .y = 11,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t17_leave)
    },
    {
        // Trigger 19,
        .x = 15,
        .y = 11,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t18_leave)
    },
    {
        // Trigger 20,
        .x = 16,
        .y = 2,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t19_leave)
    },
    {
        // Trigger 21,
        .x = 16,
        .y = 5,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t20_leave)
    },
    {
        // Trigger 22,
        .x = 16,
        .y = 8,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t21_leave)
    },
    {
        // Trigger 23,
        .x = 10,
        .y = 14,
        .width = 1,
        .height = 2,
        .script_leave = TO_FAR_PTR_T(script_s0t22_leave)
    },
    {
        // Trigger 24,
        .x = 4,
        .y = 14,
        .width = 1,
        .height = 2,
        .script = TO_FAR_PTR_T(script_s0t23_interact)
    }
};
