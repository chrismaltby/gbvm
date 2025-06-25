#pragma bank 255

#include "camera.h"

#include "actor.h"

#define CAMERA_FIXED_OFFSET_X PX_TO_SUBPX(8)
#define CAMERA_FIXED_OFFSET_Y PX_TO_SUBPX(8)

UINT16 camera_x;
UINT16 camera_y;
UINT16 camera_clamp_x;
UINT16 camera_clamp_y;
BYTE camera_offset_x;
BYTE camera_offset_y;
BYTE camera_deadzone_x;
BYTE camera_deadzone_y;
UBYTE camera_settings;

void camera_init(void) BANKED {
    camera_settings = CAMERA_LOCK_FLAG;
    camera_x = camera_y = 0;
    camera_offset_x = camera_offset_y = 0;
    camera_clamp_x = camera_clamp_y = 0;
    camera_reset();
}

void camera_update(void) BANKED {
    if (camera_settings & CAMERA_LOCK_X_FLAG)
    {
        UWORD target_pos = PLAYER.pos.x + CAMERA_FIXED_OFFSET_X - PX_TO_SUBPX(camera_offset_x);
        WORD tolerance = PX_TO_SUBPX(camera_deadzone_x);
        UWORD target_min_pos = (tolerance > target_pos) ? 0 : target_pos - tolerance;
        UWORD target_max_pos = target_pos + tolerance;
        UWORD new_cam_pos = camera_x;

        if (new_cam_pos < target_min_pos)
        {
            new_cam_pos = target_min_pos;
            if ((camera_settings & CAMERA_LOCK_X_MAX_FLAG) && new_cam_pos > camera_clamp_x)
            {
                new_cam_pos = camera_clamp_x;
            }
        }
        else if (new_cam_pos > target_max_pos)
        {
            new_cam_pos = target_max_pos;
            if ((camera_settings & CAMERA_LOCK_X_MIN_FLAG) && new_cam_pos < camera_clamp_x)
            {
                new_cam_pos = camera_clamp_x;
            }
        }
        camera_x = camera_clamp_x = new_cam_pos;
    }

    if (camera_settings & CAMERA_LOCK_Y_FLAG)
    {
        UWORD target_pos = PLAYER.pos.y + CAMERA_FIXED_OFFSET_Y - PX_TO_SUBPX(camera_offset_y);
        WORD tolerance = PX_TO_SUBPX(camera_deadzone_y);
        UWORD target_min_pos = (tolerance > target_pos) ? 0 : target_pos - tolerance;
        UWORD target_max_pos = target_pos + tolerance;
        UWORD new_cam_pos = camera_y;

        if (new_cam_pos < target_min_pos)
        {
            new_cam_pos = target_min_pos;
            if ((camera_settings & CAMERA_LOCK_Y_MAX_FLAG) && new_cam_pos > camera_clamp_y)
            {
                new_cam_pos = camera_clamp_y;
            }
        }
        else if (new_cam_pos > target_max_pos)
        {
            new_cam_pos = target_max_pos;
            if ((camera_settings & CAMERA_LOCK_Y_MIN_FLAG) && new_cam_pos < camera_clamp_y)
            {
                new_cam_pos = camera_clamp_y;
            }
        }
        camera_y = camera_clamp_y = new_cam_pos;
    }
}
