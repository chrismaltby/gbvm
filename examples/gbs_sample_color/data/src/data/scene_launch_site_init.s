.module scene_launch_site_init

.include "vm.i"
.include "data/game_globals.i"

.globl _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4

___bank_scene_launch_site_init = 255
.globl ___bank_scene_launch_site_init

_scene_launch_site_init::
        VM_LOCK

        VM_RESERVE              4

        ; Actor Deactivate
        VM_SET_CONST            .LOCAL_ACTOR, 1
        VM_ACTOR_DEACTIVATE     .LOCAL_ACTOR

        ; Call Script: common/ui/Init Menu
        VM_CALL_FAR             ___bank_script_init_menu, _script_init_menu

        ; Music Play
        VM_MUSIC_PLAY           ___bank_song_rulz_outside_0_Data, _song_rulz_outside_0_Data, .MUSIC_NO_LOOP

        ; Wait 1 Frames
        VM_IDLE

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 1
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
