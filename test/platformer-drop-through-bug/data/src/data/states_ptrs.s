.include "macro.i"

.area _CODE

_state_start_fns::
    IMPORT_FAR_PTR _platform_init
    IMPORT_FAR_PTR _logo_init

_state_update_fns::
    IMPORT_FAR_PTR _platform_update
    IMPORT_FAR_PTR _logo_update