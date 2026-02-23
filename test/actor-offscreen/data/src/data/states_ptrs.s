.include "macro.i"

.area _CODE

_state_start_fns::
    IMPORT_FAR_PTR _topdown_init
    IMPORT_FAR_PTR _logo_init

_state_update_fns::
    IMPORT_FAR_PTR _topdown_update
    IMPORT_FAR_PTR _logo_update