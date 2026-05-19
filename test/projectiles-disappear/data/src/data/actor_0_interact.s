.module actor_0_interact

.include "vm.i"
.include "data/game_globals.i"

.globl b_camera_shake_frames, _camera_shake_frames

.area _CODE_255

.LOCAL_TMP0_PARAM0_VALUE = -3
.LOCAL_TMP1_CAMERA_SHAKE_ARGS = -3

___bank_actor_0_interact = 255
.globl ___bank_actor_0_interact

_actor_0_interact::
        VM_RESERVE              3

        ; If Parameter 0 Equals 8
        VM_GET_TLOCAL           .LOCAL_TMP0_PARAM0_VALUE, 0
        VM_IF_CONST             .EQ, .LOCAL_TMP0_PARAM0_VALUE, 8, 1$, 0
        VM_JUMP                 2$
1$:
GBVM$actor_0_interact$961a0da3_f054_44ba_97b5_82d7816caffb$8e4f1f9d_d4ea_4e79_89c6_25a388370165$actor$8f986e32_72e4_44b7_8f80_bc63be5905d2$script = .
.globl GBVM$actor_0_interact$961a0da3_f054_44ba_97b5_82d7816caffb$8e4f1f9d_d4ea_4e79_89c6_25a388370165$actor$8f986e32_72e4_44b7_8f80_bc63be5905d2$script
        ; Camera Shake
        VM_SET_CONST            .LOCAL_TMP1_CAMERA_SHAKE_ARGS, 30
        VM_SET_CONST            ^/(.LOCAL_TMP1_CAMERA_SHAKE_ARGS + 1)/, .CAMERA_SHAKE_X
        VM_RPN
            .R_INT16    5
            .R_REF_SET  ^/(.LOCAL_TMP1_CAMERA_SHAKE_ARGS + 2)/
            .R_STOP
        VM_INVOKE               b_camera_shake_frames, _camera_shake_frames, 0, .LOCAL_TMP1_CAMERA_SHAKE_ARGS

        ; Stop Script
        VM_STOP
2$:

        ; Stop Script
        VM_STOP
